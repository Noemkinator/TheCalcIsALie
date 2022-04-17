/**
 * @file complx_funcs.cpp
 * @brief this file contains addition, subtraction,
 * division, multiplication, factorial,
 * power and root functions.
 * 
 * @author Ivo Puchnar, xpuchn02 
 * 
 * @date 4/28/2022
 */

#include <math.h>
#include <iostream>
#include "calc.h"

/**
 * This function adds given numbers
 * @author Ivo Puchnar, xpuchn02
 * @param a Summand/addend
 * @param b Summand/addend
 * @date 4/28/2022
 */
double sum(double a, double b){
    return a+b;
}

/**
 * This function subtracts given numbers
 * @author Ivo Puchnar, xpuchn02
 * @param a Minuend
 * @param b Subtrahend
 * @date 4/28/2022
 */
double minus(double a, double b){
    return a-b;
}

/**
 * This function multiplies given numbers
 * @author Ivo Puchnar, xpuchn02
 * @param a Multiplier
 * @param b Multiplicand
 * @date 4/28/2022
 */
double multi(double a, double b){
    return a*b;
}

/**
 * This function divides given numbers and checks
 * to not divide by 0
 * @author Ivo Puchnar, xpuchn02
 * @param a Dividend
 * @param b Dibisor
 * @date 4/28/2022
 */
double delit(double a, double b){
    if (b){
        return a/b;
    } else {
        throw "Can't divide by 0";
    }
}

/**
 * This function makes factoral of given number and checks
 * for negative numbers
 * @author Ivo Puchnar, xpuchn02
 * @param num Base for factorial
 * @date 4/28/2022
 */
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

/**
 * Function pow() is imported from library math.h,
 * it makes nth power of base
 * double pow(double x, double y);
 * author Ivo Puchnar, xpuchn02
 * param x Base
 * param y Exponent
 * date 4/28/2022
 */

/**
 * This function makes nth root of given
 * numbers and checks for negative radicands and 0 degree
 * @author Ivo Puchnar, xpuchn02
 * @param x Radicand
 * @param y Degree
 * @date 4/28/2022
 */
double root(double x, double y){
    if (x<0){
        throw "Can't make root of negative";
    }
    if (y==0){
        throw "Can't make 0th root\n";
    }
    return pow(x,1/y);
}
