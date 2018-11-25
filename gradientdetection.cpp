#include <stdio.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include "opencv2\imgproc\imgproc.hpp"
#include <opencv2\highgui\highgui.hpp>


using namespace std;
using namespace cv;

int main() {

	char imgreadtemp[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";
	Mat src, src_gray, grad;

	//generate gradient x and gadient y;
	Mat grad_x, grad_y, abs_grad_x, abs_grad_y;
	char* window_name = "Sobel demo-simple edge detector";
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	int c;

	src = imread(imgreadtemp,CV_LOAD_IMAGE_GRAYSCALE);
	if (!src.data) {

		cout << "image is empty" << src << endl;
		exit(1);

	}

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	//GRADIENT X
	Sobel(src, grad_x, ddepth, 1, 0, 5, scale, delta, 4);
	convertScaleAbs(grad_x, abs_grad_x); //we will make a conversion of 16-bit to 8-bit, which is what we do with scale conversion.


	//GRADIENT Y
	Sobel(src, grad_y, ddepth, 0, 1, 5, scale, delta, 4);
	convertScaleAbs(grad_y, abs_grad_y); //we will make a conversion of 16-bit to 8-bit, which is what we do with scale conversion.

	//approximate the gradients

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	threshold(grad, grad, 80, 255, THRESH_BINARY);

	namedWindow("original", CV_WINDOW_AUTOSIZE);
	imshow("original", src);

	namedWindow("SOBEL GRADIENT", CV_WINDOW_AUTOSIZE);
	imshow("SOBEL GRADIENT", grad);

	waitKey(0);
	return(0);


}