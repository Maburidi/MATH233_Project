//
// Created by Mohammed Aburidi on 11/21/22.
//

#ifndef OPEN_CV_PROJECT_SOLVER_LSE_H
#define OPEN_CV_PROJECT_SOLVER_LSE_H

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



Mat solver( Mat phi_0, Mat g, float lmda, float mu, float alfa, float epsilon, float time_step);
Mat div(Mat nx, Mat ny);
Mat dirac(Mat x, float  sigma);



#endif //OPEN_CV_PROJECT_SOLVER_LSE_H
