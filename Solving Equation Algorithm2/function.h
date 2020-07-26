#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

//#define DELTA 0.000001
//#define Nmax 50
//#define EPSILON 0.00001

#define OUTPUT_STEPS	  1
#define CONVERGENCE_CHECK 1

// 파라메터는 최대 3 개까지이다(변경가능)
#define PARAMETER_N		3
char pidx[PARAMETER_N+1] = "abc";

#define NEWTON_R				1
#define SECANT					2
#define BISECTION				3
// 새로운 풀이 방법을 추가하면 여기에 그 방법의 id를 부여한다

const char *NRstr = "Newton-Raphson method";
const char *SCstr = "Secant method";
const char *BSstr = "Bisection method";
// 새로운 풀이 방법을 추가하면 여기에 그 방법을 설명하는 문자열을 포함한다


double(*_F)(double, double, double, double);
double(*_FP)(double, double, double, double);

//f1 = x^2 -4x +4 -lnx = 0
//f2 = x^2 - 2 = 0

#define PROBLEM1 1
#define PROBLEM2 2
#define PROBLEM3 3
#define PROBLEM4 4
#define PROBLEM5 5

const char *LabF1str = "f1(x) = x^2 -ax +4 -ln(bx) = 0";
const char *LabF2str = "f2(x) = x^2 - 2 = 0";
const char *LabF3str = "f3(x) = x^4 + ax^2*y^2 + y^4 - x^3 + 3xy^2 = 0";
const char *LabF4str = "f4(x) = lnx - 1 = 0";
const char *LabF5str = "f5(x) = ax + b/(1+x)^c - b = 0";

double _LabF1(double x, double a, double b, double c) {
	return x*x - a*x + 4 - log(b*x);
}
double _LabFP1(double x, double a, double b, double c) {
	return 2*x - a - (1/x);
}

double _LabF2(double x, double a, double b, double c) {
	return x * x - 2;
}
double _LabFP2(double x, double a, double b, double c) {
	return 2 * x;
}

double _LabF3(double x, double a, double b, double c) {
	double y;
	y = a * x + b;
	return pow(x, 4) + 2*x*x*y*y + pow(y, 4) - pow(x, 3) + 3*x*y*y;
}
double _LabFP3(double x, double a, double b, double c) {
	double y;
	y = a * x + b;
	return 4*pow(x, 4) + 4*a*pow(y,4) + 4*x*y*y + 3*y*y - 3*x*x + 4*a*x*x*y + 6*a*x*y;
}

double _LabF4(double x, double a, double b, double c) {
	return log(x) - 1;
}
double _LabFP4(double x, double a, double b, double c) {
	return 1/x;
}

double _LabF5(double x, double a, double b, double c) {
	return a * x - b + (b / pow(1 + x, c));
}
double _LabFP5(double x, double a, double b, double c) {
	return a - (b * c * pow(1 + x, - c - 1));
}
// 문제가 추가될 때 마다 위 문제 1과 같은 내용이 추가되어야 합니다.
// 두번째 문제라면 
// #define PROBLEM2 2, LabF2str, _LabF2, _LabFP2 등 추가
