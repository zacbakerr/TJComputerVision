#include<iostream>
#include <array>
#include <random>
#include <cmath>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <algorithm>
#include<cstdlib>
#include <utility>
#include <unordered_map>

using namespace std;

int width;
int height;



    vector<vector<double>> og;
    vector<vector<double>> Gx;
    vector<vector<double>> Gy;


class RGBColor {
private:
    int R;
    int G;
    int B;

public:
    RGBColor() {
        R = 1;
        G = 1;
        B = 1;
    }

    RGBColor(int r, int g, int b) {
        R = r;
        G = g;
        B = b;
    }

    double getRed() {
        return R;
    }

    double getGreen() {
        return G;
    }

    double getBlue() {
        return B;
    }


};




class Point {
public:
    // Constructor with default values
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {
    }
    double getX() {
        return int(x );
    }
    double getY() {
        return int(y);
    }
    void setCoordinates(double newX, double newY) {
        x = newX;
        y = newY;
    }

private:
    double x;
    double y;
};




class PPM_Make {
private:
    vector<vector<RGBColor> > array;
public:
    void make() {
        vector<RGBColor> temp;
        for (int k = 0; k < width; k++) {
            temp.push_back(RGBColor());
        }
        for (int f = 0; f < height; f++) {
            array.push_back(temp);
        }
    }
    void setPoint(int x, int y, RGBColor c) {
        array[x][y] = c;

    }
    
    void circleBres(Point &p, int r, RGBColor &c) {
    int x = 0;
    int y = r;
    int y2 = y * y;
    int ty = (2 * y) - 1;
    int y2_new = y2;

    while (x <= y)
    {
        x++;

        if ((y2 - y2_new) >= ty) {
            y2 -= ty;
            y -= 1;
            ty -= 2;
        }
        setPoint((p.getX() + x), (p.getY() + y), c);
        setPoint((p.getX() - x), (p.getY() + y), c);
        setPoint((p.getX() + x), (p.getY() - y), c);
        setPoint((p.getX() - x), (p.getY() - y), c);
        setPoint((p.getX() + y), (p.getY() + x), c);
        setPoint((p.getX() - y), (p.getY() + x), c);
        setPoint((p.getX() + y), (p.getY() - x), c);
        setPoint((p.getX() - y), (p.getY() - x), c);

        y2_new -= (2 * x) - 3;

    }
}
    
    void getArr(string file, int rgb) {
        ofstream myfile;
        myfile.open(file);
        myfile << "P3 " << to_string(width) << " " << to_string(height) << " " << to_string(rgb) << endl;
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                myfile << array[i][j].getRed() << ' ' << array[i][j].getGreen() << ' ' << array[i][j].getBlue() << ' ';
            }
            myfile << endl;
        }
        myfile.close();
    }
};


class Circle {
public:
    // Constructor to initialize the circle with center and radius
    Circle(double centerX, double centerY, double radius)
        : centerX(centerX), centerY(centerY), radius(radius) {}

    // Getter methods to retrieve center and radius
    double getCenterX() {
        return centerX;
    }

    double getCenterY() {
        return centerY;
    }

    int getRadius() {
        return int(radius * 800);
    }

private:
    double centerX; // X-coordinate of the center
    double centerY; // Y-coordinate of the center
    double radius;  // Radius of the circle
};


class Line2D {
public:
    Line2D(const Point& p1, const Point& p2) : point1(p1), point2(p2) {
        // Calculate the slope and intercept from the two points
        calculateSlope();
    }

    // Method to calculate the slope of the line
    double calculateSlope() {
        double deltaX = point2.getX() - point1.getX();
        double deltaY = point2.getY() - point1.getY();

        return deltaY / deltaX;

    }
    
    

