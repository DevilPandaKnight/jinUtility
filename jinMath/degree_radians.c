#include "../jinMath.h"
double radians(double degree){
	return degree * PI/180;
}

double degree(double radians){
	return radians * 180 / PI;
}
