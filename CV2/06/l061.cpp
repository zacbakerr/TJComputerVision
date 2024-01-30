#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

vector<vector<int>> greyScale(vector<vector<vector<int>>> pixels) {
  vector<vector<int>> pixelsGrey;
  for (int i = 0; i < (int)pixels.size(); i++) {
    vector<int> row;
    pixelsGrey.push_back(row);
    for (int j = 0; j < (int)pixels[i].size(); j++){
      int grey = 0.2126 * pixels[i][j][0] + 0.7152 * pixels[i][j][1] + 0.0722 * pixels[i][j][2];
      pixelsGrey[i].push_back(grey);
    }
  }
  return pixelsGrey;
}

vector<vector<int>> sobelOperatorX(vector<vector<int>> pixelsGrey) {
  vector<vector<int>> pixelsSobelX;
  pixelsSobelX = pixelsGrey;
  for (int i = 0; i < (int)pixelsGrey.size(); i++) {
    for (int j = 0; j < (int)pixelsGrey[i].size(); j++){
      if (i == 0 || j == 0 || i == (int)pixelsGrey.size() - 1 || j == (int)pixelsGrey[i].size() - 1) {
        pixelsSobelX[i][j] = 0;
      } else {
        int sobel = (pixelsGrey[i-1][j-1] * -1) + (pixelsGrey[i][j-1] * -2) + (pixelsGrey[i+1][j-1] * -1) + (pixelsGrey[i-1][j+1] * 1) + (pixelsGrey[i][j+1] * 2) + (pixelsGrey[i+1][j+1] * 1);
        pixelsSobelX[i][j] = sobel;
      }
    }
  }
  return pixelsSobelX;
}

vector<vector<int>> sobelOperatorY(vector<vector<int>> pixelsGrey) {
  vector<vector<int>> pixelsSobelY;
  pixelsSobelY = pixelsGrey;
  for (int i = 0; i < (int)pixelsGrey.size(); i++) {
    for (int j = 0; j < (int)pixelsGrey[i].size(); j++){
      if (i == 0 || j == 0 || i == (int)pixelsGrey.size() - 1 || j == (int)pixelsGrey[i].size() - 1) {
        pixelsSobelY[i][j] = 0;
      } else {
        int sobel = (pixelsGrey[i-1][j-1] * -1) + (pixelsGrey[i-1][j] * -2) + (pixelsGrey[i-1][j+1] * -1) + (pixelsGrey[i+1][j-1] * 1) + (pixelsGrey[i+1][j] * 2) + (pixelsGrey[i+1][j+1] * 1);
        pixelsSobelY[i][j] = sobel;
      }
    }
  }
  return pixelsSobelY;
}

vector<vector<int>> sobelOperatorMagnitude(vector<vector<int>> pixelsGrey) {
  vector<vector<int>> pixelsSobelX = sobelOperatorX(pixelsGrey);
  vector<vector<int>> pixelsSobelY = sobelOperatorY(pixelsGrey);
  vector<vector<int>> pixelsSobel((int)pixelsGrey.size(), vector<int>((int)pixelsGrey[0].size(), 0));
  for (int i = 0; i < (int)pixelsGrey.size(); i++) {
    for (int j = 0; j < (int)pixelsGrey[i].size(); j++) {
      pixelsSobel[i][j] = sqrt(pow(pixelsSobelX[i][j], 2) + pow(pixelsSobelY[i][j], 2));
    }
  }
  return pixelsSobel;
}

vector<vector<double>> sobelOperatorDirection(vector<vector<int>> pixelsGrey) {
  vector<vector<int>> pixelsSobelX = sobelOperatorX(pixelsGrey);
  vector<vector<int>> pixelsSobelY = sobelOperatorY(pixelsGrey);
  vector<vector<double>> pixelsDirection((int)pixelsGrey.size(), vector<double>((int)pixelsGrey[0].size(), 0.0));
  for (int i = 0; i < (int)pixelsGrey.size(); i++) {
    for (int j = 0; j < (int)pixelsGrey[i].size(); j++) {
      pixelsDirection[i][j] = atan2(pixelsSobelY[i][j], pixelsSobelX[i][j]);
    }
  }
  return pixelsDirection;
}