    void bresenhams(Point &s, Point &e, vector<vector<int>> &voting) {
        //std::cout<<"in bresenhams"<<std::endl;
        int x1 = s.getX();
        int x2 = e.getX();
        int y1 = s.getY();
        int y2 = e.getY();
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        
        int error = dx - dy;

        for (int x = x1, y = y1; x != x2 || y != y2;) {
           // std::cout<<"starting the for loop "<< std::endl;
            voting[y][x] += 1;
            
//          std::cout<<"x " << x <<std::endl;
//          std::cout<<"x2  "<<x2<<std::endl;

//          std::cout<<"y " << y <<std::endl;
//          std::cout<<"y2  "<<x2<<std::endl;

            
            //std::cout<<"in bresenhams 3"<<std::endl;

            int doubleError = 2 * error;

            if (doubleError > -dy) {
                error -= dy;
                x += sx;
            }
            //std::cout<<"in bresenhams 4"<<std::endl;


            if (doubleError < dx) {
                error += dx;
                y += sy;
            }
            //std::cout<<"in bresenhams end  " << "current x_val: "<< x << "  current y_val: "<< y <<std::endl;

        }
    }


    void drawLine(vector<vector<int>> &voting) {
        int x2 = point2.getX();
        int y2 = point2.getY();

        bresenhams(point1, point2, voting);

        voting[y2][x2] += 1;
    }


    


private:
    Point point1;
    Point point2;
    double slope;
    double intercept;
};








void fill_in(vector<vector<double>>& screen, int x, int y) {
    if (x < 0 || x >= height || y < 0 || y >= width) {
        return;
    }
    if (screen[x][y] == 2 || screen[x][y] == 1) {
        screen[x][y] = 3;

        fill_in(screen, x + 1, y);
        fill_in(screen, x - 1, y);

        fill_in(screen, x, y + 1);

        fill_in(screen, x + 1, y + 1);
        fill_in(screen, x - 1, y + 1);

        fill_in(screen, x - 1, y - 1);

        fill_in(screen, x + 1, y - 1);
        fill_in(screen, x, y - 1);
    }
    else {
        return;
    }
}

void parseLine(int arg_c, char* arg2[], int& lt, int& ht, std::string& infile, std::string& outfile) {

    for (int i = 1; i < arg_c; i++) {
        string str = arg2[i];
        if (str == "-f") { infile = arg2[i + 1]; }
        else if (str == "-ht") { ht = stoi(arg2[i + 1]); }
        else if (str == "-lt") { lt = stoi(arg2[i + 1]); }
        else if (str == "-of") { outfile = arg2[i + 1]; }
    }

}


int roundedAngle(double deg){
    double d = deg/45.0;
    return ceil(d - 0.5) * (45);
}

void parseLine2(int argc, char* arg[], int& lt, int& ht, std::string& infile, std::string& outfile1, std::string& outfile2, std::string& outfilef, std::string& grayscale) {

    for(int i = 1; i < argc; i++){
       string str = arg[i];
       if(str == "-f"){ infile = arg[i+1]; }
       else if(str == "-fg"){ grayscale = arg[i+1];  }    
       else if(str == "-of"){ outfile1 = arg[i+1];   }       
       else if(str == "-f2"){ outfile2 = arg[i+1];   }       
       else if(str == "-ff"){ outfilef = arg[i+1];   }
       else if(str == "-lt"){ lt = stoi(arg[i+1]);  }
       else if(str == "-ht"){  ht = stoi(arg[i+1]);  }
   }
}

bool isEdgePixel(int i, int k, int height, int width) {
    return (i == 0 || i == (height - 1) || k == 0 || k == (width - 1));
}

void calculateNeighbors(int roundedAngle, int i, int k, const vector<vector<double>>& magnit1, int& neighbor1, int& neighbor2) {
    if (roundedAngle == 135 || roundedAngle == -45) {
        neighbor1 = magnit1[i - 1][k + 1];
        neighbor2 = magnit1[i + 1][k - 1];
    } else if (roundedAngle == 90 || roundedAngle == -90) {
        neighbor1 = magnit1[i + 1][k];
        neighbor2 = magnit1[i - 1][k];
    } else if (roundedAngle == 45 || roundedAngle == -135) {
        neighbor1 = magnit1[i - 1][k - 1];
        neighbor2 = magnit1[i + 1][k + 1];
    } else if (roundedAngle == 180 || roundedAngle == -180 || roundedAngle == 0) {
        neighbor1 = magnit1[i][k - 1];
        neighbor2 = magnit1[i][k + 1];
    }
}

