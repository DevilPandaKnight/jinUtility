#include "../utility.h"
#define print(t) t *ptr = (t *)array;  for (int i = 0; i < length; ++i) printf(format, *(ptr+i));
void printArrayWithFormat(void* array, size_t length, int type,char* format);

void printArray(void* array, size_t length, int type){
    char temp[10];
    memcpy(temp, getSymWithN(type), 10);
    printArrayWithFormat(array, length, type, temp);
}

void printArrayWithFormat(void* array, size_t length, int type,char* format){
    if (type == intType) {
		print(int);
	}
    else if (type == doubleType){
        print(double);
    }
    else if (type == floatType){
        print(float);
    }
    else if (type == longType){
        print(long);
    }
    else if (type == longdoubleType){
        print(long double);
    }
    else if (type == longlongType){
        print(long long);
    }
    else if (type == charType){
        print(char);
    }
    else if (type == stringType){
        print(char*);
    }
}

#undef print