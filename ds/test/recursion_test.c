/*************************************************************************** 
 * Description: Testing of Implementation of Recursive Functions
 * Author: Oriel Nofekh
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>         /* printf */
#include <stdlib.h>        /* malloc, free */
#include <string.h>        /* strlen, strcmp, etc. */
#include <assert.h>        /* assert */
#include "recursion.h"     /* recursion API */

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

#define TESTI(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %d, Expected: %d\n" DEF, name, __LINE__, (int) (real), (int) (expected)); \
    } while (0)

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)




/****************************** List Handling ******************************/

static node_t *CreateList(int *arr, int len)
{
	node_t *node = NULL;
	node_t *next = NULL;
	int i = 0;
	
	for (i = len-1; i >=0; --i)
	{
		node = (node_t *) malloc(sizeof(node_t));
		node->data = arr + i;
		node->next = next;
		next = node;
	}
	
	return node;
}

static int IsListSameAsArray(node_t *node, int *arr, int len)
{
	int i = 0;
	for (i = 0; (NULL != node) && (i < len); node = node->next, ++i)
	{
		if (*(int *) node->data != arr[i])
		{
			return 0;
		}
	}
	
	if ((NULL == node) && (i == len))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static void FreeAllNodes(node_t *node)
{
	node_t *current_node = NULL;
	node_t *next_node = NULL;
	
	assert(node);
	
	next_node = node;
	
	while (NULL != next_node)
	{
		current_node = next_node;
		next_node = next_node->next;
		
		current_node->next = NULL;
		free(current_node);
	}
}

/****************************** Str Helpers ******************************/

static int OneZeroMinusOne(int num)
{
	return (num > 0) ? 1 : ((num < 0) ? -1 : 0);
}

/************************* Tests Functions *************************/

static void TestFibonacci(void)
{
	int iterative = 0;
	int recursive = 0;
	int element_index = 0;
	int expected = 0;
	
	element_index = 1;
	expected = 1;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 2;
	expected = 1;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 3;
	expected = 2;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 4;
	expected = 3;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 5;
	expected = 5;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 6;
	expected = 8;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 7;
	expected = 13;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 8;
	expected = 21;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 9;
	expected = 34;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 10;
	expected = 55;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 11;
	expected = 89;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 12;
	expected = 144;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 30;
	expected = 832040;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 35;
	expected = 9227465;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 40;
	expected = 102334155;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	element_index = 45;
	expected = 1134903170;
	iterative = FibonacciIter(element_index);
	recursive = FibonacciRec(element_index);
	TESTI("Iterative", iterative, expected);
	TESTI("Recursive", recursive, expected);
	
	printf(BOLDBLUE "Completed TestFibonacci\n" DEF);
}

static void TestFlipList(void)
{
	int arr1[] = {1,2,3,4,5,6,7};
	int arr2[] = {7,6,5,4,3,2,1};
	int len = (int) sizeof(arr1) / sizeof(arr1[0]);
	node_t *node = NULL;
	
	node = CreateList(arr1, len);
	TESTI("(Pre-Check)", IsListSameAsArray(node, arr1, len), 1);
	
	node = FlipList(node);
	TESTI("FlipList", IsListSameAsArray(node, arr2, len), 1);
	
	FreeAllNodes(node);
	
	node = CreateList(arr2, len);
	TESTI("(Pre-Check)", IsListSameAsArray(node, arr2, len), 1);
	
	node = FlipList(node);
	TESTI("FlipList", IsListSameAsArray(node, arr1, len), 1);
	
	FreeAllNodes(node);
	
	printf(BOLDBLUE "Completed TestFlipList\n" DEF);
}

static void TestStackSort(void)
{
	int arr1[] = {0,1,2,3,4,5,6,7};
	stack_t *stack = NULL;
	size_t element_size = 4;
	size_t capacity = 10;
	

	
	stack = StackCreate(element_size, capacity);
	
	StackPush(stack, arr1+2);
	StackPush(stack, arr1+0);
	StackPush(stack, arr1+7);
	StackPush(stack, arr1+5);
	StackPush(stack, arr1+4);
	StackPush(stack, arr1+3);
	StackPush(stack, arr1+1);
	StackPush(stack, arr1+6);
	
	StackSort(stack);
	
	TESTI("StackSort", *(int *) StackPeek(stack), 0);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 1);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 2);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 3);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 4);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 5);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 6);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 7);
	StackPop(stack);
	TESTI("StackSort", StackIsEmpty(stack), 1);
	
	StackDestroy(stack);
	
	
	
	stack = StackCreate(element_size, capacity);
	
	StackPush(stack, arr1+7);
	StackPush(stack, arr1+1);
	StackPush(stack, arr1+3);
	StackPush(stack, arr1+2);
	StackPush(stack, arr1+5);
	StackPush(stack, arr1+4);
	StackPush(stack, arr1+6);
	StackPush(stack, arr1+0);
	
	StackSort(stack);
	
	TESTI("StackSort", *(int *) StackPeek(stack), 0);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 1);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 2);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 3);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 4);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 5);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 6);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 7);
	StackPop(stack);
	TESTI("StackSort", StackIsEmpty(stack), 1);
	
	StackDestroy(stack);
	
	
	
	stack = StackCreate(element_size, capacity);
	
	StackPush(stack, arr1+6);
	StackPush(stack, arr1+5);
	StackPush(stack, arr1+3);
	StackPush(stack, arr1+4);
	StackPush(stack, arr1+7);
	StackPush(stack, arr1+0);
	StackPush(stack, arr1+1);
	StackPush(stack, arr1+2);
	
	StackSort(stack);
	
	TESTI("StackSort", *(int *) StackPeek(stack), 0);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 1);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 2);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 3);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 4);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 5);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 6);
	StackPop(stack);
	TESTI("StackSort", *(int *) StackPeek(stack), 7);
	StackPop(stack);
	TESTI("StackSort", StackIsEmpty(stack), 1);
	
	StackDestroy(stack);
	
	printf(BOLDBLUE "Completed TestStackSort\n" DEF);
}

