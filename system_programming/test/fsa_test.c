/*************************************************************************** 
 * Description: Testing for doubly linked list functions
 * Author: Oriel Nofekh
 * Reviewer: 
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>         /* printf */
#include <stdlib.h>        /* malloc, free */
#include "fsa.h"           /* fsa_t and FSA API */

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

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)





typedef struct
{
	long int num;
	char c;
} long_char_t; 


/******************************************************************************/
/***                          Testing Functions                             ***/
/******************************************************************************/

static void TestCreateDestroy(void)
{
	size_t num_blocks = 20;
	size_t block_size = 11;
	void *pool = malloc(FSASuggestSize(num_blocks, block_size));
	fsa_t *fsa = FSAInit(pool, num_blocks, block_size);
	
	(void) fsa;
	
	free(pool);
	
	printf(BOLDBLUE "Completed TestCreateDestroy\n" DEF);
}



static void Test1(void)
{
	size_t i = 0;
	long_char_t *arr[12];
	size_t num_blocks = 10;
	size_t block_size = 9;
	void *pool = NULL;
	fsa_t *fsa = NULL;
	
	pool = malloc(FSASuggestSize(num_blocks, block_size));
	
	/********** Part I **********/
	
	fsa = FSAInit(pool, num_blocks, block_size);
	
	for (i = 0; i < 10; ++i)
	{
		arr[i] = FSAAlloc(fsa);
		arr[i]->num = (long) i;
		arr[i]->c = (char) ('0' + i);
	}
	
	for (i = 0; i < 10; ++i)
	{
		TEST("long value", arr[i]->num, (long) i);
		TESTC("char value", arr[i]->c, (char) ('0' + i));
	}
	
	arr[10] = FSAAlloc(fsa);
	arr[11] = FSAAlloc(fsa);
	TEST("No more space", arr[10], NULL);
	TEST("No more space", arr[11], NULL);
	
	/********** Part II **********/
	
	fsa = FSAInit(pool, num_blocks, block_size);
	
	for (i = 0; i < 10; ++i)
	{
		TEST("FSACountFree", FSACountFree(fsa), 10 - i);
		arr[i] = FSAAlloc(fsa);
		arr[i]->num = (long) -i;
		arr[i]->c = (char) ('A' - 1 + i);
	}
	
	for (i = 0; i < 10; ++i)
	{
		TEST("long value", arr[i]->num, (long) -i);
		TESTC("char value", arr[i]->c, (char) ('A' - 1 + i));
	}
	
	arr[10] = FSAAlloc(fsa);
	arr[11] = FSAAlloc(fsa);
	TEST("No more space", arr[10], NULL);
	TEST("No more space", arr[11], NULL);
	TEST("FSACountFree", FSACountFree(fsa), 0);
	
	/********** Part III **********/
	
	FSAFree(fsa, arr[2]);
	TEST("FSACountFree", FSACountFree(fsa), 1);
	arr[2] = FSAAlloc(fsa);
	TEST("FSACountFree", FSACountFree(fsa), 0);
	arr[10] = FSAAlloc(fsa);
	TEST("FSACountFree", FSACountFree(fsa), 0);
	TEST("No more space", arr[10], NULL);
	
	FSAFree(fsa, arr[2]);
	TEST("FSACountFree", FSACountFree(fsa), 1);
	FSAFree(fsa, arr[1]);
	TEST("FSACountFree", FSACountFree(fsa), 2);
	FSAFree(fsa, arr[7]);
	TEST("FSACountFree", FSACountFree(fsa), 3);
	
	arr[2] = FSAAlloc(fsa);
	TEST("FSACountFree", FSACountFree(fsa), 2);
	arr[1] = FSAAlloc(fsa);
	TEST("FSACountFree", FSACountFree(fsa), 1);
	
	FSAFree(fsa, arr[2]);
	TEST("FSACountFree", FSACountFree(fsa), 2);
	FSAFree(fsa, arr[1]);
	TEST("FSACountFree", FSACountFree(fsa), 3);
	FSAFree(fsa, arr[0]);
	TEST("FSACountFree", FSACountFree(fsa), 4);
	FSAFree(fsa, arr[9]);
	TEST("FSACountFree", FSACountFree(fsa), 5);
	FSAFree(fsa, arr[8]);
	TEST("FSACountFree", FSACountFree(fsa), 6);
	
	for (i = 3; i < 7; ++i)
	{
		TEST("long value", arr[i]->num, (long) -i);
		TESTC("char value", arr[i]->c, (char) ('A' - 1 + i));
	}
	
	/********** End **********/
	
	free(pool);
	
	printf(BOLDBLUE "Completed Test1\n" DEF);
}



static void TestMain(void)
{
	TestCreateDestroy();
	
	Test1();
	
	PASS;
}



int main(void)
{
	TestMain();
	
	return 0;
}



