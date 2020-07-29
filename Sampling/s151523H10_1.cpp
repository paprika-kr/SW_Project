#include <stdio.h>
#include <random>
#include <time.h>
#include <Windows.h>
#include <math.h>

#define N 100000

__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;

void init_elements(void);
void avrg(double x[], int n, double* avg);
void vrnc1(double x[], int n, double* avg, double* vnc1);
void vrnc2(double x[], int n, double* avg, double* vnc2);
//Q1. float vs. double

double *x, *avg, *vnc1, *vnc2;

void main(void)
{
	init_elements();

	CHECK_TIME_START;
	avrg(x, N, avg);
	CHECK_TIME_END(compute_time);
	printf("***Average of X's compute time : %f ms\n", compute_time);

	CHECK_TIME_START;
	vrnc1(x, N, avg, vnc1);
	CHECK_TIME_END(compute_time);
	printf("***Variance1 of X's compute time : %f ms\n", compute_time);

	CHECK_TIME_START;
	vrnc2(x, N, avg, vnc2);
	CHECK_TIME_END(compute_time);
	printf("***Variance2 of X's compute time : %f ms\n", compute_time);

	return;
}

void init_elements(void) {

	x = (double *)malloc(sizeof(double)*N);
	avg = (double *)malloc(sizeof(double));
	vnc1 = (double *)malloc(sizeof(double));
	vnc2 = (double *)malloc(sizeof(double));

	srand(0);

	double * ptr = x;
	for (int i = 0; i < N; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
}

void avrg(double x[], int n, double* avg) {
	double sum = 0;

	for(int i = 0;i < n;i++)
	sum += x[i];

	*avg = sum / (double)n;
	
	printf("average : %f\n", *avg);
}

void vrnc1(double x[], int n, double* avg, double* vnc1) {
	double sum = 0, tmp;

	for (int i = 0; i < n; i++) {
		tmp = pow(x[i], 2);
		sum += tmp;
	}

	*vnc1 = (n * sum - pow(*avg * n, 2)) / (double)((n - 1)*n);

	printf(" variance1 : %f\n", *vnc1);
}

void vrnc2(double x[], int n, double* avg, double* vnc2) {
	double sum = 0, tmp;

	for (int i = 0; i < n; i++) {
		tmp = pow(x[i] - *avg, 2);
		sum += tmp;
	}

	*vnc2 = sum / (double)(n - 1);

	printf(" variance2 : %f\n", *vnc2);
}