void make_image (PPM_Make ppm, int height, int width, vector<vector<double>> &result, int compare){
        for(int i = 0; i < height; i ++){
        for(int k = 0; k < width; k ++){
            if(result[i][k] == compare){
                ppm.setPoint(i, k, RGBColor(1,1,1));
            }
            else{
                ppm.setPoint(i, k, RGBColor(0,0,0));
            }
        }
    }
}

// creating the image with all edges

 vector<vector<int>> part3(int argc, char * arg[]){
    int lt = 100;
    int ht = 200;
    
    RGBColor black(0, 0, 0);
    RGBColor white(1, 1, 1);
    string text;
    string rand;
    int rgb;
    int red;
    int green;
    int blue;
    
    string infile = "ppm_ez.ppm";
    string grayscale = "imageg.ppm";
    string outfile1 = "image1.ppm";
    string outfile2 = "image2.ppm";
    string outfilef = "imagef.ppm";
   
    parseLine2(argc, arg, lt, ht, infile, outfile1, outfile2, outfilef, grayscale);
        
    ifstream file(infile);
    vector<int> ar;
    file >> rand;
    file >> width;
    file >> height;
    file >> rgb;
   
    
    for (int i = 0; i < height; i++) {
        vector<double> temp;
        for (int k = 0; k < width; k++) {
            file >> red;
            file >> green;
            file >> blue;
            double c = (red + green + blue) / 3.0;
            temp.push_back(c);
        }
        og.push_back(temp);
    }
    file.close();

    
    for (int i = 0; i < height; i++) {
        vector<double> temp_x;
        vector<double> temp_y;
        for (int k = 0; k < width; k++) {
            if (i == 0 || i == (height - 1) || k == 0 || k == (width - 1)) {
                temp_x.push_back(0);
                temp_y.push_back(0);
            }
            else {
                temp_x.push_back((-1 * og[i - 1][k - 1]) + (-2 * og[i][k - 1]) + (-1 * og[i + 1][k - 1]) +
                    (1 * og[i - 1][k + 1]) + (2 * og[i][k + 1]) + (1 * og[i + 1][k + 1]));

                temp_y.push_back((-1 * og[i - 1][k - 1]) + (-2 * og[i - 1][k]) + (-1 * og[i - 1][k + 1]) +
                                 
                    (1 * og[i + 1][k - 1]) + (2 * og[i + 1][k]) + (1 * og[i + 1][k + 1]));
            }

        }
        Gx.push_back(temp_x);
        Gy.push_back(temp_y);
    }
    
    vector<vector<double>> magnit;
    vector<vector<double>> magnit1;
    
for (int i = 0; i < height; i++) {
        std::vector<double> temp;

        for (int k = 0; k < width; k++) {
            double gx = Gx[i][k];
            double gy = Gy[i][k];

            if (gx == 0 && gy == 0) {
                temp.push_back(0);
            }
            else {
                double magnitude = std::sqrt(std::pow(gx, 2) + std::pow(gy, 2));
                temp.push_back(magnitude);
            }
        }
        magnit.push_back(temp);
        magnit1.push_back(temp);
    }
    

    for (int i = 0; i < height; i++) {
        for (int k = 0; k < width; k++) {
            if (magnit[i][k] > ht) { magnit[i][k] = 2; }
            else if (magnit[i][k] > lt) { magnit[i][k] = 1; }
            else { magnit[i][k] = 0; }
        }
    }
    
    for(int i = 0; i < height; i++){
        for(int k = 0; k < width; k++){
            if(magnit[i][k] == 2){ fill_in(magnit, i , k); }
        }
    }

    PPM_Make ppm_gray;
    ppm_gray.make();
    
    for(int i = 0; i < height; i ++){
        for(int k = 0; k < width; k ++){
            double num = og[i][k];
            RGBColor c(num, num, num);
            ppm_gray.setPoint(i, k, c);
        }
    }
    
    ppm_gray.getArr(grayscale, rgb);
    
    PPM_Make ppm1;
    ppm1.make();
    make_image(ppm1, height, width, magnit, 1);
    ppm1.getArr(outfile1, 1);
    vector<vector<double>> result;

    for (int i = 0; i < height; i++) {
        vector<double> row;
        for (int k = 0; k < width; k++) {
            double magnitude = magnit1[i][k];
            double gradientX = Gx[i][k];
            double gradientY = Gy[i][k];

            double angle = atan2(gradientY, gradientX);
            double degrees = (180 * angle / M_PI);
            int roundedAng = roundedAngle(degrees);

            if (isEdgePixel(i, k, height, width)) {
                row.push_back(0);
            } else {
                int neighbor1, neighbor2;
                calculateNeighbors(roundedAng, i, k, magnit1, neighbor1, neighbor2);

                if (magnitude >= neighbor1 && magnitude >= neighbor2) {
                    row.push_back(1);
                } else {
                    row.push_back(0);
                }
            }
        }
        result.push_back(row);
    }
    
    
    PPM_Make ppm2;
    ppm2.make();
    make_image(ppm2, height, width, result, 1);
    ppm2.getArr(outfile2, 1);
     
    
    vector<vector<int>> test_edges(result.size(), vector<int>(result[0].size()));
  
    
    PPM_Make final_ppm;
    final_ppm.make();
    for(int i = 0; i < height; i ++){
        for(int k = 0; k < width; k ++){
            if(magnit[i][k] == 3 && result[i][k] == 1){
                final_ppm.setPoint(i, k, RGBColor(1,1,1));
                test_edges[i][k] = 1;
            }
            else{
                final_ppm.setPoint(i, k, RGBColor(0,0,0));
                test_edges[i][k] = 0;

            }
        }
    }
    final_ppm.getArr(outfilef, 1);
     
    std::cout<<"Testing result  "<<result[1][1]<<std::endl;
        std::cout<<"Testing edges matrix  "<<test_edges[1][1]<<std::endl;

     
    return test_edges;
}

