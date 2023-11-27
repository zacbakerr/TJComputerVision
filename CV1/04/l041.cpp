#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>

using namespace std;

void placePointOnCircle(int (*pixels)[400][3], int ix, int iy, int x, int y) {
  for (int k = 0; k < 3; k++) {
    if ((iy + y) >= 0 && (ix + x) >= 0 && (iy + y) < 400 && (ix + x) < 400) {
      pixels[iy+y][ix+x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy + y) >= 0 && (ix - x) >= 0 && (iy + y) < 400 && (ix - x) < 400) {
      pixels[iy+y][ix-x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - y) >= 0 && (ix + x) >= 0 && (iy - y) < 400 && (ix + x) < 400) {
      pixels[iy-y][ix+x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - y) >= 0 && (ix - x) >= 0 && (iy - y) < 400 && (ix - x) < 400) {
      pixels[iy-y][ix-x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy + x) >= 0 && (ix + y) >= 0 && (iy + x) < 400 && (ix + y) < 400) {
      pixels[iy+x][ix+y][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy + x) >= 0 && (ix - y) >= 0 && (iy + x) < 400 && (ix - y) < 400) {
      pixels[iy+x][ix-y][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - x) >= 0 && (ix + y) >= 0 && (iy - x) < 400 && (ix + y) < 400) {
      pixels[iy-x][ix+y][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - x) >= 0 && (ix - y) >= 0 && (iy - x) < 400 && (ix - y) < 400) {
      pixels[iy-x][ix-y][k] = 0;
    }
  }
}

void placePointOnCircleRed(int (*pixels)[400][3], int ix, int iy, int x, int y) {
  if ((iy + y) >= 0 && (ix + x) >= 0 && (iy + y) < 400 && (ix + x) < 400) {
    pixels[iy+y][ix+x][0] = 255;
    pixels[iy+y][ix+x][1] = 0;
    pixels[iy+y][ix+x][2] = 0;
  }
  if ((iy + y) >= 0 && (ix - x) >= 0 && (iy + y) < 400 && (ix - x) < 400) {
    pixels[iy+y][ix-x][0] = 255;
    pixels[iy+y][ix-x][1] = 0;
    pixels[iy+y][ix-x][2] = 0;
  }
  if ((iy - y) >= 0 && (ix + x) >= 0 && (iy - y) < 400 && (ix + x) < 400) {
    pixels[iy-y][ix+x][0] = 255;
    pixels[iy-y][ix+x][1] = 0;
    pixels[iy-y][ix+x][2] = 0;
  }
  if ((iy - y) >= 0 && (ix - x) >= 0 && (iy - y) < 400 && (ix - x) < 400) {
    pixels[iy-y][ix-x][0] = 255;
    pixels[iy-y][ix-x][1] = 0;
    pixels[iy-y][ix-x][2] = 0;
  }
  if ((iy + x) >= 0 && (ix + y) >= 0 && (iy + x) < 400 && (ix + y) < 400) {
    pixels[iy+x][ix+y][0] = 255;
    pixels[iy+x][ix+y][1] = 0;
    pixels[iy+x][ix+y][2] = 0;
  }
  if ((iy + x) >= 0 && (ix - y) >= 0 && (iy + x) < 400 && (ix - y) < 400) {
    pixels[iy+x][ix-y][0] = 255;
    pixels[iy+x][ix-y][1] = 0;
    pixels[iy+x][ix-y][2] = 0;
  }
  if ((iy - x) >= 0 && (ix + y) >= 0 && (iy - x) < 400 && (ix + y) < 400) {
    pixels[iy-x][ix+y][0] = 255;
    pixels[iy-x][ix+y][1] = 0;
    pixels[iy-x][ix+y][2] = 0;
  }
  if ((iy - x) >= 0 && (ix - y) >= 0 && (iy - x) < 400 && (ix - y) < 400) {
    pixels[iy-x][ix-y][0] = 255;
    pixels[iy-x][ix-y][1] = 0;
    pixels[iy-x][ix-y][2] = 0;
  }
}

