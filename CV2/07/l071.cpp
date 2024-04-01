#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// void detectCoins(const Mat& inputImage) {

// }

void part1(int argc, char* argv[]) {
  int threshold = 35;
  int TCircle = 55;
  int minRadius = 75;
  int maxRadius = 175;
  int minDist = 50;
  const char* inPPM = "image.jpg";
  const char* circlesPPM = "imageCoins.jpg";
  const char* resultsText = "results.txt";

  for (int i = 0; i < argc; i++) {
    if (string(argv[i]) == "-F") { inPPM = argv[i+1]; }
    if (string(argv[i]) == "-T") { threshold = atoi(argv[i+1]); }
    if (string(argv[i]) == "-TCircle") { TCircle = atoi(argv[i+1]); }
    if (string(argv[i]) == "-minR") { minRadius = atoi(argv[i+1]); }
    if (string(argv[i]) == "-maxR") { maxRadius = atoi(argv[i+1]); }
    if (string(argv[i]) == "-minD") { minDist = atoi(argv[i+1]); }
    if (string(argv[i]) == "-FC") { circlesPPM = argv[i+1]; }
    if (string(argv[i]) == "-FR") { resultsText = argv[i+1]; }
  }
    
  Mat image = imread(inPPM, IMREAD_COLOR);

  if (image.empty()) {
    cout << "Could not open or find the image" << endl;
  } else {
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    GaussianBlur(grayImage, grayImage, Size(31, 31), 2, 2);

    vector<Vec3f> circles;
    HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1, minDist, threshold, TCircle, minRadius, maxRadius);
    
    double cost = 0;
    int numPennies = 0;
    int numNickels = 0;
    int numQuarters = 0;
    int numDimes = 0;
    int numDollars = 0;
      
    for (size_t i = 0; i < circles.size(); i++) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
        if (radius < 86) { circle(image, center, radius, Scalar(255, 0, 0), 4, 8, 0); numDimes += 1; }
        else if (radius < 96) { circle(image, center, radius, Scalar(0, 0, 255), 4, 8, 0); numPennies += 1; }
        else if (radius < 107) { circle(image, center, radius, Scalar(0, 255, 255), 4, 8, 0); numNickels += 1; }
        else if (radius < 140) { circle(image, center, radius, Scalar(255, 0, 200), 4, 8, 0); numQuarters += 1; }
        else if (radius < 150) { circle(image, center, radius, Scalar(0, 0, 255), 4, 8, 0); }
        else { circle(image, center, radius, Scalar(0, 255, 0), 4, 8, 0); numDollars += 1; }
    }
    cost = numPennies * 0.1 + numNickels * 0.05 + numQuarters * 0.25 + numDimes * 0.1 + numDollars;
    ofstream Final6PPM(resultsText);
    Final6PPM << "Cost: $" << cost << endl;
    Final6PPM << "Pennies: " << numPennies << endl;
    Final6PPM << "Nickels: " << numNickels << endl;
    Final6PPM << "Quarters: " << numQuarters << endl;
    Final6PPM << "Dimes: " << numDimes << endl;
    Final6PPM << "Dollars: " << numDollars << endl;
    Final6PPM.close();
    cout << "Cost: $" << cost << endl;
    cout << "Pennies: " << numPennies << endl;
    cout << "Nickels: " << numNickels << endl;
    cout << "Quarters: " << numQuarters << endl;
    cout << "Dimes: " << numDimes << endl;
    cout << "Dollars: " << numDollars << endl;
    imwrite(circlesPPM, image);
   }
}

int main(int argc, char* argv[]) {
    part1(argc, argv);
}