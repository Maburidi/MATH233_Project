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
 
./output ./input_imgs/img8.bmp  ./output_image.jpg 1. 200 5. -3. 1.5 0.8 0.2 2. 2 24 35 19 25 24 35 39 50
 
 
```

The argument in the command line above in order is as follows: <br />
1- Image directory to be segmented    <br />
2- Directory to save segmented image  <br />
3- Time step <br />
4- Number of Iterations <br />
5- $\lambda$          <br />       
6- $\alpha$ <br />      
7- $\epsilon$ <br />      
8- $\sigma$ <br />      
9- $\mu$. <br />   
10- $c_0$ <br />  
11- Number of 2d squares to be created in the image mask (for initial level set) <br />  
12- square 1 corner 1 <br />  
13- square 1 corner 2 <br />  
14- square 1 corner 3 <br />  
15- square 1 corner 4 <br />  
16- square 2 corner 1 <br />  
17- square 2 corner 2 <br />  
18- square 2 corner 3 <br />  
19- square 2 corner 4 <br />  


### Discriptio of the parameters:  

This table defines all the parameters used in the implementation of the model. 
<img width="1119" alt="image" src="https://user-images.githubusercontent.com/48891624/203199443-167bf55a-bbdb-45aa-a015-b4c938c7280c.png">



# Results: 


<img width="753" alt="image" src="https://user-images.githubusercontent.com/48891624/203199646-e8e5d68e-c918-4a10-bdcb-d3bde6380b0a.png">

<img width="937" alt="image" src="https://user-images.githubusercontent.com/48891624/203199700-831ff7a0-df10-4d0c-ab99-27127fc73b2a.png">



```
[1] Chunming Li, Chenyang Xu, Changfeng Gui, and Martin D. Fox. Distance regularized level set evolution and its
application to image segmentation. IEEE Transactions on Image Processing, 19(12):3243–3254, 2010


[2]  Chunming Li, Chenyang Xu, Changfeng Gui, and M.D. Fox. Level set evolution without re-initialization: a new
variational formulation. In 2005 IEEE Computer Society Conference on Computer Vision and Pattern Recognition
(CVPR’05), volume 1, pages 430–436 vol. 1, 2005.  

``` 


