#pragma once
#include <iostream>
#include <time.h>// 시간 측정 위해서
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

Mat input_im, dst;
clock_t start_time, end_time;

void blur_openCV(int blur_value, void *userData);
void blur_userdefine(int blur_value, void *userData);

string type2str(int type);

using namespace std;


void blur_openCV(int blur_value, void *userData) 
{
	string &win_name = *(static_cast<string*>(userData));
	Size ksize(blur_value, blur_value);
	start_time = clock();

	if (blur_value % 2 == 1) {
		blur(input_im, dst, ksize, Point(-1, -1), BORDER_DEFAULT);

		end_time = clock();
		cout << "Threshold value : " << blur_value << ", Exec Time : " << (double)(end_time - start_time) << " (msec)" << endl;

	}
	else {
		Size ksize(blur_value+1, blur_value+1);
		blur(input_im, dst, ksize, Point(-1, -1), BORDER_DEFAULT);

		end_time = clock();
		cout << "Threshold value : " << blur_value+1 << ", Exec Time : " << (double)(end_time - start_time) << " (msec)" << endl;
	}
		
	imshow(win_name, dst);
}

void blur_userdefine(int blur_value, void *userData) {
	string &win_name = *(static_cast<string*>(userData));
	float b_v = (float) blur_value;
	float ele_odd = 1 / (b_v*b_v);
	float ele_even = 1 / ((b_v+1)*(b_v+1));

	start_time = clock();

	if (blur_value % 2 == 1) {
		
		Mat kernel_o = Mat(blur_value, blur_value, CV_32FC1, Scalar(ele_odd));
		filter2D(input_im, dst, -1, kernel_o, Point(-1, -1), 0, BORDER_DEFAULT);

		end_time = clock();
		cout << "Threshold value : " << blur_value << ", Exec Time : " << (double)(end_time - start_time) << " (msec)" << endl;

	}
	else {
	
		Mat kernel_e = Mat(blur_value+1, blur_value+1, CV_32FC1, Scalar(ele_even));
		
		filter2D(input_im, dst, -1, kernel_e, Point(-1, -1), 0, BORDER_DEFAULT);

		end_time = clock();
		cout << "Threshold value : " << blur_value+1 << ", Exec Time : " << (double)(end_time - start_time) << " (msec)" << endl;
	}


	imshow(win_name, dst);
}

string type2str(int type) {
	// https://stackoverflow.com/questions/10167534/how-to-find-out-what-type-of-a-mat-object-is-with-mattype-in-opencv
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}

int main(int argc, char *argv[])
{
	if (argc != 3) {

		if (argc == 2) {
			cout << "[프로그램 사용법]" << endl;
			cout << "명령문 : snnnnnnHW01.exe" << *argv[1]<< "flag<ent>" << endl;
			cout << "flag : 1 - opencv function 사용" << endl;
			cout << "flag : 2 - loop로 brute force 사용" << endl;
			return 0;
		}

		cout << "[프로그램 사용법]" << endl;
		cout << "명령문 : ~.exe image_file<ent>" << endl;

	   	return 0;
	}
	//파일 주소는 argv[1]로 들어옴
	input_im = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (input_im.empty())
	{ 
		cout << "File open Error!" << endl; 
		return -1; 
	}
	cout << "Image size :" << input_im.size() << ", Type:" << type2str(input_im.type()) << endl;
	cout << argv[1] << argv[2] << endl;

	string window_name = "Average Filtering Window";
	namedWindow(window_name);
		
	//Create track bar to change kernel size
	int start_value = 3;
	int max_value = 15;

	

	if (*argv[2] == '1')
	{
		createTrackbar("KernelSize", window_name, &start_value, max_value, blur_openCV, static_cast<void*>(&window_name));
	}
	else if (*argv[2] == '2')
	{
		createTrackbar("KernelSize", window_name, &start_value, max_value, blur_userdefine, static_cast<void*>(&window_name));
	}
	
	else 
	{
		cout << "Wrong flag!!" << endl;
	}

	imshow(window_name, input_im);
	waitKey(0);
	
	return 0;
}