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
      // int grey = 0.2126 * pixels[i][j][0] + 0.7152 * pixels[i][j][1] + 0.0722 * pixels[i][j][2];
      int grey = (pixels[i][j][0] + pixels[i][j][1] + pixels[i][j][2])/3;
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

vector<vector<int>> drawLine(vector<vector<int>> pixelsIn, int x0, int y0, double theta, vector<vector<int>> combined) {
  int x1;
  int y1;

  double p = acos(-1);

  if (theta > 0 && theta < p/2) {
    x1 = x0 - 1000;
    y1 = y0 - 1000 * tan(theta);
  } else if (theta > p/2 && theta < p) {
    x1 = x0 + 1000;
    y1 = y0 + 1000 * tan(theta);
  } else if (theta < 0 && theta > -p/2) {
    x1 = x0 - 1000;
    y1 = y0 - 1000 * tan(theta);
  } else if (theta < -p/2 && theta > -p) {
    x1 = x0 + 1000;
    y1 = y0 + 1000 * tan(theta);
  } else {
    x1 = x0;
    y1 = y0;
  }

  int run = abs(x1 - x0);
  int rise = abs(y1 - y0);
  int slopesignx = (x0 < x1) ? 1 : -1;
  int slopesigny = (y0 < y1) ? 1 : -1;
  int error = run - rise;
  int counter = 0;

  while (true) {
    if (x0 < 0 || x0 >= pixelsIn[0].size() || y0 < 0 || y0 >= pixelsIn.size()) {
      break;
    }
    if (counter > 50) {
      break;
    }
    if (x0 == x1 && y0 == y1) {
      break;
    }
    pixelsIn[y0][x0] = pixelsIn[y0][x0] + 5;
    int e2 = 2 * error;
    if (e2 > -rise) { error -= rise; x0 += slopesignx; }
    if (e2 < run) { error += run; y0 += slopesigny; }
    counter += 1;
  }

  return pixelsIn;
}

vector<vector<int>> centerDetection(vector<vector<int>> combined, vector<vector<double>> direction, int TC) {
  vector<vector<int>> pixels = combined;
  for (int i = 1; i < (int)(combined.size()); i++) {
    for (int j = 1; j < (int)(combined[i].size()); j++) {
      if (combined[i][j] == 255) {
        pixels = drawLine(pixels, j, i, direction[i][j], combined);
        pixels[i][j] = 0;
      }
    }
  }
  return pixels;
}

int gcd(int a, int b) {
  while(b != 0) {
    int tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}

void part1(int argc, char* argv[]) {
  int lowThreshold = 150;
  int highThreshold = 200;
  const char* inPPM = "image.ppm";  
  int TC = 25;

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

  // int scale = gcd(width, height);
  int scale = 6;
  int newWidth = width/6;
  int newHeight = height/6;
  vector<vector<int>> pixelsGreyScaled;
  for (int i = 0; i < newHeight; i++) {
    vector<int> row;
    pixelsGreyScaled.push_back(row);
    for (int j = 0; j < newWidth; j++){
      int sum = 0;
      for (int k = 0; k < scale; k++) {
        for (int l = 0; l < scale; l++) {
          sum += pixelsGrey[i*scale + k][j*scale + l];
        }
      }
      pixelsGreyScaled[i].push_back(sum/(scale*scale));
    }
  }

  vector<vector<int>> pixelsSobel = sobelOperatorMagnitude(pixelsGreyScaled);
  vector<vector<double>> pixelsDirection = sobelOperatorDirection(pixelsGreyScaled);
  vector<vector<int>> pixelsCanny = hysteresisAlgorithm(pixelsGreyScaled, lowThreshold, highThreshold);
  set<int> seen = {};
  vector<vector<int>> pixelsRecurCanny = hysteresisAlgorithmRecursion(pixelsCanny, seen);
  vector<vector<int>> pixelsNMS = nonMaximumSuppression(pixelsSobel, pixelsDirection);
  vector<vector<int>> pixelsFinal = combinedHysteresisNMS(pixelsNMS, pixelsRecurCanny);
  vector<vector<int>> pixelsCenter = centerDetection(pixelsFinal, pixelsDirection, TC);

  ofstream FinalPPM("imagef.ppm");
  FinalPPM << "P3 " << newWidth << " " << newHeight << " " << maxval << endl;
  for (int i = 0; i < newHeight; i++) {
    for (int j = 0; j < newWidth; j++){
      FinalPPM << pixelsFinal[i][j] << " " << pixelsFinal[i][j] << " " << pixelsFinal[i][j] << " ";
    }
  }
  FinalPPM.close();

  ofstream Final2PPM("imagev.ppm");
  Final2PPM << "P3 " << newWidth << " " << newHeight << " " << maxval << endl;
  for (int i = 0; i < newHeight; i++) {
    for (int j = 0; j < newWidth; j++){
      Final2PPM << pixelsCenter[i][j] << " " << pixelsCenter[i][j] << " " << pixelsCenter[i][j] << " ";
    }
  }
  Final2PPM.close();

  for (int i = 0; i < newHeight; i++) {
    for (int j = 0; j < newWidth; j++) {
      if (pixelsCenter[i][j] >= TC) {
        pixels[i*scale][j*scale][0] = 255;
        pixels[i*scale][j*scale][1] = 0;
        pixels[i*scale][j*scale][2] = 0;
      }
    }
  }

  ofstream Final3PPM("imageCC.ppm");
  Final3PPM << "P3 " << width << " " << height << " " << maxval << endl;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++){
      Final3PPM << pixels[i][j][0] << " " << pixels[i][j][1] << " " << pixels[i][j][2] << " ";
    }
  }
  Final3PPM.close();
}



int main(int argc, char* argv[]) {
  part1(argc, argv);
}