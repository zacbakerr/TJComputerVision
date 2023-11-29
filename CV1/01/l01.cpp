#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <bits/stdc++.h>
#include <tuple>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

void bothBigger(int (*pixels)[800][3], double bigX, double bigY, double smallX, double smallY) {
  double deltaX = bigX - smallX;
  double deltaY = bigY - smallY;
  
  if (deltaX > deltaY) {
    int j = round(smallY);
    double e = deltaY - deltaX;

    for (int i = round(smallX); i < round(bigX); i++) {
      for (int k = 0; k < 3; k++) {
        pixels[j][i][k] = 0;
      }
      if (e >= 0) {
        j += 1;
        e -= deltaX;
      }
      e += deltaY;
    }
  } else {
    int j = round(smallX);
    double e = deltaX - deltaY;

    for (int i = round(smallY); i < round(bigY); i++) {
      for (int k = 0; k < 3; k++) {
        pixels[i][j][k] = 0;
      }
      if (e >= 0) {
        j += 1;
        e -= deltaY;
      }
      e += deltaX;
    }
  }
}

void lineFromSlope(int (*pixels)[800][3], int x, int y, double rise, double run) {  
  // cout << rise/run << " " << abs(run) << " " << abs(rise) << endl;
  if (rise/run > 0 and abs(run) > abs(rise)) {
    int j = y;
    int e = abs(rise) - abs(run);
    for (int i = x; i < 800; i++) {
      for (int k = 0; k < 3; k++) {
        pixels[j][i][k] = 0;
      }
      if (e >= 0) {
        j += 1;
        e -= abs(run);
      }
      if (j >= 800) {
        break;
      }
      e += abs(rise);
    }
    j = y;
    for (int i = x; i >= 0; i--) {
      for (int k = 0; k < 3; k++) {
        pixels[j][i][k] = 0;
      }
      if (e >= 0) {
        j -= 1;
        e -= abs(run);
      }
      if (j <= 0) {
        break;
      }
      e += abs(rise);
    }
  } else if ((rise/run) > 0 and abs(run) < abs(rise)) {
    int j = x;
    int e = abs(run) - abs(rise);
    for (int i = y; i < 800; i++) {
      for (int k = 0; k < 3; k++) {
        pixels[i][j][k] = 0;
      }
      if (e >= 0) {
        j += 1;
        e -= abs(rise);
      }
      if (j >= 799) {
        break;
      }
      e += abs(run);
    }
    j = x;
    for (int i = y; i >= 0; i--) {
      for (int k = 0; k < 3; k++) {
        pixels[i][j][k] = 0;
      }
      if (e >= 0) {
        j -= 1;
        e -= abs(rise);
      }
      if (j < 0) {
        break;
      }
      e += abs(run);
    }
      
  } else if ((rise/run) < 0 and abs(run) > abs(rise)) {
    int j = y;
    int e = abs(rise) - abs(run);
    for (int i = x; i >= 0; i--) {
      for (int k = 0; k < 3; k++) {
        pixels[j][i][k] = 0;
      }
      if (e >= 0) {
        j += 1;
        e -= abs(run);
      }
      if (j >= 800) {
        break;
      }
      e += abs(rise);
    }
    j = y;
    for (int i = x; i < 800; i++) {
      for (int k = 0; k < 3; k++) {
        pixels[j][i][k] = 0;
      }
      if (e >= 0) {
        j -= 1;
        e -= abs(run);
      }
      if (j < 0) {
        break;
      }
      e += abs(rise);
    }
  } else if ((rise/run) < 0 and abs(run) < abs(rise)) {
    int j = x;
    int e = abs(run) - abs(rise);
    for (int i = y; i >= 0; i--) {
      for (int k = 0; k < 3; k++) {
        pixels[i][j][k] = 0;
      }
      if (e >= 0) {
        j += 1;
        e -= abs(rise);
      }
      if (j >= 800) {
        break;
      }
      e += abs(run);
    }
    j = x;
    for (int i = y; i < 800; i++) {
      for (int k = 0; k < 3; k++) {
        pixels[i][j][k] = 0;
      }
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
}

void xBigger(int (*pixels)[800][3], double bigX, double smallY, double smallX, double bigY) {
  double deltaX = bigX - smallX;
  double deltaY = smallY - bigY;
  if (abs(deltaX) > abs(deltaY)) {
    int j = round(bigY);
    double e = deltaY - deltaX;

    for (int i = round(smallX); i < round(bigX); i++) {
      for (int k = 0; k < 3; k++) {
        pixels[j][i][k] = 0;
      }
      if (e >= 0) {
        j -= 1;
        e -= deltaX;
      }
      e -= deltaY;
    }
  } else {
    int j = round(bigX);
    double e = deltaX - deltaY;

    for (int i = round(smallY); i < round(bigY); i++) {
      for (int k = 0; k < 3; k++) {
        pixels[i][j][k] = 0;
      }
      if (e >= 0) {
        j -= 1;
        e += deltaY;
      }
      e += deltaX;
    }
  }
}

void placePointOnCircle(int (*pixels)[800][3], int ix, int iy, int x, int y) {
  for (int k = 0; k < 3; k++) {
    if ((iy + y) >= 0 and (ix + x) >= 0 and (iy + y) < 800 and (ix + x) < 800) {
      pixels[iy+y][ix+x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy + y) >= 0 and (ix - x) >= 0 and (iy + y) < 800 and (ix - x) < 800) {
      pixels[iy+y][ix-x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - y) >= 0 and (ix + x) >= 0 and (iy - y) < 800 and (ix + x) < 800) {
      pixels[iy-y][ix+x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - y) >= 0 and (ix - x) >= 0 and (iy - y) < 800 and (ix - x) < 800) {
      pixels[iy-y][ix-x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy + x) >= 0 and (ix + y) >= 0 and (iy + x) < 800 and (ix + y) < 800) {
      pixels[iy+x][ix+y][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy + x) >= 0 and (ix - y) >= 0 and (iy + x) < 800 and (ix - y) < 800) {
      pixels[iy+x][ix-y][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - x) >= 0 and (ix + y) >= 0 and (iy - x) < 800 and (ix + y) < 800) {
      pixels[iy-x][ix+y][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - x) >= 0 and (ix - y) >= 0 and (iy - x) < 800 and (ix - y) < 800) {
      pixels[iy-x][ix-y][k] = 0;
    }
  }
}

void eulers(int (*pixels)[800][3], int x1, int y1, int x2, int y2) {
  double slope = (1.0*(x2-x1))/(1.0*(y2-y1));
  double b = y1 - (slope * x1);
  // cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
  lineFromSlope(pixels, x1, y1, (y2-y1), (x2-x1));
}

void vertexSmallCircle(int (*pixels)[800][3], int x1, int y1) {
  int x = 0, y = 5;
  int d = 3 - 2 * 5;
  placePointOnCircle(pixels, x1, y1, x, y);
  while (y >= x) {
    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
    placePointOnCircle(pixels, x1, y1, x, y);
  }
}

void ninePointCircle(int (*pixels)[800][3], int x1, int y1, int x2, int y2, int x3, int y3) {
  int mx1 = (x1+x2)/2;
  int my1 = (y1+y2)/2;
  int mx2 = (x2+x3)/2;
  int my2 = (y2+y3)/2;
  int mx3 = (x1+x3)/2;
  int my3 = (y1+y3)/2;
    
  int circumCenterX = ((((mx1*mx1)+(my1*my1))*(my2-my3))+(((mx2*mx2)+(my2*my2))*(my3-my1))+(((mx3*mx3)+(my3*my3))*(my1-my2)))/(2*(mx1*(my2-my3)+mx2*(my3-my1)+mx3*(my1-my2)));
  int circumCenterY = ((((mx1*mx1)+(my1*my1))*(mx3-mx2))+(((mx2*mx2)+(my2*my2))*(mx1-mx3))+(((mx3*mx3)+(my3*my3))*(mx2-mx1)))/(2*(mx1*(my2-my3)+mx2*(my3-my1)+mx3*(my1-my2)));
  int r = sqrt(((mx1-circumCenterX)*(mx1-circumCenterX))+((my1-circumCenterY)*(my1-circumCenterY)));
    
  int cx = ((((x1*x1)+(y1*y1))*(y2-y3))+(((x2*x2)+(y2*y2))*(y3-y1))+(((x3*x3)+(y3*y3))*(y1-y2)))/(2*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2)));
  int cy = ((((x1*x1)+(y1*y1))*(x3-x2))+(((x2*x2)+(y2*y2))*(x1-x3))+(((x3*x3)+(y3*y3))*(x2-x1)))/(2*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2)));
    
  eulers(pixels, circumCenterX, circumCenterY, cx, cy);

  int x = 0, y = r;
  int d = 3 - 2 * r;
  placePointOnCircle(pixels, circumCenterX, circumCenterY, x, y);
  while (y >= x) {
    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
    placePointOnCircle(pixels, circumCenterX, circumCenterY, x, y);
  }
}

