#include "../3D.h"
vector3D vector3DMake(float i,float j,float k){
	vector3D a = {i,j,k};
	return a;
}

vector3D vector3DMakeFromPoints(point3D a, point3D b){
	return vector3DMake(b.x-a.x, b.y-a.y, b.z-a.z);
}

vector3D vector3DZero(){
	vector3D a = {0,0,0};
	return a;
}

vector3D vector3DScale(vector3D v,float scale){
	return vector3DMake(v.i*scale,v.j*scale,v.k*scale);
}

vector3D unitVector3DMake(vector3D v){
	float norm = vectorLength3D(v);
	if (norm == 0)
	{
		return vector3DZero();
	}
	float scale = 1/norm;
	return vector3DScale(v,scale);
}

vector3D vectorSub3D(vector3D u,vector3D v){
	return vector3DMake(u.i-v.i,u.j-v.j,u.k-v.k);
}

vector3D vectorAdd3D(vector3D u,vector3D v){
	return vector3DMake(u.i+v.i,u.j+v.j,u.k+v.k);
}

void printVector3D(vector3D u){
	printf("(i = %.5g, j = %.5g, k = %.5g)\n",u.i,u.j,u.k );
}

float vectorLength3D(vector3D u){
	return sqrt(pow(u.i,2)+pow(u.j,2)+pow(u.k,2));
}

float dotProduct3D(vector3D u,vector3D v){
	return u.i*v.i+u.j*v.j+u.k*v.k;
}

vector3D projection3D(vector3D u,vector3D v){
	float scale = dotProduct3D(u,v)/dotProduct3D(v,v);
	return vector3DMake(scale*v.i,scale*v.j,scale*v.k);
}

vector3D crossProduct3D(vector3D u, vector3D v){
	return vector3DMake(u.j*v.k-u.k*v.j,-(u.i*v.k-u.k*v.i),u.i*v.j-u.j*v.i);
}

float area3D(vector3D v,vector3D w){
	return vectorLength3D(crossProduct3D(v,w));
}

float volume3D(vector3D u,vector3D v,vector3D w){
	float vol = dotProduct3D(u,crossProduct3D(v,w));
	if (vol < 0)
	{
		vol = -vol;
	}
	return vol;
}



