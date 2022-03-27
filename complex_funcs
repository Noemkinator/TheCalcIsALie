/**
 * @file complex_funcs.cpp
 * @author Ivo Puchnar, xpuchn02 
 * 
 * @brief Complex Functions
 */

//#include "calc.h"
#include <iostream>
#include <math.h>

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
    std::cout << root(2,2) << "\n";
    std::cout << root(1,-4) << "\n";
    std::cout << root(2,0) << "\n";
    std::cout << root(3,-2) << "\n";
    std::cout << root(13,1) << "\n";
    std::cout << root(-22,4);
    return 0;
}*/
