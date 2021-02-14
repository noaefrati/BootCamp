/*************************************************************************** 
 * Description: Testing for Variable-Length Allocator
 * Author: Oriel Nofekh
 * Reviewer: 
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>         /* printf */
#include <stdlib.h>        /* malloc, free */
#include "vsa.h"           /* vsa_t and VSA API */

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
	size_t pool_size = 200;
	void *pool = malloc(pool_size);
	vsa_t *vsa = VSAInit(pool, pool_size);
	
	(void) vsa;
	
	free(pool);
	
	printf(BOLDBLUE "Completed TestCreateDestroy\n" DEF);
}



static void Test1(void)
{
	static void *voiders[40];
	size_t i = 0;
	size_t biggest_chunk = 0;
	int for_test = 0;
	size_t num_allocated_1 = 0;
	size_t num_allocated_2 = 0;
	
	size_t pool_size = 800;
	void *pool = malloc(pool_size);
	vsa_t *vsa = VSAInit(pool, pool_size);
	
	for (i = 0; i < 20; ++i)
	{
		size_t size_current = 7*(i+1);
		biggest_chunk = VSAMaxFreeChunk(vsa);
		voiders[i] = VSAAlloc(vsa, size_current);
		
		for_test = ((NULL == voiders[i]) && (size_current >= biggest_chunk)) ||
		           ((NULL != voiders[i]) && (size_current < biggest_chunk));
		TEST("Chunk Available", for_test, 1);
		
		if (NULL != voiders[i])
		{
			++num_allocated_1;
		}
	}
	
	for (i = 0; i < num_allocated_1; ++i)
	{
		*((size_t *) voiders[i]) = 15*i;
	}
	
	for (i = 0; i < num_allocated_1; ++i)
	{
		TEST("Value Stored", *((size_t *) voiders[i]), 15*i);
	}
	
	
	
	VSAFree(voiders[2]); voiders[2] = NULL;
    voiders[20] = VSAAlloc(vsa, 7*(2+1));
    TEST("Should be free", NULL == voiders[20], 0);
    
    VSAFree(voiders[5]); voiders[5] = NULL;
    voiders[21] = VSAAlloc(vsa, 7*(5+1));
    TEST("Should be free", NULL == voiders[21], 0);
	
	for (i = 0; i < 22; ++i)
	{
		if (NULL != voiders[i])
		{
			VSAFree(voiders[i]);
		}
	}
	
	
	
	for (i = 0; i < 20; ++i)
	{
		size_t size_current = 7*(i+1);
		biggest_chunk = VSAMaxFreeChunk(vsa);
		voiders[i] = VSAAlloc(vsa, size_current);
		for_test = ((NULL == voiders[i]) && (size_current >= biggest_chunk)) ||
		           ((NULL != voiders[i]) && (size_current < biggest_chunk));
		TEST("Chunk Available", for_test, 1);
		
		if (NULL != voiders[i])
		{
			++num_allocated_2;
		}
		else
		{
			break;
		}
	}
	
	
	
	free(pool);
	
	printf(BOLDBLUE "Completed Test1\n" DEF);
}



static void Test2(void)
{
	static void *voiders[40];
	size_t pool_size = 800;
	size_t biggest_chunk = 0;
	size_t size_current = 0;
	size_t total_size = 0;
	size_t header_size = 0;
	void *pool = malloc(pool_size);
	vsa_t *vsa = VSAInit(pool, pool_size);
	
	/* this is all in order to get the header size,
	   despite the fact that it is implementation dependent */
	biggest_chunk = VSAMaxFreeChunk(vsa);
	size_current = 8;
	voiders[0] = VSAAlloc(vsa, size_current);
	header_size = biggest_chunk - size_current - VSAMaxFreeChunk(vsa);
	
	
	
	size_current = 16;
	voiders[1] = VSAAlloc(vsa, size_current);
	voiders[2] = VSAAlloc(vsa, size_current);
	voiders[3] = VSAAlloc(vsa, size_current);
	total_size = 3 * (header_size + size_current) - header_size;
	
	voiders[4] = VSAAlloc(vsa, VSAMaxFreeChunk(vsa));
	
	TEST("Allocation should succeed", NULL != voiders[4], 1);
	TEST("No Free Space", VSAMaxFreeChunk(vsa), 0);
	
	VSAFree(voiders[1]);
	VSAFree(voiders[2]);
	VSAFree(voiders[3]);
	
	TEST("Exact Free Space", VSAMaxFreeChunk(vsa), total_size);
	voiders[5] = VSAAlloc(vsa, total_size);
	TEST("Allocation should succeed", NULL != voiders[5], 1);
	
	VSAFree(voiders[5]);
	
	
	
	size_current = 16;
	voiders[1] = VSAAlloc(vsa, size_current);
	voiders[2] = VSAAlloc(vsa, size_current);
	voiders[3] = VSAAlloc(vsa, size_current);
	total_size = 3 * (header_size + size_current) - header_size;
	
	VSAFree(voiders[1]);
	VSAFree(voiders[2]);
	VSAFree(voiders[3]);
	
	voiders[5] = VSAAlloc(vsa, total_size);
	TEST("Allocation should succeed", NULL != voiders[5], 1);
	
	
	
	free(pool);
	
	printf(BOLDBLUE "Completed Test2\n" DEF);
}



static void TestMain(void)
{
	TestCreateDestroy();
	
	Test1();
	
	Test2();
	
	PASS;
}



int main(void)
{
	TestMain();
	
	return 0;
}