void connectPoints(int (*pixels)[400][3], int x1, int y1, int x0, int y0) {
  int dx = x1 - x0; 
  int dy = y1 - y0; 

  int step; 
  if (abs(dx) > abs(dy)) {
    step = abs(dx);   
  } else {
    step = abs(dy);   
  }

  float x_incr = (float)dx / step; 
  float y_incr = (float)dy / step; 

  float x = x0; 
  float y = y0; 

  for (int i = 0; i < step; i++) { 

    int tempx = round(x);
    int tempy = round(y);
    if (tempx == 400) {
      tempx = tempx - 1;
    }
    if (tempy == 400) {
      tempy = tempy - 1;
    }
    for (int k = 0; k < 3; k++) {
      pixels[tempy][tempx][k] = 0;
    }
    x += x_incr; 
    y += y_incr; 
  } 
}

class Point {
  public:
    double x, y;
    Point(double x, double y) {
      this->x = x;
      this->y = y;
    }
    Point() {
      this->x = 0;
      this->y = 0;
    }
};

bool operator<(const Point& first, const Point& second)
{
  return first.x < second.x;
}

class Node {
  public:
    Point val;
    Node* prev;
    Node* next;
    Node(Point val) {
      this->val = val;
      this->prev = NULL;
      this->next = NULL;
    }
};

vector<Point> createPoints() {
  srand(time(NULL));
  double x, y;
  ofstream myfile;
  vector<Point> points;
  myfile.open("points.txt");
  for (int i = 0; i < 60; i++) {
    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    Point p(x, y);
    points.push_back(p);
    myfile << setprecision(20) << x << "  " << y << endl;
  }
  return points;
};

void fillConvexHull(set<Point> points, Node* from, Node* to) {
  if (points.size() == 0) {
    return;
  }

  double slope = (from->val.y - to->val.y)/(from->val.x - to->val.x);
  double b = from->val.y - (slope * from->val.x);
    
  Point farthestPoint;
  double farthestDist = 0;
    
  set<Point>::iterator it;
    
  for (it = points.begin(); it != points.end(); ++it) {
    double perpSlope = 1/slope;
    double perpB = it->y - (perpSlope * it->x);
      
    double intersectionX = (b - perpB) / (perpSlope - slope);
    double intersectionY = (perpSlope * intersectionX) + perpB;
      
    double dist = sqrt(pow(intersectionX - it->x, 2) + pow(intersectionY - it->y, 2));
    if (dist > farthestDist) {
      farthestPoint = *it;
      farthestDist = dist;
    }
  }
    
  Node* addition = new Node(farthestPoint);
  from->next = addition;
  addition->prev = from;
  addition->next = to;
  to->prev = addition;
  
  set<Point> s1;
  set<Point> s2;
    
  slope = (from->val.y-addition->val.y)/(from->val.x-addition->val.x);
  b = from->val.y - (slope * from->val.x);
    
  for (it = points.begin(); it != points.end(); ++it) {
    if (((it->x * slope) + b) > (it->y)) {
      if (from->val.x > addition->val.x) {
        continue;
      } else {
        s1.insert(*it);
      }
    } else {
      if (from->val.x > addition->val.x) {
        s1.insert(*it);
      } else {
        continue;
      }
    }
  }
    
  slope = (addition->val.y-to->val.y)/(addition->val.x-to->val.x);
  b = to->val.y - (slope * to->val.x);
    
  for (it = points.begin(); it != points.end(); ++it) {
    if (((it->x * slope) + b) > (it->y)) {
      if (addition->val.x > to->val.x) {
        continue;
      } else {
        s2.insert(*it);
      }
    } else {
      if (addition->val.x > to->val.x) {
        s2.insert(*it);
      } else {
        continue;
      }
    }
  }
  s1.erase(farthestPoint);
  s2.erase(farthestPoint);
  fillConvexHull(s1, from, addition);
  fillConvexHull(s2, addition, to);
  return;
}

