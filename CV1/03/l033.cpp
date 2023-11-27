#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <iomanip>
#include <tuple>
#include <algorithm>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

void placePointOnCircle(int (*pixels)[800][3], int ix, int iy, int x, int y) {
  for (int k = 0; k < 3; k++) {
    if ((iy + y) >= 0 && (ix + x) >= 0 && (iy + y) < 800 && (ix + x) < 800) {
      pixels[iy+y][ix+x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy + y) >= 0 && (ix - x) >= 0 && (iy + y) < 800 && (ix - x) < 800) {
      pixels[iy+y][ix-x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - y) >= 0 && (ix + x) >= 0 && (iy - y) < 800 && (ix + x) < 800) {
      pixels[iy-y][ix+x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - y) >= 0 && (ix - x) >= 0 && (iy - y) < 800 && (ix - x) < 800) {
      pixels[iy-y][ix-x][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy + x) >= 0 && (ix + y) >= 0 && (iy + x) < 800 && (ix + y) < 800) {
      pixels[iy+x][ix+y][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy + x) >= 0 && (ix - y) >= 0 && (iy + x) < 800 && (ix - y) < 800) {
      pixels[iy+x][ix-y][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - x) >= 0 && (ix + y) >= 0 && (iy - x) < 800 && (ix + y) < 800) {
      pixels[iy-x][ix+y][k] = 0;
    }
  }
  for (int k = 0; k < 3; k++) {
    if ((iy - x) >= 0 && (ix - y) >= 0 && (iy - x) < 800 && (ix - y) < 800) {
      pixels[iy-x][ix-y][k] = 0;
    }
  }
}

void placePointOnCircleRed(int (*pixels)[800][3], int ix, int iy, int x, int y) {
  if ((iy + y) >= 0 && (ix + x) >= 0 && (iy + y) < 800 && (ix + x) < 800) {
    pixels[iy+y][ix+x][0] = 255;
    pixels[iy+y][ix+x][1] = 0;
    pixels[iy+y][ix+x][2] = 0;
  }
  if ((iy + y) >= 0 && (ix - x) >= 0 && (iy + y) < 800 && (ix - x) < 800) {
    pixels[iy+y][ix-x][0] = 255;
    pixels[iy+y][ix-x][1] = 0;
    pixels[iy+y][ix-x][2] = 0;
  }
  if ((iy - y) >= 0 && (ix + x) >= 0 && (iy - y) < 800 && (ix + x) < 800) {
    pixels[iy-y][ix+x][0] = 255;
    pixels[iy-y][ix+x][1] = 0;
    pixels[iy-y][ix+x][2] = 0;
  }
  if ((iy - y) >= 0 && (ix - x) >= 0 && (iy - y) < 800 && (ix - x) < 800) {
    pixels[iy-y][ix-x][0] = 255;
    pixels[iy-y][ix-x][1] = 0;
    pixels[iy-y][ix-x][2] = 0;
  }
  if ((iy + x) >= 0 && (ix + y) >= 0 && (iy + x) < 800 && (ix + y) < 800) {
    pixels[iy+x][ix+y][0] = 255;
    pixels[iy+x][ix+y][1] = 0;
    pixels[iy+x][ix+y][2] = 0;
  }
  if ((iy + x) >= 0 && (ix - y) >= 0 && (iy + x) < 800 && (ix - y) < 800) {
    pixels[iy+x][ix-y][0] = 255;
    pixels[iy+x][ix-y][1] = 0;
    pixels[iy+x][ix-y][2] = 0;
  }
  if ((iy - x) >= 0 && (ix + y) >= 0 && (iy - x) < 800 && (ix + y) < 800) {
    pixels[iy-x][ix+y][0] = 255;
    pixels[iy-x][ix+y][1] = 0;
    pixels[iy-x][ix+y][2] = 0;
  }
  if ((iy - x) >= 0 && (ix - y) >= 0 && (iy - x) < 800 && (ix - y) < 800) {
    pixels[iy-x][ix-y][0] = 255;
    pixels[iy-x][ix-y][1] = 0;
    pixels[iy-x][ix-y][2] = 0;
  }
}

