#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>
#include<vector>
#include<iostream>

#define nclass1 11
#define nclass2 13
//#define nclass3 13
#define nentry (nclass1+nclass2)

using namespace cv;
using namespace std;


static Ptr<ml::TrainData>
prepare_train_data(const Mat& data, const Mat& reponse, int n_trainsample) {
	Mat sample_idx = Mat::zeros(data.rows,1,CV_8UC1);
	Mat train_sample = sample_idx.colRange(0, n_trainsample);
	train_sample.setTo(Scalar::all(1));

	//Convert an array data type to TrainData
	int nvars = data.cols;
	Mat var_type(nvars, 1, 1, CV_8U);
	var_type.setTo(Scalar::all(ml::VAR_ORDERED));  //this may not be used in my program
	var_type.at<char>(nvars) = ml::VAR_CATEGORICAL;
	return ml::TrainData::create(data, ml::ROW_SAMPLE, reponse, noArray(), sample_idx, noArray(), var_type);
	//the above statement is creating data from in memory array ; 
	//@param 1 should CV_32F TYPE,@param 2 ml_sampletypes,@param3 if the response is a scalar the data will be saved as a 
	// single row or single column the type of data must be CV_32F OR CV_32S in the first case the data will be ordered by default 
	// in the later case the data will be categorical.
}
int main() {

	Mat image, image_bin, image_color;
	vector<vector<Point>> mycontour;

	int i = 0, myclass, k = 0;
	double perimeter, area;
	char* numberof_class[2] = { "screw","bolt" };  //im my program there will be three classes

	char * inputimage[2] = { "Clase1.jpg","Clase2.jpg" };
	Ptr<ml::NormalBayesClassifier> mybayes = ml::NormalBayesClassifier::create();


	Mat train_data(nentry, 2, CV_32FC1);
	Mat response_data(nentry,  1, CV_32FC1);
	Mat test_data(nentry, 2, CV_32FC1);
	Mat test_data_2(1, 2, CV_32FC1);

	for (myclass = 0; myclass < 2; myclass++) {

		image = imread(inputimage[myclass]);
		if (!image.data) {
			cout << "image is empty" << endl;
			exit(1);
		}

		image_bin = (image.size(), CV_8UC1, 1);
		cvtColor(image,image,CV_BGR2GRAY);
		threshold ( image, image_bin, 130, 255, CV_THRESH_BINARY);

		namedWindow("image_bin", 1);
		imshow("image_bin", image_bin);

		findContours(image_bin, mycontour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

		cout << "the total number of" << numberof_class[myclass] << "contour size" << mycontour.size() << endl;// here i may have to apply the loop to output like c
		// the above will give the total number of parts.
		for (size_t idx=0; idx < mycontour.size();idx++) {// loop to fill the data with the parameters perimeter area
			area = contourArea(mycontour[idx],false);
			perimeter = arcLength(mycontour[idx], 1);
			

			train_data.at<float>(k,0) = perimeter;
			train_data.at<float>(k, 1)=area;
			response_data.at<float>(k) =myclass ;
			k++;
			//cout << "area s " << area << endl;

				
		}
		cvWaitKey(0);

	}


	int ntrain_samples = (int)(nentry);
	Ptr<ml::TrainData> tdata=prepare_train_data(train_data,response_data,ntrain_samples);
	mybayes->train(tdata);

	//proof

	char  inputimage2[] =  "Clasif.jpg" ;
	Mat imageclasify = imread(inputimage2, 1);
	image_bin = Mat(imageclasify.size(),8,1);
	threshold(imageclasify, image_bin, 130, 255, CV_THRESH_BINARY);

	image_color = Mat(imageclasify.size(),CV_8UC1,3);
	cvtColor(imageclasify, image_color, CV_GRAY2BGR);
	imshow("IMAGE_COLOR",image_color);


	findContours(image,image_color,CV_RETR_EXTERNAL,CHAIN_APPROX_NONE);
	cout << "contour size" << mycontour.size() << endl;

	Mat clasif(mycontour.size(),1,CV_32FC1);
	for (size_t idx = 0; idx < mycontour.size(); idx++) {

		area = contourArea(mycontour[idx],false);
		perimeter = arcLength(mycontour.size(), 1);

		test_data_2.at<float>(0, 0) = perimeter;
		test_data_2.at<float>(0, 1) = area;

		clasif.at<float>(idx) = mybayes->predict(test_data_2);


		cvtColor(image, image_color, CV_BGR2GRAY);
		Scalar color_rojo(0, 25, 0);
		drawContours(image_color,mycontour,idx,color_rojo,2);
		imshow("image_color",image_color);
		cout << "number of classes" << numberof_class[(int)clasif.at<float>(idx)] << endl;
		waitKey(0);

	}

	return 0;
}

// in my program i may need to use erode or dilation




