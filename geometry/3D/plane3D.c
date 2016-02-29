#include "../3D.h"
plane3D plane3DMake(vector3D normal, point3D pointOnPlane){
	plane3D p = {normal,pointOnPlane};
	return p;
}

plane3D plane3DFrom3Points(point3D a,point3D b,point3D c){
	vector3D ab = vector3DMakeFromPoints(a,b);
	vector3D ac = vector3DMakeFromPoints(a,c);
	return plane3DMake(crossProduct3D(ab,ac),c);
}

void printPlane(plane3D p){
	vector3D point = vector3DMake(p.pointOnPlane.x,p.pointOnPlane.y,p.pointOnPlane.z);
	printf("%gx+%gy+%gz=%g\n",p.normal.i,p.normal.j,p.normal.k,dotProduct3D(p.normal,point));
}
