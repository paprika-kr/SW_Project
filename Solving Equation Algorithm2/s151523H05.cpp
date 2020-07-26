#include "functionL05.h"

#define OUTPUT_STEPS   1	// display detailed solution finding steps(stdout)
							// must use redirection to save and see these outputs

#define BISECTION      1	// use bisection methof
#define NEWTON_RAPHSON 2	// use Newton-Raphson method
#define SECANT         3	// use Secant method(HW)
#define IMPROVED       4	// use improved method over the Newton-Raphson(HW)

void   pdfGeneration(void);					// nomalize samples to generate pdf
void   cdfGeneration(void);					// cdf generation
double interpolationF(double x, double U);	// given x, find the value of F_X(x)-U
double interpolationFD(double x);			// given x, fine the value of p_X(x)

double genRandN_Bisection(double U, int si);		// function using the bisection method
double genRandN_NewtonRaphson(double U, int si);	// function using the Newton-Raphson method	
double genRandN_Secant(double U, int si);			// function using the secant method(HW)
double genRandN_Improved(double U, int si);			// function using the improved method(HW)
double Sub_Bisection(double U, int si);

int main(void) {
	int TN;				// # of tests
	int histo_i;
	srand((unsigned int)time(NULL));	// init rand()
	//srand(0);			// use this line when debugging
	scanf("%d", &TN);	// read # of tests		

	for (int t = 0; t < TN; ++t) {
		start_time = clock();				// start time measure

		// preparation
		getParameters_openFiles();			// get parameters and open files
		fscanf(sfp, "%d %lf", &SN, &dx);	// read # of samples and x-distance between two adjacent samples
		allocateMemory();
		readSamples();
		pdfGeneration();
		cdfGeneration();
		save_pdf_cdf();

		// start generation
		fprintf(Xfp, "%d\n", XN);			// write # of random numbers generated
		for (int d = 0; d < XN; d++) {
			double U = (double)rand() / RAND_MAX;	// generate U : [0.0,1.0]
			double X;			// random number generated

			// generate a random number
			switch (method) {
				case (BISECTION):
					X = genRandN_Bisection(U, d);	// d is needed to display steps 
					fflush(stdout);		// can be removed(just for debugging)
					break;
				case (NEWTON_RAPHSON):	
					X = genRandN_NewtonRaphson(U, d);
					fflush(stdout);		// "
					break;
				case (SECANT):	
					X = genRandN_Secant(U, d);
					fflush(stdout);		// "
					break;
				case (IMPROVED):
					X = genRandN_Improved(U, d);
					fflush(stdout);		// "
					break;
				default:
					printf("Unknown method");
					exit(-1);
			}
			fprintf(Xfp, "%.12f\n", X);		// save X

			// find the proper histogram bin for X and increase the bin by one
			if(X < 1 && X >= 0)
			histo_i = (int)floor(X * 100);
			histoGram[histo_i] += 1;
			// *** histoGram[ ]을 설정하는 이 부분을 작성하세요
			//     구한 X 값으로부터 histoGram[] 배열의 index i를 구한후
			//     histoGram[i]=histoGram[i]+1해주면 됩니다.

		}
		end_time = clock();					// stop time measure
		printf(" time : %.6f \n", (double)(end_time - start_time));//
		saveHistogram();					// write histogram to the file
		closeFile_deallocateMemory();		// deallocate memory
	}
}

double genRandN_Bisection(double U, int si) {
	// initial interval is [0.0, 1.0] (can always find a root)
	double L = 0.0, R = 1.0;
	double x1 = (L + R) / 2;
	double x0, F1;	// you may change the name of variable x1 if you want
	int iter;

	printf(" n              xn1                                |f(xn1)|			  U = %4f\n", U);

	for (iter = 0; iter <= maxIter; iter++) {

		x1 = (L + R) / 2;
		F1 = interpolationF(x1, U);

		if (showSteps == OUTPUT_STEPS) 
			printf("%2d  %.18e  %.18e\n", iter, x1, fabs(F1));
		
		if (fabs(F1) < delta)
			break;
		if (iter != 0 && fabs(x1 - x0) < epsilon)
			break;

		// 다음 두 줄이 Bisection method core 입니다

		if (interpolationF(L, U) * F1 < 0)
			R = x1;
		else
			L = x1;

		x0 = x1;
	}

	

	return x1;		// you can change the return variable if you want
}


double genRandN_NewtonRaphson(double U, int si) {
	double x1 = 0.9;	// just for initial buid without coding
	double x0, F1, FP1;
	int iter;
	
	printf(" n              xn1                         |f(xn1)|			U = %4f\n", U);
	
	for (iter = 0; iter <= maxIter; iter++) {

		F1 = interpolationF(x1, U);
		FP1 = interpolationFD(x1);

		if (showSteps == OUTPUT_STEPS) 
			printf("%2d  %.18e  %.18e\n", iter, x1, fabs(F1));
		
		if (fabs(F1) < delta)
			break;
		if (iter != 0 && fabs(x1 - x0) < epsilon)
			break;

		// 다음 두 줄이 Newton-Raphsom method core 입니다
		x0 = x1;
		x1 = x1 - (F1 / FP1);
	}
	if (x1 <= 0)
		x1 = 0;
	else if (x1 >= 1)
		x1 = 1;
	
	return x1;	// you can change the return variable if you want
}

