/*************************************************************************** 
 * Description: Testing of Implementation of Calculator
 * Author: Oriel Nofekh
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>         /* printf */
#include <math.h>          /* pow */
#include "calculator.h"    /* calculator API */

/******************************************************************************/
/***                        Color Defines   		                      ***/
/******************************************************************************/
#define DEF     "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

static int test_counter_g = 0;
static int success_counter_g = 0;

#define TEST(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEF, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)

#define TESTC(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %c, Expected: %c\n" DEF, name, __LINE__, (char) (real), (char) (expected)); \
    } while (0)

#define TESTD(name, real, expected) \
    do { \
        ++test_counter_g; \
        (((real)-(expected) < 0.0000000001) || ((expected)-(real) < 0.0000000001)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %.30g, Expected: %.30g\n" DEF, name, __LINE__, (double) (real), (double) (expected)); \
    } while (0)

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)





/************************* Tests Functions *************************/

static void TestPhase1(void)
{
	calc_status_t calc_status = 0;
	double res = 0.0;
	
	/* first, we test only + and -, and without white spaces */
	
	calc_status = Calculate("1+2+3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1+2+3);
	
	calc_status = Calculate("1-2", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1-2);
	
	
	
	calc_status = Calculate("1-2-3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1-2-3);
	
	calc_status = Calculate("0-6+1.2-2-3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 0-6+1.2-2-3);
	
	/* next, we test with white spaces */
	
	calc_status = Calculate("1 +2 +3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1 +2 +3);
	
	calc_status = Calculate("1- 2", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1- 2);
	
	calc_status = Calculate(" 1 -2-  3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1 -2-  3);
	
	calc_status = Calculate("0- 6.56 + 1-  2 -3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 0- 6.56 + 1-  2 -3);
	
	/* now, we test with * only */
	
	calc_status = Calculate("7 * 8.0 * 9", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 7 * 8.0 * 9);
	
	calc_status = Calculate("1 * 5 * 13 * 19", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1 * 5 * 13 * 19);
	
	/* now, we test with / only */
	
	calc_status = Calculate("5.0 / 7.0", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 5.0 / 7.0);
	
	calc_status = Calculate("15.5 / 31.0", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 15.5 / 31.0);
	
	calc_status = Calculate("5 / 7", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 5.0 / 7.0);
	
	calc_status = Calculate("15.5 / 31", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 15.5 / 31.0);
	
	calc_status = Calculate("15.5 / 31.0 / 2.0", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 15.5 / 31.0 / 2.0);
	
	/* now, with both * and / */
	
	calc_status = Calculate("15.5 / 31 * 2.5 / 8", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 15.5 / 31.0 * 2.5 / 8.0);
	
	calc_status = Calculate("15.5 / 31 * 2.5 / 8 / 5.0 / 1.25", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 15.5 / 31.0 * 2.5 / 8.0 / 5.0 / 1.25);
	
	/* finally, tests with all 4 operators: + - * / */
	
	calc_status = Calculate("1 + 2*3 + 4 - 5/2", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1.0 + 2.0*3.0 + 4.0 - 5.0/2.0);
	
	calc_status = Calculate("100*7/70 + 4/7*3*13 - 5+2/4", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 100.0*7.0/70.0 + 4.0/7.0*3.0*13.0 - 5.0+2.0/4.0);
	
	/* ok, and let's test some cases with syntax and with math errors */
	
	/* syntax errors */
	
	calc_status = Calculate("*5", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("55 5", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("15/", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("4 + 6 - *6", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("4 + 7 - a", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("2 + 3x", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	/* math errors */
	
	calc_status = Calculate("8/0", &res);
	TEST("calc_status", calc_status, CALC_MATH_ERROR);
	
	calc_status = Calculate("0/0", &res);
	TEST("calc_status", calc_status, CALC_MATH_ERROR);
	
	calc_status = Calculate("0*18/0", &res);
	TEST("calc_status", calc_status, CALC_MATH_ERROR);
	
	calc_status = Calculate("2- 8/ 0+5", &res);
	TEST("calc_status", calc_status, CALC_MATH_ERROR);
	
	printf(BOLDBLUE "Completed TestPhase1\n" DEF);
}

static void TestPhase2(void)
{
	calc_status_t calc_status = 0;
	double res = 0.0;
	
	/* first, we test without any syntax errors */
	
	calc_status = Calculate("1+(2+3)", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1+(2+3));
	
	calc_status = Calculate("1-(2+3)", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1-(2+3));
	
	calc_status = Calculate("1-[2+3]", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1-(2+3));
	
	calc_status = Calculate("1+((2+3))", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1+((2+3)));
	
	calc_status = Calculate("5*{2+3}", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 5*(2+3));
	
	calc_status = Calculate("5/(4+3)", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 5.0/(4+3));
	
	calc_status = Calculate("5/(6 + 7*(4+3))", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 5.0/(6 + 7*(4+3)));
	
	calc_status = Calculate("5/(6 + 7*(4+3) - 2*(3-7))", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 5.0/(6 + 7*(4+3) - 2*(3-7)));
	
	calc_status = Calculate("(2+3)", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, (2+3));
	
	calc_status = Calculate("(2+3)*18", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, (2+3)*18);
	
	calc_status = Calculate("(2+3)*(6+7)", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, (2+3)*(6+7));
	
	calc_status = Calculate("(2+3)*(8+ 9*(7-17)/6/(10-210))", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, (2+3)*(8+ 9*(7-17)/6.0/(10.0-210.0)));
	
	calc_status = Calculate("1.2 + (2.77 - 8.2*9.1*(1.1-9.301))*6.2", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 1.2 + (2.77 - 8.2*9.1*(1.1-9.301))*6.2);
	
	/* now, let's test cases with syntax errors and math errors */
	
	/* syntax errors */
	
	calc_status = Calculate("(2+3", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("2+3)", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("(2+3))", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("((2+3)", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("1+(2+(3*6)-7", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("1+[2+[3*6]-7", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("1+2+{3*6}-7}-9", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("2+(*3)", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("2-(/3)", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("(2+3*) 7", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("(2+3/) 7", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	/* math errors */
	
	calc_status = Calculate("8 / (2+3-5)", &res);
	TEST("calc_status", calc_status, CALC_MATH_ERROR);
	
	calc_status = Calculate("8 / (5*(2+3)-25)", &res);
	TEST("calc_status", calc_status, CALC_MATH_ERROR);
	
	printf(BOLDBLUE "Completed TestPhase2\n" DEF);
}

static void TestPhase3(void)
{
	calc_status_t calc_status = 0;
	double res = 0.0;
	
	/* first, we test without any syntax errors */
	
	/* first, only power, no other operators */
	
	calc_status = Calculate("2^4", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(2.0, 4.0));
	
	calc_status = Calculate("1^10", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(1.0, 10.0));
	
	calc_status = Calculate("1.7^2.8", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(1.7, 2.8));
	
	calc_status = Calculate("1.3^2.7^0.3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(1.3, pow(2.7, 0.3)));
	
	calc_status = Calculate("0.3^2.7^2.3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(0.3, pow(2.7, 2.3)));
	
	calc_status = Calculate("(1.3^2.7)^0.3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(pow(1.3, 2.7), 0.3));
	
	calc_status = Calculate("2.2^1.1^(1.3^2.7)^0.3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(2.2, pow(1.1, pow(pow(1.3, 2.7), 0.3))));
	
	/* now, combined with other operators */
	
	calc_status = Calculate("(2+5)^4", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(2.0+5.0, 4.0));
	
	calc_status = Calculate("(2-5)^4", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(2.0-5.0, 4.0));
	
	calc_status = Calculate("(2-5)^3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(2.0-5.0, 3.0));
	
	calc_status = Calculate("3*(2-5)^3", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 3*pow(2.0-5.0, 3.0));
	
	calc_status = Calculate("3*(2-5)^3 * 4", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 3*pow(2.0-5.0, 3.0) * 4);
	
	calc_status = Calculate("3.0*(5.0-4.1)^(3.0 * 2.2) / 6.2", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 3.0*pow(5.0-4.1, 3.0 * 2.2) / 6.2);
	
	calc_status = Calculate("3.0*(5.0-4.1)^(3.0 * 2.2)^16.3 / 6.2", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, 3.0*pow(5.0-4.1, pow(3.0 * 2.2, 16.3)) / 6.2);
	
	calc_status = Calculate("(2.0-5.0)^(4.0^3.0/2.0)", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(2.0-5.0, pow(4.0, 3.0)/2.0));
	
	calc_status = Calculate("(2.0-5.0)^(4.0^(3.0/2.0))", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(2.0-5.0, pow(4.0, 3.0/2.0)));
	
	calc_status = Calculate("4.3^(1.0-6.7)", &res);
	TEST("calc_status", calc_status, CALC_SUCCESS);
	TESTD("result", res, pow(4.3, 1.0-6.7));
	
	/* ok, and let's test some cases with syntax and with math errors */
	
	/* syntax errors */
	
	calc_status = Calculate("^5", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("2^5^", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("2^^5", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	calc_status = Calculate("2^(^5)", &res);
	TEST("calc_status", calc_status, CALC_SYNTAX_ERROR);
	
	/* math errors */
	
	calc_status = Calculate("(2-7)^0.5", &res);
	TEST("calc_status", calc_status, CALC_MATH_ERROR);
	
	calc_status = Calculate("0^(2-5)", &res);
	TEST("calc_status", calc_status, CALC_MATH_ERROR);
	/*
	calc_status = Calculate("0^0", &res);
	TEST("calc_status", calc_status, CALC_MATH_ERROR);
	*/
	printf(BOLDBLUE "Completed TestPhase3\n" DEF);
}

/************************* main function *************************/

int main(void)
{
	TestPhase1();
	
	TestPhase2();
	
	TestPhase3();

	
	PASS;
	
	return 0;
}




















