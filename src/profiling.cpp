/**
 * @file profiling.cpp
 * @brief this file contains algorithm for standard deviation
 * @author Jan Zajicek, xzajic22
 * @date 4/28/2022
 */
#include "calc.cpp"
#include <cmath>
#include <iostream>
#include <vector>

/// typedef for used variable type
typedef long double ld;

/**
 * @brief Function for calculating average of array N elements
 * @param x vector of numbers
 * @param N size of array
 * @return average of array
 */
ld average(std::vector<ld> x, ld N)
{
    ld avg = 0;
    for (auto i : x) {
        avg = MathLib::sum(avg, i);
    }
    return MathLib::delit(avg, N);
}

/**
 * @brief Function for calculating standard deviation of values in stdin. 
 */
int main()
{
    std::vector<ld> x;
    long N = 0;
    ld input;
    for (; std::cin >> input; N++) {
        x.push_back(input);
    }
    ld avg = average(x, N);
    ld summ = 0;
    for (auto i : x) {
        summ = MathLib::sum(MathLib::pow(MathLib::minus(i, avg), 2), summ);
    }
    ld s = MathLib::multi(MathLib::delit(1, N - 1), summ);
    ld stddev = MathLib::root(s, 2);
    std::cout << stddev << std::endl;
    return 0;
}
