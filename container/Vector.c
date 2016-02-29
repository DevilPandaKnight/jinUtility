#include "Vector.h"
#define initVector(t) {vector *temp = (vector *)malloc(sizeof(vector)); if (temp==NULL) return NULL; temp->value=NULL; temp->isinitialized=true;    temp->capacity =0; temp->currentSize=0; temp->type = type; return temp;}

vector* intVector(){
	int type = intType;
	initVector(int)
}
vector* doubleVector(){
	int type = doubleType;
	initVector(double)
}
vector* floatVector(){
	int type = floatType;
	initVector(float)
}
vector* charVector(){
	int type = charType;
	initVector(char)
}
vector* longVector(){
	int type = longType;
	initVector(long)
}


#define push(val,v,t) if (v->capacity==0 && v->currentSize==0){v->value = malloc(sizeof(t));if (v->value==NULL) return; v->capacity=1; ptr=(t *)v->value;  ptr[v->currentSize++]= val;  return;} if (v->currentSize>=v->capacity) {v->capacity *=2;void *temp=realloc(v->value, sizeof(t)*(v->capacity)); if (temp==NULL) {printf("ask too large memory, killed vector to save memory.\n");freeVector(v);return; } v->value = temp; ptr=(t *)v->value; ptr[v->currentSize++]=val;} else{ ptr=(t *)v->value; ptr[v->currentSize++]=val; }


void pushToVector(long double vl, vector *v){
    if (v==NULL || v->isinitialized==false) {
		printf("please init vector first.\n");
		return;
	}
    
    else{
		if (v->type==intType) {int *ptr; int val = (int)vl; push(val,v,int);}
		else if (v->type==charType) {char *ptr;char val=(char)vl; push(val,v,char);}
		else if (v->type==floatType) {float *ptr;float val =(float)vl; push(val,v,float);}
		else if (v->type==doubleType) {double *ptr; double val=(double)vl; push(val,v,double);}
		else if (v->type==longType) {long *ptr; long val= (long)vl; push(val,v,long);}
    }
}


int pushStringToVector(char* string, size_t length, vector *v){
    if (string==NULL || v==NULL || v->isinitialized==false) {
        return 0;
    }
    int i =0;
    while (*string != '\0') {
        if (i == length && length != 0) {
            break;
        }
        pushToVector(*string, v);
        i++;
        string++;
    }
    if (length == -1 || length>i) {
        pushToVector('\0', v);
        i++;
    }
    return i;
}


#define checkIndex(index,v) if (v==NULL) {printf("Null vetor\n");return 0;} if (index>=v->currentSize) {printf("index out of range\n"); return 0;}

#define typeCheck(v,t) if (v->type != t) {printf("operation failed! get value from wrong type, please check your vector type.\n"); return 0;}

int getIntValueFromIndex(int index, vector *v){
	typeCheck(v,intType);
	int *ptr = (int *)v->value;
	checkIndex(index,v);
	return ptr[index];
}
float getFloatValueFromIndex(int index, vector *v){
	typeCheck(v,floatType);
	float *ptr = (float *)v->value;
	checkIndex(index,v);
	return ptr[index];
}
double getDoubleValueFromIndex(int index, vector *v){
	typeCheck(v,doubleType);
	double *ptr = (double *)v->value;
	checkIndex(index,v);
	return ptr[index];
}
char getCharValueFromIndex(int index, vector *v){
	typeCheck(v,charType);
	char *ptr = (char *)v->value;
	checkIndex(index,v);
	return ptr[index];
}
long getLongValueFromIndex(int index, vector *v){
	typeCheck(v,longType);
	long *ptr = (long *)v->value;
	checkIndex(index,v);
	return ptr[index];
}

#define changeValue(t) t val = (t)vl; t *ptr = (t *)v->value; ptr[index] = val; return true;


bool changeValueAtIndex(int index,long double vl, vector *v){
    checkIndex(index, v);
    if (v->type==intType) {
        changeValue(int);
    }
    else if (v->type==floatType) {
        changeValue(float);
    }
    else if (v->type==doubleType) {
        changeValue(double);
    }
    else if (v->type==charType) {
        changeValue(char);
    }
    else if (v->type==longType) {
        changeValue(long);
    }
    return false;
    
}

