//#include<stdio.h>
#include<iostream>

#include<opencv/cv.hpp>


using namespace cv;
using namespace std;

int main(){
	Mat src, dst;
	char inputimage[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";
	src = imread(inputimage, 1);
	if (!src.data) {
	
		cout << "no image" << endl;
		exit(1);
	}
	 
	//erode(src,dst,Mat(),Point(-1,-1),6);
	//dilate(src,dst,Mat(),Point(-1,-1),2);
	//morphologyEx(src, dst, CV_MOP_OPEN, Mat(), Point(-1, -1), 2); //erosion +dilation
	morphologyEx(src, dst, CV_MOP_CLOSE, Mat(), Point(-1, -1), 2); //dilation +erosion



	namedWindow("src",CV_WINDOW_AUTOSIZE);
	imshow("src",src);

	namedWindow("dst", CV_WINDOW_AUTOSIZE);
	imshow("dst", dst);

	waitKey(0);
	return 0;


}