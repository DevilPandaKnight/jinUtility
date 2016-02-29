#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "jinMath.h"
/*
 electricties
 */
static const double electronCharge = -1.6e-19; //Coulomb
static const double protonCharge = 1.6e-19; //Coulomb
static const double electronMass = 9.1e-31; //kg
static const double protonMass = 1.6e-27; //kg
static const double electricalConstant = 9e9;

double eforceOnTwoCharges(double q1, double q2, double distance);
double eFieldOnInfiniteLine(double chargeDensity, double distance);
double eFieldOnPointCharge(double q1, double distance);
double eFieldOnSolidSphericalInsulator(double q, double radius, double distance);
double eFieldOnInfiniteSheet(double chargeDensity);
double eFlux(double q);
double eWorkDoneByCoulombForce(double q1,double q2,double beginPosition, double endPosition);
double electricPE(double q1, double q2, double distance);
double electricPotential(double q,double distance);
double eEnergyDensity(double eField);
double eCapacitance(double q, double v);
double eCapacitanceBetweenPlates(double area,double distance);
double eCapacitanceStoreEnergyQV(double q, double v);
double eCapacitanceStoreEnergyQC(double q, double c);
double eCapacitanceStoreEnergyCV(double c, double v);
double eCapacitanceInParallel(double c[],int len);
double eCapacitanceInSeries(double c[],int len);

/*
 magnetism
 */
static const double megneticConstant = 4*PI*1e-7;

double mForceOnCharge(double q,double v,double b,double angle);
double mForceOnWire(double current, double length, double mField,double angle);
double mTorqueOnLoop(double current, double area, double mField,double angle);
double mFieldFromInfiniteWire(double current, double length);
double mFieldOnCenterOfLoop(double current, double radius);
double mFieldAlongAxisOfCenterOfLoop(double current,double radius,double length);
double mFieldInsideWire(double current,double radius, double length);
double mFieldOfInfiniteSheetOfCurrent(double wireDensity,double current);
double mEMFPotentialDifference(double v,double mField, double length);
double mEMFPower(double v,double mField,double length,double resistence);


/*
 mechanics
 */
static const double GravitationalConstant = 6.67e-11;

double mforce(double m, double a);

/*
opticals
*/
static const double planckConstant = 6.62606957e-34; // J-s
static const double boltzmannConstant = 1.3806488e-23; // J/K

#ifdef __cplusplus
};
#endif

#endif