#include "../2D.h"
vector2D vector2DMake(float i,float j){
	vector2D a = {i,j};
	return a;
}

vector2D vectorSub2D(vector2D u,vector2D v){
	return vector2DMake(u.i-v.i,u.j-v.j);
}

vector2D vectorAdd2D(vector2D u,vector2D v){
	return vector2DMake(u.i+v.i,u.j+v.j);
}


float vectorLength2D(vector2D u){
	return sqrt(pow(u.i,2)+pow(u.j,2));
}


void printVector2D(vector2D u){
	printf("(i = %.5g, j = %.5g)\n",u.i,u.j);
}

vector2D vector2DScale(vector2D v,float scale){
	return vector2DMake(v.i*scale,v.j*scale);
}

vector2D vector2DZero(){
	return vector2DMake(0,0);
}
vector2D unitVector2DMake(vector2D v){
	float norm = vectorLength2D(v);
	if (norm==0)
	{
		return vector2DZero();
	}
	return vector2DScale(v,1/norm);
}

float dotProduct2D(vector2D u,vector2D v){
	return u.i*v.i+u.j*v.j;
}
vector2D projection2D(vector2D u,vector2D v){
	float scale = dotProduct2D(u,v)/dotProduct2D(v,v);
	return vector2DScale(v,scale);
}