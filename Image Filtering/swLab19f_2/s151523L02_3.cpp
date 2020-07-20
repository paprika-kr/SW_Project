#pragma once
#include <iostream>
#include <time.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

Mat input_im, dst;
clock_t start_time, end_time;

void sobel_blur_openCV(int sblur_value, void *userData);


string type2str(int type);

using namespace std;


void sobel_blur_openCV(int sblur_value, void *userData)
{
	string &win_name = *(static_cast<string*>(userData));
	int dx = 1, dy = 1;
	start_time = clock();

	if (sblur_value % 2 == 1) {
	
		Sobel(input_im, dst,-1, dx, dy, sblur_value, 1, 0, BORDER_DEFAULT);
		end_time = clock();
		cout << "Threshold value : " << sblur_value << ", Exec Time : " << (double)(end_time - start_time) << " (msec)" << endl;

	}
	else {

		Sobel(input_im, dst, -1, dx, dy, sblur_value + 1, 1, 0, BORDER_DEFAULT);
				end_time = clock();
		cout << "Threshold value : " << sblur_value + 1 << ", Exec Time : " << (double)(end_time - start_time) << " (msec)" << endl;
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
	if (argc != 2) {
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
	cout << argv[1] << endl;

	string window_name = "Sobel Operator Window";
	namedWindow(window_name);

	//Create track bar to change kernel size
	int start_value = 3;
	int max_value = 15;


	createTrackbar("KernelSize", window_name, &start_value, max_value, sobel_blur_openCV, static_cast<void*>(&window_name));


	imshow(window_name, input_im);
	waitKey(0);

	return 0;
}