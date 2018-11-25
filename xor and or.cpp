#include<iostream>
#include <stdio.h>
#include <opencv2\core\core.hpp>
#include "opencv2\imgproc\imgproc.hpp"
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat artificialimage1 = Mat::zeros(Size(400, 200),CV_8UC1);
	Mat artificialimage2 = Mat::zeros(Size(400, 200),CV_8UC1);

	artificialimage1(Range(0, artificialimage1.rows), Range(0, artificialimage2.cols / 2)) = 255;
	artificialimage2(Range(100, 150), Range(150,350))=255;

	
	imshow("img1",artificialimage1);

	
	imshow("img2", artificialimage2);
	Mat result;
/*
	bitwise_and(artificialimage1,artificialimage2,result);
	imshow("img1", result);
*/

	/*
	bitwise_or(artificialimage1,artificialimage2,result);
	imshow("img3", result);
	
	*/

	
	bitwise_not(artificialimage1,result);
	imshow("img3", result);

	

	/*
	bitwise_xor(artificialimage1,artificialimage2,result);
	imshow("img3", result);

	*/

	cvWaitKey(0);
	return(0);


}