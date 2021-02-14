/*************************************************************************** 
 * Description: Testing of Implementation of AVL
 * Author: Oriel Nofekh
 *
 * Infinity Labs OL97
 ***************************************************************************/


#include <stdio.h>     /* printf */
#include <assert.h>    /* assert */
#include <stdlib.h>    /* rand, srand */
#include <time.h>      /* time */
#include "heap.h"      /* Min Heap API */


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




/************************* Helper Functions *************************/

static int CompareInts(const void *one, const void *two)
{
	assert(one);
	assert(two);
	return (*(int *) one) - (*(int *) two);
}

static int IsMatch(const void *data, const void *against)
{
	assert(data);
	assert(against);
	
	return (*(int*) data == *(int*) against);
}

static int IsAlmostMatch(const void *data, const void *against)
{
	assert(data);
	assert(against);
	
	return ((*(int*) data - *(int*) against <= 2) &&  
	        (*(int*) against - *(int*) data <= 2));
}

/************************* Tests Functions *************************/

static void TestCreateDestroy(void)
{
	heap_t *heap = HeapCreate(&CompareInts);
	
	HeapDestroy(heap);
	
	printf(BOLDBLUE "Completed TestCreateDestroy\n" DEF);
}

static void Test1(void)
{
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
	
	heap_t *heap = HeapCreate(&CompareInts);
	
	/*TEST("IsEmpty", HeapIsEmpty(heap), 1);
	TEST("Size", HeapSize(heap), 0);
	TEST("Peek", HeapPeek(heap), NULL);
	
	HeapPush(heap, arr + 8);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 1);
	TEST("Peek", (int *) HeapPeek(heap), arr + 8);
	
	HeapPush(heap, arr + 6);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 2);
	TEST("Peek", (int *) HeapPeek(heap), arr + 6);
	
	HeapPop(heap);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 1);
	TEST("Peek", (int *) HeapPeek(heap), arr + 8);
	
	HeapPop(heap);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 1);
	TEST("Size", HeapSize(heap), 0);
	TEST("Peek", HeapPeek(heap), NULL);
	*/
	HeapPush(heap, arr + 13);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 1);
	TEST("Peek", (int *) HeapPeek(heap), arr + 13);
	
	HeapPush(heap, arr + 18);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 2);
	TEST("Peek", (int *) HeapPeek(heap), arr + 13);
	
	HeapPush(heap, arr + 8);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 3);
	TEST("Peek", (int *) HeapPeek(heap), arr + 8);
	
	HeapPush(heap, arr + 5);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 4);
	TEST("Peek", (int *) HeapPeek(heap), arr + 5);
	
	HeapPush(heap, arr + 12);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 5);
	TEST("Peek", (int *) HeapPeek(heap), arr + 5);
	
	HeapPush(heap, arr + 21);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 6);
	TEST("Peek", (int *) HeapPeek(heap), arr + 5);
	
	HeapPush(heap, arr + 18);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 7);
	TEST("Peek", (int *) HeapPeek(heap), arr + 5);
	
	HeapPush(heap, arr + 2);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 8);
	TEST("Peek", (int *) HeapPeek(heap), arr + 2);
	
	HeapPop(heap);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 7);
	TEST("Peek", (int *) HeapPeek(heap), arr + 5);
	
	HeapPop(heap);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 6);
	TEST("Peek", (int *) HeapPeek(heap), arr + 8);
	
	HeapPop(heap);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 5);
	TEST("Peek", *(int *) HeapPeek(heap), 12);
	
	HeapPop(heap);
	
	TEST("IsEmpty", HeapIsEmpty(heap), 0);
	TEST("Size", HeapSize(heap), 4);
	TEST("Peek", *(int *) HeapPeek(heap), 13);
	
	HeapDestroy(heap);
	
	printf(BOLDBLUE "Completed Test1\n" DEF);
}

