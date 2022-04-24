/**
 * @file profiling.cpp
 * @brief this file contains algorithm for standard deviation
 * @author Jan Zajicek, xzajic22
 * @date 4/28/2022
 */
#include <iostream>
#include "calc.cpp"
typedef long double ld;

ld average(ld *x,ld N){
	ld avg=0;
	for(long i=0;i<N;i++){
		avg= MathLib::sum(avg,x[i]);
	}
	return MathLib::delit(avg,N);
}
int main(int argc,char *argv[]){
	ld x[4096];
	long N=0;
	ld input;
	for(N;std::cin >> input;N++){
		x[N]=input;
	}
	ld avg=average((ld*)x,N);
	ld summ=0;
	for(long i=0;i<N;i++){
		summ=MathLib::sum(pow(MathLib::minus(x[i],avg),2),summ);
	}
	ld s = MathLib::multi(MathLib::delit(1,N-1),summ);
	ld stddev= MathLib::root(s,2);
	std::cout << stddev << std::endl;
	return 0;
}

