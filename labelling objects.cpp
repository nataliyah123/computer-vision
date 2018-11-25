#include<stdio.h>
#include<iostream>
#include<opencv/cv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

	char inputimage[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";
	Mat src, dst, srcclone;
	src = imread(inputimage, 1);
	if (!src.data) {
		cout << "no data" << endl;
		exit(1);

	}
	imshow("src", src);
	resizeWindow("src", 512, 512);
	//prepare the image to find the contour
	cvtColor(src, dst, CV_BGR2GRAY);
	threshold(dst,dst,130,255,CV_THRESH_BINARY);

	//FIND THE CONTOUR and clone the image so the original image is not overwritten
	vector<vector<Point>>  contour;
	srcclone = dst.clone();
	findContours(srcclone,contour,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);

	//DRAW THE CONTOUR
	Mat contourImage(dst.size(), CV_8UC3, Scalar(0, 0, 0));
	Scalar color[3];

	color[0] = Scalar(255,0,0);
	color[1] = Scalar(0,255,0);
	color[2] = Scalar(0,0,255);

	for (size_t idx = 0; idx < contour.size(); idx++)
		drawContours(contourImage,contour,idx,color[idx %3]);

	imshow("contour", contourImage);
	resizeWindow("contour",512,512);

	waitKey(0);
	return 0;

}