void printVector(vector *v){
	if (v==NULL) return;
	if (v->currentSize==0){
		printf("empty vector.\n");
		return;
	}
	if (v->type == intType) {
		int *ptr = (int *)v->value;
	    for (int i=0; i<v->currentSize; i++) {
	        printf("%d\n",ptr[i]);
	    }
	}
	else if (v->type == doubleType) {
		double *ptr = (double *)v->value;
	    for (int i=0; i<v->currentSize; i++) {
	        printf("%f\n",ptr[i]);
	    }
	}
	else if (v->type == floatType) {
		float *ptr = (float *)v->value;
	    for (int i=0; i<v->currentSize; i++) {
	        printf("%f\n",ptr[i]);
	    }
	}
	else if (v->type == charType) {
		char *ptr = (char *)v->value;
	    for (int i=0; i<v->currentSize; i++) {
	        printf("%c\n",ptr[i]);
	    }
	}
	else if (v->type == longType) {
		long *ptr = (long *)v->value;
	    for (int i=0; i<v->currentSize; i++) {
	        printf("%ld\n",ptr[i]);
	    }
	}
}

#define checkEmpty(v) if (v==NULL) {printf("Null vetor\n");return 0;}if (v->currentSize==0) {printf("pop from empty vector\n");return 0; }

int popIntFromVector(vector *v){
	typeCheck(v,intType);
	int *ptr= (int *)v->value;
	checkEmpty(v);
    return ptr[--(v->currentSize)];
}
double popDoubleFromVector(vector *v){
	typeCheck(v,doubleType);
	double *ptr= (double *)v->value;
	checkEmpty(v);
    return ptr[--(v->currentSize)];
}
float popFloatFromVector(vector *v){
	typeCheck(v,floatType);
	float *ptr=(float *)v->value;
	checkEmpty(v);
    return ptr[--(v->currentSize)];
}
char popCharFromVector(vector *v){
	typeCheck(v,charType);
	char *ptr=(char *)v->value;
	checkEmpty(v);
    return ptr[--(v->currentSize)];
}
long popLongFromVector(vector *v){
	typeCheck(v,longType);
	long *ptr=(long *)v->value;
	checkEmpty(v);
    return ptr[--(v->currentSize)];
}


long getVectorLength(vector *v){
	if (v==NULL) {
		printf("Null vetor\n");
		return 0;
	}
    return v->currentSize;
}

void freeVector(vector *v){
    if (v!=NULL && v->value != NULL) {
		v->isinitialized = false;
        free(v->value);
        v->value=NULL;
        free(v);
        v=NULL;
    }
    else if (v!=NULL && v->value == NULL) {
        free(v);
        v=NULL;
    }
}

#define popValueFromIndex(t) checkIndex(index,v);  t *ptr = (t *)v->value; t value = ptr[index]; for (int i=0; i<(v->currentSize-index-1); i++) {ptr[index+i] = ptr[index+i+1];} v->currentSize--;return value;

int popIntFromVectorAtIndex(int index,vector *v){
    typeCheck(v, intType);
    popValueFromIndex(int)
}
double popDoubleFromVectorAtIndex(int index,vector *v){
    typeCheck(v, doubleType);
    popValueFromIndex(double)
}
float popFloatFromVectorAtIndex(int index,vector *v){
    typeCheck(v, floatType);
    popValueFromIndex(float)
}
char popCharFromVectorAtIndex(int index,vector *v){
    typeCheck(v, charType);
    popValueFromIndex(char)
}
long popLongFromVectorAtIndex(int index,vector *v){
    typeCheck(v, longType);
    popValueFromIndex(long)
}


void printVectorType(vector *v){
	if (v->type == intType) printf("int type\n");
	else if (v->type == doubleType) printf("double type\n");
	else if (v->type == floatType) printf("float type\n");
	else if (v->type == charType) printf("char type\n");
	else if (v->type == longType) printf("long type\n");
}

#undef initVector
#undef push
#undef checkIndex
#undef typeCheck
#undef changeValue
#undef checkEmpty
#undef popValueFromIndex