#pragma once
#include <stdlib.h>
#include <iostream>
#include <time.h>// 시간 측정 위해서
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <queue>

using namespace cv;

Mat input_im, dst;
clock_t start_time, end_time;

void movingAvrg_filter(int blur_value, void *userData);

string type2str(int type);

using namespace std;


void movingAvrg_filter(int blur_value, void *userData)
{
	string &win_name = *(static_cast<string*>(userData));
	dst = input_im;
	uchar *imdata = (input_im).data;
	uchar *data;
	uchar *dstdata = (dst).data;

	queue<int> Q;

	int cnt_c = 1;
	int cnt_r = 1;
	int tmp = 0;
	int cut, cutt;
	int q_pop;
	int h = input_im.rows;
	int w = input_im.cols;
	float sum = 0;

	start_time = clock();

	if (blur_value % 2 == 0)
		blur_value++;

	if (blur_value > 15)
		blur_value = 15;

	if (blur_value < 1)
		blur_value = 1;

	for (int s = 0 - blur_value / 2; s <= blur_value / 2; s++) {
		//처음 커널 data 값 큐에 삽입
		for (int r = 0 - blur_value / 2; r <= blur_value / 2; r++) {
			Q.push(*(imdata + (r*w) + s));

			if ((r >= 0) && (s >= 0)) {
				sum = sum + *(imdata + (r*w) + s);
			}
		}
	}

	for (int p = 0; p < h * w * dst.channels(); p++) {

		cut = blur_value - (h - cnt_c);
		cutt = blur_value - cnt_c;

		if (cnt_r >= w) {
			tmp = 0;
			*dstdata++ = (uchar)(sum / ((blur_value)*(blur_value)));

			for (int s = 0; s <= (blur_value / 2); s++) {
				for (int r = (0 -blur_value / 2); r <= (blur_value / 2); r++) {

					if ((cnt_c <= h - (blur_value / 2)) && (cnt_c > (blur_value / 2))) {
						tmp = tmp + *(imdata - s + r * w);
					}
					else if (cnt_c > h - (blur_value / 2)) {
						if (cut >= 0) {
							tmp = tmp + *(imdata - s + r * w);
							cut--;
						}
					}
					else if (cnt_c <= (blur_value / 2)) {

						if (cutt <= blur_value / 2) {
							tmp = tmp + *(imdata - s + r * w);
						}
						cutt--;
					}
				}
			}
			*imdata++;
			cnt_r = 1;
			cnt_c++;
			sum = sum - tmp;

			cut = blur_value - (h - cnt_c);
			cutt = blur_value - cnt_c;

			for (int s = 0; s < blur_value / 2; s++) {
				for (int r = 0 - blur_value / 2; r <= blur_value / 2; r++) {

					if ((cnt_c <= h - (blur_value / 2)) && (cnt_c > (blur_value / 2))) {
						sum = sum + *(imdata + s + r * w);
					}
					else if (cnt_c > h - (blur_value / 2)) {
						if (cut >= 0) {
							sum = sum + *(imdata + s + r * w);
							cut--;
						}
					}
					else if (cnt_c <= (blur_value / 2)) {

						if (cutt <= blur_value / 2) {
							sum = sum + *(imdata + s + r * w);
						}
						cutt--;
					}

				}
			}

		}

		else {
			*imdata++;
			tmp = 0;

			cut = blur_value - (h - cnt_c);
			cutt = blur_value - cnt_c;

			*dstdata++ = (uchar)(sum / ((blur_value)*(blur_value)));
			cnt_r++;
		}

		for (int r = (0 - blur_value / 2); r <= (blur_value / 2); r++) {
			//커널 밸류값 반복
			q_pop = Q.front();

			if ((cnt_c <= h - (blur_value / 2)) && (cnt_c > (blur_value / 2))) {
				//커널의 위아래가 이미지 안에 위치할 때

				if ((cnt_r <= w - (blur_value / 2)) && (cnt_r > (blur_value / 2) + 1)) {
					//커널의 좌우가 이미지 안에 위치할 때
					sum = sum - q_pop + *(imdata + (blur_value / 2) + (r * w));
				}
				else if (cnt_r > w - (blur_value / 2)) {
					//커널의 우측이 이미지 밖으로 나갈 때
					sum = sum - q_pop;
				}
				else if (cnt_r <= (blur_value / 2) + 1) {
					//커널의 좌측이 이미지 밖으로 나갈 때
					sum = sum + *(imdata + (blur_value / 2) + (r * w));
				}

			}

			else if (cnt_c > h - (blur_value / 2)) {
				//커널 아래가 이미지 밖으로 나갈 때

				if ((cnt_r <= w - (blur_value / 2)) && (cnt_r > (blur_value / 2) + 1)) {
					//커널의 좌우가 이미지 안에 위치할 때
					if (cut >= 0) {
						sum = sum - q_pop + *(imdata + (blur_value / 2) + (r * w));
						cut--;
					}
				}
				else if (cnt_r > w - (blur_value / 2)) {
					//커널의 우측이 이미지 밖으로 나갈 때
					if (cut >= 0) {
						sum = sum - q_pop;
						cut--;
					}
				}
				else if (cnt_r <= (blur_value / 2) + 1) {
					//커널의 좌측이 이미지 밖으로 나갈 때
					if (cut >= 0) {
						sum = sum + *(imdata + (blur_value / 2) + (r * w));
						cut--;
					}
				}

			}

			else if (cnt_c <= (blur_value / 2)) {
				//커널 위가 이미지 밖으로 나갈 때

				if ((cnt_r <= w - (blur_value / 2)) && (cnt_r > (blur_value / 2) + 1)) {
					//커널의 좌우가 이미지 안에 위치할 때

					if (cutt <= blur_value / 2) {
						sum = sum - q_pop + *(imdata + (blur_value / 2) + (r * w));
					}
					cutt--;
				}
				else if (cnt_r > w - (blur_value / 2)) {
					//커널의 우측이 이미지 밖으로 나갈 때

					if (cutt <= blur_value / 2) {
						sum = sum - q_pop;
					}
					cutt--;
				}
				else if (cnt_r <= (blur_value / 2) + 1) {
					//커널의 좌측이 이미지 밖으로 나갈 때

					if (cutt <= blur_value / 2) {
						sum = sum + *(imdata + (blur_value / 2) + (r * w));
					}
					cutt--;
				}
			}

			Q.pop();
			Q.push(*(imdata + (blur_value / 2) + (r * w)));

		}
	}
		end_time = clock();

		cout << "Kernel Size : " << blur_value << ", Exec Time : " << (double)(end_time - start_time) << " (msec)" << endl;
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
	int kernel;

	if (argc != 3) {

		cout << "[프로그램 사용법]" << endl;
		cout << "명령문 : snnnnnnHW01.exe imageFile kernalSize<ent>" << endl;

		return 0;
	}
	//파일 주소는 argv[1]로 들어옴
	input_im = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	kernel = atoi(argv[2]);

	if (input_im.empty())
	{
		cout << "File open Error!" << endl;
		return -1;
	}
	cout << "Filename = " << argv[1] << "Image size :" << input_im.size() << ", Type:" << type2str(input_im.type()) << endl;

	string window_name = "movingAvrg HW";
	namedWindow(window_name);


	movingAvrg_filter(kernel, static_cast<void*>(&window_name));


	waitKey(0);

	return 0;
}