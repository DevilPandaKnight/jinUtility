#include "../jinMath.h"
double summation(char* equation,double from, double to){
    char* replaced;
    char buf[BUFSIZ];
    double result = 0;
    memset(buf, '\0', BUFSIZ);
    for (double i = from; i<=to; i++) {
        sprintf(buf, "%f",i);
        replaced = replaceStr(equation, "n", buf);
        memset(buf, '\0', BUFSIZ);
        result += evaluate(replaced);
        free(replaced);
    }
    return result;
}


//give expression like m*2^i and binary sequence like 111
//it will replace m with the squence from LSB to MSB.
//and replace i with the range you enterd
double binarySummation(char* exp,char* binarySequence, double from, double to){
    if (from < 0) {
        from = 0;
    }
    int bLen=(int)strlen(binarySequence);
    if (to < 0) {
        to = bLen-1;
    }
    if (exp == NULL || binarySequence == NULL) {
        printf("expression or binarySequence are not set.\n");
        return 0;
    }
    for (int i = 0,len = strlen(binarySequence); i<len; i++) {
        if (binarySequence[i] != '1' && binarySequence[i]!='0') {
            printf("invalid binary sequence.\n");
            return 0;
        }
    }
    char bufForI[BUFSIZ];
    char bufForM[2] = {'\0','\0'};
    
    double result = 0;
    char* format;
    char* temp;
    for (int i = from; i<=to; i++) {
        bufForM[0] = binarySequence[--bLen];
        temp = replaceStr(exp, "m", bufForM);
        memset(bufForI, '\0', BUFSIZ);
        sprintf(bufForI, "%d",i);
        format = replaceStr(temp, "i", bufForI);
        result += evaluate(format);
        free(format);
        free(temp);
    }
    return result;
}
