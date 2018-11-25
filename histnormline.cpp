#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main() {
	// filename
	char imageread[] = "image030.png";
	Mat  src, dis;

	// check whether the image is loaded correctly or not

	src = cv::imread(imageread);
	if (!src.data) {
		cout << "image is not loaded correctly" << imageread << endl;
		exit(1);
	}
	// seperate an image into R G B planes
	vector <Mat>bgr_planes;
	split(src, bgr_planes); //To extract a channel from a new-style matrix, use mixChannels() or split() .
	//The function split() does the reverse operation. If you need to shuffle channels in some other advanced way, use mixChannels().

	// variables for the histogram

	int histSize = 256;

	//ranges
	float range[] = {0,256};
	const float *histrange = { range };

	bool uniform = true;
	bool accumulate = false;
	Mat b_hist, g_hist, r_hist;// ouput histogram 5 parameter

	//calculate histogram

	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist,1,&histSize,&histrange,uniform,accumulate);//  10 parameters are used.b,,bgr_planes are source arrays,1 is number of source images, 0 is list of channels used to compute histogram,
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histrange, uniform, accumulate);//g_hist is output histogram, 1 is for histogram dimensionality,
	//histsize =The number of bins per each used dimension,
	//histrange=Array of the dims arrays of the histogram bin boundaries in each dimension.
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histrange, uniform, accumulate);// channels are different dimensions of an image that holds value for every pixel.
	// RGB image has 3 channels . bit depth or color depth ,when the image is digitized it is converted into numbers each channel is encoded in as few number of bits as possible such as 8 bits per channel
	// or 16 bits per channel. indexed image get rid of channel altogether.
	//cv_8u,cv_32fc1,
	
	//draw a histogram for each channel R,G,B

	int hist_w = 720;
	int hist_h = 1280;

	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_w,hist_h,CV_8UC3,Scalar(0,0,0));//with histimage we create an image on which we are going to display our histogram

	// normalize result to [0,histimage.rows]

	 normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	 normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	 normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	 /// Draw for each channel
	 for (int i = 1; i < histSize; i++)
	 {
		 line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))), // not read
			 Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			 Scalar(255, 0, 0), 2, 8, 0);
		 line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			 Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			 Scalar(0, 255, 0), 2, 8, 0);
		 line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			 Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			 Scalar(0, 0, 255), 2, 8, 0);
	 }

	 namedWindow("calculate histo", CV_WINDOW_AUTOSIZE);
	 imshow("calculate histo", histImage);

	 waitKey (0);
	 return (0);




}

// dims: The number of parameters you want to collect data of.In our example, dims = 1 because we are only counting the intensity values of each pixel(in a greyscale image).
// bins : It is the number of subdivisions in each dim.In our example, bins = 16
// range : The limits for the values to be measured.In this case: range = [0, 255]


//Histograms are collected counts of data organized into a set of predefined bins
//[0,255]= [0,15]U[16,31]U.....[240,255]
//range = bin1 U bin2 .....binn.

// NORMALIZE
//  b_hist: Input array
//	b_hist : Output normalized array(can be the same)
//	0 and **histImage.rows** : For this example, they are the lower and upper limits to normalize the values of r_hist
//	NORM_MINMAX : Argument that indicates the type of normalization(as described above, it adjusts the values between the two limits set before)
//	- 1 : Implies that the output normalized array will be the same type as the input
//	Mat() : Optional mask