/*************************************************************************** 
 * Description: Testing of Implementations of Sorting Algorithms
 * Author: Oriel Nofekh
 *
 * Infinity Labs OL97
 ***************************************************************************/


#include <stdio.h>      /* printf */
#include <stdlib.h>     /* malloc, free, qsort */
#include <time.h>       /* clock_t, clock, time */
#include <assert.h>     /* assert */
#include <string.h>     /* strlen */
#include "sort.h"       /* various sort functions / algorithms */



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





/*************************** Compare Functions ****************************/

static int CompareInts(const void *one, const void *other)
{
	return (*(int *) one) - (*(int *) other);
}

/************************* Functions Declarations *************************/

static int TestSortAlgorithm(int *arr, size_t len, 
                             void (*sort_func)(int *arr, size_t len), 
                             char *algo_name);
static int *GetRandomArray(size_t size, int min_value, int max_value);
static int *GetCopyArray(int *arr, size_t len);
static int IsSorted(int *arr, size_t len);
static int IsSame(int *arr1, int *arr2, size_t len);
static int CompareIntegers(const void *int1, const void *int2);
static void QSortWrapper(int *arr, size_t len);
static void CountingSortWrapper(int *arr, size_t len);
static void RadixSortWrapper1Bits(int *arr, size_t len);
static void RadixSortWrapper2Bits(int *arr, size_t len);
static void RadixSortWrapper4Bits(int *arr, size_t len);
static void RadixSortWrapper8Bits(int *arr, size_t len);
static void RadixSortWrapper16Bits(int *arr, size_t len);
static void MergeSortWrapper(int *arr, size_t len);
static void QuickSortWrapper(int *arr, size_t len);
static void PrintArray(int *arr, size_t len);   /* for debugging */

/************************* main function *************************/

