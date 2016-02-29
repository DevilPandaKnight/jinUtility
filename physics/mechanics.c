#include "../physics.h"
#define G GravitationalConstant

double mforce(double m, double a){
	return m*a;
}

#undef G