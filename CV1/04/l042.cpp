#include <iostream> 
#include <stack>
#include <vector>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <set>

using namespace std;

void placePointOnCircle(int (*pixels)[400][3], int ix, int iy, int x, int y) {
  int indicies[10][2] = {{iy+y, ix+x}, {iy+y, ix-x}, {iy-y, ix+x}, {iy-y, ix-x}, {iy+x, ix+y}, {iy+x, ix-y}, {iy-x, ix+y}, {iy-x, ix-y}};
  for (int p = 0; p < 10; p++) {
    for (int k = 0; k < 3; k++) {
      if ((indicies[p][0]) >= 0 && (indicies[p][1]) >= 0 && indicies[p][0] < 400 && indicies[p][1] < 400) {
        pixels[indicies[p][0]][indicies[p][1]][k] = 0;
      }
    }
  }
}

void placePointOnCircleRed(int (*pixels)[400][3], int ix, int iy, int x, int y) {
  int indicies[10][2] = {{iy+y, ix+x}, {iy+y, ix-x}, {iy-y, ix+x}, {iy-y, ix-x}, {iy+x, ix+y}, {iy+x, ix-y}, {iy-x, ix+y}, {iy-x, ix-y}};
  for (int p = 0; p < 10; p++) {
    if (indicies[p][0] >= 0 && indicies[p][1] >= 0 && indicies[p][0] < 400 && indicies[p][1] < 400) {
      pixels[indicies[p][0]][indicies[p][1]][0] = 255;
      pixels[indicies[p][0]][indicies[p][1]][1] = 0;
      pixels[indicies[p][0]][indicies[p][1]][2] = 0;
    }
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

double ccw(Point nextToTop, Point top, Point curr) {
  double val = ((top.y - nextToTop.y) * (curr.x - top.x)) - ((top.x - nextToTop.x) * (curr.y - top.y));
  if (val == 0) return 0;  // collinear
  return (val > 0) ? 1: 2; // clock or counterclock wise
}

Point nextToTop(stack<Point> convexhull) {
  Point top = convexhull.top();
  convexhull.pop();
  Point val = convexhull.top();
  convexhull.push(top);
  return val;
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

void part0() {
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
};

int distSq(Point p1, Point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

bool operator<(const Point& first, const Point& second) {
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
  ifstream myfile;
  myfile.open("points.txt");
  double x, y;
  vector<Point> points;
  while (myfile >> x >> y) {
    Point p(x, y);
    points.push_back(p);
  }
    
  vector<Point> pointsSorted = points;
        
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

void part2() {
  ifstream myfile;
  myfile.open("points.txt");
  double x, y;
  vector<Point> points;
  while (myfile >> x >> y) {
    Point p(x, y);
    points.push_back(p);
  }
  
  Point lowy = points[0];
  double miny = points[0].y;
  
  for (int i = 1; i < points.size(); i++) {
    if (points[i].y < miny) {
      lowy = points[i];
      miny = points[i].y;
    }
  }
    
  sort(points.begin(), points.end(), [&](const Point &a, const Point &b) {
    double dist1 = sqrt(pow(a.y - lowy.y, 2) + pow(a.x - lowy.x, 2));
    double dist2 = sqrt(pow(b.y - lowy.y, 2) + pow(b.x - lowy.x, 2));
    double y1 = a.y - lowy.y;
    double y2 = b.y - lowy.y;
    double theta1 = asin(y1/dist1);
    double theta2 = asin(y2/dist2);
    if (a.x < lowy.x) {
      theta1 = 3.1415926 - theta1;
    }
    if (b.x < lowy.x) {
      theta2 = 3.1415926 - theta2;
    } 
    if (a.y == lowy.y) {
      return true;
    } else if (b.y == lowy.y) {
      return false;
    }
    return theta1 < theta2;
  });
        
  for (int i = 0; i < points.size(); i++) {
    double dist1 = sqrt(pow(points[i].y - lowy.y, 2) + pow(points[i].x - lowy.x, 2));
    double dist2 = sqrt(pow(points[i+1].y - lowy.y, 2) + pow(points[i+1].x - lowy.x, 2));
    double y1 = points[i].y - lowy.y;
    double y2 = points[i+1].y - lowy.y;
    double theta1 = asin(y1/dist1);
    double theta2 = asin(y2/dist2);
    if (points[i].x < lowy.x) {
      theta1 = 3.1415926 - theta1;
    }
    if (points[i+1].x < lowy.x) {
      theta2 = 3.1415926 - theta2;
    }
    if (theta1 == theta2) {
      if (dist1 > dist2) {
        points.erase(points.begin() + i + 1);
      } else {
        points.erase(points.begin() + i);
      }
    }
  }
    
  stack<Point> convexhull;
    
  for (int i = 0; i < points.size(); i++) {
    while ((convexhull.size() > 1) && (ccw(nextToTop(convexhull), convexhull.top(), points[i]) != 2)) {
      convexhull.pop();
    }
    convexhull.push(points[i]);
  }

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
    
  Point lastconnect = convexhull.top();

  while (!convexhull.empty()) {
    Point currpoint = convexhull.top();
    convexhull.pop();
    if (!convexhull.empty()) {
      Point nextpoint = convexhull.top();
      connectPoints(pixels, currpoint.x*400, currpoint.y*400, nextpoint.x*400, nextpoint.y*400);      
    } else {
      connectPoints(pixels, currpoint.x*400, currpoint.y*400, lastconnect.x*400, lastconnect.y*400);
    }
    for (int i = 0; i < points.size(); i++) {
      int r = 3;
      int x = 0, y = r; 
      int d = 3 - 2 * r; 
      placePointOnCircleRed(pixels, round(currpoint.x * 400), round(currpoint.y * 400), x, y); 
      while (y >= x) {   
        x++; 
        if (d > 0) { 
          y--;  
          d = d + 4 * (x - y) + 10; 
        } 
        else {
          d = d + 4 * x + 6;  
        }
        placePointOnCircleRed(pixels, round(currpoint.x * 400), round(currpoint.y * 400), x, y); 
      } 
    }
  }
    
  ofstream MyFile("grahamscan.ppm");
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
}

int main() {
  // part0();
  // part1();
  part2();
}