#include "../number.h"
int getint(){
    while (true) {
        char* line = getstring();
        if (line==NULL) {
            return 0;
        }
        
        int n; char c;
        if (sscanf(line, "%d %c" ,&n,&c)==1) {
            free(line);
            return n;
        }
        else{
            free(line);
            printf("Retry\n");
        }
    }
}

float getfloat(){
    while (true) {
        char* line = getstring();
        if (line==NULL) {
            return 0;
        }
        
        float n; char c;
        if (sscanf(line, "%f %c" ,&n,&c)==1) {
            free(line);
            return n;
        }
        else{
            free(line);
            printf("Retry\n");
        }
    }
}

long getlong(){
    while (true) {
        char* line = getstring();
        if (line==NULL) {
            return 0;
        }
        
        long n; char c;
        if (sscanf(line, "%ld %c" ,&n, &c)==1) {
            free(line);
            return n;
        }
        else{
            free(line);
            printf("Retry\n");
        }
    }
}


double getdouble(){
    while (true) {
        char* line = getstring();
        if (line==NULL) {
            return 0;
        }
        
        double n; char c;
        if (sscanf(line, "%lf %c" ,&n,&c)==1) {
            free(line);
            return n;
        }
        else{
            free(line);
            printf("Retry\n");
        }
    }
}


long long getllong(){
    while (true) {
        char* line = getstring();
        if (line==NULL) {
            return 0;
        }
        
        long long n; char c;
        if (sscanf(line, "%lld %c" ,&n,&c)==1) {
            free(line);
            return n;
        }
        else{
            free(line);
            printf("Retry\n");
        }
    }
}




long double getldouble(){
    while (true) {
        char* line = getstring();
        if (line==NULL) {
            return 0;
        }
        
        long double n; char c;
        if (sscanf(line, "%Lf %c" ,&n,&c)==1) {
            free(line);
            return n;
        }
        else{
            free(line);
            printf("Retry\n");
        }
    }
}