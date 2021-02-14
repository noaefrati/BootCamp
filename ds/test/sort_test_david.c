/*************************************************************************** 
 * Description: Testing for doubly linked list functions
 * Author: David Horovitz
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>    /* printf */
#include <stdlib.h>   /* malloc, free */
#include <string.h>   /* strlen */
#include <ctype.h>    /* toupper */
#include <time.h>     /* time_t, time */
#include <assert.h>   /* assert */
#include "sort.h"    /* sorted_list_t, node_t and sortlist_iter_t 
                                  and declarations of all its functions */
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

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)


#define N 5000
#define K 2000
#define AMOUNT_SHOW 200
#define IN_LINE 15
#define N_BITS 4

/*****************************************************************************/
static void TCountSort(int *array, size_t size)
{
	CountingSort(array, size);
}

static void TRadixSort(int *array, size_t size)
{
	RadixSort(array, size, N_BITS);
}

static int cmpfunc (const void * a, const void * b)
{
   return (*(int*)a - *(int*)b);
}
/*
static void PrintArr(const int *arr, int size, int to_print)
{
	int i = 0;
	
	assert(arr);
	
	for (;i < size && i < to_print; ++i)
	{
		printf("%d ", arr[i]);
		if (0 == (i+1) % IN_LINE)
			{printf("\n");}
	}
	printf("\n");
}
*/
static void CopyArr(const int *src_arr, int *dest_arr, size_t size)
{
	size_t i;
	
	assert(src_arr);
	assert(dest_arr);
	
	for (i = 0; i < size; ++i)
	{
		dest_arr[i] = src_arr[i];
	}
}

static void CheckArray(const int *arr, size_t size)
{
	size_t i = 0;
	
	assert(arr);
	
	for (i = 0; i < size - 1 ; ++i)
	{
		TEST("ERROR",(arr[i] > arr[i + 1]), 0 );
	}
}

static void InitialAaray(int *arr, size_t size)
{
	size_t i = 0;
	srand((unsigned) time(0));
	
	for (; i < size; ++i)
	{
		arr[i] = rand() % K;
	}
}

static float TestSortArray(void sort_func(int *arr, size_t n)
											,int *arr, size_t n, char *name)
{
	clock_t start_t, end_t;
	
	assert(sort_func);
	assert(arr);
	
	start_t = clock();	
	sort_func(arr, n);
	end_t = clock();
	
	/*PrintArr(arr, n, AMOUNT_SHOW);
	*/printf(BOLDBLUE "Time to %s: %f\n" DEF, 
								name, (double)(end_t - start_t)/CLOCKS_PER_SEC);
	CheckArray(arr, n);
	
	return (double)(end_t - start_t)/CLOCKS_PER_SEC;
}

static float TestTimeQsort(int *arr, size_t size)
{
	clock_t start_t, end_t;

	start_t = clock();	
	qsort(arr, size, sizeof(int), cmpfunc);
	end_t = clock();
	
	printf(BOLDBLUE "Time to qsort: %f\n" DEF, 
								 (double)(end_t - start_t)/CLOCKS_PER_SEC);
	
	return (double)(end_t - start_t)/CLOCKS_PER_SEC;
}
static void TestTimeBetweenSortAlgorithm(void sort_func1(int *arr, size_t n),
											 void sort_func2(int *arr, size_t n)
											 , size_t n,
											 char *func_name1, char *func_name2)
{
	float a, b;
	static int arr[N];
	static int arr_copy[N];

	assert(sort_func1);
	assert(sort_func2);
	
	InitialAaray(arr, n);
	CopyArr(arr, arr_copy, n);
		
	a = TestSortArray(sort_func1, arr, n, func_name1);
	if (!strcmp(func_name2, "qsort"))
	{
		b = TestTimeQsort(arr , n);	
	}
	else
	{	
		b = TestSortArray(sort_func2, arr_copy, n, func_name2);
	}
	
	printf(BOLDBLUE "Time differences bitween %s to %s: %f\n\n" DEF,
											func_name1, func_name2,  a - b);
	
}


int main(void)
{
	static int arr1[N];
	InitialAaray(arr1, N);

	TestTimeBetweenSortAlgorithm(InsertionSort, InsertionSort,
											N, "InsertionSort", "qsort");	
	
	TestTimeBetweenSortAlgorithm(BubbleSort, SelectionSort, 						
											N, "BubbleSort" ,"SelectionSort");	
	
	TestTimeBetweenSortAlgorithm(InsertionSort, SelectionSort, 
											N, "InsertionSort" ,"SelectionSort");
	
	TestTimeBetweenSortAlgorithm(InsertionSort, BubbleSort,
											N, "InsertionSort" ,"BubbleSort");
	
	TestTimeBetweenSortAlgorithm(InsertionSort, TCountSort,
											N, "InsertionSort" ,"CountSort");

	TestSortArray(InsertionSort, arr1, N , "InsertionSort");
	
	
	TestTimeBetweenSortAlgorithm(TCountSort, TCountSort,
											N, "CountSort" ,"qsort");
	TestTimeBetweenSortAlgorithm(TCountSort, TRadixSort,
											N, "CountSort" ,"TRadixSort");
	
	PASS;

	return 0;
}
