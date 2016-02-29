#ifndef __MATHEVALUATOR_H__
#define __MATHEVALUATOR_H__
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../jinString.h"
#include "../jinMath.h"
#include "../container.h"

typedef struct MathString{
    JObject* object;
    int numberOfNumsPointToOperator;
    double left;
    double right;
    double string;
    char operString;
    int index;
}MathString;

double evaluate(char* expression);

#ifdef __cplusplus
};
#endif

#endif