#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/core.hpp>
#include "src/tools.h"
#include "src/solver_lse.h"

#define pi 3.141592653589793238463

using namespace cv;
using namespace std;



int main(int argc, char** argv){

    //////////////////////////////// Load Image //////////////////////////////
    std::string path = "/Users/maburidi/Desktop/MATH233_project/img8.bmp";
    Mat img_rgb = imread(path);    // IMREAD_GRAYSCALE if gray scale
    //imshow("Image", img_rgb);

    cout << "Image Size = " << img_rgb.size <<endl;
    cout << "Image Channels = " << img_rgb.channels() <<endl;
    Mat img;
    cvtColor(img_rgb, img, COLOR_BGR2GRAY);              // convert to gray scale
    cout << "---- Image has been converted to gray scale ---- "<<endl;
    cout << "Image Channels now = " << img.channels() <<endl;

    int width = img.cols;
    int height = img.rows;

    // convert image to vector
    vector<float> v_img =  mat_to_vec(img);
    Mat img2 =vec_to_mat(v_img,height,width);    // convert back vector to image
    img2.convertTo(img2, CV_8U);          // convert to 8 bit unsigned integer
    //imshow("Image", img2);


    ///////////////////////////// Model Parameters ////////////////////////////
    float time_step = 1.;        // time step
    int iter_outer= 30;
    float lmda_= 5.;             // coefficient of the weighted length term L(phi)
    float alfa = -3.;            // coefficient of the weighted area term A(phi)
    double epsilon= 1.5;         // parameter that specifies the width of the DiracDelta function
    double sigma= 0.8;           // scale parameter in Gaussian kernel


    ///////////////////////////// Create a Mask ///////////////////////////////
    vector<float> lsf;

    lsf.assign(height*width,2.);
    for(int i=24; i<35; i++){
        for(int j=19; j<25; j++){
            lsf [i*width +j] = -2.;
        }
        for(int j=39; j < 50; j++){
            lsf [i*width +j] = -2.;
        }
    }

    // convert the mask vector into an image
    Mat mask =vec_to_mat( lsf,  height, width);

    ///////////////////////////////////////////////////////////////////////////

    if ( img.cols != mask.cols && img.rows != mask.rows ){
        throw std::invalid_argument("Input image and the initial LSF should be in the same shape");
    }

    float  mu = 0.2 / time_step;   // coefficient of the distance regularization term R(phi)
    Mat img_smooth;
    GaussianBlur(img, img_smooth, Size(3, 3), sigma);    // smooth image with gaussian filter with 3X3 kernel
    Mat dstx;
    Mat dsty;

    //Sobel and Scharr Derivatives
    Sobel(img, dstx, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    Sobel(img, dsty, CV_8U, 0, 1, 3, 1, 0, BORDER_DEFAULT);
    // Scharr(img, dstx, CV_8U, 1, 0, 1, 0, BORDER_DEFAULT);
    // Scharr(img, dsty, CV_8U, 0, 1, 1, 0, BORDER_DEFAULT);

     Mat f = dstx.mul(dstx) + dsty.mul(dsty);
     //f.convertTo(f, CV_32F);
     // imshow("Image2", f);

     Mat g = 1./(1.+f);
     g.convertTo(g, CV_32F);

     Mat phi = mask;
     for(int i=0;i<iter_outer; i++){
         phi =  solver(  phi, g, lmda_, mu, alfa, epsilon, time_step);
         cout << "Evolving in:  " << i << " iteration" << endl;
     }

     phi.convertTo(phi, CV_32F);
     imshow("Image2", phi);


    bool check = imwrite("/Users/maburidi/Desktop/segmentedimage.jpg", phi);
    if (check == false) {
        cout << "Mission - Saving the image, FAILED" << endl;
    }
    cout << "Successfully saved the image. " << endl;


    //waitKey(0);
    //blue.deallocate();
    //img.deallocate();
    //mask.deallocate();

    return 0;
}
