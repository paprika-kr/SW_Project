#pragma once
#include <iostream>
#include <time.h>// �ð� ���� ���ؼ�
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

Mat input_im, dst;
clock_t start_time, end_time;

void binaryThresholding_opencvCommand(int kernelsize, void *userData);
string type2str(int type);