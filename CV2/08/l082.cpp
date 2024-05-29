#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <cmath>

using namespace std;
using namespace cv;

Mat performTranslation(Mat inputMat, double offsetX, double offsetY, double offsetZ) {
    std::vector<std::vector<double>> transMatrix = {{1, 0, 0, offsetX},
                                                    {0, 1, 0, offsetY},
                                                    {0, 0, 1, offsetZ},
                                                    {0, 0, 0, 1}};

    Mat transformMatrix = (Mat_<double>(4, 4) << transMatrix[0][0], transMatrix[0][1], transMatrix[0][2], transMatrix[0][3],
                           transMatrix[1][0], transMatrix[1][1], transMatrix[1][2], transMatrix[1][3],
                           transMatrix[2][0], transMatrix[2][1], transMatrix[2][2], transMatrix[2][3],
                           transMatrix[3][0], transMatrix[3][1], transMatrix[3][2], transMatrix[3][3]);

    return transformMatrix * inputMat;
}

Mat performScaling(Mat inputMat, double scaleX, double scaleY, double scaleZ) {
    std::vector<std::vector<double>> scaleMatrix = {{scaleX, 0, 0, 0},
                                                    {0, scaleY, 0, 0},
                                                    {0, 0, scaleZ, 0},
                                                    {0, 0, 0, 1}};

    Mat transformMatrix = (Mat_<double>(4, 4) << scaleMatrix[0][0], scaleMatrix[0][1], scaleMatrix[0][2], scaleMatrix[0][3],
                           scaleMatrix[1][0], scaleMatrix[1][1], scaleMatrix[1][2], scaleMatrix[1][3],
                           scaleMatrix[2][0], scaleMatrix[2][1], scaleMatrix[2][2], scaleMatrix[2][3],
                           scaleMatrix[3][0], scaleMatrix[3][1], scaleMatrix[3][2], scaleMatrix[3][3]);

    return transformMatrix * inputMat;
}

Mat rotateAroundX(Mat inputMat, double angle) {
    std::vector<std::vector<double>> rotXMatrix = {{1, 0, 0, 0},
                                                   {0, cos(angle), -sin(angle), 0},
                                                   {0, sin(angle), cos(angle), 0},
                                                   {0, 0, 0, 1}};

    Mat transformMatrix = (Mat_<double>(4, 4) << rotXMatrix[0][0], rotXMatrix[0][1], rotXMatrix[0][2], rotXMatrix[0][3],
                           rotXMatrix[1][0], rotXMatrix[1][1], rotXMatrix[1][2], rotXMatrix[1][3],
                           rotXMatrix[2][0], rotXMatrix[2][1], rotXMatrix[2][2], rotXMatrix[2][3],
                           rotXMatrix[3][0], rotXMatrix[3][1], rotXMatrix[3][2], rotXMatrix[3][3]);

    return transformMatrix * inputMat;
}

Mat rotateAroundY(Mat inputMat, double angle) {
    std::vector<std::vector<double>> rotYMatrix = {{cos(angle), 0, sin(angle), 0},
                                                   {0, 1, 0, 0},
                                                   {-sin(angle), 0, cos(angle), 0},
                                                   {0, 0, 0, 1}};

    Mat transformMatrix = (Mat_<double>(4, 4) << rotYMatrix[0][0], rotYMatrix[0][1], rotYMatrix[0][2], rotYMatrix[0][3],
                           rotYMatrix[1][0], rotYMatrix[1][1], rotYMatrix[1][2], rotYMatrix[1][3],
                           rotYMatrix[2][0], rotYMatrix[2][1], rotYMatrix[2][2], rotYMatrix[2][3],
                           rotYMatrix[3][0], rotYMatrix[3][1], rotYMatrix[3][2], rotYMatrix[3][3]);

    return transformMatrix * inputMat;
}

Mat rotateAroundZ(Mat inputMat, double angle) {
    std::vector<std::vector<double>> rotZMatrix = {{cos(angle), -sin(angle), 0, 0},
                                                   {sin(angle), cos(angle), 0, 0},
                                                   {0, 0, 1, 0},
                                                   {0, 0, 0, 1}};

    Mat transformMatrix = (Mat_<double>(4, 4) << rotZMatrix[0][0], rotZMatrix[0][1], rotZMatrix[0][2], rotZMatrix[0][3],
                           rotZMatrix[1][0], rotZMatrix[1][1], rotZMatrix[1][2], rotZMatrix[1][3],
                           rotZMatrix[2][0], rotZMatrix[2][1], rotZMatrix[2][2], rotZMatrix[2][3],
                           rotZMatrix[3][0], rotZMatrix[3][1], rotZMatrix[3][2], rotZMatrix[3][3]);

    return transformMatrix * inputMat;
}

