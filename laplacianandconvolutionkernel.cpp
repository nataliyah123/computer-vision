#include <stdio.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include "opencv2\imgproc\imgproc.hpp"
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main() {

	char imgreadtemp[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";

	Mat src = imread(imgreadtemp,-1);
	if (!src.data ) {

		cout << "image is empty" << src << endl;
		exit(1);

			}
	Mat imagefilt(src.rows,src.cols,CV_8U);
	Mat kernel(3, 3, CV_8S);

	kernel.at<char>(0) = -1; kernel.at<char>(1) = -1; kernel.at<char>(2) = -1;
	kernel.at<char>(3) = -1;; kernel.at<char>(4) = 9; kernel.at<char>(5) = -1;
	kernel.at<char>(6) = -1; kernel.at<char>(7) = -1; kernel.at<char>(8) = -1;
/*
	Kernel.at<char>(0) = 0; Kernel.at<char>(1) = -1; Kernel.at<char>(2) = 0;
	Kernel.at<char>(3) = -1;; Kernel.at<char>(4) = 5; Kernel.at<char>(5) = -1;
	Kernel.at<char>(6) = 0; Kernel.at<char>(7) = -1; Kernel.at<char>(8) = 0;
*/

/*
Kernel.at<char>(0) = -1; Kernel.at<char>(1) = -2; Kernel.at<char>(2) = -1;
Kernel.at<char>(3) = -1;; Kernel.at<char>(4) = 13; Kernel.at<char>(5) = -1;
Kernel.at<char>(6) = -1; Kernel.at<char>(7) = -2; Kernel.at<char>(8) = -1;
*/
	filter2D(src, imagefilt, CV_8U, kernel);


	namedWindow("original");
		imshow("original", imagefilt);

		namedWindow("edge enhancement");
		imshow("edge enhancement",imagefilt);
	
	waitKey(0);
	return(0);
}
