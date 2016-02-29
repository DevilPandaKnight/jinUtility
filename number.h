#ifndef __NUMBER_H__
#define __NUMBER_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

#include "jinString.h"
#include "container.h"
#include "jinMath.h"
#include "jinObject.h"

/*******************************************************************/
//pass in the address of val to get the binary sequance, which is malloc from heap.
void printBinaryInMemory(void* num,size_t bytes,void* val);
void printBinary(long long n);
char* tobinary(int n);
char* tobinary2(int n);
/*******************************************************************/




/*******************************************************************/
int getint();
float getfloat();
double getdouble();
long getlong();
long long getllong();
long double getldouble();
/*******************************************************************/




/*******************************************************************/
double IEEE754ToFloat(char* binary,int precision);
unsigned long htd(char* str);
//return a binary representation string allocated from heap.
char* htb(char* hex);
/*******************************************************************/

#ifdef __cplusplus
};
#endif


#endif