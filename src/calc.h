/**
 * @file calc.h
 * @brief Header file for the calculation functions.
 */

#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

namespace MathLib {
    double sum(double a, double b);
    double minus(double a, double b);
    double multi(double a, double b);
    double delit(double a, double b);

    long factorial(long num);
    double pow(double x, double y);
    double root(double x, double y);
} // namespace MathLib

#endif