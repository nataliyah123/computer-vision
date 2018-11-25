#include <stdio.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include "opencv2\imgproc\imgproc.hpp"
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main() {

	char imgreadtemp[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";
	char model[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/model.png";

	int i;

	Mat src = imread(imgreadtemp);
	Mat temp1 = imread(model);

	if (!src.data || !temp1.data) {

		cout << "image is empty" << src << endl;
		exit(1);

	}
	// create a new image with the same number of height and width as the original image minus the template for six different methods of matchtemplate.
	Mat ftmp[6];
	int iwidth;
	int iheight;

	// reserve memory for the various methods.

	iwidth = src.cols - temp1.cols + 1;
	iheight = src.rows - temp1.rows + 1;


	for (i = 0; i < 6; i++)

		ftmp[i].create(iheight, iwidth, CV_32SC1);

	for (i = 0; i < 6; i++) {

		matchTemplate(src, temp1, ftmp[i], i);
		normalize(ftmp[i], ftmp[i], 1, 0, CV_MINMAX);
	}





	namedWindow("src", CV_WINDOW_AUTOSIZE);
	imshow("src", src);

	namedWindow("temp1", WINDOW_AUTOSIZE);
	imshow("temp1", temp1);

	namedWindow("SQIFF", CV_WINDOW_AUTOSIZE);
	imshow("SQIFF", ftmp[0]);

	namedWindow("SQIFF_NORMED", CV_WINDOW_AUTOSIZE);
	imshow("SQIFF_NORMED", ftmp[1]);

	namedWindow("CORR", CV_WINDOW_AUTOSIZE);
	imshow("CORR", ftmp[2]);

	namedWindow("CORR_NORMED", CV_WINDOW_AUTOSIZE);
	imshow("CORR_NORMED", ftmp[3]);



	namedWindow("COEFF", CV_WINDOW_AUTOSIZE);
	imshow("COEFF", ftmp[4]);

	namedWindow("COEFF_NORMED", CV_WINDOW_AUTOSIZE);
	imshow("COEFF_NORMED", ftmp[5]);

	waitKey(0);
	return(0);


	}
