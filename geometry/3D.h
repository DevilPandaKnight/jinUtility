#ifndef __3D_H__
#define __3D_H__
#include <math.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
	float x;
	float y;
	float z;
}point3D;

typedef struct
{
	float i;
	float j;
	float k;
}vector3D;


typedef struct
{
	vector3D normal;
	point3D pointOnPlane;
}plane3D;

typedef struct{
	float width;
	float depth;
	float height;
}size3D;


static const vector3D VECTOR_3D_STANDARD_BASIS_I = {1,0,0};
static const vector3D VECTOR_3D_STANDARD_BASIS_J = {0,1,0};
static const vector3D VECTOR_3D_STANDARD_BASIS_K = {0,0,1};

//point3D
point3D point3DMake(float x,float y,float z);
point3D point3DZero();
point3D pointAdd3D(point3D p,point3D q);
point3D pointSub3D(point3D p,point3D q);
void printPoint3D(point3D p);
float point3Ddistance(point3D p,point3D q);


//vector3D
vector3D vector3DMake(float i,float j,float k);
vector3D vector3DMakeFromPoints(point3D a, point3D b);
vector3D vector3DZero();
vector3D unitVector3DMake(vector3D v);
vector3D crossProduct3D(vector3D u, vector3D v);
float area3D(vector3D v,vector3D w);
float volume3D(vector3D u,vector3D v,vector3D w);
vector3D vector3DScale(vector3D v,float scale);
vector3D vectorAdd3D(vector3D u,vector3D v);
vector3D vectorSub3D(vector3D u,vector3D v);
float vectorLength3D(vector3D u);
float dotProduct3D(vector3D u,vector3D v);
vector3D projection3D(vector3D u,vector3D v);
void printVector3D(vector3D u);



//plane3D
plane3D plane3DMake(vector3D normal, point3D pointOnPlane);
plane3D plane3DFrom3Points(point3D a,point3D b,point3D c);
void printPlane(plane3D p);

#ifdef __cplusplus
};
#endif



#endif