static void TestStrFuncs(void)
{
	char c1[] = "hello";
	char c2[] = "world! hey";
	char c3[] = " ab ";
	char c4[] = "";
	
	char c5[] = "hello";
	char c6[] = "hello ";
	char c7[] = "hell";
	char c8[] = "hellio";
	
	char c100[100];
	char *cptr = c100;
	
	char c20[] = "hello \0\0\0\0\0\0\0\0\0\0\0";
	char c30[] = "world!\0\0\0\0\0\0\0\0\0\0\0";
	char c40[] = "hello world!";
	
	char c50[] = " That is \0\0\0\0\0\0\0\0\0\0\0";
	char c60[] = "Amazing. \0\0\0\0\0\0\0\0\0\0\0";
	char c70[] = " That is Amazing. ";
	
	char ch1[] = "abcdefg";
	char ch2[] = "def";
	char ch3[] = "abc";
	char ch4[] = "efgh";
	char ch5[] = "ab c";
	char ch6[] = "bcdefh";
	char ch7[] = "b";
	char ch8[] = "ef";
	char ch9[] = "g";
	
	TEST("StrLen", StrLen(c1), strlen(c1));
	TEST("StrLen", StrLen(c2), strlen(c2));
	TEST("StrLen", StrLen(c3), strlen(c3));
	TEST("StrLen", StrLen(c4), strlen(c4));
	
	TESTI("StrCmp", OneZeroMinusOne(StrCmp(c1, c2)), OneZeroMinusOne(strcmp(c1, c2)));
	TESTI("StrCmp", OneZeroMinusOne(StrCmp(c1, c5)), OneZeroMinusOne(strcmp(c1, c5)));
	TESTI("StrCmp", OneZeroMinusOne(StrCmp(c1, c6)), OneZeroMinusOne(strcmp(c1, c6)));
	TESTI("StrCmp", OneZeroMinusOne(StrCmp(c1, c7)), OneZeroMinusOne(strcmp(c1, c7)));
	TESTI("StrCmp", OneZeroMinusOne(StrCmp(c1, c8)), OneZeroMinusOne(strcmp(c1, c8)));
	
	StrCpy(cptr, c1);
	TESTI("StrCpy", StrCmp(cptr, c1), 0);
	StrCpy(cptr, c2);
	TESTI("StrCpy", StrCmp(cptr, c2), 0);
	cptr = StrCpy(cptr, c3);
	TESTI("StrCpy", StrCmp(cptr, c3), 0);
	cptr = StrCpy(cptr, c4);
	TESTI("StrCpy", StrCmp(cptr, c4), 0);
	
	StrCat(c20, c30);
	TESTI("StrCat", StrCmp(c20, c40), 0);
	cptr = StrCat(c50, c60);
	TESTI("StrCat", StrCmp(c50, c70), 0);
	TESTI("StrCat", StrCmp(cptr, c70), 0);
	
	printf("%p\n", StrStr(ch1, ch2));
	TEST("StrStr", StrStr(ch1, ch2), ch1 + 3);
	TEST("StrStr", StrStr(ch1, ch3), ch1 + 0);
	TEST("StrStr", StrStr(ch1, ch4), NULL);
	TEST("StrStr", StrStr(ch1, ch5), NULL);
	TEST("StrStr", StrStr(ch1, ch6), NULL);
	TEST("StrStr", StrStr(ch1, ch7), ch1 + 1);
	TEST("StrStr", StrStr(ch1, ch8), ch1 + 4);
	TEST("StrStr", StrStr(ch1, ch9), ch1 + 6);
	
	printf(BOLDBLUE "Completed TestStrFuncs\n" DEF);
}

/************************* main function *************************/

int main(void)
{
	TestFibonacci();
	
	TestFlipList();
	
	TestStackSort();
	
	TestStrFuncs();
	
	PASS;
	
	return 0;
}




















