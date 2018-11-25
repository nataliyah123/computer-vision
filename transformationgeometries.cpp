
#include <stdio.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include "opencv2\imgproc\imgproc.hpp"
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main() {

	char imgreadtemp[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";
	Mat src, dst;

	src = imread(imgreadtemp);
	if (!src.data ) {

		cout << "image is empty" << imgreadtemp << endl;
		exit(1);

	}
	imshow("src",src);

	//scale
	resize(src,dst,Size(0,0),0.5,0.5,INTER_LINEAR);
	imshow("scale",dst);

	//translation
	dst = Mat::zeros(src.size(),src.type());
	src(Rect(100,100,src.cols-100,src.rows-100)).copyTo(dst(cv::Rect(0,0,dst.cols-100,dst.rows-100)));
	imshow("translation",dst);

	//rotation
	int len = max(src.cols, src.rows);
	double angle = 60;
	Point2f pt(len/2.0,len/2.0);
	Mat r = getRotationMatrix2D(pt,angle,1.0);
	warpAffine(src,dst,r,Size(len,len));

	imshow("rotation", dst);

	//reflection
	flip(src,dst,1);
	imshow("reflection",dst);


	waitKey(0);
	return(0);



}