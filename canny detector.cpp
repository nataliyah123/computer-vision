#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include"opencv2/imgproc/imgproc.hpp"
#include<opencv2/highgui/highgui.hpp>
#include<vector>
//#pragma comment(lib, "opencv_calib3d310d.lib")

using namespace std;
using namespace cv;

int main() {
	char imgreadtemp[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";
	Mat src, edges;
	Mat gray_scale;
	int lowerthreshold = 80;
	int ratio = 3;
	src = imread(imgreadtemp);
	if (!src.data) {

		cout << "image is empty" << src << endl;
		exit(1);

	}

	gray_scale.create(src.size(),src.type());
	cvtColor(src,gray_scale,CV_BGR2GRAY);

	Canny(src, edges, lowerthreshold, lowerthreshold*ratio, 3, false);

	vector<vector<Point>> mycontours;
	Mat image_bin;
	image_bin = Mat(edges.size(), CV_8UC1, 1);
	threshold(edges, image_bin, 0, 255, CV_THRESH_BINARY);// removable

    findContours(image_bin,mycontours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);// removable
	cout << "the number of elements is " << mycontours.size() << endl;

	namedWindow("canny detector", CV_WINDOW_AUTOSIZE);
	imshow("canny detector", edges);

	namedWindow("image_bin", CV_WINDOW_AUTOSIZE);
	imshow("image_bin", edges);

	waitKey(0);
	return(0);

}

