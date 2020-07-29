#include <stdio.h>
#include <random>
#include <time.h>
#include <Windows.h>
#include <math.h>

#define N 2

__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;

void init_elements(void);
void poly(double* a, double* b , double* c, double x[]);

double *x, *a, *b, *c;

void main(void)
{
	init_elements();

	CHECK_TIME_START;
	poly(a, b, c, x);
	CHECK_TIME_END(compute_time);
	printf("***Equation compute time : %f ms\n", compute_time);

	return;
}

void init_elements(void) {

	x = (double *)malloc(sizeof(double)*2);
	a = (double *)malloc(sizeof(double));
	b = (double *)malloc(sizeof(double));
	c = (double *)malloc(sizeof(double));

	srand((unsigned int)time(NULL));

	double * ptr = a;

	for (int i = 0; i < N; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);

	ptr = b;
	for (int i = 0; i < N; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);

	ptr = c;
	for (int i = 0; i < N; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
}

void poly(double* a, double* b, double* c, double x[]){
	double dec, fx1, fx2;

	x[0] = (0 - *b + sqrt(pow(*b, 2) - 4 * (*a) * (*c))) / (2 * (*a));
	x[1] = (0 - *b - sqrt(pow(*b, 2) - 4 * (*a) * (*c))) / (2 * (*a));
	
	dec = pow(*b, 2) - 4 * (*a) * (*c);
	printf("dec = %f\n", dec);
	printf("a = %f  b = %f  c = %f\n", *a, *b, *c);
	printf("x1 = %f  x2 = %f\n", x[0], x[1]);

	//if (dec < 0) {
		fx1 = (*a) * pow(x[0], 2) + (*b) * x[0] + *c;
		fx2 = (*a) * pow(x[1], 2) + (*b) * x[1] + *c;

		printf("fx1 = %f  fx2 = %f\n", fx1, fx2);
//	}
}

