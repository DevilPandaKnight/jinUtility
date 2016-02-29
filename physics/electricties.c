#include "../physics.h"
#define k electricalConstant
double eforceOnTwoCharges(double q1, double q2, double distance){
	return k*((q1*q2)/(distance*distance));
}

double eFieldOnInfiniteLine(double chargeDensity, double distance){
	return 2*k*chargeDensity/distance;
}

double eFieldOnPointCharge(double q1, double distance){
	return k*(q1/(distance*distance));
}

double eFieldOnSolidSphericalInsulator(double q, double radius, double distance){
	if (radius<distance){
		return q*k/(distance*distance);
	}
	else{
		return (k*q*distance)/(radius*radius*radius);
	}
}

double eFieldOnInfiniteSheet(double chargeDensity){
	return chargeDensity/(2*0.00000000000885);
}

double eFlux(double q){
	return q/0.00000000000885;
}

double eWorkDoneByCoulombForce(double q1,double q2,double beginPosition, double endPosition){
	return k*q1*q2/((1/beginPosition)-(1/endPosition));
}

double electricPE(double q1, double q2, double distance){
	return k*((q1*q2)/distance);
}

double electricPotential(double q,double distance){
	return k*q/distance;
}

double eEnergyDensity(double eField){
	return 0.5*0.00000000000885*eField*eField;
}

double eCapacitance(double q, double v){
	return q/v;
}

double eCapacitanceBetweenPlates(double area,double distance){
	return 0.00000000000885*area/distance;
}

double eCapacitanceStoreEnergyQV(double q, double v){
	return 0.5*q*v;
}

double eCapacitanceStoreEnergyQC(double q, double c){
	return (q*q)/(2*c);
}

double eCapacitanceStoreEnergyCV(double c, double v){
	return 0.5*c*v*v;
}

double eCapacitanceInParallel(double c[],int len){
	double result = 0;
	for (int i = 0; i <len;i++) {
		result += c[i];
	}
	return result;
}

double eCapacitanceInSeries(double c[],int len){
	double result = 0;
	for (int i = 0;i < len;i++) {
		result += (1/c[i]);
	}
	return 1/result;
}

#undef k
