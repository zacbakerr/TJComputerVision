#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

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

vector<vector<int>> sobelOperator(vector<vector<int>> pixelsGrey) {
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
  vector<vector<int>> pixelsSobel;
  pixelsSobel = pixelsGrey;
  for (int i = 0; i < pixelsGrey.size(); i++) {
    for (int j = 0; j < pixelsGrey[i].size(); j++){
      pixelsSobel[i][j] = sqrt(pow(pixelsSobelX[i][j], 2) + pow(pixelsSobelY[i][j], 2));
      if (pixelsSobel[i][j] < 275) {
        pixelsSobel[i][j] = 0;
      } else {
        pixelsSobel[i][j] = 255;
      }
    }
  }
  return pixelsSobel;
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
  vector<vector<int>> pixelsSobel = sobelOperator(pixelsGrey);

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

int main() {
  part1();
}