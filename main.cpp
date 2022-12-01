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
#include <time.h>

#define pi 3.141592653589793238463

using namespace cv;
using namespace std;

// path to image, path to save output image
//
// g++ -o output main.cpp
// ./output /Users/maburidi/Desktop/MATH233_project_/img8.bmp  /Users/maburidi/Desktop/output_image.jpg 1. 200 5. -3. 1.5 0.8 0.2 2. 2 24 35 19 25 24 35 39 50



int main(int argc, char** argv){

    ///////////////////////////////// Read Inputs /////////////////////////////////
    std::string path =  argv[1];
    std::string path_out = argv[2];
    //--------  Model Parameters ---------//
    float time_step = atof(argv[3]);        // time step
    int iter= atoi(argv[4]);
    float lmda_=  atof(argv[5]);             // coefficient of the weighted length term L(phi)
    float alfa = atof(argv[6]);            // coefficient of the weighted area term A(phi)
    double epsilon= atof(argv[7]);        // parameter that specifies the width of the DiracDelta function
    double sigma= atof(argv[8]);           // scale parameter in Gaussian kernel
    float  mu = atof(argv[9]);   // coefficient of the distance regularization term R(phi)
    float c_0= atof(argv[10]);
    int mask_ = atoi(argv[11]);     // spacify how many sqaure in the mask 1 or 2 , at least one is needed
    int mask_corner1_sq1 = atoi(argv[12]);
    int mask_corner2_sq1 = atoi(argv[13]);
    int mask_corner3_sq1 = atoi(argv[14]);
    int mask_corner4_sq1 = atoi(argv[15]);

    if ( mask_corner1_sq1 > mask_corner2_sq1 ||  mask_corner3_sq1 > mask_corner4_sq1 ){
        throw std::invalid_argument("Mask corners positions dose noe make sense, please input a square shaped corners positions");
    }

    //////////////////////////////// Load Image //////////////////////////////

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

    ///////////////////////////// Create a Mask ///////////////////////////////
    vector<float> lsf;

    lsf.assign(height*width,c_0);
    for(int i=mask_corner1_sq1; i<mask_corner2_sq1; i++){
        for(int j=mask_corner3_sq1; j<mask_corner4_sq1; j++){
            lsf [i*width +j] = -c_0;
        }}

    if(mask_ > 1) {
        int mask_corner1_sq2 = atoi(argv[16]);
        int mask_corner2_sq2 = atoi(argv[17]);
        int mask_corner3_sq2 = atoi(argv[18]);
        int mask_corner4_sq2 = atoi(argv[19]);

        for (int i = mask_corner1_sq2; i < mask_corner2_sq2; i++) {
            for (int j = mask_corner3_sq2; j < mask_corner4_sq2; j++) {
                lsf[i * width + j] = -c_0;
            }
        }
    }
    // convert the mask vector into an image
    Mat mask =vec_to_mat( lsf,  height, width);

    //////////////////////////////////// Start Algorithm ///////////////////////////////////////

    if ( img.cols != mask.cols && img.rows != mask.rows ){
        throw std::invalid_argument("Input image and the initial LSF should be in the same shape");
    }
    ///// filter /////
    Mat img_smooth;
    GaussianBlur(img, img_smooth, Size(3, 3), sigma);    // smooth image with gaussian filter with 3X3 kernel
    Mat dstx;
    Mat dsty;

    //// Calculate gradient /////
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

    clock_t tStart = clock();


    //////// Main Solver - Iterate to Solve the LSE ////////
    Mat phi = mask;
     for(int i=0;i<iter; i++){
         phi =  solver(  phi, g, lmda_, mu, alfa, epsilon, time_step);
         cout << "Evolving in:  " << i << " iteration" << endl;
     }
     printf("Time taken: %.5f s\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
     ///////

     phi.convertTo(phi, CV_32F);
     imshow("Image2", phi);


    ///////////// Save Output Segmented Image ////////////////
    bool check = imwrite(path_out, phi);
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
