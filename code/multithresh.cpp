/*
Author: Rishiraj Surti

About:

Thresholding an image using two OpenCV functions: 
1)	cv::threshold 
2)	cv::inRange

This program implements the cv::threshold function on an
image for a single channel.
cv::inRange function is implemented on a Video Capture frame
using three channels RGB. This program can also be used as a 
a simple object detection program.
*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace cv;

/** Function Headers */
void on_low_r_thresh_trackbar(int, void *);
void on_high_r_thresh_trackbar(int, void *);
void on_low_g_thresh_trackbar(int, void *);
void on_high_g_thresh_trackbar(int, void *);
void on_low_b_thresh_trackbar(int, void *);
void on_high_b_thresh_trackbar(int, void *);
void img_thresh(int, void *);
/** Global Variables */
int low_r=30, low_g=30, low_b=30;
int high_r=100, high_g=100, high_b=100;
int img_l = 50;
/** @function main */
int main()
{
	Mat frame, frame_threshold;
	/*For Image*/
	Mat img, img_gray, img_result;
	
	img = imread("../data/lena.jpg", 1);
	
	cvtColor(img, img_gray, COLOR_RGB2GRAY);
	namedWindow("Image Threshold", WINDOW_NORMAL);
	createTrackbar("Image T", "Image Threshold", &img_l, 255, img_thresh);
	/*For Video*/
	VideoCapture cap(0);
	namedWindow("Video Capture", WINDOW_NORMAL);
	namedWindow("Object Detection", WINDOW_NORMAL);

	//-- Trackbars to set thresholds for RGB values
	createTrackbar("Low R","Object Detection", &low_r, 255, on_low_r_thresh_trackbar);
	createTrackbar("High R","Object Detection", &high_r, 255, on_high_r_thresh_trackbar);
	createTrackbar("Low G","Object Detection", &low_g, 255, on_low_g_thresh_trackbar);
	createTrackbar("High G","Object Detection", &high_g, 255, on_high_g_thresh_trackbar);
	createTrackbar("Low B","Object Detection", &low_b, 255, on_low_b_thresh_trackbar);
	createTrackbar("High B","Object Detection", &high_b, 255, on_high_b_thresh_trackbar);

	while(char(waitKey(1))!='q'){
		cap>>frame;
		if(frame.empty())
			break;
		//-- Detect the object based on RGB Range Values
		inRange(frame,Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),frame_threshold);
		
		threshold(img_gray, img_result, img_l, 255, 1);
		//-- Show the frames
		imshow("Image Threshold", img_result);
		imshow("Video Capture",frame);
		imshow("Object Detection",frame_threshold);

	}
	return 0;
}

/** @function img_thresh */
void img_thresh(int, void *){
	setTrackbarPos("Image T", "Image Threshold", img_l);
}

/** @function on_low_r_thresh_trackbar */
void on_low_r_thresh_trackbar(int, void *)
{	
	low_r = min(high_r-1, low_r);
	setTrackbarPos("Low R","Object Detection", low_r);
}

/** @function on_high_r_thresh_trackbar */
void on_high_r_thresh_trackbar(int, void *)
{	
	high_r = max(high_r, low_r+1);
	setTrackbarPos("High R", "Object Detection", high_r);
}

/** @function on_low_g_thresh_trackbar */
void on_low_g_thresh_trackbar(int, void *)
{	
	low_g = min(high_g-1, low_g);
	setTrackbarPos("Low G","Object Detection", low_g);
}

/** @function on_high_g_thresh_trackbar */
void on_high_g_thresh_trackbar(int, void *)
{	
	high_g = max(high_g, low_g+1);
	setTrackbarPos("High G", "Object Detection", high_g);
}

/** @function on_low_b_thresh_trackbar */
void on_low_b_thresh_trackbar(int, void *)
{	
	low_b= min(high_b-1, low_b);
	setTrackbarPos("Low B","Object Detection", low_b);
}

/** @function on_high_b_thresh_trackbar */
void on_high_b_thresh_trackbar(int, void *)
{	
	high_b = max(high_b, low_b+1);
	setTrackbarPos("High B", "Object Detection", high_b);
}