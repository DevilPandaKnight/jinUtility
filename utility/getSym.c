#include "../utility.h"
static char* printSym[] = {"%d","%f","%f","%c","%ld","%s","%lld","%Lf"};
static char* printSymN[] = {"%d\n","%f\n","%f\n","%c\n","%ld\n","%s\n","%lld\n","%Lf\n"};
char* getSym(int type){
	if (type >7) return NULL;
	return printSym[type];
}

char* getSymWithN(int type){
	if (type >7) return NULL;
	return printSymN[type];
}