vector<vector<int>> hysteresisAlgorithmRecursion(vector<vector<int>> pixels, set<int> seen) {
  bool done = false;
  for (int i = 0; i < (int)pixels.size(); i++) {
    for (int j = 0; j < (int)pixels[i].size(); j++) {
      int ind = i*j + j;
      if ((pixels[i][j] == 2) && !(seen.find(ind) != seen.end())) {
        if (pixels[i+1][j] == 1) { pixels[i+1][j] == 2; }
        if (pixels[i][j+1] == 1) { pixels[i][j+1] == 2; }
        if (pixels[i-1][j] == 1) { pixels[i-1][j] == 2; }
        if (pixels[i][j-1] == 1) { pixels[i][j-1] == 2; }
        seen.insert(ind);
        done = true;
      }
    }
  }
  if (done == false) {
    return hysteresisAlgorithmRecursion(pixels, seen);
  } else {
    for (int i = 0; i < (int)pixels.size(); i++) {
      for (int j = 0; j < (int)pixels[i].size(); j++) {
        if (pixels[i][j] == 2) {
          pixels[i][j] = 255;
        } else {
          pixels[i][j] = 0;
        }
      }
    }
    return pixels;
  }
}

vector<vector<int>> hysteresisAlgorithm(vector<vector<int>> pixelsGrey, int lowThreshold, int highThreshold) {
  vector<vector<int>> pixelsSobelX = sobelOperatorX(pixelsGrey);
  vector<vector<int>> pixelsSobelY = sobelOperatorY(pixelsGrey);
  vector<vector<int>> pixelsSobel;
  pixelsSobel = pixelsGrey;
  for (int i = 0; i < (int)pixelsGrey.size(); i++) {
    for (int j = 0; j < (int)pixelsGrey[i].size(); j++) {
      pixelsSobel[i][j] = sqrt(pow(pixelsSobelX[i][j], 2) + pow(pixelsSobelY[i][j], 2));
      if (pixelsSobel[i][j] > highThreshold) {
        pixelsSobel[i][j] = 2;
      } else if ((pixelsSobel[i][j] > lowThreshold) && (pixelsSobel[i][j] <= highThreshold)) {
        pixelsSobel[i][j] = 1;
      } else {
        pixelsSobel[i][j] = 0;
      }
    }
  }
  return pixelsSobel;
}

vector<vector<int>> nonMaximumSuppression(vector<vector<int>> magnitude, vector<vector<double>> direction) {
  vector<vector<int>> nms = magnitude;
  for (int i = 1; i < (int)magnitude.size() - 1; i++) {
    for (int j = 1; j < (int)magnitude[0].size() - 1; j++) {
      if (((direction[i][j] >= (acos(-1)/8)) && (direction[i][j] < ((3*acos(-1))/8))) || ((direction[i][j] >= -((7*acos(-1)/8))) && (direction[i][j] < ((5*acos(-1))/4)))) { 
        if ((magnitude[i][j] >= magnitude[i-1][j-1]) && (magnitude[i][j] >= magnitude[i+1][j+1])) {
          nms[i][j] = 255;
        } else {
          nms[i][j] = 0;
        }
      } else if ((direction[i][j] >= ((3*acos(-1))/8) && direction[i][j] < ((5*acos(-1))/8)) || (direction[i][j] >= -((5*acos(-1))/8) && direction[i][j] < ((3*acos(-1))/8))) { 
        if ((magnitude[i][j] >= magnitude[i-1][j]) && (magnitude[i][j] >= magnitude[i+1][j])) {
          nms[i][j] = 255;
        } else {
          nms[i][j] = 0;
        }
      } else if ((direction[i][j] >= ((5*acos(-1))/8) && direction[i][j] < ((7*acos(-1))/8)) || (direction[i][j] >= -((3*acos(-1))/8) && direction[i][j] < -(acos(-1)/8))) { 
        if ((magnitude[i][j] >= magnitude[i-1][j+1]) && (magnitude[i][j] >= magnitude[i+1][j-1])) {
          nms[i][j] = 255;
        } else {
          nms[i][j] = 0;
        }
      } else if (direction[i][j] >= ((7*acos(-1))/8) || direction[i][j] < -((7*acos(-1))/8) || (direction[i][j] >= -(acos(-1)/8) && direction[i][j] < (acos(-1)/8))) { 
        if ((magnitude[i][j] >= magnitude[i][j-1]) && (magnitude[i][j] >= magnitude[i][j+1])) {
          nms[i][j] = 255;
        } else {
          nms[i][j] = 0;
        }
      } 
    }
  }

  return nms;
}