int main(void)
{
	int to_find = 0;
	size_t to_find_index = 0;
	int *found_index = NULL;
	
	int result = 0;
	size_t size = 2000;
	int min_value = 100000;
	int max_value = 200000;
	int *arr = GetRandomArray(size, min_value, max_value);
	int *arr1 = GetCopyArray(arr, size);
	int *arr2 = GetCopyArray(arr, size);
	int *arr3 = GetCopyArray(arr, size);
	int *arr4 = GetCopyArray(arr, size);
	int *arr5 = GetCopyArray(arr, size);
	int *arr6 = GetCopyArray(arr, size);
	int *arr7 = GetCopyArray(arr, size);
	int *arr8 = GetCopyArray(arr, size);
	int *arr9 = GetCopyArray(arr, size);
	int *arr10 = GetCopyArray(arr, size);
	int *arr11 = GetCopyArray(arr, size);
	int *arr12 = GetCopyArray(arr, size);
	
	/* O(n^2) Comparison Algorithms */
	result = TestSortAlgorithm(arr1, size, BubbleSort, "Bubble");
	TEST("Bubble", result, 1);
	/*result = TestSortAlgorithm(arr2, size, InsertionSort, "Insertion");
	TEST("Insertion", result, 1);*/
	result = TestSortAlgorithm(arr3, size, SelectionSort, "Selection");
	TEST("Selection", result, 1);
	
	/* Standard Library QSort */
	result = TestSortAlgorithm(arr4, size, QSortWrapper, "QSort");
	TEST("QSort", result, 1);
	
	/* Non-Comparison Algorithms */
	/* ONLY NON-NEGATIVE NUMBERS (for RadixSort) */
	result = TestSortAlgorithm(arr5, size, CountingSortWrapper, "Counting");
	TEST("Counting", result, 1);
	result = TestSortAlgorithm(arr6, size, RadixSortWrapper1Bits, "Radix 1 bits");
	TEST("Radix 1 bits", result, 1);
	result = TestSortAlgorithm(arr7, size, RadixSortWrapper2Bits, "Radix 2 bits");
	TEST("Radix 2 bits", result, 1);
	result = TestSortAlgorithm(arr8, size, RadixSortWrapper4Bits, "Radix 4 bits");
	TEST("Radix 4 bits", result, 1);
	result = TestSortAlgorithm(arr9, size, RadixSortWrapper8Bits, "Radix 8 bits");
	TEST("Radix 8 bits", result, 1);
	result = TestSortAlgorithm(arr10, size, RadixSortWrapper16Bits, "Radix 16 bits");
	TEST("Radix 16 bits", result, 1);
	
	/* O(n log(n)) Comparison Algorithms */
	result = TestSortAlgorithm(arr11, size, MergeSortWrapper, "Merge");
	TEST("Merge", result, 1);
	result = TestSortAlgorithm(arr12, size, QuickSortWrapper, "Quick");
	TEST("Quick", result, 1);
	
	result = IsSame(arr1, arr4, size);
	TEST("Bubble", result, 1);
	/*result = IsSame(arr2, arr4, size);
	TEST("Insertion", result, 1);
	result = IsSame(arr3, arr4, size);*/
	TEST("Selection", result, 1);
	result = IsSame(arr5, arr4, size);
	TEST("Counting", result, 1);
	result = IsSame(arr6, arr4, size);
	TEST("Radix 1 bits", result, 1);
	result = IsSame(arr7, arr4, size);
	TEST("Radix 2 bits", result, 1);
	result = IsSame(arr8, arr4, size);
	TEST("Radix 4 bits", result, 1);
	result = IsSame(arr9, arr4, size);
	TEST("Radix 8 bits", result, 1);
	result = IsSame(arr10, arr4, size);
	TEST("Radix 16 bits", result, 1);
	result = IsSame(arr11, arr4, size);
	TEST("Merge", result, 1);
	result = IsSame(arr12, arr4, size);
	TEST("Quick", result, 1);
	
	if (0)
	{
		PrintArray(arr, size);    /* original, non-sorted */
		PrintArray(arr4, size);   /* qsort */
		PrintArray(arr12, size);
	}
	
	to_find_index = size/2;
	to_find = arr4[to_find_index];
	found_index = IterBinarySearch(arr4, size, to_find);
	TEST("IterBinarySearch", *found_index, to_find);
	found_index = RecBinarySearch(arr4, size, to_find);
	TEST("RecBinarySearch", *found_index, to_find);
	
	to_find_index = size/5;
	to_find = arr4[to_find_index];
	found_index = IterBinarySearch(arr4, size, to_find);
	TEST("IterBinarySearch", *found_index, to_find);
	found_index = RecBinarySearch(arr4, size, to_find);
	TEST("RecBinarySearch", *found_index, to_find);
	
	to_find_index = size*6/7;
	to_find = arr4[to_find_index];
	found_index = IterBinarySearch(arr4, size, to_find);
	TEST("IterBinarySearch", *found_index, to_find);
	found_index = RecBinarySearch(arr4, size, to_find);
	TEST("RecBinarySearch", *found_index, to_find);
	
	free(arr);
	free(arr1);
	free(arr2);
	free(arr3);
	free(arr4);
	free(arr5);
	free(arr6);
	free(arr7);
	free(arr8);
	free(arr9);
	free(arr10);
	free(arr11);
	free(arr12);
	
	PASS;
	
	return 0;
}

/******************** Functions Implementations - For Tests ********************/

static int TestSortAlgorithm(int *arr, size_t len, 
                             void (*sort_func)(int *arr, size_t len), 
                             char *algo_name)
{
	clock_t start = clock();
	clock_t end = clock();
	double cpu_time_used = 0.0;
	int result = 0;
	static char blanks[] = "               ";
	blanks[sizeof(blanks) - strlen(algo_name)] = '\0';
	
	start = clock();   /* start measuring time */
	
	sort_func(arr, len);     /* sort the array with the given algorithm */
	
	end = clock();     /* end time measurement */
	
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	printf("%s %s running time   =   %10.6f seconds\n", algo_name, blanks, cpu_time_used);
	
	blanks[sizeof(blanks) - strlen(algo_name)] = ' ';
	
	result = IsSorted(arr, len);   /* check if it is now sorted */
	
	return result;
} 

