// for larger images it would be wise to calculate all possible values beforehand and during the assignment just make the assignment, by using a lookup table. Lookup tables are simple arrays (having one or more dimensions) that for a given input value variation holds the final output value. Its strength lies in that we do not need to make the calculation, we just need to read the result.

#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "opencv2\imgproc\imgproc.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int main() {

	char imageread[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";
	Mat myimage = cv::imread(imageread);
	Mat resultantlut;
	int i;

	if (!myimage.data) {
		cout << "myimage doesn't contain any data" << imageread << endl;
		exit(1);
	}

	// make a Mat type matrix for lut

	Mat mylookuptable(1, 256, CV_8U);

	for (i = 0; i < 256; ++i) {

		//mylookuptable.at<uchar>(i) = 255-i;
		//mylookuptable.at<uchar>(i) = pow((float) i *255,(float)(1 / 2.0));
		mylookuptable.at<uchar>(i) = pow((float)i,(float) 3.0)/ (255*255);
	}
	LUT(myimage,mylookuptable, resultantlut);

	namedWindow("original", CV_WINDOW_AUTOSIZE);
	imshow("original", myimage);
	
	namedWindow("lutimage", CV_WINDOW_AUTOSIZE);
	imshow("lutimage", resultantlut);

	waitKey(0);
	return(0);

}

