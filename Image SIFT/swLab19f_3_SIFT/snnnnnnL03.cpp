#include "SIFT.h"
#define DIST_RATIO_THR 0.49
#define PI 3.14159265358979323846

void customGaussianBlur(const Mat &src, Mat &dst, double sigma) {
	////////////////////////////////////////////////////////////
	// ����þ� Ŀ���� ������ �̹����� �����ϴ� �Լ�
	// Ŀ���� ũ��� 2*(4*sigma)+1 (�Ҽ����� �ø� �Ǵ� �ݿø����� ó���Ѵ�)
	// ����þ� Ŀ���� float���� ���� ����
	// ����þ� Ŀ���� Ŀ�� �� ��� �� ��ü�� �������� ������ 0~1������ ���� �������� ����ȭ
	// ����þ� Ŀ���� �̹����� �����Ҷ��� filter2D() �Լ��� ���
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

	//���� ����

	

	// Compute gaussian kernel value
	//���� ����
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
	// �̹���1�� ��ũ���͵�� �̹���2�� ��ũ���͵� �� ��Ī�Ǵ� ����� ������ ����ϴ� �Լ�
	// �̹���1�� 1���� ��ũ���Ϳ� �̹���2�� ��� ��ũ���� ������ L2 �Ÿ��� ��� 
	// ���� ����� �Ÿ� (d1) �� �ι�°�� ����� �Ÿ�(d2) �� ���� (d1/d2) �� ���� ������ �Ӱ谪 (DIST_RATIO_THR) ���� �۴ٸ� ��Ī���� �Ǵ�
	// machingIdx ���� ��Ī�� �� �ε����� ���� (machingIdx[idx1] = idx2, idx1�� �̹���1�� ��ũ������ �ε����̰�, idx2�� ��Ī�� �̹���2�� ��ũ������ �ε���)
	// �Լ��� ���ϰ����δ� ��Ī�� ����� ������ ���
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