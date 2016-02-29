#ifndef __2D_H__
#define __2D_H__
#include <math.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
	float x;
	float y;
}point2D;

typedef struct
{
	float i;
	float j;
}vector2D;

typedef struct{
	float width;
	float height;
}size2D;

static const vector2D VECTOR_2D_STANDARD_BASIS_I = {1,0};
static const vector2D VECTOR_2D_STANDARD_BASIS_J = {0,1};

//point2D
point2D point2DMake(float x,float y);
point2D point2DZero();
point2D pointAdd2D(point2D p,point2D q);
point2D pointSub2D(point2D p,point2D q);
void printPoint2D(point2D p);
float point2Ddistance(point2D p,point2D q);


//vector2D
vector2D vector2DMake(float i,float j);
vector2D vector2DZero();
vector2D vectorSub2D(vector2D u,vector2D v);
vector2D vectorAdd2D(vector2D u,vector2D v);
float vectorLength2D(vector2D u);
void printVector2D(vector2D u);
vector2D unitVector2DMake(vector2D v);
vector2D vector2DScale(vector2D v,float scale);
float dotProduct2D(vector2D u,vector2D v);
vector2D projection2D(vector2D u,vector2D v);


//size2D
size2D size2DMake(float width, float height);
size2D size2DZero();


#ifdef __cplusplus
};
#endif


#endif