static void Test2(void)
{
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
	int to_remove = 0;
	int *removed = NULL;
	
	heap_t *heap = HeapCreate(&CompareInts);
	
	TEST("Peek", HeapPeek(heap), NULL);
	
	/* first part */
	
	HeapPush(heap, arr + 8);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 8);
	TEST("Peek Value", *(int *) HeapPeek(heap), 8);
	
	HeapPush(heap, arr + 6);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 6);
	TEST("Peek Value", *(int *) HeapPeek(heap), 6);
	
	HeapPush(heap, arr + 12);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 6);
	TEST("Peek Value", *(int *) HeapPeek(heap), 6);
	
	HeapPush(heap, arr + 4);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 4);
	TEST("Peek Value", *(int *) HeapPeek(heap), 4);
	
	HeapPush(heap, arr + 5);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 4);
	TEST("Peek Value", *(int *) HeapPeek(heap), 4);
	TEST("Size", HeapSize(heap), 5);
	
	to_remove = 7;
	removed = (int *) HeapRemove(heap, &IsMatch, &to_remove);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 4);
	TEST("Peek Value", *(int *) HeapPeek(heap), 4);
	TEST("Remove", removed, NULL);
	TEST("Size", HeapSize(heap), 5);
	
	to_remove = 6;
	removed = (int *) HeapRemove(heap, &IsMatch, &to_remove);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 4);
	TEST("Peek Value", *(int *) HeapPeek(heap), 4);
	TEST("Remove", removed, arr + 6);
	TEST("Size", HeapSize(heap), 4);
	
	to_remove = 4;
	removed = (int *) HeapRemove(heap, &IsMatch, &to_remove);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 5);
	TEST("Peek Value", *(int *) HeapPeek(heap), 5);
	TEST("Remove", removed, arr + 4);
	TEST("Size", HeapSize(heap), 3);
	
	to_remove = 12;
	removed = (int *) HeapRemove(heap, &IsMatch, &to_remove);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 5);
	TEST("Peek Value", *(int *) HeapPeek(heap), 5);
	TEST("Remove", removed, arr + 12);
	TEST("Size", HeapSize(heap), 2);
	
	to_remove = 5;
	removed = (int *) HeapRemove(heap, &IsMatch, &to_remove);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 8);
	TEST("Peek Value", *(int *) HeapPeek(heap), 8);
	TEST("Remove", removed, arr + 5);
	TEST("Size", HeapSize(heap), 1);
	
	to_remove = 8;
	removed = (int *) HeapRemove(heap, &IsMatch, &to_remove);
	TEST("Peek Address", (int *) HeapPeek(heap), NULL);
	TEST("Remove", removed, arr + 8);
	TEST("Size", HeapSize(heap), 0);

	
	HeapPush(heap, arr + 16);
	HeapPush(heap, arr + 6);
	HeapPush(heap, arr + 12);
	HeapPush(heap, arr + 18);
	HeapPush(heap, arr + 7);
	HeapPush(heap, arr + 4);
	HeapPush(heap, arr + 3);
	HeapPush(heap, arr + 5);
	HeapPush(heap, arr + 9);
	HeapPush(heap, arr + 8);
	HeapPush(heap, arr + 11);
	HeapPush(heap, arr + 10);
	HeapPush(heap, arr + 13);
	HeapPush(heap, arr + 3);
	HeapPush(heap, arr + 14);
	HeapPush(heap, arr + 15);
	HeapPush(heap, arr + 4);
	
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 3);
	TEST("Peek Value", *(int *) HeapPeek(heap), 3);
	TEST("Size", HeapSize(heap), 17);
	
	to_remove = 4;
	removed = (int *) HeapRemove(heap, &IsMatch, &to_remove);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 3);
	TEST("Peek Value", *(int *) HeapPeek(heap), 3);
	TEST("Remove", removed, arr + 4);
	TEST("Size", HeapSize(heap), 16);
	
	to_remove = 3;
	removed = (int *) HeapRemove(heap, &IsMatch, &to_remove);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 3);
	TEST("Peek Value", *(int *) HeapPeek(heap), 3);
	TEST("Remove", removed, arr + 3);
	TEST("Size", HeapSize(heap), 15);
	
	to_remove = 3;
	removed = (int *) HeapRemove(heap, &IsMatch, &to_remove);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 4);
	TEST("Peek Value", *(int *) HeapPeek(heap), 4);
	TEST("Remove", removed, arr + 3);
	TEST("Size", HeapSize(heap), 14);
	
	HeapPop(heap); 
	HeapPop(heap); 
	HeapPop(heap);  
	
	to_remove = 9;
	removed = (int *) HeapRemove(heap, &IsMatch, &to_remove);
	TEST("Remove", removed, arr + 9);
	
	HeapPop(heap);  
	HeapPop(heap);  
	
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 10);
	TEST("Peek Value", *(int *) HeapPeek(heap), 10);
	
	HeapDestroy(heap);
	
	printf(BOLDBLUE "Completed Test2\n" DEF);
}