void inCircle(int (*pixels)[800][3], int x1, int y1, int x2, int y2, int x3, int y3) {
  double sideLength1 = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  double sideLength2 = sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
  double sideLength3 = sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
  double incenterX = (sideLength2*x1+sideLength3*x2+sideLength1*x3)/(sideLength1+sideLength2+sideLength3);
  double incenterY = (sideLength2*y1+sideLength3*y2+sideLength1*y3)/(sideLength1+sideLength2+sideLength3);

  double s = 0.5*(sideLength1+sideLength2+sideLength3);
  double r = sqrt(((s-sideLength1)*(s-sideLength2)*(s-sideLength3))/s);
  double br = (sideLength1*sideLength2*sideLength3)/(4*r*s);
    
  double x = 0, y = r;
  double d = 3 - 2 * r;
  placePointOnCircle(pixels, round(incenterX), round(incenterY), round(x), round(y));
  while (y >= x) {
    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
    placePointOnCircle(pixels, round(incenterX), round(incenterY), round(x), round(y));
  }
}

void circle(int (*pixels)[800][3], double x1, double y1, double x2, double y2, double x3, double y3) {
  double sideLength1 = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  double sideLength2 = sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
  double sideLength3 = sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
  
  inCircle(pixels, x1, y1, x2, y2, x3, y3);
  ninePointCircle(pixels, x1, y1, x2, y2, x3, y3);
    
  double s = 0.5*(sideLength1+sideLength2+sideLength3);
  double r = sqrt(((s-sideLength1)*(s-sideLength2)*(s-sideLength3))/s);
  double br = (sideLength1*sideLength2*sideLength3)/(4*r*s);
    
  double circumCenterX = ((((x1*x1)+(y1*y1))*(y2-y3))+(((x2*x2)+(y2*y2))*(y3-y1))+(((x3*x3)+(y3*y3))*(y1-y2)))/(2*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2)));
  double circumCenterY = ((((x1*x1)+(y1*y1))*(x3-x2))+(((x2*x2)+(y2*y2))*(x1-x3))+(((x3*x3)+(y3*y3))*(x2-x1)))/(2*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2)));

  double x = 0, y = br;
  double d = 3 - 2 * br;
