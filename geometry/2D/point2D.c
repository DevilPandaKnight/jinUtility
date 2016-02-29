#include "../2D.h"
point2D point2DMake(float x,float y){
	point2D a = {x,y};
	return a;
}
point2D point2DZero(){
	return point2DMake(0, 0);
}

point2D pointAdd2D(point2D p,point2D q){
	return point2DMake(p.x+q.x, p.y+q.y);
}

point2D pointSub2D(point2D p,point2D q){
	return point2DMake(p.x-q.x, p.y-q.y);
}

void printPoint2D(point2D p){
	printf("(x = %.5g, y = %.5g)\n",p.x,p.y);
}


float point2Ddistance(point2D p,point2D q){
	return sqrt(pow(p.x-q.x,2)+pow(p.y-q.y,2));
}