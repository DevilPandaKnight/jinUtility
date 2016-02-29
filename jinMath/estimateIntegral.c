#include "../jinMath.h"
double leftEndPoint(double a, double b, int n,double (*f)(double xi)){
    double dx = (b-a)/n;
    double xi;
    double result = 0;
    for (int i = 0; i<n; i++) {
        xi = a + dx * i;
        result += dx * (*f)(xi);
    }
    return result;
}



double rightEndPoint(double a, double b, int n,double (*f)(double xi)){
    double dx = (b-a)/n;
    double xi;
    double result = 0;
    for (int i = 1; i<=n; i++) {
        xi = a + dx * i;
        result += dx * (*f)(xi);
    }
    return result;
}


double midPoint(double a,double b, int n, double (*f)(double xi)){
    double dx = (b-a)/n;
    double xi;
    double result = 0;
    for (int i = 0, len = n-1; i<=len; i++) {
        xi = a + dx*i + dx/2;
        result += dx * (*f)(xi);
    }
    return result;
}


double simpsonRule(double a,double b, int n, double (*f)(double xi)){
    if (n % 2 != 0) {
        printf("N must be an even number in order to make Simpson's Rule work out!\n");
        return 0;
    }
    double dx = (b-a)/n;
    double xi;
    double result = 0;
    for (int i = 0; i<=n; i++) {
        xi = a + dx * i;
        if (i == 0) {
            result += (dx/3) * (*f)(xi);
        }
        else if (i == n) {
            result += (dx/3) * (*f)(xi);
        }
        else if (i % 2 != 0){
            result += (dx/3) * 4 * (*f)(xi);
        }
        else if (i % 2 == 0){
            result += (dx/3) * 2 * (*f)(xi);
        }
    }
    return result;
}


double simpsonSum(double list[],double dx, int len){
    double result=0;
    for (int i = 0; i < len; ++i)
    {
        if (i==0 || i==len -1) result+=list[i];
        else if (i % 2 == 1) result += 4 * list[i];
        else result += 2 * list[i];
    }
    return (dx/3)*result;
}



//act on function
double integrate(double (*f)(double xi), double from, double to){
    if (from==to) {return 0;}
    double result=0;
    double tempTo;
    bool isSwaped = false;
    if (from>to) {
        isSwaped=true;
        swap(from, to,double);
    }
    while (from<to) {
        tempTo = from+100;
        if (tempTo<to) {
            result += simpsonRule(from, tempTo, 10000, f);
            from = tempTo;
        }
        else{
            result += simpsonRule(from, to, 10000, f);
            from = to;
        }
    }
    return isSwaped? -result:result;
}