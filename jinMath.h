#ifndef __JINMATH_H__
#define __JINMATH_H__
#include <stdio.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "jinObject.h"
#include "jinString.h"
#include "dataType.h"
#include "utility.h"
#define PI 3.1415926535897932384626433832795

/**************************************/
double leftEndPoint(double a, double b, int n,double (*f)());
double rightEndPoint(double a, double b, int n,double (*f)());
double midPoint(double a,double b, int n, double (*f)());
double simpsonRule(double a,double b, int n, double (*f)());
double simpsonSum(double list[], double dx,int len);
double integrate(double (*f)(double xi), double from, double to);
/**************************************/




/*************************************/
double radians(double degree);
double degree(double radians);
/*************************************/




/*************************************/
dataType secondPolyRoot(double a,double b,double c,double *root1, double *root2);
/*************************************/



/*************************************/
//use independent variable n for the equation.
//example: 1/n^2 from 1 to 100
double summation(char* equation,double from, double to);

//give expression like m*2^i and binary sequence like 111
//it will replace m with the squence from LSB to MSB.
//and replace i with the range you enterd
double binarySummation(char* exp,char* binarySequence, double from, double to);
/*************************************/



/*************************************/
double* hann(size_t length);
int dirac(long t);
int unitstep(long t);
/*************************************/



/*************************************/
//variable = 1 means take partial derivative on x, 
//variable = 2 means take partial derivative on y.
//variable > 2 means take partial derivative on z.
double partial3Derivative(double (*f)(double,double,double),double x,double y,double z,int variable);

//variable = 1 means take partial derivative on x
//variable > 1 means take partial derivative on y.
double partial2Derivative(double (*f)(double,double),double x,double y,int variable);

double derivative(double (*f)(double),double point);
double secondDerivative(double (*f)(double),double point);
/*************************************/



/*************************************/
long gcd(long a,long b);
/*************************************/



#ifdef __cplusplus
};
#endif






#endif