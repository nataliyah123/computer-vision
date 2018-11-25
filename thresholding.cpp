#include<stdio.h>
#include "iostream"
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"


using namespace std;
using namespace cv;

int main() {

	Mat src, src_gray, dst;

	src = imread("C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/assignment 2 bayes classifier/assignment 2 bayes classifier/Clase1.JPG");

	if (!src.data) {
		cout << "image is empty";
		exit(1);
	}

	cvtColor(src,src_gray, CV_BGR2GRAY);

	//threshold(src_gray, dst, 150, 255, THRESH_TOZERO_INV);
	//threshold(src_gray, dst, 50, 255, THRESH_BINARY);
	//threshold(src_gray, dst, 150, 255, THRESH_TOZERO);
	//threshold(src_gray, dst, 50, 255, THRESH_TRUNC);
	threshold(src_gray, dst, 50, 255,THRESH_BINARY_INV);

	namedWindow("src", CV_WINDOW_AUTOSIZE);
	imshow("src", src);
	namedWindow("dst", CV_WINDOW_AUTOSIZE);
	imshow("dst", dst);


	waitKey(0);
	return (0);

}