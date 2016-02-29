#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif

#define cnew(s) malloc(sizeof(s))
#define cRaise(condition,msg) if(condition){printf("%s\n",msg ); return 0;}
#define swap(a,b,T) {T __jinTempSwapVariable__ = a;a = b;b = __jinTempSwapVariable__;}

#include "dataType.h"

/*************************************/
char* getSym(int type);
char* getSymWithN(int type);
/*************************************/


/*************************************/
void printArray(void* array, size_t length, int type);
void printArrayWithFormat(void* array, size_t length, int type,char* format);
/*************************************/

#ifdef __cplusplus
};
#endif

#endif