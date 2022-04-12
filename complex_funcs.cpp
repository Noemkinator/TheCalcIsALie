/**
 * @file complex_funcs.cpp
 * @author Ivo Puchnar, xpuchn02 
 * 
 * @brief Complex Functions
 */

//#include "calc.h"
#include <iostream>
#include <math.h>

int sum(int a, int b){
    return a+b;
}

int minus(int a, int b){
    return a-b;
}

int multi(int a, int b){
    return a*b;
}

int delit(int a, int b){
    if (b){
        return (float)a/b;
    } else {
        //placeholder
        std::cout << "Error\n";
        return 0;
    }
}

int factorial(int num){
    if (num<0){
        //placeholder
        std::cout << "Error\n";
        return 0;
    }
    int x = 1;
    for (int i = 0;i+1 < num;i++){
        x*= num - i;
    }
    return x;
}

//double pow(double x, double y){;} from library math.h

double root(double x, double y){
    if (x<0){
        //placeholder
        std::cout << "Error";
        return 0;
    }
    if (y==0){
        //placeholder
        std::cout << "Error";
        return 0;
    }
    return pow(x,1/y);
}



/*int main() for testing DELETE
{
    std::cout << delit(2,2) << "\n";
    std::cout << delit(1,-4) << "\n";
    std::cout << delit(2,0) << "\n";
    std::cout << delit(3,-2) << "\n";
    std::cout << delit(13,1) << "\n";
    std::cout << delit(-22,4);
    return 0;
}*/
