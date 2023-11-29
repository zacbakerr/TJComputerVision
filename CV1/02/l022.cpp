#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>
// #include <bits/stdc++.h>
#include <tuple>
#include <ctime>
#include <fstream>

using namespace std;

bool pointsWork(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
  double area123 = abs((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2))/2.0);
  double area124 = abs((x1*(y2-y4) + x2*(y4-y1) + x4*(y1-y2))/2.0);
  double area134 = abs((x1*(y3-y4) + x3*(y4-y1) + x4*(y1-y3))/2.0);
  double area234 = abs((x2*(y3-y4) + x3*(y4-y2) + x4*(y2-y3))/2.0);
  if (abs(area123-(area124 + area134 + area234))<0.0001) {
    return false;
  }
  if (abs(area124-(area123 + area134 + area234))<0.0001) {
    return false;
  }
  if (abs(area134-(area123 + area124 + area234))<0.0001) {
    return false;
  }
  if (abs(area234-(area123 + area124 + area134))<0.0001) {
    return false;
  }
  return true;
}

void part1() {
  srand(time(0));

  double pointsX[4];
  double pointsY[4];
  for (int k = 0; k < 3; k++) {
    double currPointX = (((double)rand()) / RAND_MAX);
    pointsX[k] = currPointX;
    double currPointY = (((double)rand()) / RAND_MAX);
    pointsY[k] = currPointY;
  }

  ofstream MyFile("log.txt");
  MyFile << "(" << setprecision(17) << pointsX[0] << ", " << pointsY[0] << ")" << endl;
  cout << "(" << setprecision(17) << pointsX[0] << ", " << pointsY[0] << ")" << endl;
  MyFile << "(" << pointsX[1] << ", " << pointsY[1] << ")" << endl;
  cout << "(" << pointsX[1] << ", " << pointsY[1] << ")" << endl;
  MyFile << "(" << pointsX[2] << ", " << pointsY[2] << ")" << endl;
  cout << "(" << pointsX[2] << ", " << pointsY[2] << ")" << endl;

  pointsX[3] = (((double)rand()) / RAND_MAX);
  pointsY[3] = (((double)rand()) / RAND_MAX);

  MyFile << "testing point (" << setprecision(17) << pointsX[3] << ", " << pointsY[3] << ")" << endl;
  cout << "testing point (" << setprecision(17) << pointsX[3] << ", " << pointsY[3] << ")" << endl;

  while (!pointsWork(pointsX[0], pointsY[0], pointsX[1], pointsY[1], pointsX[2], pointsY[2], pointsX[3], pointsY[3])) {
    pointsX[3] = (((double)rand()) / RAND_MAX);
    pointsY[3] = (((double)rand()) / RAND_MAX);
    MyFile << "testing point (" << setprecision(17) << pointsX[3] << ", " << pointsY[3] << ")" << endl;
    cout << "testing point (" << setprecision(17) << pointsX[3] << ", " << pointsY[3] << ")" << endl;
  }
  MyFile.close();

  ofstream MyFile2("points.txt");
  MyFile2 << "(" << setprecision(17) << pointsX[0] << ", " << pointsY[0] << "), " << "(" << pointsX[1] << ", " << pointsY[1] << "), " << "(" << pointsX[2] << ", " << pointsY[2] << "), " << "(" << pointsX[3] << ", " << pointsY[3] << ")";
  MyFile2.close();
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

void lineFromSlope(int (*pixels)[800][3], int x, int y, double rise, double run) {  
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

void bothBigger(int (*pixels)[800][3], int bigX, int bigY, int smallX, int smallY) {
  int deltaX = bigX - smallX;
  int deltaY = bigY - smallY;
  
  if (deltaX > deltaY) {
    int j = smallY;
    int e = deltaY - deltaX;

    for (int i = smallX; i < bigX; i++) {
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
    int j = smallX;
    int e = deltaX - deltaY;

    for (int i = smallY; i < bigY; i++) {
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

void xBigger(int (*pixels)[800][3], int bigX, int smallY, int smallX, int bigY) {
  int deltaX = bigX - smallX;
  int deltaY = smallY - bigY;
  if (abs(deltaX) > abs(deltaY)) {
    int j = bigY;
    int e = deltaY - deltaX;

    for (int i = smallX; i < bigX; i++) {
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
    int j = bigX;
    int e = deltaX - deltaY;

    for (int i = smallY; i < bigY; i++) {
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

void part2() {
  ifstream MyFile("points.txt");
  string line;
  getline(MyFile, line);
  string delimiter = ") , (";
  size_t pos = 0;
  string token;
  string points[4];
  int i = 0;
  while ((pos = line.find(delimiter)) != string::npos) {
    token = line.substr(0, pos);
    points[i] = token;
    line.erase(0, pos + delimiter.length());
    i++;
  }
  points[i] = line;
  points[0].erase(0, 1);
  points[3].erase(points[3].length()-1, 1);

  int pixels[800][800][3];
  for (int i = 0; i < 800; i++) {
    for (int j = 0; j < 800; j++) {
      for (int k = 0; k < 3; k++) {
        pixels[i][j][k] = 255;
      }
    }
  }
  MyFile.close();
  double pointsX[4];
  double pointsY[4];
  
  // split each point into x and y
  for (int i = 0; i < 4; i++) {
    int split = points[i].find(",");

    string x = points[i].substr(0, split);
    string y = points[i].substr(split+2, points[i].length());
    pointsX[i] = stod(x);
    pointsY[i] = stod(y);
  }

  int smallestSoFar = 9999999;
  int chosenZ = 0;
  int chosenT = 0;

  ofstream MyFile3("output.txt");
  MyFile3 << setprecision(17) << "(" << pointsX[0] << ", " << pointsY[0] << "), (" << pointsX[1] << ", " << pointsY[1] << "), (" << pointsX[2] << ", " << pointsY[2] << "), (" << pointsX[3] << ", " << pointsY[3] << ")" << endl;

  for (int z = 1; z < 4; z++) {
    for (int t = 0; t < 2; t++) {
      int p = 1;
      if (z == 1) {
        p = 2;
      }

      if (t == 1) {
        p = 3;
        if (z == 3) {
          p = 2;
        }
      }

      double slope1 = (pointsY[0]-pointsY[z])/(pointsX[0]-pointsX[z]);
      double slope2 = -1/slope1;
      double intersectionX = (pointsY[p]-pointsY[0]+slope1*pointsX[0]-slope2*pointsX[p])/(slope1-slope2);
      double intersectionY = slope1*(intersectionX-pointsX[0])+pointsY[0];

      double distance = (sqrt(pow(pointsX[0]*800-pointsX[z]*800, 2)+pow(pointsY[0]*800-pointsY[z]*800, 2)));

      double newX = (pointsX[p]*800) - sqrt(pow(distance, 2)/(1+pow(slope2, 2)));
      double newY = slope2*(newX-(intersectionX*800))+intersectionY*800;
      double distance2 = (sqrt(pow(newX-pointsX[p]*800, 2)+pow(newY-pointsY[p]*800, 2)));

      int q = 3;
      if ((z == 3) || (p == 3)) {
        q = 2;
        if (z == 2 || p == 2) {
          q = 1;
        }
      }

      // line 1
      lineFromSlope(pixels, round(pointsX[q]*800), round(pointsY[q]*800), round(pointsY[q]*800-newY), round(pointsX[q]*800-newX));
        
      // line 2
      slope1 = (pointsY[q]*800-newY)/(pointsX[q]*800-newX);
      slope2 = -1/slope1;
      intersectionX = (pointsY[0]-newY+slope1*newX-slope2*pointsX[0])/(slope1-slope2);
      intersectionY= slope1*(intersectionX-newX)+newY;
      lineFromSlope(pixels, round(pointsX[0]*800), round(pointsY[0]*800), round(intersectionY*800-pointsY[0]*800), round(intersectionX*800-pointsX[0]*800));

      // calulate intersection of line 1 and line 2
      double b1 = pointsY[q]*800 - slope1*pointsX[q]*800;
      double b2 = pointsY[0]*800 - slope2*pointsX[0]*800;  
      double intersectionX1 = (b2-b1)/(slope1-slope2);
      double intersectionY1 = slope1*intersectionX1+b1;

      // line 3
      slope1 = (pointsY[q]*800-newY)/(pointsX[q]*800-newX);
      slope2 = -1/slope1;
      intersectionX = (pointsY[z]-newY+slope1*newX-slope2*pointsX[z])/(slope1-slope2);
      intersectionY = slope1*(intersectionX-newX)+newY;
      lineFromSlope(pixels, round(pointsX[z]*800), round(pointsY[z]*800), round(intersectionY*800-pointsY[z]*800), round(intersectionX*800-pointsX[z]*800)); 

      // calulate intersection of line 1 and line 3
      b1 = pointsY[q]*800 - slope1*pointsX[q]*800;
      b2 = pointsY[z]*800 - slope2*pointsX[z]*800;
      double intersectionX2 = ((b2-b1)/(slope1-slope2));
      double intersectionY2 = (slope1*intersectionX2+b1);

      int ix2 = round(intersectionX2);
      int iy2 = round(intersectionY2);

      // line 4
      slope1 = slope2;
      slope2 = -1/slope1;
      intersectionX = (pointsY[p]-newY+slope1*newX-slope2*pointsX[p])/(slope1-slope2);
      intersectionY = slope1*(intersectionX-newX)+newY;
      cout << pointsX[p]*800 << " " << pointsY[p]*800 << endl;
      lineFromSlope(pixels, round(pointsX[p]*800), round(pointsY[p]*800), round(intersectionY*800-pointsY[p]*800), round(intersectionX*800-pointsX[p]*800)); 

      // calulate intersection of line 2 and line 4
      b1 = pointsY[0]*800 - slope1*pointsX[0]*800;
      b2 = pointsY[p]*800 - slope2*pointsX[p]*800;
      double intersectionX3 = (b2-b1)/(slope1-slope2);
      double intersectionY3 = slope1*intersectionX3+b1;

      // calulate intersection of line 3 and line 4
      b1 = pointsY[z]*800 - slope1*pointsX[z]*800;
      b2 = pointsY[p]*800 - slope2*pointsX[p]*800;
      double intersectionX4 = (b2-b1)/(slope1-slope2);
      double intersectionY4 = slope1*intersectionX4+b1;   

      if (intersectionX1 >= 0 && intersectionY1 >= 0) {
        int x = 0, y = 4;
        int d = 3 - 2 * 4;
        placePointOnCircle(pixels, round(intersectionX1), round(intersectionY1), x, y);
        while (y >= x) {
          x++;
          if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
          } else {
            d = d + 4 * x + 6;
          }
          placePointOnCircle(pixels, round(intersectionX1), round(intersectionY1), x, y);
        } 
      }

      if (ix2 >= 0 && iy2 >= 0) {
        int x = 0, y = 4;
        int d = 3 - 2 * 4;
        placePointOnCircle(pixels, ix2, iy2, x, y);
        while (y >= x) {
          x++;
          if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
          } else {
            d = d + 4 * x + 6;
          }
          placePointOnCircle(pixels, ix2, iy2, x, y);
        } 
      }
      
      if (intersectionX3 >= 0 && intersectionY3 >= 0) {
        int x = 0, y = 4;
        int d = 3 - 2 * 4;
        placePointOnCircle(pixels, round(intersectionX3), round(intersectionY3), x, y);
        while (y >= x) {
          x++;
          if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
          } else {
            d = d + 4 * x + 6;
          }
          placePointOnCircle(pixels, round(intersectionX3), round(intersectionY3), x, y);
        } 
      }

      if (intersectionX4 >= 0 && intersectionY4 >= 0) {
        int x = 0, y = 4;
        int d = 3 - 2 * 4;
        placePointOnCircle(pixels, round(intersectionX4), round(intersectionY4), x, y);
        while (y >= x) {
          x++;
          if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
          } else {
            d = d + 4 * x + 6;
          }
          placePointOnCircle(pixels, round(intersectionX4), round(intersectionY4), x, y);
        } 
      }


      double distance3 = (sqrt(pow(intersectionX1-ix2, 2)+pow(intersectionY1-iy2, 2)));
      double area = pow(distance3, 2);
      if (area < smallestSoFar) {
        smallestSoFar = area;
        chosenZ = z;
        chosenT = t;
      }
      // find area scaled down by 800
      area = pow(distance3/800, 2);

      MyFile3 << setprecision(17) << "(" << intersectionX1/800 << ", " << intersectionY1/800 << "), (" << intersectionX2/800 << ", " << intersectionY2/800 << "), (" << intersectionX3/800 << ", " << intersectionY3/800 << "), (" << intersectionX4/800 << ", " << intersectionY4/800 << ") Area = " << area << endl;
      for (int i = 0; i < 800; i++) {
        for (int j = 0; j < 800; j++) {
          for (int k = 0; k < 3; k++) {
            pixels[i][j][k] = 255;
          }
        }
      }
    }
  }

  int z = chosenZ;
  int t = chosenT;

  int p = 1;
  if (z == 1) {
    p = 2;
  }

  if (t == 1) {
    p = 3;
    if (z == 3) {
      p = 2;
    }
  }

  double slope1 = (pointsY[0]-pointsY[z])/(pointsX[0]-pointsX[z]);
  double slope2 = -1/slope1;
  double intersectionX = (pointsY[p]-pointsY[0]+slope1*pointsX[0]-slope2*pointsX[p])/(slope1-slope2);
  double intersectionY = slope1*(intersectionX-pointsX[0])+pointsY[0];

  double distance = (sqrt(pow(pointsX[0]*800-pointsX[z]*800, 2)+pow(pointsY[0]*800-pointsY[z]*800, 2)));

  double newX = (pointsX[p]*800) - sqrt(pow(distance, 2)/(1+pow(slope2, 2)));
  double newY = slope2*(newX-(intersectionX*800))+intersectionY*800;
  double distance2 = (sqrt(pow(newX-pointsX[p]*800, 2)+pow(newY-pointsY[p]*800, 2)));

  int q = 3;
  if ((z == 3) || (p == 3)) {
    q = 2;
    if (z == 2 || p == 2) {
      q = 1;
    }
  }

  // line 1
  lineFromSlope(pixels, round(pointsX[q]*800), round(pointsY[q]*800), round(pointsY[q]*800-newY), round(pointsX[q]*800-newX));
    
  // line 2
  slope1 = (pointsY[q]*800-newY)/(pointsX[q]*800-newX);
  slope2 = -1/slope1;
  intersectionX = (pointsY[0]-newY+slope1*newX-slope2*pointsX[0])/(slope1-slope2);
  intersectionY= slope1*(intersectionX-newX)+newY;
  lineFromSlope(pixels, round(pointsX[0]*800), round(pointsY[0]*800), round(intersectionY*800-pointsY[0]*800), round(intersectionX*800-pointsX[0]*800));

  // calulate intersection of line 1 and line 2
  double b1 = pointsY[q]*800 - slope1*pointsX[q]*800;
  double b2 = pointsY[0]*800 - slope2*pointsX[0]*800;  
  double intersectionX1 = (b2-b1)/(slope1-slope2);
  double intersectionY1 = slope1*intersectionX1+b1;

  // line 3
  slope1 = (pointsY[q]*800-newY)/(pointsX[q]*800-newX);
  slope2 = -1/slope1;
  intersectionX = (pointsY[z]-newY+slope1*newX-slope2*pointsX[z])/(slope1-slope2);
  intersectionY = slope1*(intersectionX-newX)+newY;
  lineFromSlope(pixels, round(pointsX[z]*800), round(pointsY[z]*800), round(intersectionY*800-pointsY[z]*800), round(intersectionX*800-pointsX[z]*800)); 

  // calulate intersection of line 1 and line 3
  b1 = pointsY[q]*800 - slope1*pointsX[q]*800;
  b2 = pointsY[z]*800 - slope2*pointsX[z]*800;
  int intersectionX2 = round((b2-b1)/(slope1-slope2));
  int intersectionY2 = round(slope1*intersectionX2+b1);

  // line 4
  slope1 = slope2;
  slope2 = -1/slope1;
  intersectionX = (pointsY[p]-newY+slope1*newX-slope2*pointsX[p])/(slope1-slope2);
  intersectionY = slope1*(intersectionX-newX)+newY;
  lineFromSlope(pixels, round(pointsX[p]*800), round(pointsY[p]*800), round(intersectionY*800-pointsY[p]*800), round(intersectionX*800-pointsX[p]*800)); 

  // calulate intersection of line 2 and line 4
  b1 = pointsY[0]*800 - slope1*pointsX[0]*800;
  b2 = pointsY[p]*800 - slope2*pointsX[p]*800;
  double intersectionX3 = (b2-b1)/(slope1-slope2);
  double intersectionY3 = slope1*intersectionX3+b1;

  // calulate intersection of line 3 and line 4
  b1 = pointsY[z]*800 - slope1*pointsX[z]*800;
  b2 = pointsY[p]*800 - slope2*pointsX[p]*800;
  double intersectionX4 = (b2-b1)/(slope1-slope2);
  double intersectionY4 = slope1*intersectionX4+b1;   

  if (intersectionX1 >= 0 && intersectionY1 >= 0) {
    int x = 0, y = 3;
    int d = 3 - 2 * 3;
    placePointOnCircle(pixels, round(intersectionX1), round(intersectionY1), x, y);
    while (y >= x) {
      x++;
      if (d > 0) {
        y--;
        d = d + 4 * (x - y) + 10;
      } else {
        d = d + 4 * x + 6;
      }
      placePointOnCircle(pixels, round(intersectionX1), round(intersectionY1), x, y);
    } 
  }

  if (intersectionX2 >= 0 && intersectionY2 >= 0) {
    int x = 0, y = 3;
    int d = 3 - 2 * 3;
    placePointOnCircle(pixels, intersectionX2, intersectionY2, x, y);
    while (y >= x) {
      x++;
      if (d > 0) {
        y--;
        d = d + 4 * (x - y) + 10;
      } else {
        d = d + 4 * x + 6;
      }
      placePointOnCircle(pixels, intersectionX2, intersectionY2, x, y);
    } 
  }
  
  if (intersectionX3 >= 0 && intersectionY3 >= 0) {
    int x = 0, y = 3;
    int d = 3 - 2 * 3;
    placePointOnCircle(pixels, round(intersectionX3), round(intersectionY3), x, y);
    while (y >= x) {
      x++;
      if (d > 0) {
        y--;
        d = d + 4 * (x - y) + 10;
      } else {
        d = d + 4 * x + 6;
      }
      placePointOnCircle(pixels, round(intersectionX3), round(intersectionY3), x, y);
    } 
  }

  if (intersectionX4 >= 0 && intersectionY4 >= 0) {
    int x = 0, y = 3;
    int d = 3 - 2 * 3;
    placePointOnCircle(pixels, round(intersectionX4), round(intersectionY4), x, y);
    while (y >= x) {
      x++;
      if (d > 0) {
        y--;
        d = d + 4 * (x - y) + 10;
      } else {
        d = d + 4 * x + 6;
      }
      placePointOnCircle(pixels, round(intersectionX4), round(intersectionY4), x, y);
    } 
  }


  for (int i = 0; i < 4; i++) {
    int x = 0, y = 3;
    int d = 3 - 2 * 3;
    placePointOnCircle(pixels, round(pointsX[i]*800), round(pointsY[i]*800), x, y);
    while (y >= x) {
      x++;
      if (d > 0) {
        y--;
        d = d + 4 * (x - y) + 10;
      } else {
        d = d + 4 * x + 6;
      }
      placePointOnCircle(pixels, round(pointsX[i]*800), round(pointsY[i]*800), x, y);
    }
  }

  ofstream MyFile2("output.ppm");
  MyFile2 << "P3 800 800 255" << endl;
  for (int i = 0; i < 800; i++) {
    for (int j = 0; j < 800; j++) {
      for (int k = 0; k < 3; k++) {
        MyFile2 << pixels[i][j][k];
        MyFile2 << " ";
      }
      MyFile2 << endl;
    }
  }
  MyFile2.close();
}

int main() {
  // part1();
  part2();
}