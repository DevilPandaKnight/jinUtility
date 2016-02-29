#include "../3D.h"


point3D point3DMake(float x,float y,float z){
	point3D a = {x,y,z};
	return a;
}
point3D point3DZero(){
	return point3DMake(0,0,0);
}

point3D pointAdd3D(point3D p,point3D q){
	return point3DMake(p.x+q.x,p.y+q.y,p.z+q.z);
}
point3D pointSub3D(point3D p,point3D q){
	return point3DMake(p.x-q.x,p.y-q.y,p.z-q.z);
}

void printPoint3D(point3D p){
	printf("(x = %.5g, y = %.5g, z = %.5g)\n",p.x,p.y,p.z);
}

float point3Ddistance(point3D p,point3D q){
	return sqrt(pow(p.x-q.x,2)+pow(p.y-q.y,2)+pow(p.z-q.z,2));
}