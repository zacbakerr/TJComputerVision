#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <math.h>

using namespace std;
using namespace cv;

Mat performTranslation(Mat inputMat, double offsetX, double offsetY, double offsetZ) {
    std::vector<std::vector<double>> transMatrix = {{1, 0, 0, offsetX},
                                                    {0, 1, 0, offsetY},
                                                    {0, 0, 1, offsetZ},
                                                    {0, 0, 0, 1}};

    Mat transformMatrix = (Mat_<double>(4, 4) << transMatrix[0][0], transMatrix[0][1], transMatrix[0][2], transMatrix[0][3],
                           transMatrix[1][0], transMatrix[1][1], transMatrix[1][2], transMatrix[1][3],
                           transMatrix[2][0], transMatrix[2][1], transMatrix[2][2], transMatrix[2][3],
                           transMatrix[3][0], transMatrix[3][1], transMatrix[3][2], transMatrix[3][3]);

    return transformMatrix * inputMat;
}

Mat performScaling(Mat inputMat, double scaleX, double scaleY, double scaleZ) {
    std::vector<std::vector<double>> scaleMatrix = {{scaleX, 0, 0, 0},
                                                    {0, scaleY, 0, 0},
                                                    {0, 0, scaleZ, 0},
                                                    {0, 0, 0, 1}};

    Mat transformMatrix = (Mat_<double>(4, 4) << scaleMatrix[0][0], scaleMatrix[0][1], scaleMatrix[0][2], scaleMatrix[0][3],
                           scaleMatrix[1][0], scaleMatrix[1][1], scaleMatrix[1][2], scaleMatrix[1][3],
                           scaleMatrix[2][0], scaleMatrix[2][1], scaleMatrix[2][2], scaleMatrix[2][3],
                           scaleMatrix[3][0], scaleMatrix[3][1], scaleMatrix[3][2], scaleMatrix[3][3]);

    return transformMatrix * inputMat;
}

Mat rotateAroundX(Mat inputMat, double angle) {
    std::vector<std::vector<double>> rotXMatrix = {{1, 0, 0, 0},
                                                   {0, cos(angle), -sin(angle), 0},
                                                   {0, sin(angle), cos(angle), 0},
                                                   {0, 0, 0, 1}};

    Mat transformMatrix = (Mat_<double>(4, 4) << rotXMatrix[0][0], rotXMatrix[0][1], rotXMatrix[0][2], rotXMatrix[0][3],
                           rotXMatrix[1][0], rotXMatrix[1][1], rotXMatrix[1][2], rotXMatrix[1][3],
                           rotXMatrix[2][0], rotXMatrix[2][1], rotXMatrix[2][2], rotXMatrix[2][3],
                           rotXMatrix[3][0], rotXMatrix[3][1], rotXMatrix[3][2], rotXMatrix[3][3]);

    return transformMatrix * inputMat;
}

Mat rotateAroundY(Mat inputMat, double angle) {
    std::vector<std::vector<double>> rotYMatrix = {{cos(angle), 0, sin(angle), 0},
                                                   {0, 1, 0, 0},
                                                   {-sin(angle), 0, cos(angle), 0},
                                                   {0, 0, 0, 1}};

    Mat transformMatrix = (Mat_<double>(4, 4) << rotYMatrix[0][0], rotYMatrix[0][1], rotYMatrix[0][2], rotYMatrix[0][3],
                           rotYMatrix[1][0], rotYMatrix[1][1], rotYMatrix[1][2], rotYMatrix[1][3],
                           rotYMatrix[2][0], rotYMatrix[2][1], rotYMatrix[2][2], rotYMatrix[2][3],
                           rotYMatrix[3][0], rotYMatrix[3][1], rotYMatrix[3][2], rotYMatrix[3][3]);

    return transformMatrix * inputMat;
}

Mat rotateAroundZ(Mat inputMat, double angle) {
    std::vector<std::vector<double>> rotZMatrix = {{cos(angle), -sin(angle), 0, 0},
                                                   {sin(angle), cos(angle), 0, 0},
                                                   {0, 0, 1, 0},
                                                   {0, 0, 0, 1}};

    Mat transformMatrix = (Mat_<double>(4, 4) << rotZMatrix[0][0], rotZMatrix[0][1], rotZMatrix[0][2], rotZMatrix[0][3],
                           rotZMatrix[1][0], rotZMatrix[1][1], rotZMatrix[1][2], rotZMatrix[1][3],
                           rotZMatrix[2][0], rotZMatrix[2][1], rotZMatrix[2][2], rotZMatrix[2][3],
                           rotZMatrix[3][0], rotZMatrix[3][1], rotZMatrix[3][2], rotZMatrix[3][3]);

    return transformMatrix * inputMat;
}

Mat create_3D_Mat(double x, double y, double z) {
    Mat temp = (Mat_<double>(3, 1) << x, y, z);
    return temp;
}

Mat get_unit_vector(Mat original) {
    std::vector<double> out(original.begin<double>(), original.end<double>());
    double magnitude = sqrt(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);
    return (1.0 / magnitude) * original;
}

