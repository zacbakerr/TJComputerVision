#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

vector<vector<int>> greyScale(vector<vector<vector<int>>> pixels) {
  vector<vector<int>> pixelsGrey;
  for (int i = 0; i < pixels.size(); i++) {
    vector<int> row;
    pixelsGrey.push_back(row);
    for (int j = 0; j < pixels[i].size(); j++){
      int grey = 0.2126 * pixels[i][j][0] + 0.7152 * pixels[i][j][1] + 0.0722 * pixels[i][j][2];
      pixelsGrey[i].push_back(grey);
    }
  }
  return pixelsGrey;
}

vector<vector<int>> sobelOperatorX(vector<vector<int>> pixelsGrey) {
  vector<vector<int>> pixelsSobelX;
  pixelsSobelX = pixelsGrey;
  for (int i = 0; i < pixelsGrey.size(); i++) {
    for (int j = 0; j < pixelsGrey[i].size(); j++){
      if (i == 0 || j == 0 || i == pixelsGrey.size() - 1 || j == pixelsGrey[i].size() - 1) {
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
  for (int i = 0; i < pixelsGrey.size(); i++) {
    for (int j = 0; j < pixelsGrey[i].size(); j++){
      if (i == 0 || j == 0 || i == pixelsGrey.size() - 1 || j == pixelsGrey[i].size() - 1) {
        pixelsSobelY[i][j] = 0;
      } else {
        int sobel = (pixelsGrey[i-1][j-1] * -1) + (pixelsGrey[i-1][j] * -2) + (pixelsGrey[i-1][j+1] * -1) + (pixelsGrey[i+1][j-1] * 1) + (pixelsGrey[i+1][j] * 2) + (pixelsGrey[i+1][j+1] * 1);
        pixelsSobelY[i][j] = sobel;
      }
    }
  }
  return pixelsSobelY;
}

vector<vector<int>> sobelOperator(vector<vector<int>> pixelsGrey) {
  vector<vector<int>> pixelsSobelX = sobelOperatorX(pixelsGrey);
  vector<vector<int>> pixelsSobelY = sobelOperatorY(pixelsGrey);
  vector<vector<int>> pixelsSobel;
  vector<vector<int>> pixelsDirection;
  pixelsSobel = pixelsGrey;
  for (int i = 0; i < pixelsGrey.size(); i++) {
    for (int j = 0; j < pixelsGrey[i].size(); j++) {
      pixelsSobel[i][j] = sqrt(pow(pixelsSobelX[i][j], 2) + pow(pixelsSobelY[i][j], 2));
      pixelsDirection[i][j] = atan2(pixelsSobelY[i][j], pixelsSobelX[i][j]);
    }
  }
  return pixelsSobel, pixelsDirection;
}

vector<vector<int>> hysteresisAlgorithmRecursion(vector<vector<int>> pixels, set<int> seen) {
  bool done = false;
  for (int i = 0; i < pixels.size(); i++) {
    for (int j = 0; j < pixels[i].size(); j++) {
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
    for (int i = 0; i < pixels.size(); i++) {
      for (int j = 0; j < pixels[i].size(); j++) {
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
  for (int i = 0; i < pixelsGrey.size(); i++) {
    for (int j = 0; j < pixelsGrey[i].size(); j++) {
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

vector<vector<int>> nonMaximumSuppression(vector<vector<int>> pixels) {

}

void part1() {
  FILE* ppmfile;
  ppmfile = fopen("image.ppm", "rb");
  
  int width, height, maxval;
  fscanf(ppmfile, "P3\n%d %d %d\n", &width, &height, &maxval);

  int widthcounter = 0;
  int heightcounter = 0;

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
  vector<vector<int>> pixelsSobel, vector<vector<int>> direction = sobelOperator(pixelsGrey);

  ofstream GreyPPM("imageg.ppm");
  GreyPPM << "P3 " << width << " " << height << " " << maxval << endl;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++){
      GreyPPM << pixelsGrey[i][j] << " " << pixelsGrey[i][j] << " " << pixelsGrey[i][j] << endl;
    }
  }
  GreyPPM.close();

  ofstream SobelPPM("imagem.ppm");
  SobelPPM << "P3 " << width << " " << height << " " << maxval << endl;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++){
      SobelPPM << pixelsSobel[i][j] << " " << pixelsSobel[i][j] << " " << pixelsSobel[i][j] << endl;
    }
  }
  SobelPPM.close();
}

void part2(int argc, char* argv[]) {
  int lowThreshold = 75;
  int highThreshold = 100;
  const char* inPPM = "image.ppm";
  const char* outPPM = "image1.ppm";

  for (int i = 0; i < argc; i++) {
    if (string(argv[i]) == "-f") { inPPM = argv[i+1]; }
    if (string(argv[i]) == "-lt") { lowThreshold = atoi(argv[i+1]); }
    if (string(argv[i]) == "-ht") { highThreshold = atoi(argv[i+1]); }
    if (string(argv[i]) == "-of") { outPPM = argv[i+1]; }
  }

  FILE* ppmfile;
  ppmfile = fopen(inPPM, "rb");
  
  int width, height, maxval;
  fscanf(ppmfile, "P3\n%d %d %d\n", &width, &height, &maxval);

  int widthcounter = 0;
  int heightcounter = 0;

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
  vector<vector<int>> pixelsCanny = hysteresisAlgorithm(pixelsGrey, lowThreshold, highThreshold);
  set<int> seen = {};
  vector<vector<int>> pixelsRecurCanny = hysteresisAlgorithmRecursion(pixelsCanny, seen);

  ofstream CannyPPM(outPPM);
  CannyPPM << "P3 " << width << " " << height << " " << maxval << endl;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++){
      CannyPPM << pixelsRecurCanny[i][j] << " " << pixelsRecurCanny[i][j] << " " << pixelsRecurCanny[i][j] << endl;
    }
  }
  CannyPPM.close();
}

void part3(int argc, char* argv[]) {
  int lowThreshold = 75;
  int highThreshold = 100;
  const char* inPPM = "image.ppm";
  const char* outPPM = "image1.ppm";
  const char* greyOutPPM = "imageg.ppm";
  const char* nmsOutPPM = "image2.ppm";
  const char* finalOutPPM = "imagef.ppm";

  for (int i = 0; i < argc; i++) {
    if (string(argv[i]) == "-f") { inPPM = argv[i+1]; }
    if (string(argv[i]) == "-lt") { lowThreshold = atoi(argv[i+1]); }
    if (string(argv[i]) == "-ht") { highThreshold = atoi(argv[i+1]); }
    if (string(argv[i]) == "-of") { outPPM = argv[i+1]; }
    if (string(argv[i]) == "-fg") { greyOutPPM = argv[i+1]; }
    if (string(argv[i]) == "-f2") { nmsOutPPM = argv[i+1]; }
    if (string(argv[i]) == "-ff") { finalOutPPM = argv[i+1]; }
  }

  FILE* ppmfile;
  ppmfile = fopen(inPPM, "rb");
  
  int width, height, maxval;
  fscanf(ppmfile, "P3\n%d %d %d\n", &width, &height, &maxval);

  int widthcounter = 0;
  int heightcounter = 0;

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
  vector<vector<int>> pixelsCanny = hysteresisAlgorithm(pixelsGrey, lowThreshold, highThreshold);
  set<int> seen = {};
  vector<vector<int>> pixelsRecurCanny = hysteresisAlgorithmRecursion(pixelsCanny, seen);

  ofstream HysteresisPPM(outPPM);
  HysteresisPPM << "P3 " << width << " " << height << " " << maxval << endl;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++){
      HysteresisPPM << pixelsRecurCanny[i][j] << " " << pixelsRecurCanny[i][j] << " " << pixelsRecurCanny[i][j] << endl;
    }
  }
  HysteresisPPM.close();
  ofstream GreyPPM(greyOutPPM);
  GreyPPM << "P3 " << width << " " << height << " " << maxval << endl;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++){
      GreyPPM << pixelsGrey[i][j] << " " << pixelsGrey[i][j] << " " << pixelsGrey[i][j] << endl;
    }
  }
  GreyPPM.close();
}

int main(int argc, char* argv[]) {
  // part1();
  // part2(argc, argv);
  part3(argc, argv);
}