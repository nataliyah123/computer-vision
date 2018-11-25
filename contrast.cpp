#include <stdio.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include "opencv2\imgproc\imgproc.hpp"
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	char inputimage[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/contrast/lowcontrastimage.jpg";
	//char inputimage[] = "C:/Users/sumaira/mscs/Documents/Visual Studio 2015/Projects/COMPUTER VISION USING OPENCV/obtaininghist/obtaininghist/image030.png";
	
	Mat original_image, equalized_image;

	original_image = cv::imread(inputimage,CV_LOAD_IMAGE_GRAYSCALE);
	if (!original_image.data) {
		cout << "myimage doesn't contain any data" << inputimage << endl;

		exit(1);
	}


	// create variables for histogram
	int histsize = 256;
	// the defined range for gray level 0-255
	float range[] = {0,256};
	const float* histrange = { range };
	bool uniform = true;
	bool accumulate = false;
	// next we create an image where we want to display our histogram and equalize the hist image

	//int hist_w = 512; int hist_h = 400; // choosing the height and width of destination image where we will draw a histogram
	int hist_w =183; int hist_h = 275;
	Mat histImage(hist_w,hist_h,CV_8UC3,Scalar(0,0,0));//with histimage we create an image on which we are going to display our histogram
	Mat equalizedHistImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));

	// now we declare the bin width of the histogram

	int bin_w = cvRound((double)hist_w/histsize);
	
	// now we are going to calculate histogram
	Mat original_hist, normalized_hist, equalized_normalized_hist, equalized_hist;
	calcHist(&original_image, 1 , 0 , Mat(), original_hist, 1 , &histsize , &histrange, uniform, accumulate);

	cout << "original image" << endl;

	// dislay the values of original histogram
	for (int h = 0; h < histsize;h++) {
		int binval = original_hist.at<float>(h);
		cout << " " <<binval;

	}
	cout << endl;
	//normalize the histogram [0,_histImage.rows]
	normalize(original_hist, normalized_hist,0,histImage.rows,NORM_MINMAX,-1,Mat());
	cout << endl;
	cout << "normalized histogram";
	//display the values
	for (int j = 0; j < histsize;j++) {
		float binval = normalized_hist.at<float>(j);
		cout << " " << binval;
	
	}
	cout << endl;

	//equalize and calculate normalized histogram for a gray scale image

	equalizeHist(original_image, equalized_image);
	calcHist(&equalized_image, 1, 0, Mat(), equalized_hist, 1, &histsize, &histrange, true, false);
	cout << "EQUALIZE IMAGE" << endl;

	//display the values
		for (int h = 0; h < histsize; h++) {
			int binval = equalized_hist.at<float>(h);
			cout << " " << binval;
		}
		cout<< endl;

		cout << "normalized equalized histogram" << endl;
		// normalize the equalized histogram
		normalize(equalized_hist, equalized_normalized_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		//display the values for the equalized normalized histogram
		for (int h = 0; h < histsize; h++) {
			int binval = equalized_normalized_hist.at<float>(h);
			cout << " " << binval;
		}
		cout << endl;
		// DISPLAY HISTOGRAMS.
		for (int i = 0; i < histsize;i++) {
			line(histImage,Point(bin_w*i,hist_w),Point(bin_w*i,hist_h-cvRound(normalized_hist.at<float>(i))),Scalar(255,0,0),bin_w,8,0);
			line(equalizedHistImage, Point(bin_w*i, hist_w), Point(bin_w*i, hist_h - cvRound(equalized_normalized_hist.at<float>(i))), Scalar(0, 255, 0), bin_w, 8, 0);

		}

		namedWindow("original", WINDOW_AUTOSIZE);
		imshow("original", original_image);

		namedWindow("equalized", WINDOW_AUTOSIZE);
		imshow("equalized", equalized_image);

		namedWindow("originalhistogram", WINDOW_AUTOSIZE);
		imshow("originalhistogram", original_hist);

		namedWindow("equalized histogram", WINDOW_AUTOSIZE);
		imshow("equalized histogram", equalizedHistImage);

		waitKey(0);
		return(0);




}
