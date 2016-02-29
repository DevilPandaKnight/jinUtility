#include "../physics.h"
#define u megneticConstant
double mForceOnCharge(double q,double v,double b,double angle){
    return q*v*b*sin(radians(angle));
}

double mForceOnWire(double current, double length, double mField,double angle){
    return current*length*mField*sin(radians(angle));
}

double mTorqueOnLoop(double current, double area, double mField,double angle){
    return current*area*mField*sin(radians(angle));
}

double mFieldFromInfiniteWire(double current, double length){
    return (u*current)/(2*PI*length);
}

double mFieldOnCenterOfLoop(double current, double radius){
    return (u*current)/(2*radius);
}

double mFieldAlongAxisOfCenterOfLoop(double current,double radius,double length){
    return (u*current*radius*radius)/(2*pow((radius*radius+length*length), 3.0/2));
}

double mFieldInsideWire(double current,double radius, double length){
    return (u*current*radius)/(2*PI*length*length);
}

double mFieldOfInfiniteSheetOfCurrent(double wireDensity,double current){
    return 0.5*u*wireDensity*current;
}

double mEMFPotentialDifference(double v,double mField, double length){
    return v*mField*length;
}

double mEMFPower(double v,double mField,double length,double resistence){
    return (pow(v*mField*length, 2))/resistence;
}

#undef u
