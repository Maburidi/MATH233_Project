//
// Created by Mohammed Aburidi on 11/21/22.
//

#include "tools.h"

Mat cos_mat(Mat x){

    int width = x.cols;
    int height = x.rows;
    x.convertTo(x, CV_8U);
    vector<float> array;
    array.assign(width*height,0.0);

    for(int i=0; i < width  ; i++ ){
        for(int j=0; j < height ; j++ ){
            array[i*width +j] = std::cos( pi/180.0 * float(x.at<uchar>(i,j))) ;
        }
    }
    Mat M = vec_to_mat( array,  height, width);

    return M;
}

Mat vec_to_mat(vector<float> V, int height,int width){
    Mat M2=Mat(height,width,CV_32FC1);
    memcpy(M2.data,V.data(),V.size()*sizeof(float));
    return M2;
}


vector<float> mat_to_vec(Mat mat){
    int width = mat.cols;
    int height = mat.rows;

    vector<float> array;
    array.assign(height*width,0.);

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++) {
            array[i*width +j] = float(mat.at<uchar>(i,j));
        }
    }
    return array;
}


Mat vec_to_mat_uchar(vector<float> V, int height,int width){
    Mat M=Mat(height,width,CV_32F);
    memcpy(M.data,V.data(),V.size()*sizeof(float));
    return M;

}