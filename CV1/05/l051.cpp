#include <fstream>
#include <iostream>

using namespace std;

void part1() {
  FILE* ppmfile;
  ppmfile = fopen("image.ppm", "rb");
  
  int width, height, maxval;
  fscanf(ppmfile, "P3\n%d %d %d\n", &width, &height, &maxval);

  int widthcounter = 0;
  int heightcounter = 0;

  int pixels[400][400][3];
  // int pixelsgrey[400][400][3];

  int r, g, b;
  while (fscanf(ppmfile, "%d %d %d", &r, &g, &b) != EOF) {
    pixels[heightcounter][widthcounter][0] = r;
    pixels[heightcounter][widthcounter][1] = g;
    pixels[heightcounter][widthcounter][2] = b;
    widthcounter++;
    if (widthcounter == width) {
      widthcounter = 0;
      heightcounter++;
    }
  }
  
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++){
      int grey = 0.2126 * pixels[i][j][0] + 0.7152 * pixels[i][j][1] + 0.0722 * pixels[i][j][2];
      pixels[i][j][0] = grey;
      pixels[i][j][1] = grey;
      pixels[i][j][2] = grey;
    }
  }

  ofstream MyFile("imageg.ppm");
  MyFile << "P3 " << width << " " << height << " " << maxval << endl;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++){
      // MyFile << pixelsgrey[i][j] << " " << pixelsgrey[i][j] << " " << pixelsgrey[i][j] << endl;
      for (int k = 0; k < 3; k++) {
        MyFile << pixels[i][j][k] << " ";
      }
      MyFile << endl;
    }
  }
  MyFile.close();
}

int main() {
  part1();
}