//
// Created by Mohammed Aburidi on 11/21/22.
//

#include "solver_lse.h"


Mat dirac(Mat x, float  sigma){

    Mat in_cos = (pi/sigma)* x;
    Mat p=    cos_mat( in_cos);
    p.convertTo(p, CV_32F);

    Mat f = (1./(2.*sigma)) *  (1 +  p )  ;
    Mat b1 = (x >= -sigma)/255. ;
    Mat b2 = (x <= sigma)/ 255. ;
    Mat b = b2.mul(b1);
    b.convertTo(b, CV_32F);

    return f.mul(b);
}

Mat div(Mat nx, Mat ny){
    Mat nx_x;
    Mat ny_y;

    Sobel(nx, nx_x, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    Sobel(ny, ny_y, CV_8U, 0, 1, 3, 1, 0, BORDER_DEFAULT);
    ny_y.convertTo(ny_y, CV_32F);
    nx_x.convertTo(nx_x, CV_32F);

    return nx_x + ny_y ;
}


Mat solver( Mat phi_0, Mat g, float lmda, float mu, float alfa, float epsilon, float time_step){
    Mat phi = phi_0;
    Mat phi_x;
    Mat phi_y;
    Mat vx;
    Mat vy;
    Sobel(g, vx, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    Sobel(g, vy, CV_8U, 0, 1, 3, 1, 0, BORDER_DEFAULT);
    float delta =1.0e-10;
    //Sobel and Scharr Derivatives

    for(int k=0; k < 10; k++){

        Sobel(phi, phi_x, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);
        Sobel(phi, phi_y, CV_8U, 0, 1, 3, 1, 0, BORDER_DEFAULT);
        Mat f = phi_x.mul(phi_x) + phi_y.mul(phi_y);
        f.convertTo(f, CV_32F);
        phi_x.convertTo(phi_x, CV_32F);
        phi_y.convertTo(phi_y, CV_32F);
        vx.convertTo(vx, CV_32F);
        vy.convertTo(vy, CV_32F);
        cv::sqrt( f,f);


        f = f+delta;
        Mat n_x;
        Mat n_y;
        cv::divide( phi_x ,f , n_x);
        cv::divide( phi_y ,f , n_y);
        Mat curvature = div(n_x,n_y);
        Mat Lap;
        cv::Laplacian(phi,Lap,CV_32F, 3,1, 0, BORDER_DEFAULT);
        Mat dist_reg_term = Lap - curvature;
        Mat dirac_phi = dirac(phi, epsilon);
        //dirac_phi.convertTo(dirac_phi, CV_8U);
        Mat area_term = dirac_phi.mul(g);
        Mat h = (vx.mul(n_x) + vy.mul(n_y));
        Mat hh = g.mul(curvature);
        Mat edge_term = dirac_phi.mul(h) + dirac_phi.mul(hh);
        phi += time_step * (mu * dist_reg_term + lmda * edge_term + alfa * area_term);

    }

    //imshow("Image2", phi);

    return phi;
}
