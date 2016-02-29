#include "../2D.h"
size2D size2DMake(float width, float height){
	size2D a = {width,height};
	return a;
}
size2D size2DZero(){
	return size2DMake(0, 0);
}