class Point {
  public:
    double x, y;
    Point(double x, double y) {
      this->x = x;
      this->y = y;
    }
};

void part0() {
  ofstream myfile;
  myfile.open("results.txt");
  myfile.close();    
   
  string answer;
  cout << "Would you like to generate points? Yes or No." << endl;
  cin >> answer;

  if (answer == "Yes") {
    string answer2;
    cout << "How many points would you like to generate?" << endl;
    cin >> answer2;
    srand(time(NULL));
    double x, y;
    ofstream myfile;
    myfile.open("points.txt");
    for (int i = 0; i < stoi(answer2); i++) {
      x = (double)rand() / RAND_MAX;
      y = (double)rand() / RAND_MAX;
      myfile << setprecision(17) << x << " " << y << endl;
    }
  }

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
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  double min = 100000;
  double minx, miny, minx2, miny2;
  vector<Point>::iterator it1;
  vector<Point>::iterator it2;
  for (it1 = points.begin(); it1 != points.end(); it1++) {
    for (it2 = points.begin(); it2 != points.end(); it2++) {
      if (it1 != it2) {
        double dist = sqrt(pow((it1->x - it2->x), 2) + pow((it1->y - it2->y), 2));
        if (dist < min) {
          min = dist;
          minx = it1->x;
          miny = it1->y;
          minx2 = it2->x;
          miny2 = it2->y;
        }
      }
    }
  }
  end = clock();

  int pixels[800][800][3];
  for (int i = 0; i < 800; i++) {
    for (int j = 0; j < 800; j++) {
      for (int k = 0; k < 3; k++) {
        pixels[i][j][k] = 255;
      }
    }
  }

  for (it1 = points.begin(); it1 != points.end(); it1++) {
    int x = 0, y = 3;
    int d = 3 - 2 * 3;
    placePointOnCircle(pixels, round(it1->x * 800), round(it1->y * 800), x, y);
    while (y >= x) {
      x++;
      if (d > 0) {
        y--;
        d = d + 4 * (x - y) + 10;
      } else {
        d = d + 4 * x + 6;
      }
      placePointOnCircle(pixels, round(it1->x * 800), round(it1->y * 800), x, y);
    } 
  }
  for (it1 = points.begin(); it1 != points.end(); it1++) {
    int x = 0, y = 2;
    int d = 3 - 2 * 2;
    placePointOnCircle(pixels, round(it1->x * 800), round(it1->y * 800), x, y);
    while (y >= x) {
      x++;
      if (d > 0) {
        y--;
        d = d + 4 * (x - y) + 10;
      } else {
        d = d + 4 * x + 6;
      }
      placePointOnCircle(pixels, round(it1->x * 800), round(it1->y * 800), x, y);
    } 
  }

  int x2 = 0, y2 = 3;
  int d = 3 - 2 * 3;
  placePointOnCircleRed(pixels, round(minx * 800), round(miny * 800), x2, y2);
  while (y2 >= x2) {
    x2++;
    if (d > 0) {
      y2--;
      d = d + 4 * (x2 - y2) + 10;
    } else {
      d = d + 4 * x2 + 6;
    }
    placePointOnCircleRed(pixels, round(minx * 800), round(miny * 800), x2, y2);
  } 

  x2 = 0, y2 = 3;
  d = 3 - 2 * 3;
  placePointOnCircleRed(pixels, round(minx2 * 800), round(miny2 * 800), x2, y2);
  while (y2 >= x2) {
    x2++;
    if (d > 0) {
      y2--;
      d = d + 4 * (x2 - y2) + 10;
    } else {
      d = d + 4 * x2 + 6;
    }
    placePointOnCircleRed(pixels, round(minx2 * 800), round(miny2 * 800), x2, y2);
  } 
  x2 = 0, y2 = 2;
  d = 3 - 2 * 2;
  placePointOnCircleRed(pixels, round(minx * 800), round(miny * 800), x2, y2);
  while (y2 >= x2) {
    x2++;
    if (d > 0) {
      y2--;
      d = d + 4 * (x2 - y2) + 10;
    } else {
      d = d + 4 * x2 + 6;
    }
    placePointOnCircleRed(pixels, round(minx * 800), round(miny * 800), x2, y2);
  } 

  x2 = 0, y2 = 2;
  d = 3 - 2 * 2;
  placePointOnCircleRed(pixels, round(minx2 * 800), round(miny2 * 800), x2, y2);
  while (y2 >= x2) {
    x2++;
    if (d > 0) {
      y2--;
      d = d + 4 * (x2 - y2) + 10;
    } else {
      d = d + 4 * x2 + 6;
    }
    placePointOnCircleRed(pixels, round(minx2 * 800), round(miny2 * 800), x2, y2);
  } 
  cout << "Part 1: ";
  cout << setprecision(17) << "The closest pair of points is (" << minx << ", " << miny << ") && (" << minx2 << ", " << miny2 << ") with distance " << min << ". It took " << (double)(end - start) / CLOCKS_PER_SEC << " seconds to run." << endl;
  cout << endl;

  ofstream myfile2;
  myfile2.open("results.txt");
  myfile2 << setprecision(17) << "Part 1 obtained pair of points: (" << minx << ", " << miny << ")" << minx2 << ", " << miny2 << ") with a distance " << min << ". It took " << (double)(end - start) / CLOCKS_PER_SEC << " seconds to run." << endl;

  ofstream image;
  image.open("points.ppm");
  image << "P3 800 800 255 ";
  for (int i = 0; i < 800; i++) {
    for (int j = 0; j < 800; j++) {
      for (int k = 0; k < 3; k++) {
        image << pixels[i][j][k] << " ";
      }
    }
  }
  image.close();
}

