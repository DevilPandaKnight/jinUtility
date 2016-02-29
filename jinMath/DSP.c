#include "../jinMath.h"
double* hann(size_t length){
	double t;
	double* result = malloc(length*sizeof(double));
	assert(result != NULL);
    if (length <= 0) {
        printf("length has to be greater than 0.\n");
        return NULL;
    }
	for (int i = 0; i < length; ++i)
	{
		t = 0.5*(1 - cos(2 * PI*i / (length - 1)));
		result[i] = t;
	}
	return result;
}


int unitstep(long t){
	return t>=0;
}

int dirac(long t){
	return t==0;
}