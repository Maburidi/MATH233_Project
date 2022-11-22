# Image Segmentation Using Regularized Level Set Method 

## This is the C++ code for the MATH-233 final Project 
Comments/Bugs/Problems: maburidi@ucmerced.edu

November, 2022. Initial release


## C++ Code: 

### Building
This README covers instructions for building the code and using the following example for image segmentation  

### Dependencies
OpenCV – 4.5.5

[OpenCV](https://opencv.org/) As of this writing, the version installed from this github [github](https://github.com/opencv/opencv) is returning OpenCV 4.5.5


After installing the dependencies. The project can be built using g++, in the terminal run the following:  

```
git clode https://github.com/Maburidi/MATH233_Project.git
cd MATH233_Project 
g++ -o output main.cpp  
./output  ./input_imgs/img8.bmp ./output_imgs/output_img8.jpg 0.5 -3.0 0.2 1.5 0.8 1 2 200 [24,35,19,25,24,35,39,50]
 
```

The argument in the command line above in order is as follows: \\
Image to be segmented:     
$\lambda$:                 