tuple<double, Point, Point> part2recursion(vector<Point> points) {
  if (points.size() == 2) {
    tuple<double, Point, Point> t(sqrt(pow((points[0].x - points[1].x), 2) + pow((points[0].y - points[1].y), 2)), points[0], points[1]);
    return t;
  } else if (points.size() == 3) {
    double dist1 = sqrt(pow((points[0].x - points[1].x), 2) + pow((points[0].y - points[1].y), 2));
    double dist2 = sqrt(pow((points[0].x - points[2].x), 2) + pow((points[0].y - points[2].y), 2));
    double dist3 = sqrt(pow((points[1].x - points[2].x), 2) + pow((points[1].y - points[2].y), 2));
    if (dist1 < dist2 && dist1 < dist3) {
      tuple<double, Point, Point> t(dist1, points[0], points[1]);
      return t;
    } else if (dist2 < dist1 && dist2 < dist3) {
      tuple<double, Point, Point> t(dist2, points[0], points[2]);
      return t;
    } else {
      tuple<double, Point, Point> t(dist3, points[1], points[2]);
      return t;
    }
  }

  vector<Point> pointsLeft;
  vector<Point> pointsRight;
  for (int i = 0; i < points.size(); i++) {
    if (i < points.size() / 2) {
      pointsLeft.push_back(points[i]);
    } else {
      pointsRight.push_back(points[i]);
    }
  }

  tuple<double, Point, Point> mindistleft = (part2recursion(pointsLeft));
  tuple<double, Point, Point> mindistright = (part2recursion(pointsRight));
  tuple<double, Point, Point> mindist(0, Point(0, 0), Point(0, 0));
  if (get<0>(mindistleft) < get<0>(mindistright)) {
    mindist = mindistleft;
  } else {
    mindist = mindistright;
  }

  vector<Point> pointsMiddle;
  for (int i = 0; i < points.size(); i++) {
    if (abs(points[i].x - points[points.size() / 2].x) < get<0>(mindist)) {
      pointsMiddle.push_back(points[i]);
    }
  }

  for (int i = 0; i < pointsMiddle.size(); i++) {
    for (int j = i + 1; j < pointsMiddle.size(); j++) {
      double dist = sqrt(pow((pointsMiddle[i].x - pointsMiddle[j].x), 2) + pow((pointsMiddle[i].y - pointsMiddle[j].y), 2));
      if (dist < get<0>(mindist)) {
        tuple<double, Point, Point> t(dist, pointsMiddle[i], pointsMiddle[j]);
        mindist = t;
      }
    }
  }

  return mindist;
}

