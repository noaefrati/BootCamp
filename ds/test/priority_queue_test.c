/*************************************************************************** 
 * Description: Testing for doubly linked list functions
 * Author: Oriel Nofekh
 * Reviewer: 
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>    /* printf */
#include <stdlib.h>   /* malloc, free */
#include <string.h>   /* strlen */
#include <ctype.h>    /* toupper */
#include <time.h>     /* time_t, time */
#include <assert.h>   /* assert */
#include "priority_queue.h"    /* pq_t and declarations of all its functions */
/*#include "tests.h"*/              /* tools for easy and nicely styled testing */





/******************************************************************************/
/***                        Color Defines   		                        ***/
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



/*****************************************************************************/

/* simple compare functions */

static int CompareChar(const void *one, const void *other)
{
	char *char1 = (char *) one;
	char *char2 = (char *) other;
	
	if (*char1 < *char2)
	{
		return -1;
	}
	else if (*char1 > *char2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



/*****************************************************************************/

/* Used as "is_match" for the FindIf function */
static int IsSameChar(const void *one, const void *other)
{
	if ((*(char *) one) == (*(char *) other))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



/*****************************************************************************/


static void TestCreateDestroy(void)
{
	pq_t *pq = PQCreate(&CompareChar);
	
	PQDestroy(pq);
}



static int Test1(void)
{
	/* 
	tests functions: 
	    Enqueue, Dequeue, Peek
	    IsEmpty, Size,
	    Clear, Erase
	*/
	
	char char_arr[] = {'0','1','2','3','4','5','6','7','8','9'};
	char *value = NULL;
	char *to_erase = NULL;
	char c = '\0';
	int status = 0;
	
	pq_t *pq = PQCreate(&CompareChar);
	
	TEST("IsEmpty", PQIsEmpty(pq), 1);
	TEST("Size", PQSize(pq), 0);
	
	status = PQEnqueue(pq, char_arr + 5);
	TEST("Enqueue success or failure", status, 0);
	TEST("IsEmpty", PQIsEmpty(pq), 0);
	TEST("Size", PQSize(pq), 1);
	
	status = PQEnqueue(pq, char_arr + 3);
	TEST("Enqueue success or failure", status, 0);
	TEST("IsEmpty", PQIsEmpty(pq), 0);
	TEST("Size", PQSize(pq), 2);
	
	status = PQEnqueue(pq, char_arr + 2);
	TEST("Enqueue success or failure", status, 0);
	TEST("IsEmpty", PQIsEmpty(pq), 0);
	TEST("Size", PQSize(pq), 3);
	
	status = PQEnqueue(pq, char_arr + 4);
	TEST("Enqueue success or failure", status, 0);
	TEST("IsEmpty", PQIsEmpty(pq), 0);
	TEST("Size", PQSize(pq), 4);
	
	value = PQPeek(pq);
	TESTC("Peek", *value, char_arr[2]); 
	TEST("Size", PQSize(pq), 4);
	
	value = PQDequeue(pq);
	TESTC("Dequeue", *value, char_arr[2]); 
	TEST("Size", PQSize(pq), 3);
	
	value = PQPeek(pq);
	TESTC("Peek", *value, char_arr[3]);
	TEST("Size", PQSize(pq), 3);
	
	value = PQDequeue(pq);
	TESTC("Dequeue", *value, char_arr[3]);
	TEST("Size", PQSize(pq), 2);
	
	/********** clear the queue, then we start over **********/
	
	PQClear(pq);
	TEST("IsEmpty", PQIsEmpty(pq), 1);
	TEST("Size", PQSize(pq), 0);
	
	status = PQEnqueue(pq, char_arr + 5);
	TEST("Enqueue success or failure", status, 0);
	
	status = PQEnqueue(pq, char_arr + 4);
	TEST("Enqueue success or failure", status, 0);
	
	status = PQEnqueue(pq, char_arr + 4);
	TEST("Enqueue success or failure", status, 0);
	
	status = PQEnqueue(pq, char_arr + 2);
	TEST("Enqueue success or failure", status, 0);
	
	status = PQEnqueue(pq, char_arr + 4);
	TEST("Enqueue success or failure", status, 0);
	
	status = PQEnqueue(pq, char_arr + 3);
	TEST("Enqueue success or failure", status, 0);
	TEST("Size", PQSize(pq), 6);
	
	c = char_arr[3];
	to_erase = &c;
	value = PQErase(pq, &IsSameChar, to_erase);
	TESTC("PQErase", *value, *to_erase);
	TEST("Size", PQSize(pq), 5);
	
	c = char_arr[4];
	to_erase = &c;
	while (NULL != value)
	{
		value = PQErase(pq, &IsSameChar, to_erase);
	}
	TEST("Size", PQSize(pq), 2);
	
	PQDestroy(pq);
	
	return 0;
}



static void TestDurability(void)
{
	/* This test randomly adds and removes elements from the list,
	   and only checks two things while doing so:
	      (1) that the program doesn't crash
	      (2) that the size is correct
	   It stops when a big enough size is reached. */
	
	int status = 0;
	
	pq_t *que = NULL;
	
	size_t i = 0;
	const size_t NUM_ITERATIONS = 40;
	
	size_t num_actions = 0;
	
	size_t size = 0;
	const size_t MAX_SIZE = 100;
	
	char char_arr[] = {'a','b','c','d','e',
	                   'f','g','h','i','j',
	                   'k','l','m','n','o',
	                   'p','q','r','s','t'};
	size_t arr_len = sizeof(char_arr) / sizeof(char_arr[0]);
	
	/* for random generation */
	time_t t = time(NULL);
	srand((unsigned) time(&t));
	
	for (i = 0; i < NUM_ITERATIONS; ++i)
	{
		size = 0;
		
		que = PQCreate(&CompareChar);
		
		while (size < MAX_SIZE)
		{
			if ((0 == size) || (rand() % 7) <= 3)
			{
				status = PQEnqueue(que, char_arr + (rand() % arr_len));
				if (0 != status)
				{
					printf(RED "Enqueue Failed, at line %d, in iteration %lu, "
					       "when size of queue was %lu\n\n" DEF, __LINE__, i, size);
					PQDestroy(que); que = NULL;
					return;
				}
				++size;
			}
			else
			{
				PQDequeue(que);
				--size;
			}
			
			if (size != PQSize(que))
			{
				printf(RED "Size of queue is incorrect, at line %d, in iteration %lu, "
			       "when size of queue was %lu, but should have been %lu\n\n" DEF, __LINE__, i, PQSize(que), size);
				PQDestroy(que); que = NULL;
				return;
			}
			++num_actions;
		}
		
		PQDestroy(que); que = NULL;
		
	}
	printf(BOLDBLUE "Durability Test total number of actions (Enqueue and Dequeue) was: %lu\n\n" DEF, num_actions);
}



static void TestMain(void)
{
	int status = 0;
	
	TestCreateDestroy();
	
	status += Test1();
	
	TestDurability();
	
	PASS;
}



int main(void)
{
	TestMain();
	
	return 0;
}