void part1() {
    int imageHeight = 600;
    int imageWidth = 800;
    double pi = 3.141592653589793;

    std::vector<std::vector<double>> cubeVertices = {{1, 1, 1, 1},
                                                     {1, 1, -1, 1},
                                                     {1, -1, 1, 1},
                                                     {-1, 1, 1, 1},
                                                     {-1, -1, 1, 1},
                                                     {-1, 1, -1, 1},
                                                     {1, -1, -1, 1},
                                                     {-1, -1, -1, 1}};

    vector<Mat> cubePoints;
    int frameRate = 60;

    VideoWriter videoWriter;
    videoWriter.open("rotation.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), frameRate, Size(imageWidth, imageHeight));

    for (int index = 0; index < cubeVertices.size(); index++) {
        Mat point = (Mat_<double>(4, 1) << cubeVertices[index][0], cubeVertices[index][1], cubeVertices[index][2], cubeVertices[index][3]);
        cubePoints.push_back(performScaling(point, 50, 50, 50));
    }

    int totalFrames = 300;
    double angleStep = 2 * pi / static_cast<double>(totalFrames);

    ofstream coordOutput("coordinates.txt");

    for (int frameIndex = 0; frameIndex <= totalFrames; frameIndex++) {
        Mat currentImage(imageHeight, imageWidth, CV_8UC3, Scalar(255, 255, 255));

        vector<Mat> tempCubePoints;
        vector<Point> pointConversion;

        for (int i = 0; i < cubePoints.size(); i++) {
            Mat transformation = performTranslation(rotateAroundZ(rotateAroundY(rotateAroundX(cubePoints[i], angleStep * frameIndex), angleStep * frameIndex), angleStep * frameIndex), 400, 300, 0);
            tempCubePoints.push_back(transformation);
            std::vector<double> output(transformation.begin<double>(), transformation.end<double>());
            circle(currentImage, Point(output[0], output[1]), 3, Scalar(0, 0, 0), 3);

            if (frameIndex < 4) {
                if (i != cubePoints.size() - 1) {
                    coordOutput << "(" << output[0] << "," << output[1] << "," << output[2] << "), ";
                } else {
                    coordOutput << "(" << output[0] << "," << output[1] << "," << output[2] << ")" << endl;
                }
            }

            if (frameIndex == 4) {
                coordOutput.close();
            }
        }

        for (int i = 0; i < tempCubePoints.size(); i++) {
            std::vector<double> output(tempCubePoints[i].begin<double>(), tempCubePoints[i].end<double>());
            pointConversion.push_back(Point(output[0], output[1]));
        }

        line(currentImage, pointConversion[0], pointConversion[1], Scalar(0, 0, 0));
        line(currentImage, pointConversion[0], pointConversion[2], Scalar(0, 0, 0));
        line(currentImage, pointConversion[0], pointConversion[3], Scalar(0, 0, 0));

        line(currentImage, pointConversion[7], pointConversion[6], Scalar(0, 0, 0));
        line(currentImage, pointConversion[7], pointConversion[5], Scalar(0, 0, 0));
        line(currentImage, pointConversion[7], pointConversion[4], Scalar(0, 0, 0));

        line(currentImage, pointConversion[4], pointConversion[3], Scalar(0, 0, 0));
        line(currentImage, pointConversion[4], pointConversion[2], Scalar(0, 0, 0));

        line(currentImage, pointConversion[5], pointConversion[3], Scalar(0, 0, 0));
        line(currentImage, pointConversion[5], pointConversion[1], Scalar(0, 0, 0));

        line(currentImage, pointConversion[6], pointConversion[2], Scalar(0, 0, 0));
        line(currentImage, pointConversion[6], pointConversion[1], Scalar(0, 0, 0));

        videoWriter << currentImage;
    }

    std::vector<std::vector<double>> tetrahedronVertices = {{1.0 / sqrt(3), 0, 0, 1},
                                                           {0, 0, 2 / sqrt(6), 1},
                                                           {-sqrt(3) / 6.0, 0.5, 0, 1},
                                                           {-sqrt(3) / 6.0, -0.5, 0, 1}};

    vector<Mat> tetrahedronPoints;

    for (int index = 0; index < tetrahedronVertices.size(); index++) {
        Mat point = (Mat_<double>(4, 1) << tetrahedronVertices[index][0], tetrahedronVertices[index][1], tetrahedronVertices[index][2], tetrahedronVertices[index][3]);
        tetrahedronPoints.push_back(performScaling(point, 200, 200, 200));
    }

    for (int frameIndex = 0; frameIndex <= totalFrames; frameIndex++) {
        Mat currentImage(imageHeight, imageWidth, CV_8UC3, Scalar(255, 255, 255));

        vector<Mat> tempTetrahedronPoints;
        vector<Point> pointConversion;

        for (int i = 0; i < tetrahedronPoints.size(); i++) {
            Mat transformation = performTranslation(rotateAroundZ(rotateAroundY(rotateAroundX(tetrahedronPoints[i], angleStep * frameIndex), angleStep * frameIndex), angleStep * frameIndex), 400, 300, 0);
            tempTetrahedronPoints.push_back(transformation);
            std::vector<double> output(transformation.begin<double>(), transformation.end<double>());
            circle(currentImage, Point(output[0], output[1]), 3, Scalar(0, 0, 0), 3);
        }

        for (int i = 0; i < tempTetrahedronPoints.size(); i++) {
            std::vector<double> output(tempTetrahedronPoints[i].begin<double>(), tempTetrahedronPoints[i].end<double>());
            pointConversion.push_back(Point(output[0], output[1]));
        }

        line(currentImage, pointConversion[1], pointConversion[0], Scalar(0, 0, 0));
        line(currentImage, pointConversion[1], pointConversion[2], Scalar(0, 0, 0));
        line(currentImage, pointConversion[1], pointConversion[3], Scalar(0, 0, 0));

        line(currentImage, pointConversion[2], pointConversion[0], Scalar(0, 0, 0));
        line(currentImage, pointConversion[2], pointConversion[3], Scalar(0, 0, 0));

        line(currentImage, pointConversion[0], pointConversion[3], Scalar(0, 0, 0));

        videoWriter << currentImage;
    }
}
void part2() {
    int imageHeight = 600;
    int imageWidth = 800;
    double pi = 3.141592653589793;
        
    std::vector<std::vector<double>> cubeVertices = {{1, 1, 1, 1},
                                                     {1, 1, -1, 1},
                                                     {1, -1, 1, 1},
                                                     {-1, 1, 1, 1},
                                                     {-1, -1, 1, 1},
                                                     {-1, 1, -1, 1},
                                                     {1, -1, -1, 1},
                                                     {-1, -1, -1, 1}};
    
    vector<Mat> cubePoints;
    int frameRate = 60;
    
    VideoWriter videoWriter;
    videoWriter.open("rotation.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), frameRate, Size(imageWidth, imageHeight));
    
    for(int i = 0; i < cubeVertices.size(); i++) {
        Mat point = (Mat_<double>(4, 1) << cubeVertices[i][0], cubeVertices[i][1], cubeVertices[i][2], cubeVertices[i][3]);
        cubePoints.push_back(performScaling(point, 100, 100, 100));
    }
    
    int totalFrames = 300;
    double angleStep = 2 * pi / static_cast<double>(totalFrames);
    
    ofstream coordOutput("coordinates.txt");
    
    for(int frameIndex = 0; frameIndex <= totalFrames; frameIndex++) {
        Mat currentImage(imageHeight, imageWidth, CV_8UC3, Scalar(255, 255, 255));
        vector<Point> pointConversion;
        
        for(int i = 0; i < cubePoints.size(); i++) {
            Mat transformation = performTranslation(rotateAroundZ(rotateAroundY(rotateAroundX(cubePoints[i], angleStep * frameIndex), angleStep * frameIndex), angleStep * frameIndex), 400, 300, 0);
            std::vector<double> output(transformation.begin<double>(), transformation.end<double>());
            
            circle(currentImage, Point(output[0], output[1]), 3, Scalar(0, 0, 0), 3);
            
            pointConversion.push_back(Point(output[0], output[1]));
            
            if(frameIndex < 4) {
                if(i != cubePoints.size() - 1) {
                    coordOutput << "(" << output[0] << "," << output[1] << "," << output[2] << "), ";
                }
                else {
                    coordOutput << "(" << output[0] << "," << output[1] << "," << output[2] << ")" << endl;
                }
            }
            
            if(frameIndex == 4) {
                coordOutput.close();
            }
            
        }
        
        line(currentImage, pointConversion[0], pointConversion[1], Scalar(0, 0, 0));
        line(currentImage, pointConversion[0], pointConversion[2], Scalar(0, 0, 0));
        line(currentImage, pointConversion[0], pointConversion[3], Scalar(0, 0, 0));
        
        line(currentImage, pointConversion[7], pointConversion[6], Scalar(0, 0, 0));
        line(currentImage, pointConversion[7], pointConversion[5], Scalar(0, 0, 0));
        line(currentImage, pointConversion[7], pointConversion[4], Scalar(0, 0, 0));
        
        line(currentImage, pointConversion[4], pointConversion[3], Scalar(0, 0, 0));
        line(currentImage, pointConversion[4], pointConversion[2], Scalar(0, 0, 0));
        
        line(currentImage, pointConversion[5], pointConversion[3], Scalar(0, 0, 0));
        line(currentImage, pointConversion[5], pointConversion[1], Scalar(0, 0, 0));
        
        line(currentImage, pointConversion[6], pointConversion[2], Scalar(0, 0, 0));
        line(currentImage, pointConversion[6], pointConversion[1], Scalar(0, 0, 0));
        
        
        videoWriter << currentImage;
    }
        
    std::vector<std::vector<double>> tetrahedronVertices = {{1.0 / sqrt(3), 0, 0, 1},
                                                            {0, 0, 2 / sqrt(6), 1},
                                                            {-sqrt(3) / 6.0, 0.5, 0, 1},
                                                            {-sqrt(3) / 6.0, -0.5, 0, 1}};
    
    vector<Mat> tetrahedronPoints;
    
    for(int i = 0; i < tetrahedronVertices.size(); i++) {
        Mat point = (Mat_<double>(4, 1) << tetrahedronVertices[i][0], tetrahedronVertices[i][1], tetrahedronVertices[i][2], tetrahedronVertices[i][3]);
        tetrahedronPoints.push_back(performScaling(point, 250, 250, 250));
    }
    
    for(int frameIndex = 0; frameIndex <= totalFrames; frameIndex++) {
        Mat currentImage(imageHeight, imageWidth, CV_8UC3, Scalar(255, 255, 255));
        vector<Point> pointConversion;
        
        for(int i = 0; i < tetrahedronPoints.size(); i++) {
            Mat transformation = performTranslation(rotateAroundZ(rotateAroundY(rotateAroundX(tetrahedronPoints[i], angleStep * frameIndex), angleStep * frameIndex), angleStep * frameIndex), 400, 300, 0);
            std::vector<double> output(transformation.begin<double>(), transformation.end<double>());
            
            circle(currentImage, Point(output[0], output[1]), 3, Scalar(0, 0, 0), 3);
            
            pointConversion.push_back(Point(output[0], output[1]));
            
            if(frameIndex < 4) {
                if(i != tetrahedronPoints.size() - 1) {
                    coordOutput << "(" << output[0] << "," << output[1] << "," << output[2] << "), ";
                }
                else {
                    coordOutput << "(" << output[0] << "," << output[1] << "," << output[2] << ")" << endl;
                }
            }
            
            if(frameIndex == 4) {
                coordOutput.close();
            }
        }
        
        line(currentImage, pointConversion[1], pointConversion[0], Scalar(0, 0, 0));
        line(currentImage, pointConversion[1], pointConversion[2], Scalar(0, 0, 0));
        line(currentImage, pointConversion[1], pointConversion[3], Scalar(0, 0, 0));
        
        line(currentImage, pointConversion[2], pointConversion[0], Scalar(0, 0, 0));
        line(currentImage, pointConversion[2], pointConversion[3], Scalar(0, 0, 0));
        
        line(currentImage, pointConversion[0], pointConversion[3], Scalar(0, 0, 0));
        
        
        videoWriter << currentImage;
    }
}

int main(int argc, char** argv) {
    part2();
    return 0;
}