double genRandN_Secant(double U, int si) {
	double x0 = 0.8, x1=0.9;	
	double F1, tmp;
	int iter;

	printf(" n              xn1                         |f(xn1)|			U = %4f\n", U);

	for (iter = 0; iter <= maxIter; iter++) {

		F1 = interpolationF(x1, U);

		if (showSteps == OUTPUT_STEPS) 
				printf("%2d  %.18e  %.2e\n", iter, x1, fabs(F1));
		
		if (fabs(F1) < delta)
			break;
		if (iter != 0 && fabs(x1 - x0) < epsilon)
			break;

		tmp = x0;
		x0 = x1;
		x1 = x1 - (F1 * (x1 - tmp) / (F1 - interpolationF(tmp, U)));
	}

	if (x1 <= 0)
		x1 = 0;
	else if (x1 >= 1)
		x1 = 1;

	return x1;			
}

double genRandN_Improved(double U, int si) {		
	double x1 = 0.7;
	double x0, F1, FP1;
	int sign_stack=0, Dsign_flag=0, Dsign_stack=0, flag=0;
	
	int iter;

	printf(" n              xn1                         |f(xn1)|			U = %4f\n", U);

	for (iter = 0; iter <= maxIter; iter++) {

		F1 = interpolationF(x1, U);
		FP1 = interpolationFD(x1);

		if (showSteps == OUTPUT_STEPS)
			printf("%2d  %.18e  %.18e\n", iter, x1, fabs(F1));

		//case 1 : f' = 0 을 만나 벗어나는 경우
		if (x1 > 1 || x1 < 0) {
			flag = 1;
			break;
		}

		//case 2 : 변곡점 근처에서 진동하는 경우 (10회 이상)
		if (iter != 0) {
			if (F1 * interpolationF(x0, U) < 0)
				sign_stack += 1;
		}

		if (sign_stack >= 10) {
			flag = 1;
			break;
		}

		// case 3 : 최소값 근처에서 진동하는 경우 (10회 이상)	
		if (Dsign_flag == 0 && FP1 < 0) {
			Dsign_flag = 1;
			Dsign_stack += 1;
		}

		else if (Dsign_flag == 1 && FP1 > 0) {
			Dsign_flag = 0;
			Dsign_stack += 1;
		}

		if (Dsign_stack >= 10) { 
			flag = 1;
			break;
		}
		
		if (fabs(F1) < delta)
			break;
		if (iter != 0 && fabs(x1 - x0) < epsilon)
			break;

		// 다음 두 줄이 Newton-Raphsom method core 입니다
		x0 = x1;
		x1 = x1 - (F1 / FP1);
	}

	if (flag == 1)
		x1 = Sub_Bisection(U, si);
	
	return x1;
}

double Sub_Bisection(double U, int si) {
	// initial interval is [0.0, 1.0] (can always find a root)
	double L = 0.0, R = 1.0;
	double x1 = (L + R) / 2;
	double x0, F1;	// you may change the name of variable x1 if you want
	int iter;

	for (iter = 0; iter <= maxIter; iter++) {

		x1 = (L + R) / 2;
		F1 = interpolationF(x1, U);

		if (showSteps == OUTPUT_STEPS)
			printf("%2d  %.18e  %.18e\n", iter, x1, fabs(F1));

		if (fabs(F1) < delta)
			break;
		if (iter != 0 && fabs(x1 - x0) < epsilon)
			break;

		// 다음 두 줄이 Bisection method core 입니다

		if (interpolationF(L, U) * F1 < 0)
			R = x1;
		else
			L = x1;

		x0 = x1;
	}

	return x1;
}

void pdfGeneration(void) {
	// input pdfX[], pdfY[], SN
	// output pdfX[] (scale so that the range is 0 ~ 1)
	//        pdfY[] normalization
	double Xzero = pdfX[0];
	double Xlast = pdfX[SN-1];
	double Yzero = pdfY[0];
	double Ylast = pdfY[SN-1];
	double total = 0;
	double d;

	for (int i = 0; i < SN; i++) {
		pdfX[i] = (pdfX[i] - Xzero) / (Xlast - Xzero);
		total += pdfY[i];
	}

	d = pdfX[1] - pdfX[0];

	for (int i = 0; i < SN; i++)
		pdfY[i] = pdfY[i] / ((2 * total - Yzero - Ylast) / 2 * d);


	// *** 이 함수를 작성하세요

}

void cdfGeneration(void) {
	// input:  normalized pdfX[], pdfY[], SN
	// output: cdfY[]

	double d = pdfX[1] - pdfX[0];

	for (int i = 0; i < SN; i++) {
	
		if (i == 0)
			cdfY[i] = 0;

		else
			cdfY[i] = cdfY[i - 1] + (pdfY[i - 1] + pdfY[i]) * (d / 2);
	}
	// *** 이 함수를 작성하세요

}

double interpolationF(double x, double U) {
	// return the value of F_X(x) - U by interpolation
	double F = 0;		// just for building before coding
	double d = pdfX[1] - pdfX[0];
	int i;
	for (i = 0; i < SN; i++) {
		if (x <= pdfX[i + 1])
			break;
	}
	F = cdfY[i] + (cdfY[i + 1] - cdfY[i]) * (x - pdfX[i]) / d - U;
	return F;	// you may modify the variable name
}

double interpolationFD(double x) {
	// return the value of p_X(x) by interpolation
	double FD = 0;		// just for building before coding
	double d = pdfX[1] - pdfX[0];
	int i;
	for (i = 0; i < SN; i++) {
		if (x <= pdfX[i + 1])
			break;
	}
	FD = pdfY[i] + (pdfY[i + 1] - pdfY[i]) * (x - pdfX[i]) / d;
	return FD;	// you may modify the variable name
}