void part2() {
  ifstream myfile;
  myfile.open("points.txt");
  double x, y;
  vector<Point> points;
  while (myfile >> x >> y) {
    Point p(x, y);
    points.push_back(p);
  }

  clock_t start, end;
  double cpu_time_used;
  start = clock();
  vector<Point> pointsSorted = points;
  sort(pointsSorted.begin(), pointsSorted.end(), [](const Point &a, const Point &b) {
    return a.x < b.x;
  });

  vector<Point> pointsLeft;
  vector<Point> pointsRight;
  for (int i = 0; i < pointsSorted.size(); i++) {
    if (i < pointsSorted.size() / 2) {
      pointsLeft.push_back(pointsSorted[i]);
    } else {
      pointsRight.push_back(pointsSorted[i]);
    }
  }

  tuple<double, Point, Point> mindistleft = part2recursion(pointsLeft);
  tuple<double, Point, Point> mindistright = part2recursion(pointsRight);
  tuple<double, Point, Point> mindist(0, Point(0, 0), Point(0, 0));
  if (get<0>(mindistleft) < get<0>(mindistright)) {
    mindist = mindistleft;
  } else {
    mindist = mindistright;
  }
  end = clock();
  cout << "Part 2: ";
  cout << setprecision(17) << "The closest pair of points is (" << (get<1>(mindist).x) << ", " << (get<1>(mindist).y) << ") && (" << (get<2>(mindist).x) << ", " << (get<2>(mindist).y) << ") with a distance " << (get<0>(mindist)) << ". It took " << (double)(end - start) / CLOCKS_PER_SEC << " seconds to run." << endl;
  cout << endl;

  ofstream myfile2;
  myfile2.open("results.txt", std::ios_base::app);
  myfile2 << setprecision(17) << "Part 2 obtained pair of points: (" << (get<1>(mindist).x) << ", " << (get<1>(mindist).y) << ") && (" << (get<2>(mindist).x) << ", " << (get<2>(mindist).y) << ") with a distance " << (get<0>(mindist)) << ". It took " << (double)(end - start) / CLOCKS_PER_SEC << " seconds to run." << endl;
}

