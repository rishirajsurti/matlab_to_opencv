/*
Author: Rishiraj Surti
About:
This program implements equivalent of imfill in Matlab.
First of all the image is binary-thresholded.
Then FloodFill function is used to fill the connected components.
The resultant image is obtained by bitwise(pixelwise) OR of inverted floodfill image
and the binary thresholded image.
*/

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <stdlib.h>
using namespace cv;
using namespace std;

int main(){
    Mat img, img_bin, img_thresh, img_ff, img_ff_inv, img_result;
    //read an image
    img = imread("../data/coins.jpg", CV_LOAD_IMAGE_COLOR);
    
    //convert to grayscale
    cvtColor(img, img, CV_BGR2GRAY);

    //convert to binary
    threshold(img, img_bin, 100, 255, THRESH_BINARY_INV );

    //clone the binary image
    img_ff = img_bin.clone();

    uchar fillValue = 255;
    Point seed(0, 0);
    Mat mask;
    Canny(img_bin, mask, 200, 200);
    copyMakeBorder(mask, mask, 1, 1, 1, 1, BORDER_REPLICATE);

    //FloodFill
    floodFill(img_ff,  mask, seed, cv::Scalar(255) ,0, cv::Scalar(), cv::Scalar(), 8);
    
    bitwise_not(img_ff, img_ff_inv);
    
    img_result = (img_bin | img_ff_inv) & img_ff;
    imshow("Original Image", img);
    imshow("Binary Image", img_bin);
    imshow("Floodfill Image", img_ff);
    imshow("Inverted Floodfill", img_ff_inv);
    imshow("Result", img_result);
    waitKey(0);
    return 0;
}