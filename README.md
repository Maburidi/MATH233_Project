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

The argument in the command line above in order is as follows: <br />
1- Image directory to be segmented    <br />
2- Output image directory to be saved in <br />
3- $\lambda$          <br />       
4- $\alpha$ <br />      
5- $\mu$. <br />      
6- $\epsilon$ <br />      
7- $\sigma$ <br />      
8- $\Delta t$ <br />      
9- $c_0$ <br />      
10- $Iter$  <br />      
12- Boxs positions to create the initial level set. Should be divisible by 4. (i.e. four courners $[y_1,y_0,x_0,x_1]$) 


### Discriptio of the parameters:  

This table defines all the parameters used in the implementation of the model. 
<img width="1119" alt="image" src="https://user-images.githubusercontent.com/48891624/203199443-167bf55a-bbdb-45aa-a015-b4c938c7280c.png">



# Results: 


<img width="753" alt="image" src="https://user-images.githubusercontent.com/48891624/203199646-e8e5d68e-c918-4a10-bdcb-d3bde6380b0a.png">

<img width="937" alt="image" src="https://user-images.githubusercontent.com/48891624/203199700-831ff7a0-df10-4d0c-ab99-27127fc73b2a.png">