Mat find_projection(Mat v, Mat a, Mat e, Mat n) {
    return (v - e) * ((a - e).dot(n) / (v - e).dot(n)) + e;
}

void part3(int count, char** args) {
    int w = 800;
    int h = 600;
    double pi_val = 3.1415926535;
    
    std::vector<std::vector<double>> v_list = {{1, 1, 1, 1},
                                                {1, 1, -1, 1},
                                                {1, -1, 1, 1},
                                                {-1, 1, 1, 1},
                                                {-1, -1, 1, 1},
                                                {-1, 1, -1, 1},
                                                {1, -1, -1, 1},
                                                {-1, -1, -1, 1}};
    
    vector<Mat> m_list;
    int f_count = 60;
    
    VideoWriter vid_writer;
    vid_writer.open("rotation.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), f_count, Size(w, h));
    
    for(int i = 0; i < v_list.size(); i++) {
        Mat p = (Mat_<double>(4, 1) << v_list[i][0], v_list[i][1], v_list[i][2], v_list[i][3]);
        m_list.push_back(p);
    }
    
    int frame_count = 300;
    double angle_step = 2 * pi_val / static_cast<double>(frame_count);
    
    Mat e = create_3D_Mat(400.0, 400.0, 500.0);
    Mat plane_point = create_3D_Mat(400.0, 200.0, 300.0);
    Mat n = create_3D_Mat(1.0, 3.0, 2.0);
    
    for (int i = 0; i < count; i++) {
        if (string(args[i]) == "-a") {
            string curr = args[i+1];
            curr = curr.substr(1, curr.length()-3);
            string x = (curr.substr(0, curr.find(",")));
            curr.erase(0, curr.find(",") + 1);
            string y = (curr.substr(0, curr.find(",")));
            curr.erase(0, curr.find(",") + 1);
            string z = (curr.substr(0, curr.find(",")));
            plane_point = create_3D_Mat(stod(x), stod(y), stod(z));
        }
        if (string(args[i]) == "-n") {
            string curr = args[i+1];
            curr = curr.substr(1, curr.length()-3);
            string x = (curr.substr(0, curr.find(",")));
            curr.erase(0, curr.find(",") + 1);
            string y = (curr.substr(0, curr.find(",")));
            curr.erase(0, curr.find(",") + 1);
            string z = (curr.substr(0, curr.find(",")));
            n = create_3D_Mat(stod(x), stod(y), stod(z));
        }
        if (string(args[i]) == "-e") {
            string curr = args[i+1];
            curr = curr.substr(1, curr.length()-3);
            string x = (curr.substr(0, curr.find(",")));
            curr.erase(0, curr.find(",") + 1);
            string y = (curr.substr(0, curr.find(",")));
            curr.erase(0, curr.find(",") + 1);
            string z = (curr.substr(0, curr.find(",")));
            e = create_3D_Mat(stod(x), stod(y), stod(z));
        }
    }

    Mat o = create_3D_Mat(0.0, 0.0, 0.0);
    Mat p0_new = find_projection(o, plane_point, e, n);
    
    Mat p1_raw = create_3D_Mat(1.0, 1.0, 1.0);
    Mat p1_new = find_projection(p1_raw, plane_point, e, n);

    Mat p2_raw = create_3D_Mat(1.0, 1.0, -1.0);
    Mat p2_new = find_projection(p2_raw, plane_point, e, n);

    Mat p3_raw = create_3D_Mat(1.0, -1.0, 1.0);
    Mat p3_new = find_projection(p3_raw, plane_point, e, n);
    
    Mat a_new = p1_new - p2_new;
    Mat b_new = p3_new - p2_new; 
    Mat w1_new = get_unit_vector(a_new);
    Mat c_new = b_new - a_new * (b_new.dot(a_new) / a_new.dot(a_new));
    Mat w2_new = get_unit_vector(c_new);
    
    
    ofstream log("log.txt");

    std::vector<double> a_out(plane_point.begin<double>(), plane_point.end<double>());
    std::vector<double> n_out(n.begin<double>(), n.end<double>());
    std::vector<double> e_out(e.begin<double>(), e.end<double>());
    std::vector<double> p0_out(p0_new.begin<double>(), p0_new.end<double>());
    std::vector<double> w1_out(w1_new.begin<double>(), w1_new.end<double>());
    std::vector<double> w2_out(w2_new.begin<double>(), w2_new.end<double>());
    

    log << "The plane defined by (x-a)*n=0 is:\n";
    log << "\ta="<<"("<<a_out[0]<<","<<a_out[1]<<","<<a_out[2]<<")"<<"\n";
    log << "\tn="<<"("<<n_out[0]<<","<<n_out[1]<<","<<n_out[2]<<")"<<"\n";
    log << "The eye e is:\n";
    log << "\te="<<"("<<e_out[0]<<","<<e_out[1]<<","<<e_out[2]<<")"<<"\n";
    log << "The coordinates in the plane x = p0 + u*w1 + v*w2 is:\n";
    log << "\tp0="<<"("<<p0_out[0]<<","<<p0_out[1]<<","<<p0_out[2]<<")"<<"\n";
    log << "\tw1="<<"("<<w1_out[0]<<","<<w1_out[1]<<","<<w1_out[2]<<")"<<"\n";
    log << "\tw2="<<"("<<w2_out[0]<<","<<w2_out[1]<<","<<w2_out[2]<<")"<<"\n";
    
    for(int f_num = 0; f_num <= frame_count; f_num++) {
        Mat img(h, w, CV_8UC3, Scalar(255, 255, 255));
        vector<Point> m_to_p;
        vector<vector<double>> m_to_p3; 

        stringstream out_3d;
        out_3d<<"The frame "<<f_num + 1<<" in 3d has the following edges:\n";

        stringstream out_2d;
        out_2d<<"The frame "<<f_num + 1<<" in 2d has the following edges:\n";
        
        for(int i = 0; i < m_list.size(); i++) {
            Mat v_mat = performScaling(rotateAroundZ(rotateAroundY(rotateAroundX(m_list[i], angle_step * f_num), angle_step * f_num), angle_step * f_num), 150.0, 150.0, 150.0);
            std::vector<double> v_out(v_mat.begin<double>(), v_mat.end<double>());
            m_to_p3.push_back({v_out[0] / v_out[3], v_out[1] / v_out[3], v_out[2] / v_out[3]});
            
            Mat v_actual = (Mat_<double>(3, 1) << v_out[0] / v_out[3], v_out[1] / v_out[3], v_out[2] / v_out[3]);
            
            Mat pv = find_projection(v_actual, plane_point, e, n);
            double u = (pv - p0_new).dot(w1_new) / w1_new.dot(w1_new);
            double v = (pv - p0_new).dot(w2_new) / w2_new.dot(w2_new);
            
            std::vector<double> final_out{u + 400.0, v + 300.0};
            
            circle(img, Point(final_out[0], final_out[1]), 3, Scalar(0, 0, 0), 3);
            
            m_to_p.push_back(Point(final_out[0], final_out[1]));
        }

        if(f_num < 4) {
            out_3d<<"\t("<<m_to_p3[0][0]<<","<<m_to_p3[0][1]<<","<<m_to_p3[0][2]<<"), ";
            out_3d<<"("<<m_to_p3[1][0]<<","<<m_to_p3[1][1]<<","<<m_to_p3[1][2]<<")\n";

            out_2d<<"\t("<<m_to_p[0].x<<","<<m_to_p[0].y<<"), ";
            out_2d<<"("<<m_to_p[1].x<<","<<m_to_p[1].y<<")\n";

            log << out_3d.str() << endl;
            log << out_2d.str() << endl;
        }

        if(f_num == 4) {
            log.close();
        }
        
        line(img, m_to_p[0], m_to_p[1], Scalar(0, 0, 0));
        
        vid_writer << img;
    }
        
    std::vector<std::vector<double>> t_v_list = {{1.0 / sqrt(3), 0, 0, 1},
                                                 {0, 0, 2 / sqrt(6), 1},
                                                 {-sqrt(3) / 6.0, 0.5, 0, 1},
                                                 {-sqrt(3) / 6.0, -0.5, 0, 1}};
    
    vector<Mat> t_list;
    
    for(int i = 0; i < t_v_list.size(); i++) {
        Mat p = (Mat_<double>(4, 1) << t_v_list[i][0], t_v_list[i][1], t_v_list[i][2], t_v_list[i][3]);
        t_list.push_back(p);
    }
    
    for(int f_num = 0; f_num <= frame_count; f_num++) {
        Mat img(h, w, CV_8UC3, Scalar(255, 255, 255));
        
        vector<Point> m_to_p;
        
        for(int i = 0; i < t_list.size(); i++) {
            Mat v_mat = performScaling(rotateAroundZ(rotateAroundY(rotateAroundX(t_list[i], angle_step * f_num), angle_step * f_num), angle_step * f_num), 350.0, 350.0, 350.0);
            std::vector<double> v_out(v_mat.begin<double>(), v_mat.end<double>());
            Mat v_actual = (Mat_<double>(3, 1) << v_out[0] / v_out[3], v_out[1] / v_out[3], v_out[2] / v_out[3]);
            
            Mat pv = find_projection(v_actual, plane_point, e, n);
            double u = (pv - p0_new).dot(w1_new) / w1_new.dot(w1_new);
            double v = (pv - p0_new).dot(w2_new) / w2_new.dot(w2_new);
            
            std::vector<double> final_out{u + 400.0, v + 300.0};
            
            circle(img, Point(final_out[0], final_out[1]), 3, Scalar(0, 0, 0), 3);
            
            m_to_p.push_back(Point(final_out[0], final_out[1]));
        }
                
        vid_writer << img;
    }
}

int main(int argc, char** argv) {
    part3(argc, argv);
    return 0;
}