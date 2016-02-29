#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../dataType.h"

typedef struct{
	void *value;
    size_t capacity;
    size_t currentSize;
	int type;
	bool isinitialized;
}vector;


vector* intVector();
vector* doubleVector();
vector* floatVector();
vector* charVector();
vector* longVector();

void pushToVector(long double vl, vector *v);

int pushStringToVector(char * string, size_t length, vector *v);
//length = 0, push exactly the length of string without '\0', length = -1 or greater then actual length of string will add '\0' to the end.

int getIntValueFromIndex(int index, vector *v);
float getFloatValueFromIndex(int index, vector *v);
double getDoubleValueFromIndex(int index, vector *v);
char getCharValueFromIndex(int index, vector *v);
long getLongValueFromIndex(int index, vector *v);

void printVector(vector *v);

bool changeValueAtIndex(int index,long double vl, vector *v);

int popIntFromVector(vector *v);
double popDoubleFromVector(vector *v);
float popFloatFromVector(vector *v);
char popCharFromVector(vector *v);
long popLongFromVector(vector *v);
int popIntFromVectorAtIndex(int index,vector *v);
double popDoubleFromVectorAtIndex(int index,vector *v);
float popFloatFromVectorAtIndex(int index,vector *v);
char popCharFromVectorAtIndex(int index,vector *v);
long popLongFromVectorAtIndex(int index,vector *v);

long getVectorLength(vector *v);
void freeVector(vector *v);
void printVectorType(vector *v);

#ifdef __cplusplus
};
#endif

#endif