vector<vector<int>> combinedHysteresisNMS(vector<vector<int>> nms, vector<vector<int>> hysteresis) {
  vector<vector<int>> combined = nms;
  for (int i = 0; i < (int)nms.size(); i++) {
    for (int j = 0; j < (int)nms[i].size(); j++) {
      if (nms[i][j] == 255 && hysteresis[i][j] == 255) {
        combined[i][j] = 255;
      } else {
        combined[i][j] = 0;
      }
    }
  }
  return combined;
}

vector<vector<int>> drawLine(vector<vector<int>> pixelsIn, int x, int y, double theta) {
  vector<vector<int>> pixels = pixelsIn;
  int finalX = 0;
  int finalY = 0;
  if (x < pixels.size()/2) {
    int finalX = x + acos(theta)*(pixels.size()/2);
  } else {
    int finalX = x - acos(theta)*(pixels.size()/2);
  }
  if (y < pixels[0].size()/2) {
    int finalY = y + asin(theta)*(pixels[0].size()/2);
  } else {
    int finalY = y - asin(theta)*(pixels[0].size()/2);
  }

  int rise = finalY - y;
  int run = finalX - x;

  if (rise/run > 0 && abs(run) > abs(rise)) {
    int j = y;
    int e = abs(rise) - abs(run);
    for (int i = x; i < pixels[0].size(); i++) {
      pixels[j][i] = 0;
      if (e >= 0) {
        j += 1;
        e -= abs(run);
      }
      if (j >= pixels.size()) {
        break;
      }
      e += abs(rise);
    }
    j = y;
    for (int i = x; i >= 0; i--) {
      pixels[j][i] = 0;
      if (e >= 0) {
        j -= 1;
        e -= abs(run);
      }
      if (j <= 0) {
        break;
      }
      e += abs(rise);
    }
  } else if ((rise/run) > 0 && abs(run) < abs(rise)) {
    int j = x;
    int e = abs(run) - abs(rise);
    for (int i = y; i < pixels[0].size(); i++) {
      pixels[i][j] = 0;
      if (e >= 0) {
        j += 1;
        e -= abs(rise);
      }
      if (j >= pixels.size()) {
        break;
      }
      e += abs(run);
    }
    j = x;
    for (int i = y; i >= 0; i--) {
      pixels[i][j] = 0;
      if (e >= 0) {
        j -= 1;
        e -= abs(rise);
      }
      if (j < 0) {
        break;
      }
      e += abs(run);
    }
      
  } else if ((rise/run) < 0 && abs(run) > abs(rise)) {
    int j = y;
    int e = abs(rise) - abs(run);
    for (int i = x; i >= 0; i--) {
      pixels[j][i] = 0;
      if (e >= 0) {
        j += 1;
        e -= abs(run);
      }
      if (j >= pixels.size()) {
        break;
      }
      e += abs(rise);
    }
    j = y;
    for (int i = x; i < pixels[0].size(); i++) {
      pixels[j][i] = 0;
      if (e >= 0) {
        j -= 1;
        e -= abs(run);
      }
      if (j < 0) {
        break;
      }
      e += abs(rise);
    }
  } else if ((rise/run) < 0 && abs(run) < abs(rise)) {
    int j = x;
    int e = abs(run) - abs(rise);
    for (int i = y; i >= 0; i--) {
      pixels[i][j] = 0;
      if (e >= 0) {
        j += 1;
        e -= abs(rise);
      }
      if (j >= pixels.size()) {
        break;
      }
      e += abs(run);
    }
    j = x;
    for (int i = y; i < pixels.size(); i++) {
      pixels[i][j] = 0;
      if (e >= 0) {
        j -= 1;
        e -= abs(rise);
      }
      if (j < 0) {
        break;
      }
      e += abs(run);
    }
  }
  return pixels;
}