void part1() {
  vector<Point> points = createPoints();
  vector<Point> pointsSorted = points;
    
  // NEED TO ACCOUNT FOR SAME X VALUES (PICK THE HIGHEST Y VALUE)
    
  sort(pointsSorted.begin(), pointsSorted.end(), [](const Point &a, const Point &b) {
    return a.x < b.x;
  });
  
  Node* convexHullHead = new Node(pointsSorted[0]);
  Node* convexHullMiddle = new Node(pointsSorted[pointsSorted.size()-1]);
  Node* convexHullTail = new Node(pointsSorted[0]);
      
  convexHullHead->prev = NULL;
  convexHullHead->next = convexHullMiddle;
  convexHullMiddle->prev = convexHullHead;
  convexHullMiddle->next = convexHullTail;
  convexHullTail->prev = convexHullMiddle;
  convexHullTail->next = NULL;   
    
  set<Point> s1;
  set<Point> s2;
    
  double slope = (convexHullMiddle->val.y-convexHullHead->val.y)/(convexHullMiddle->val.x-convexHullHead->val.x);
  double b = convexHullHead->val.y - (slope * convexHullHead->val.x);
      
  for (int i = 0; i < points.size(); i++) {
    if (((points[i].x * slope) + b) > (points[i].y)) {
      s1.insert(points[i]);
    } else {
      s2.insert(points[i]);
    }
  }
    
  fillConvexHull(s1, convexHullHead, convexHullMiddle);
  fillConvexHull(s2, convexHullMiddle, convexHullTail);
    
  int pixels[400][400][3];
  for (int i = 0; i < 400; i++) {
    for (int j = 0; j < 400; j++) {
      for (int k = 0; k < 3; k++) {
        pixels[i][j][k] = 255;
      }
    }
  }
    
  for (int i = 0; i < points.size(); i++) {
    int r = 3;
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    placePointOnCircle(pixels, round(points[i].x * 400), round(points[i].y * 400), x, y); 
    while (y >= x) {   
      x++; 
      if (d > 0) { 
        y--;  
        d = d + 4 * (x - y) + 10; 
      } 
      else {
        d = d + 4 * x + 6;  
      }
      placePointOnCircle(pixels, round(points[i].x * 400), round(points[i].y * 400), x, y); 
    } 
  }
    
  while (convexHullHead->next != NULL) {
    if (convexHullHead->val.x == 0 && convexHullHead->val.y == 0) {
      convexHullHead = convexHullHead->next;
    }
    if (convexHullHead->next->val.x == 0 && convexHullHead->next->val.y == 0) {
      connectPoints(pixels, ((convexHullHead->val.x)*400), (convexHullHead->val.y*400), (convexHullHead->next->next->val.x*400), (convexHullHead->next->next->val.y*400));
    } else {
      connectPoints(pixels, ((convexHullHead->val.x)*400), (convexHullHead->val.y*400), (convexHullHead->next->val.x*400), (convexHullHead->next->val.y*400)); 
    }
      
    for (int i = 0; i < points.size(); i++) {
    int r = 3;
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    placePointOnCircleRed(pixels, round(convexHullHead->val.x * 400), round(convexHullHead->val.y * 400), x, y); 
    while (y >= x) {   
      x++; 
      if (d > 0) { 
        y--;  
        d = d + 4 * (x - y) + 10; 
      } 
      else {
        d = d + 4 * x + 6;  
      }
      placePointOnCircleRed(pixels, round(convexHullHead->val.x * 400), round(convexHullHead->val.y * 400), x, y); 
    } 
    }

    for (int i = 0; i < points.size(); i++) {
    int r = 4;
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    placePointOnCircleRed(pixels, round(convexHullHead->val.x * 400), round(convexHullHead->val.y * 400), x, y); 
    while (y >= x) {   
      x++; 
      if (d > 0) { 
        y--;  
        d = d + 4 * (x - y) + 10; 
      } 
      else {
        d = d + 4 * x + 6;  
      }
      placePointOnCircleRed(pixels, round(convexHullHead->val.x * 400), round(convexHullHead->val.y * 400), x, y); 
    } 
    }
    convexHullHead = convexHullHead->next;
  }
    
  ofstream MyFile("quickhull.ppm");
  MyFile << "P3 400 400 255" << endl;
  for (int i = 0; i < 400; i++) {
    for (int j = 0; j < 400; j++) {
      for (int k = 0; k < 3; k++) {
        MyFile << pixels[i][j][k];
        MyFile << " ";
      }
      MyFile << endl;
    }
  }
  MyFile.close();
};

int main() {
  part1();
};