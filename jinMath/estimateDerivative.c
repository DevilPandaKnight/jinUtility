#include "../jinMath.h"
//variable = 1 means take partial derivative on x, 
//variable = 2 means take partial derivative on y.
//variable > 2 means take partial derivative on z.
double partial3Derivative(double (*f)(double,double,double),double x,double y,double z,int variable){
	if (variable==1) {
		double dx = x/1e8;
		return (f(x+dx,y,z)-f(x,y,z))/dx;
	}
	else if (variable==2) {
		double dy = y/1e8;
		return (f(x,y+dy,z)-f(x,y,z))/dy;
	}
	else{
		double dz = z/1e8;
		return (f(x,y,z+dz)-f(x,y,z))/dz;
	}
}

//variable = 1 means take partial derivative on x
//variable > 1 means take partial derivative on y.
double partial2Derivative(double (*f)(double,double),double x,double y,int variable){
	if (variable==1) {
		double dx = x/1e8;
		return (f(x+dx,y)-f(x,y))/dx;
	}
	else {
		double dy = y/1e8;
		return (f(x,y+dy)-f(x,y))/dy;
	}
}


double derivative(double (*f)(double),double point){
	double dx = point/1e8;
	return (f(point+dx)-f(point))/dx;
}



double secondDerivative(double (*f)(double),double point){
	double dx = point/3e5;
	return (f(point+dx) - 2*f(point) +f(point-dx) )/(dx*dx);
}