static int *GetRandomArray(size_t size, int min_value, int max_value)
{
	int *arr = NULL;
	size_t i = 0;
	
	assert(min_value <= max_value);
	
	srand((unsigned) time(NULL));   /* set seed for randomization */
	
	arr = (int *) malloc(size * sizeof(int));
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = (rand() % (max_value - min_value + 1)) + min_value;
	}
	
	return arr;
}

static int *GetCopyArray(int *arr, size_t len)
{
	int *copy_arr = NULL;
	size_t i = 0;
	
	assert(arr);
	
	copy_arr = (int *) malloc(len * sizeof(int));
	
	for (i = 0; i < len; ++i)
	{
		copy_arr[i] = arr[i];
	}
	
	return copy_arr;
}

static int IsSorted(int *arr, size_t len)
{
	int current = 0;
	size_t i = 0;
	
	assert(arr);
	
	current = arr[0];
	for (i = 1; i < len; ++i)
	{
		if (current > arr[i])
		{
			return 0;
		}
		current = arr[i];
	}
	return 1;
}

static int IsSame(int *arr1, int *arr2, size_t len)
{
	size_t i = 0;
	
	assert(arr1);
	assert(arr2);
	
	for (i = 1; i < len; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			return 0;
		}
	}
	
	return 1;
}

/*
Format of qsort:
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));
*/

static int CompareIntegers(const void *int1, const void *int2)
{
	return (*(int *) int1) - (*(int *) int2);
}

static void QSortWrapper(int *arr, size_t len)
{
	assert(arr);
	
	qsort(arr, len, sizeof(int), CompareIntegers);
}

static void PrintArray(int *arr, size_t len)
{
	size_t i = 0;
	for (i = 0; i < len; ++i)
	{
		printf("%d  ", arr[i]);
	}
	printf("\n");
}

/****************************** Wrappers ******************************/

static void CountingSortWrapper(int *arr, size_t len)
{
	int status = CountingSort(arr, len);
	if (0 != status)
	{
		printf(RED "CountingSort Failed Misserably\n" DEF);
	}
}

static void RadixSortWrapper1Bits(int *arr, size_t len)
{
	size_t nbits = 1;
	int status = RadixSort(arr, len, nbits);
	if (0 != status)
	{
		printf(RED "RadixSort with nbits=%lu Failed Misserably\n" DEF, nbits);
	}
}

static void RadixSortWrapper2Bits(int *arr, size_t len)
{
	size_t nbits = 2;
	int status = RadixSort(arr, len, nbits);
	if (0 != status)
	{
		printf(RED "RadixSort with nbits=%lu Failed Misserably\n" DEF, nbits);
	}
}

static void RadixSortWrapper4Bits(int *arr, size_t len)
{
	size_t nbits = 4;
	int status = RadixSort(arr, len, nbits);
	if (0 != status)
	{
		printf(RED "RadixSort with nbits=%lu Failed Misserably\n" DEF, nbits);
	}
}

static void RadixSortWrapper8Bits(int *arr, size_t len)
{
	size_t nbits = 8;
	int status = RadixSort(arr, len, nbits);
	if (0 != status)
	{
		printf(RED "RadixSort with nbits=%lu Failed Misserably\n" DEF, nbits);
	}
}

static void RadixSortWrapper16Bits(int *arr, size_t len)
{
	size_t nbits = 16;
	int status = RadixSort(arr, len, nbits);
	if (0 != status)
	{
		printf(RED "RadixSort with nbits=%lu Failed Misserably\n" DEF, nbits);
	}
}

static void MergeSortWrapper(int *arr, size_t len)
{
	int status = MergeSort(arr, len);
	if (0 != status)
	{
		printf(RED "MergeSort Failed Misserably\n" DEF);
	}
}

static void QuickSortWrapper(int *arr, size_t len)
{
	Qsort(arr, len, sizeof(int), &CompareInts);
}