static void Test3(void)
{
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
	size_t len = sizeof(arr) / sizeof(arr[0]);
	size_t num_insertions = 1000;
	size_t i = 0;
	int prev_peeked = 0;
	int curr_peeked = 0;
	
	heap_t *heap = HeapCreate(&CompareInts);
	
	for (i = 0; i < num_insertions; ++i)
	{
		int rand_int = rand() % len;
		HeapPush(heap, arr + rand_int);
	}
	
	prev_peeked = *(int *) HeapPeek(heap);
	HeapPop(heap);
	for (i = 1; i < num_insertions; ++i)
	{
		curr_peeked = *(int *) HeapPeek(heap);
		TEST("curr_peeked >= prev_peeked", curr_peeked >= prev_peeked, 1);
		curr_peeked = prev_peeked;
		HeapPop(heap);
	}
	
	HeapDestroy(heap);
	
	printf(BOLDBLUE "Completed Test3\n" DEF);
}

static void Test4(void)
{
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
	int to_remove = 0;
	int *removed = NULL;
	
	heap_t *heap = HeapCreate(&CompareInts);
	
	HeapPush(heap, arr + 1);
	
	HeapPush(heap, arr + 7);
	HeapPush(heap, arr + 2);
	
	HeapPush(heap, arr + 15);
	HeapPush(heap, arr + 16);
	HeapPush(heap, arr + 8);
	HeapPush(heap, arr + 3);
	
	HeapPush(heap, arr + 17);
	HeapPush(heap, arr + 18);
	HeapPush(heap, arr + 19);
	HeapPush(heap, arr + 20);
	HeapPush(heap, arr + 9);
	HeapPush(heap, arr + 10);
	HeapPush(heap, arr + 5);
	HeapPush(heap, arr + 4);
	
	TEST("Size", HeapSize(heap), 15);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 1);
	TEST("Peek Value", *(int *) HeapPeek(heap), 1);
	
	to_remove = 17;
	removed = (int *) HeapRemove(heap, &IsMatch, &to_remove);
	TEST("Remove", removed, arr + 17);
	
	TEST("Size", HeapSize(heap), 14);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 1);
	TEST("Peek Value", *(int *) HeapPeek(heap), 1);
	
	HeapPop(heap);
	TEST("Size", HeapSize(heap), 13);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 2);
	TEST("Peek Value", *(int *) HeapPeek(heap), 2);
	
	HeapPop(heap);
	TEST("Size", HeapSize(heap), 12);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 3);
	TEST("Peek Value", *(int *) HeapPeek(heap), 3);
	
	HeapPop(heap);
	TEST("Size", HeapSize(heap), 11);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 4);
	TEST("Peek Value", *(int *) HeapPeek(heap), 4);
	
	HeapPop(heap);
	TEST("Size", HeapSize(heap), 10);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 5);
	TEST("Peek Value", *(int *) HeapPeek(heap), 5);
	
	HeapPop(heap);
	TEST("Size", HeapSize(heap), 9);
	TEST("Peek Address", (int *) HeapPeek(heap), arr + 7);
	TEST("Peek Value", *(int *) HeapPeek(heap), 7);
	
	HeapDestroy(heap);
	
	printf(BOLDBLUE "Completed Test4\n" DEF);
}

/************************* main function *************************/

int main(void)
{
	srand(time(NULL));
	
	/* just create and destroy */
	TestCreateDestroy();
	
	/* push and pop, and check size and peek */
	Test1();
	 Test2();
	Test3();
	Test4();
	
	
	PASS;
	
	return 0;
}




