//   if (x <= 800 and y <= 800 and x >= 0 and y >= 0) { 
  placePointOnCircle(pixels, circumCenterX, circumCenterY, x, y);
//   }
  while (y >= x) {
    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
    placePointOnCircle(pixels, round(circumCenterX), round(circumCenterY), round(x), round(y));
  }
}

int main() {
  srand(time(0));
    
  int pixels[800][800][3];
  for (int i = 0; i < 800; i++) {
    for (int j = 0; j < 800; j++) {
      for (int k = 0; k < 3; k++) {
        pixels[i][j][k] = 255;
      }
    }
  }
  int pointsX[3];
  int pointsY[3];
  for (int k = 0; k < 3; k++) {
    double currPointX = (((double)rand()) / RAND_MAX * 800);
    pointsX[k] = currPointX;
    double currPointY = (((double)rand()) / RAND_MAX * 800);
    pointsY[k] = currPointY;
    // for (int i = 0; i < 3; i++) {
    //   pixels[currPointY][currPointX][i] = 0;
    // }
  }

  vertexSmallCircle(pixels, pointsX[0], pointsY[0]);
  vertexSmallCircle(pixels, pointsX[1], pointsY[1]);
  vertexSmallCircle(pixels, pointsX[2], pointsY[2]);

  if (pointsX[0] > pointsX[1] and pointsY[0] > pointsY[1]) {
    bothBigger(pixels, pointsX[0], pointsY[0], pointsX[1], pointsY[1]);
  } else if (pointsX[1] > pointsX[0] and pointsY[1] > pointsY[0]) {
    bothBigger(pixels, pointsX[1], pointsY[1], pointsX[0], pointsY[0]);
  } else if (pointsX[0] > pointsX[1] and pointsY[0] < pointsY[1]) {
    xBigger(pixels, pointsX[0], pointsY[0], pointsX[1], pointsY[1]);
  } else if (pointsX[1] > pointsX[0] and pointsY[1] < pointsY[0]) {
    xBigger(pixels, pointsX[1], pointsY[1], pointsX[0], pointsY[0]);
  }
   
  if (pointsX[0] > pointsX[2] and pointsY[0] > pointsY[2]) {
    bothBigger(pixels, pointsX[0], pointsY[0], pointsX[2], pointsY[2]);
  } else if (pointsX[2] > pointsX[0] and pointsY[2] > pointsY[0]) {
    bothBigger(pixels, pointsX[2], pointsY[2], pointsX[0], pointsY[0]);
  } else if (pointsX[0] > pointsX[2] and pointsY[0] < pointsY[2]) {
    xBigger(pixels, pointsX[0], pointsY[0], pointsX[2], pointsY[2]);
  } else if (pointsX[2] > pointsX[0] and pointsY[2] < pointsY[0]) {
    xBigger(pixels, pointsX[2], pointsY[2], pointsX[0], pointsY[0]);
  }
    
  if (pointsX[1] > pointsX[2] and pointsY[1] > pointsY[2]) {
    bothBigger(pixels, pointsX[1], pointsY[1], pointsX[2], pointsY[2]);
  } else if (pointsX[2] > pointsX[1] and pointsY[2] > pointsY[1]) {
    bothBigger(pixels, pointsX[2], pointsY[2], pointsX[1], pointsY[1]);
  } else if (pointsX[1] > pointsX[2] and pointsY[1] < pointsY[2]) {
    xBigger(pixels, pointsX[1], pointsY[1], pointsX[2], pointsY[2]);
  } else if (pointsX[2] > pointsX[1] and pointsY[2] < pointsY[1]) {
    xBigger(pixels, pointsX[2], pointsY[2], pointsX[1], pointsY[1]);
  }
    
  circle(pixels, pointsX[0], pointsY[0], pointsX[1], pointsY[1], pointsX[2], pointsY[2]);

  ofstream MyFile("triangle.ppm");
  MyFile << "P3 800 800 255" << endl;
  for (int i = 0; i < 800; i++) {
    for (int j = 0; j < 800; j++) {
      for (int k = 0; k < 3; k++) {
        MyFile << pixels[i][j][k];
        MyFile << " ";
      }
      MyFile << endl;
    }
  }
  MyFile.close();
}