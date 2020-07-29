#include <stdio.h>
#include <random>
#include <time.h>
#include <math.h>
#include <Windows.h>

#define DEGREE 10

#define N_X 1024

__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;

void init_polynomial(void);
void Eval_Poly_Naive(double y[], double x[], int n_x, double a[], int deg);
void Eval_Poly_Horner(double y[], double x[], int n_x, double a[], int deg);
void Check_Difference(double y_n[], double y_h[], int n_x);

double *a, *x, *y_n, *y_h;

void main(void)
{
	init_polynomial();
	printf("%f\n", x[0]);
	CHECK_TIME_START;
	Eval_Poly_Naive(y_n, x, N_X, a, DEGREE);
	CHECK_TIME_END(compute_time);
	printf("***Polynomial Naive  compute time : %f ms\n", compute_time);

	CHECK_TIME_START;
	Eval_Poly_Horner(y_h, x, N_X, a, DEGREE);
	CHECK_TIME_END(compute_time);
	printf("***Polynomial Horner compute time : %f ms\n", compute_time);

	Check_Difference(y_n, y_h, N_X);

	printf("*** Naive[10] = %lf, Horner[10] = %lf\n", y_n[10], y_h[10]);
}
void init_polynomial(void) {
	a = (double *)malloc(sizeof(double)*(DEGREE + 1));
	x = (double *)malloc(sizeof(double)*N_X);
	y_n = (double *)malloc(sizeof(double)*N_X);
	y_h = (double *)malloc(sizeof(double)*N_X);

	srand(0);

	double * ptr = a;
	for (int i = 0; i < DEGREE; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
	ptr = x;
	for (int i = 0; i < N_X; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
}
void Eval_Poly_Naive(double y[], double x[], int n_x, double a[], int deg)
{
	int i,j;
	double tmp;

	for (i = 0; i < n_x; i++) {
		for (j = 0; j <= deg; j++) {
			tmp = pow(x[i], j);
			y[i] += a[j] * tmp;
		}
	}

}
void Eval_Poly_Horner(double y[], double x[], int n_x, double a[], int deg)
{
	int i, j;

	for (i = 0; i < n_x; i++) {
		y[i] = a[deg] * x[i];

		for (j = deg - 1; j >= 0; j--) {
			
			y[i] = y[i] * x[i] + a[j];
		}
	}
}
void Check_Difference(double y_n[], double y_h[], int n_x) {
	int i;

	for (i = 0; i < n_x; i++) {
		if ((float)y_n[i] != (float)y_h[i]) {
			printf("Value y_n[%d] (%.15lf) is not equal with y_h[%d] (%.15lf)\n", i, y_n[i], i, y_h[i]);
		}
	}

	printf("All values are equal\n\n");
}