void findCenters(vector<vector<int>> &result, int argc, char * arg[]){
    
    int lt = 100;
    int ht = 200;
    
    string text;
    string rand;
    int rgb;

    string infile = "ppm_ez.ppm";
    string grayscale2 = "votingImage.ppm";
    string grayscale = "imageg.ppm";
    string outfile1 = "image1.ppm";
    string outfile2 = "image2.ppm";
    string outfilef = "imagef.ppm";
   
    parseLine2(argc, arg, lt, ht, infile, outfile1, outfile2, outfilef, grayscale2);
        
    ifstream file(infile);
    vector<int> ar;
    file >> rand;
    file >> width;
    file >> height;
    file >> rgb;
    
    vector<vector<int>> votes(result.size(), vector<int>(result[0].size()));
    
    
    int y_height = votes.size()-1;
    int x_width = votes[0].size()-1;
    
//      std::cout<<"temp Height "<< y_height<<std::endl;
//      std::cout<<"temp Width " << x_width <<std::endl;

    
    for(int i = 0; i<int(result.size()); i++){
        for (int j = 0; j<int(result[i].size()); j++){
            votes[i][j] = 0;
        }
    }
    
    int count=0;
    for (int y = 0; y<votes.size(); y++){
        for (int x = 0; x<votes[0].size(); x++){
            
            if (result[y][x]==1 /*&& count<1*/){
                //count++;
                double gy = Gy[y][x];
                double gx = Gx[y][x];
                double theta = atan2(gy,gx);
                double slope = 0;
                
                if (gx!=0){slope = gy/gx;}
                else{slope=y_height/1;} 
                

                // use point slope form to find intersections
                int y_x_zero_case = (-1*slope*x)+y;
                int y_x_width_case = (slope*x_width - slope*x)+y;
                int x_y_zero_case = ((-1*y)+(slope*x))/slope;
                int x_y_height_case = (y_height - y + (slope*x))/slope;
                
                Point p1(x,y);
                
                int maxDiameter = 100;

                double p = acos(-1);

                int p2_x;
                int p2_y;

                if (theta > 0 && theta < p/2) {
                  p2_x = p1.getX() - maxDiameter;
                  p2_y = p1.getY() - maxDiameter*theta;
                } else if (theta > p/2 && theta < p) {
                  p2_x = p1.getX() + maxDiameter;
                  p2_y = p1.getY() + maxDiameter*theta;
                } else if (theta < 0 && theta > -p/2) {
                  p2_x = p1.getX() - maxDiameter;
                  p2_y = p1.getY() - maxDiameter*theta;
                } else if (theta < -p/2 && theta > -p) {
                  p2_x = p1.getX() + maxDiameter;
                  p2_y = p1.getY() + maxDiameter*theta;
                } else {
                  p2_x = x;
                  p2_y = y;
                }

                p2_y = y + 1;
                p2_x = x + 1;
                
                Point p2(p2_x, p2_y);
                
                

//                 std::cout<<"theta  " <<theta << std::endl;
//                 std::cout<<"slope  " <<slope << std::endl;

//                 std::cout<<"y  " <<y << std::endl;
//                 std::cout<<"x  " <<x << std::endl;

//                     int intersection_final_1 = -100000;
//                     Point p1(0,0);
//                     int intersection_final_2 = -100000;
//                     Point p2(0,0);

//                 if (y_x_zero_case >= 0 && y_x_zero_case <= y_height){
//                     if (intersection_final_1 < 0){
//                         intersection_final_1 = y_x_zero_case;
//                         p1.setCoordinates(0,y_x_zero_case);
//                     }
//                     else if (intersection_final_1 > 0 && intersection_final_2 == -100000){
//                         //std::cout<<"HERE 0"<< std::endl;
//                         intersection_final_2 = y_x_zero_case;
//                         p2.setCoordinates(0,y_x_zero_case);
//                     }

//                 }
                

//                 if (y_x_width_case >= 0 && y_x_width_case <= y_height){
//                     if (intersection_final_1 < 0){
//                         intersection_final_1 = y_x_width_case;
//                         p1.setCoordinates(x_width,y_x_width_case);
//                     }
//                     else if (intersection_final_1 > 0 && intersection_final_2 == -100000){
//                         //std::cout<<"HERE 1"<< std::endl;
//                         intersection_final_2 = y_x_width_case;
//                         p2.setCoordinates(x_width,y_x_width_case);
//                     }
//                 }
                
//                 if (x_y_zero_case >= 0 && x_y_zero_case <= x_width){
//                     if (intersection_final_1 < 0){
//                         intersection_final_1 = x_y_zero_case;
//                         p1.setCoordinates(x_y_zero_case,0);
//                     }
//                     else if (intersection_final_1 > 0 && intersection_final_2 == -100000){
//                         //std::cout<<"HERE 2"<< std::endl;

//                         intersection_final_2 = x_y_zero_case;
//                         p2.setCoordinates(x_y_zero_case,0);
//                     }
//                 }
                
                
//                 if (x_y_height_case >= 0 && x_y_height_case <= x_width){
//                      if (intersection_final_1 < 0){
//                         intersection_final_1 = x_y_zero_case;
//                         p1.setCoordinates(x_y_zero_case,0);
//                     }
//                     else if (intersection_final_1 > 0 && intersection_final_2 == -100000){
//                         //std::cout<<"HERE 3"<< std::endl;

//                         intersection_final_2 = x_y_height_case;
//                         p2.setCoordinates(x_y_height_case, y_height);
//                     }
//                 }
                
                Line2D votingLine(p1, p2);
                votingLine.drawLine(votes); 
                
//                 std::cout<<"Point 1"<< p1.getX() << "   "<<p1.getY()<<std::endl;
//                 std::cout<<"Point 2"<< p2.getX() << "   "<<p2.getY()<<std::endl;

               }
            } 
        }
        
    PPM_Make ppm_gray;
    ppm_gray.make();
    double max = 0;
    
    for(int i = 0; i < int(votes.size()); i ++){
        for(int k = 0; k < int(votes[0].size()); k ++){
            double num = votes[i][k];
            if (num>max){
                max = num;
            }
            RGBColor c(num, num, num);
            ppm_gray.setPoint(i, k, c);
        }
    }
    ppm_gray.getArr(grayscale2, max);
}



int main(int arg_c, char* arg2[]) {
    vector<vector<int>> result = part3(arg_c, arg2);
    findCenters(result, arg_c, arg2);
    std::cout <<"here 3 " <<  std::endl;
    return 0;
}