#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core.hpp>     
#include <opencv2/videoio.hpp>  

using namespace std;
using namespace cv;

void calibrateAndProcess(VideoCapture& videoCapture, const Size& frameSize, const vector<Point3f>& targetCorners3D,
                         vector<vector<Point2f>>& calibrationCorners, vector<vector<Point3f>>& objectPoints,
                         vector<vector<Point2f>>& allFrameCorners) {
  Mat currentFrame, previousFrame, grayCurrentFrame, grayPreviousFrame;
  vector<Point2f> previousVertices;
  int frameCounter = 0;

  while (true) {
    videoCapture >> currentFrame;
    if (currentFrame.empty()) break;

    rotate(currentFrame, currentFrame, 1);
    vector<Point2f> detectedCorners;

    bool cornersFound = findChessboardCorners(currentFrame, Size(7, 7), detectedCorners);
    if (!cornersFound) {
      vector<uchar> opticalFlowStatus;
      vector<float> opticalFlowError;

      cvtColor(previousFrame, grayPreviousFrame, COLOR_BGR2GRAY);
      cvtColor(currentFrame, grayCurrentFrame, COLOR_BGR2GRAY);

      calcOpticalFlowPyrLK(grayPreviousFrame, grayCurrentFrame, previousVertices, detectedCorners, opticalFlowStatus, opticalFlowError); 
    }

    previousVertices = detectedCorners;
    currentFrame.copyTo(previousFrame);

    vector<Point2f> selectedCorners = {detectedCorners[16], detectedCorners[18], detectedCorners[32], detectedCorners[30]};

    if (frameCounter % 5 == 0) {
      calibrationCorners.push_back(selectedCorners);
      objectPoints.push_back(targetCorners3D);
    }

    allFrameCorners.push_back(selectedCorners);
    frameCounter++;
  }
}

void processVideo(VideoCapture& videoCapture, VideoWriter& videoWriter, const Size& frameSize, 
                  const vector<Point3f>& targetCorners3D, const vector<vector<Point2f>>& allFrameCorners,
                  const Mat& cameraMatrix, const Mat& distortionCoefficients) {
  Mat currentFrame;
  vector<Point3f> projectedCorners3D = {{-1, 1, 0}, {1, 1, 0}, {1, -1, 0}, {-1, -1, 0}, 
                                          {-1, 1, 2}, {1, 1, 2}, {1, -1, 2}, {-1, -1, 2}};
  videoCapture.open("withChessBoard.MOV");
  int frameCounter = 0;

  while (true) {
    videoCapture >> currentFrame;
    if (currentFrame.empty()) break;

    rotate(currentFrame, currentFrame, 1);

    Mat rotationVectors, translationVectors;
    solvePnP(targetCorners3D, allFrameCorners[frameCounter], cameraMatrix, distortionCoefficients, rotationVectors, translationVectors);

    vector<Point2f> projectedPoints2D;
    projectPoints(projectedCorners3D, rotationVectors, translationVectors, cameraMatrix, distortionCoefficients, projectedPoints2D);

    vector<Point> bottomPoints = {projectedPoints2D[0], projectedPoints2D[1], projectedPoints2D[2], projectedPoints2D[3]};
    vector<Point> topPoints = {projectedPoints2D[4], projectedPoints2D[5], projectedPoints2D[6], projectedPoints2D[7]};

    for (int i = 0; i < 4; i++) {
      line(currentFrame, bottomPoints[i], bottomPoints[(i+1)%4], Scalar(255, 0, 0), 3);
      line(currentFrame, topPoints[i], topPoints[(i+1)%4], Scalar(255, 0, 0), 3);
      line(currentFrame, bottomPoints[i], topPoints[i], Scalar(255, 0, 0), 3);
    }

    videoWriter << currentFrame; 
    frameCounter++;
  }
}

void part1() {
  VideoCapture videoCapture("withChessBoard.MOV"); 
  Size frameSize(static_cast<int>(videoCapture.get(CAP_PROP_FRAME_WIDTH)), static_cast<int>(videoCapture.get(CAP_PROP_FRAME_HEIGHT)));
  VideoWriter videoWriter("vr.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), static_cast<int>(videoCapture.get(CAP_PROP_FPS)), frameSize);

  vector<Point3f> targetCorners3D = {{-1, 1, 0}, {1, 1, 0}, {1, -1, 0}, {-1, -1, 0}};

  vector<vector<Point2f>> calibrationCorners, allFrameCorners;
  vector<vector<Point3f>> objectPoints;

  calibrateAndProcess(videoCapture, frameSize, targetCorners3D, calibrationCorners, objectPoints, allFrameCorners);

  Mat cameraMatrix, distortionCoefficients, rotationVectors, translationVectors;
  Mat intrinsicsStdDeviations, extrinsicsStdDeviations, perViewErrors;

  calibrateCamera(objectPoints, calibrationCorners, frameSize, cameraMatrix, distortionCoefficients, rotationVectors, translationVectors, intrinsicsStdDeviations, extrinsicsStdDeviations, perViewErrors);

  processVideo(videoCapture, videoWriter, frameSize, targetCorners3D, allFrameCorners, cameraMatrix, distortionCoefficients);
}

int main() {
  part1();
}