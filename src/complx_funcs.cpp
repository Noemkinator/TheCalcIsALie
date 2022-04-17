/**
 * @file complex_funcs.cpp
 * @author Ivo Puchnar, xpuchn02 
 * 
 * @brief Complex Functions
 */

#include <math.h>
#include <iostream>
#include "calc.h"

double sum(double a, double b){
    return a+b;
}

double minus(double a, double b){
    return a-b;
}

double multi(double a, double b){
    return a*b;
}

double delit(double a, double b){
    if (b){
        return a/b;
    } else {
        throw "Can't divide by 0";
    }
}

int factorial(int num){
    if (num<0){
        throw "Can't make factorial of negative";
    }
    int x = 1;
    for (int i = 0;i+1 < num;i++){
        x*= (num - i);
    }
    return x;
}

//double pow(double x, double y){;} from library math.h

double root(double x, double y){
    if (x<0){
        throw "Can't make root of negative";
    }
    if (y==0){
        throw "Can't make 0th root\n";
    }
    return pow(x,1/y);
}
