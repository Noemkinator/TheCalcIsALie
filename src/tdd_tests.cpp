/**
 * @file tdd_tests.cpp
 * @author Veronika Trutnovska, xtrutn00 
 * 
 * @brief Tests for a calculator 
 */

#include "gtest/gtest.h"
#include "calc.h"
TEST (Calc, Add){
    //valid function calls
	EXPECT_DOUBLE_EQ(f_add(4356,-8765),-4409);
	EXPECT_DOUBLE_EQ(f_add(-42.756,-34.11),-76.866);
	
	//double loses too much precision
	EXPECT_ANY_THROW(f_add(30,90071992547409929007199254740992)); 
}
TEST (Calc, Sub){
    //valid function calls
	EXPECT_DOUBLE_EQ(f_sub(4356,1765),2591);
	EXPECT_DOUBLE_EQ(f_sub(-42.756,34.11),-76.866);
	
	//double loses too much precision
	EXPECT_ANY_THROW(f_sub(-30,90071992547409929007199254740992)); 
}
TEST (Calc, Mul){
    //valid function calls
	EXPECT_DOUBLE_EQ(f_mul(4356.784,-8765),38187211.76);
	EXPECT_DOUBLE_EQ(f_mul(-42.756,-34.11),1458.40716);
	EXPECT_DOUBLE_EQ(f_mul(0,-34.11),0);
	
	//TODO double 'overflow'
	//double loses too much precision
	EXPECT_ANY_THROW(f_mul(1,1));//can't reach the limit for some reason, i'll work on that
}
TEST (Calc, Div){
    //valid function calls
	//precision 15 decimal places
	EXPECT_DOUBLE_EQ(f_div(4862,645),7.537984496124031);
	EXPECT_DOUBLE_EQ(f_div(-48.6512,34.11),-1.426303136909997);
	EXPECT_DOUBLE_EQ(f_div(48.6512,-34.11),-1.426303136909997);
	EXPECT_DOUBLE_EQ(f_div(0,34.11),0);

	//division by zero
	EXPECT_ANY_THROW(f_div(6543.65,0));
	EXPECT_ANY_THROW(f_div(0,0));
}
TEST (Calc, Exponent){
    //valid function calls
	EXPECT_DOUBLE_EQ(f_exponent(9,5),59049);
	EXPECT_DOUBLE_EQ(f_exponent(-9,5),-59049);
	EXPECT_DOUBLE_EQ(f_exponent(-9,4),6561);
	EXPECT_DOUBLE_EQ(f_exponent(191,18),114445997944945590502027775581205708144640);
	EXPECT_DOUBLE_EQ(f_exponent(-5,0),1);
	EXPECT_DOUBLE_EQ(f_exponent(0,19),0);
	EXPECT_DOUBLE_EQ(f_exponent(0,0),1);
	EXPECT_DOUBLE_EQ(f_exponent(-5,0),1);

	//double loses too much precision, it just shows infinity
	EXPECT_ANY_THROW(f_exponent(1991,188));
	//non-natural exponent
	EXPECT_ANY_THROW(f_exponent(16,-4));
	EXPECT_ANY_THROW(f_exponent(16,2.5));
	EXPECT_ANY_THROW(f_exponent(0,-4));
	EXPECT_ANY_THROW(f_exponent(0,2.5));
} 
TEST (Calc, Root){
    //valid function calls
	//15 decimal places
	EXPECT_DOUBLE_EQ(f_root(13,2),3.605551275463989);
	EXPECT_DOUBLE_EQ(f_root(-1728,3),-12);
	EXPECT_DOUBLE_EQ(f_root(4,0.125),65536);
	EXPECT_DOUBLE_EQ(f_root(0.2,0.5),0.04);
	EXPECT_DOUBLE_EQ(f_root(4,-0.5),0.0625);

	//invalid root
	EXPECT_ANY_THROW(f_root(16,0));
	EXPECT_ANY_THROW(f_root(0,0));
	EXPECT_ANY_THROW(f_root(-9,4));
}
TEST (Calc, Factrial){
    //valid function calls
	EXPECT_DOUBLE_EQ(f_factorial(0),1);
	EXPECT_DOUBLE_EQ(f_factorial(1),1);
	EXPECT_DOUBLE_EQ(f_factorial(8),40320);
	
	//double loses too much precision (i think it'll just show inf?)
	EXPECT_ANY_THROW(f_factorial(171));
	//invalid factorial
	EXPECT_ANY_THROW(f_factorial(-9));
	EXPECT_ANY_THROW(f_factorial(2.4));
}
