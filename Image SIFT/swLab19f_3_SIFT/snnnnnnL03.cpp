#include "SIFT.h"
#define DIST_RATIO_THR 0.49
#define PI 3.14159265358979323846

void customGaussianBlur(const Mat &src, Mat &dst, double sigma) {
	////////////////////////////////////////////////////////////
	// 가우시안 커널을 생성해 이미지에 적용하는 함수
	// 커널의 크기는 2*(4*sigma)+1 (소수점은 올림 또는 반올림으로 처리한다)
	// 가우시안 커널은 float형의 값을 가짐
	// 가우시안 커널은 커널 값 계산 후 전체의 총합으로 나눠서 0~1사이의 값을 가지도록 정규화
	// 가우시안 커널을 이미지에 적용할때는 filter2D() 함수를 사용
	////////////////////////////////////////////////////////////
	
	Mat gau_kernel;
	uchar *gaudata = (gau_kernel).data;
	int kernel_size, sigma_c, x, y;

	float expo, sum;
	int h, w;

	sigma_c = (int)ceil(4 * sigma);
	kernel_size = 2 * sigma_c + 1;
	gau_kernel = Mat(kernel_size, kernel_size, CV_32FC1);
	
	
	h = gau_kernel.rows;
	w = gau_kernel.cols;

	//내용 구현

	

	// Compute gaussian kernel value
	//내용 구현
	sum = 0;
	for (int r = 0; r < h; r++) {
		for (int c = 0; c < w; c++) {
			x = (-1) * sigma_c + c;
			y = (-1) * sigma_c + r;
			expo = (float)exp(((-1) * ((x * x) + (y * y))) / (2 * sigma*sigma));
			gau_kernel.at<float>(r, c) = expo / (float)(2 * sigma * sigma * PI);
			sum = sum + gau_kernel.at<float>(r, c);
		}
	}

	// Normalize the kernel


	for (int r = 0; r < h; r++) {
		for (int c = 0; c < w; c++) 
			gau_kernel.at<float>(r, c) = gau_kernel.at<float>(r, c) / sum;
	}
		

	// Apply Gaussian kernel

	filter2D(src, dst, -1, gau_kernel, Point(-1, -1), 0, BORDER_DEFAULT);
	
}
//////////////////////////////////////////////


int MatchDescriptor(const Mat &descriptor1, const Mat &descriptor2, vector<int> &machingIdx) {
	///////////////////////////////////////////////////////////////
	// 이미지1의 디스크립터들과 이미지2의 디스크립터들 중 매칭되는 페어의 개수를 계산하는 함수
	// 이미지1의 1개의 디스크립터와 이미지2의 모든 디스크립터 사이의 L2 거리를 계산 
	// 가장 가까운 거리 (d1) 와 두번째로 가까운 거리(d2) 의 비율 (d1/d2) 을 구해 설정된 임계값 (DIST_RATIO_THR) 보다 작다면 매칭으로 판단
	// machingIdx 에는 매칭이 된 인덱스를 저장 (machingIdx[idx1] = idx2, idx1은 이미지1의 디스크립터의 인덱스이고, idx2는 매칭된 이미지2의 디스크립터의 인덱스)
	// 함수의 리턴값으로는 매칭된 페어의 개수를 출력
	//////////////////////////////////////////////////////////////
	int numMatches = 0;
	float d1, d2;
	float L2norm, sum;
	int tmp, idx1, idx2 ,flag;
	
	machingIdx.resize(descriptor1.rows);
	
	L2norm = 0;
	
	for (int i = 0; i < descriptor1.rows; i++) {

		idx1 = i;
		idx2 = -1;
		flag = -1;
		d2 = -1;
		for (int j = 0; j < descriptor2.rows; j++) {

			sum = 0;
			
			for (int k = 0; k < 128; k++) {
				sum += (descriptor1.at<float>(i, k) - descriptor2.at<float>(j, k))*(descriptor1.at<float>(i, k) - descriptor2.at<float>(j, k));
			}
			
			L2norm = sqrt(sum);

		
			if (j == 0) {
				d1 = L2norm;
				idx2 = j;
			}

			else {

				if (L2norm < d1) {
					d2 = d1;
					d1 = L2norm;
					idx2 = j;
					flag = 0;
				}
				
				else if (L2norm < d2) {
					d2 = L2norm;
					idx2 = j;
					flag = 0;
				}
			}
		}
		
		if ((d1 / d2) < DIST_RATIO_THR && d2 != -1) {
			numMatches++;
			machingIdx[idx1] = idx2;
		}

		else
			machingIdx[idx1] = -1;
			
	}
		
	return numMatches;
}