vector<vector<int>> centerDetection(vector<vector<int>> combined, vector<vector<double>> direction) {
  for (int i = 1; i < (int)combined.size() - 1; i++) {
    for (int j = 1; j < (int)combined[0].size() - 1; j++) {
      if (combined[i][j] == 255) {
        vector<vector<int>> combined = drawLine(combined, i, j, direction[i][j]);
      }
    }
  }
  return combined;
}

void part1(int argc, char* argv[]) {
  int lowThreshold = 70;
  int highThreshold = 140;
  const char* inPPM = "image.ppm";
  const char* finalOutPPM = "imagef.ppm";
  int TC = 100;

  for (int i = 0; i < argc; i++) {
    if (string(argv[i]) == "-F") { inPPM = argv[i+1]; }
    if (string(argv[i]) == "-L") { lowThreshold = atoi(argv[i+1]); }
    if (string(argv[i]) == "-H") { highThreshold = atoi(argv[i+1]); }
    if (string(argv[i]) == "-TC") { TC = atoi(argv[i+1]); }
  }

  FILE* ppmfile;
  ppmfile = fopen(inPPM, "rb");
  
  int width, height, maxval;
  fscanf(ppmfile, "P3\n%d %d %d\n", &width, &height, &maxval);

  vector<vector<vector<int>>> pixels;

  for (int i = 0; i < height; i++) {
    vector<vector<int>> row;
    pixels.push_back(row);
    for (int j = 0; j < width; j++){
      vector<int> pixel;
      pixels[i].push_back(pixel);
      for (int k = 0; k < 3; k++) {
        int value;
        fscanf(ppmfile, "%d", &value);
        pixels[i][j].push_back(value);
      }
    }
  }

  vector<vector<int>> pixelsGrey = greyScale(pixels);
  vector<vector<int>> pixelsSobel = sobelOperatorMagnitude(pixelsGrey);
  vector<vector<double>> pixelsDirection = sobelOperatorDirection(pixelsGrey);
  vector<vector<int>> pixelsCanny = hysteresisAlgorithm(pixelsGrey, lowThreshold, highThreshold);
  set<int> seen = {};
  vector<vector<int>> pixelsRecurCanny = hysteresisAlgorithmRecursion(pixelsCanny, seen);
  vector<vector<int>> pixelsNMS = nonMaximumSuppression(pixelsSobel, pixelsDirection);
  vector<vector<int>> pixelsFinal = combinedHysteresisNMS(pixelsNMS, pixelsRecurCanny);
  vector<vector<int>> pixelsCenter = centerDetection(pixelsFinal, pixelsDirection);

  ofstream FinalPPM(finalOutPPM);
  FinalPPM << "P3 " << width << " " << height << " " << maxval << endl;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++){
      FinalPPM << pixelsCenter[i][j] << " " << pixelsCenter[i][j] << " " << pixelsCenter[i][j] << endl;
    }
  }
  FinalPPM.close();
}

int main(int argc, char* argv[]) {
  part1(argc, argv);
}