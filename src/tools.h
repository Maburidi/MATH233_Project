//
// Created by Mohammed Aburidi on 11/21/22.
//

#ifndef OPEN_CV_PROJECT_TOOLS_H
#define OPEN_CV_PROJECT_TOOLS_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/core.hpp>
#include "tools.h"

#define pi 3.141592653589793238463

using namespace cv;
using namespace std;


Mat cos_mat(Mat x);
vector<float> mat_to_vec(Mat mat);
Mat vec_to_mat(vector<float> V, int height,int width);
Mat vec_to_mat_uchar(vector<float> V, int height,int width);



#endif //OPEN_CV_PROJECT_TOOLS_H
