#include "../jinMath.h"
dataType secondPolyRoot(double a,double b,double c,double *root1, double *root2){
	double r1 = (-b+pow(pow(b,2)-4*a*c,0.5))/(2*a);
	double r2 = (-b-pow(pow(b,2)-4*a*c,0.5))/(2*a);
	bool complex = false;
	if (isnan(r1)){
		r1 = -b/(2*a);
        r2 = pow(-(pow(b,2)-4*a*c),0.5)/(2*a);
		complex = true;
	}
	if (root1 != NULL) *root1 = r1;
	if (root2 != NULL)*root2 = r2;
	return complex? complexType:doubleType;
}
