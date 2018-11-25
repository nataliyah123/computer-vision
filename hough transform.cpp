#include<stdio.h>
#include<iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;


/*int main(int argc,char**argv) {

	char inputimage[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";
	Mat src = imread(inputimage,0);

	if (!src.data) {

		cout << "image is empty" << endl;
		exit(1);
	}

	Mat dst, cdst;
	Canny(src,dst,50,200,3);
	cvtColor(dst,cdst,CV_GRAY2BGR);

	vector<Vec2f>lines;
	HoughLines(dst, lines, 1, CV_PI / 180, 200, 0, 0); //vector to store the detection lines

	for (size_t i = 0; i < lines.size(); i++) {  //code to paint the lines in the image

		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0+1000*(-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 255),3, CV_AA);
	}

	imshow("source", src);
	resizeWindow("source", 512, 512);
	imshow("detected lines", cdst);
	resizeWindow("detected lines", 512, 512);



	cvWaitKey(0);
	return 0;
}
*/
/*
int main(int argc,char**argv) {

char inputimage[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";
Mat src = imread(inputimage,0);

if (!src.data) {

cout << "image is empty" << endl;
exit(1);
}

Mat dst, cdst;
Canny(src,dst,50,200,3);
cvtColor(dst,cdst,CV_GRAY2BGR);

vector<Vec4i>lines;
HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10); //vector to store the detection lines

for (size_t i = 0; i < lines.size(); i++) {
	Vec4i l =lines[i];
	line(cdst, Point(l[0],l[1]), Point(l[2],l[3]), Scalar(0,0, 255),3, CV_AA);

	}


	imshow("source",src);
	resizeWindow("source",512,512);
	imshow("detected lines", cdst);
	cvResizeWindow("detected lines",512,512);

	waitKey(0);
	return 0;

	}
	

*/

int main(int argc,char**argv) {
Mat src,src_gray;
//char inputimage[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";
char inputimage[] = "TIRE.JPG";
 src = imread(inputimage,1);

if (!src.data) {

cout << "image is empty" << endl;
exit(1);
}



cvtColor(src,src_gray,CV_BGR2GRAY);

GaussianBlur(src_gray,src_gray,Size(9,9),2,2);

vector<Vec3f>circles;
HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT,1, src_gray.rows /6, 100, 75, 0,0); //vector to store the detection lines

for (size_t i = 0; i < circles.size(); i++) {
Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
int radius =(cvRound(circles[i][2]));
circle(src,center,3,Scalar(0,255,0),-1,8,0);
circle(src,center,radius,Scalar(255,0,0),3,8,0);


}

namedWindow("hough transform demo",CV_WINDOW_AUTOSIZE);
imshow("hough transform demo",src);
 

waitKey(0);
return 0;

}
















