#include <stdio.h>
#include <iostream>
#include "opencv/cv.hpp"
#include <stdlib.h>

using namespace std;
using namespace cv;

#define MAX_CORNERS 500  //  my macros
#define ESCAPE 27

int main(int argc, char* argv[]) {

	VideoCapture cap ;
	Mat frame;

	char keypressed=0;
	bool success;
	cap.open(0);
	if (!cap.isOpened()) {
		cout << "video is empty"  << endl;
		getchar();
		return 1;
	
	}

	//parameters for shi tomasi algorithms

	vector<Point2f> cornerA, cornerB;
	double qualitylevel =0.01;
	double minDistance =10 ;
	int blocksize = 3;
	bool useHarrisDetector = false; // use cornermineignval then
	double k= 0.04;
	int maxcorner = MAX_CORNERS;


	//winsize has to be 11 or 13 otherwise nothing is to be found

	vector<uchar> status;
	vector<float> error;
	int winsize = 11;
	int maxlvl = 5;

	//objects

	Mat img_prev, img_next, grayA, grayB;


	success = cap.read(frame);
	if (success == false) {
		cout << "cannot read from file" << endl;
		getchar();
		return 1;
	}

	img_prev = frame.clone();
	// windows for all images

	namedWindow("corners A", CV_WINDOW_AUTOSIZE);
	namedWindow("corners B", CV_WINDOW_AUTOSIZE);
	// read frame by frame in a loop
	while (keypressed != ESCAPE) {
		success = cap.read(frame);

		if (success = false) {

			cout << "cannot read from file" << endl;
			getchar();
			return 1;
			}
		img_next = frame.clone();

		//convert to grayscale
		cvtColor(img_prev,grayA,CV_BGR2GRAY);
		cvtColor(img_prev, grayB, CV_BGR2GRAY);

		//APPLY CORNER DETECTION

		goodFeaturesToTrack(grayA, cornerA, maxcorner, qualitylevel, minDistance, noArray(), blocksize, useHarrisDetector, k);

		calcOpticalFlowPyrLK(grayA, grayB, cornerA, cornerB, status, error, Size(winsize, winsize), maxlvl);

		for (int i = 0; i < cornerA.size(); i++) {


			line(img_prev, cornerA[i], cornerB[i], Scalar(0, 255, 0), 2);
		}
			imshow("cornerA", img_prev);
			imshow("cornerB", img_next);


			keypressed = waitKey(1);
			img_prev = img_next;

		}
		//free the memory
		img_prev.release();
		img_next.release();
		
		grayA.release();
		grayB;
		destroyAllWindows();


		return 0;
	
}