tuple<double, Point, Point> part3recursion(vector<Point> points) {
  if (points.size() == 2) {
    tuple<double, Point, Point> t(sqrt(pow((points[0].x - points[1].x), 2) + pow((points[0].y - points[1].y), 2)), points[0], points[1]);
    return t;
  } else if (points.size() == 3) {
    double dist1 = sqrt(pow((points[0].x - points[1].x), 2) + pow((points[0].y - points[1].y), 2));
    double dist2 = sqrt(pow((points[0].x - points[2].x), 2) + pow((points[0].y - points[2].y), 2));
    double dist3 = sqrt(pow((points[1].x - points[2].x), 2) + pow((points[1].y - points[2].y), 2));
    if (dist1 < dist2 && dist1 < dist3) {
      tuple<double, Point, Point> t(dist1, points[0], points[1]);
      return t;
    } else if (dist2 < dist1 && dist2 < dist3) {
      tuple<double, Point, Point> t(dist2, points[0], points[2]);
      return t;
    } else {
      tuple<double, Point, Point> t(dist3, points[1], points[2]);
      return t;
    }
  }

  vector<Point> pointsLeft;
  vector<Point> pointsRight;
  for (int i = 0; i < points.size(); i++) {
    if (i < points.size() / 2) {
      pointsLeft.push_back(points[i]);
    } else {
      pointsRight.push_back(points[i]);
    }
  }

  tuple<double, Point, Point> mindistleft = (part3recursion(pointsLeft));
  tuple<double, Point, Point> mindistright = (part3recursion(pointsRight));
  tuple<double, Point, Point> mindist(0, Point(0, 0), Point(0, 0));
  if (get<0>(mindistleft) < get<0>(mindistright)) {
    mindist = mindistleft;
  } else {
    mindist = mindistright;
  }

  vector<Point> vectorStrip;
  for (int i = 0; i < points.size(); i++) {
    if (abs(points[i].x - points[points.size() / 2].x) < get<0>(mindist)) {
      vectorStrip.push_back(points[i]);
    }
  }

  if (vectorStrip.size() > 15) {
    sort(vectorStrip.begin(), vectorStrip.end(), [](const Point &a, const Point &b) {
      return a.y < b.y;
    });
  }

  for (int i = 0; i < vectorStrip.size(); i++) {
    for (int j = i + 1; vectorStrip[i].y + get<0>(mindist) > vectorStrip[j].y && j < vectorStrip.size() && j < i + 15; j++) {
      double dist = sqrt(pow((vectorStrip[i].x - vectorStrip[j].x), 2) + pow((vectorStrip[i].y - vectorStrip[j].y), 2));
      if (dist < get<0>(mindist)) {
        tuple<double, Point, Point> t(dist, vectorStrip[i], vectorStrip[j]);
        mindist = t;
      }
    }
  }

  return mindist;
}

void part3() {
  ifstream myfile;
  myfile.open("points.txt");
  double x, y;
  vector<Point> points;
  while (myfile >> x >> y) {
    Point p(x, y);
    points.push_back(p);
  }

  clock_t start, end;
  double cpu_time_used;
  start = clock();
  vector<Point> pointsSorted = points;
  sort(pointsSorted.begin(), pointsSorted.end(), [](const Point &a, const Point &b) {
    return a.x < b.x;
  });

  vector<Point> pointsLeft;
  vector<Point> pointsRight;
  for (int i = 0; i < pointsSorted.size(); i++) {
    if (i < pointsSorted.size() / 2) {
      pointsLeft.push_back(pointsSorted[i]);
    } else {
      pointsRight.push_back(pointsSorted[i]);
    }
  }

  tuple<double, Point, Point> mindistleft = part3recursion(pointsLeft);
  tuple<double, Point, Point> mindistright = part3recursion(pointsRight);
  tuple<double, Point, Point> mindist(0, Point(0, 0), Point(0, 0));
  if (get<0>(mindistleft) < get<0>(mindistright)) {
    mindist = mindistleft;
  } else {
    mindist = mindistright;
  }
  end = clock();
  cout << "Part 3: ";
  cout << setprecision(17) << "The closest pair of points is (" << (get<1>(mindist).x) << ", " << (get<1>(mindist).y) << ") && (" << (get<2>(mindist).x) << ", " << (get<2>(mindist).y) << ") with a distance " << (get<0>(mindist)) << ". It took " << (double)(end - start) / CLOCKS_PER_SEC << " seconds to run." << endl;

  ofstream myfile2;
  myfile2.open("results.txt", std::ios_base::app);
  myfile2 << setprecision(17) << "Part 3 obtained pair of points: (" << (get<1>(mindist).x) << ", " << (get<1>(mindist).y) << ") && (" << (get<2>(mindist).x) << ", " << (get<2>(mindist).y) << ") with a distance " << (get<0>(mindist)) << ". It took " << (double)(end - start) / CLOCKS_PER_SEC << " seconds to run." << endl;
}

int main() {
  part0();
  part1();  
  part2();
  part3();
}