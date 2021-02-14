/******************************************************************************* 
 * Description: Implemention of Bubble, Insertion and Selection sort           *
 * Author: Noa Efrati                                                          *
 * Reviewer: Yuval Krytzer                                                     *
 * Date: 06.01.2021                                                            *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/

#include <stdlib.h>      /* malloc, free                                      */
#include <assert.h>      /* assert                                            */
#include "sort.h"        /* sort api                                          */

#define SIZEOF_INT sizeof(int)
#define FREE(var) free(var); var = NULL;
#define BITS_IN_BYTE 8

/**************************** Private Functions *******************************/
/******************************************************************************/					 
static void CountingImpl(int *input,
					   	 int *output,
					     size_t size,
					 	 int *histogram,
					 	 size_t range,
					     int mask,
					     int shift,
					     int min);
/******************************************************************************/
static int FindMax(int *arr, size_t size);
/******************************************************************************/
static int FindMin(int *arr, size_t size);					   
/******************************************************************************/
static void SwapContent(char *one, char *other, size_t size);

static int MergeSortImpl(int *arr, size_t left, size_t right);
static int Merge(int *arr, size_t left, size_t middle, size_t right);


static void QSortRec(char *base,
					size_t start,
					size_t end,
					size_t size, 
                    int (*compar)(const void *, const void *));
                     
static size_t Partition(char *base,
						size_t start,
						size_t end, 
						size_t size, 
						int (*compar)(const void *, const void *));
						
int *RecBinarySearchImpl(int *array,
						 size_t start,
						 size_t end,
						 int num_to_find);

/******************************************************************************/

void BubbleSort(int *arr, size_t size)
{
	size_t swapped = 0, i = 0, j = 0;
		
	while (swapped == 0)
	{
		swapped = 1;
		
		for (j = 0; j < (size - i - 1); ++j)
		{
			if (arr[j] > arr[j + 1])
			{			
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				
				swapped = 0;
			}
		}	
		++i;
	}
}

void InsertionSort(int *arr, size_t size)
{
	size_t i = 1;
	int current = arr[i];
	long j = 0;
	
	while (i < size)
	{
		current = arr[i];
		j = i - 1;
		
		while (j >= 0 && arr[j] > current)
		{
			arr[j + 1] = arr[j];
			--j;
		}
		
		arr[j + 1] = current;
		++i;
	}
}

void SelectionSort(int *arr, size_t size)
{
	size_t i = 0, j = 0, min_index = 0;
	
	while (i < size - 1)
	{
		j = i;
		min_index = j;
		
		for (; j < size; ++j)
		{
			if (arr[min_index] > arr[j])
			{
				min_index = j;
			}
			
		}
		if (i != min_index)
		{
			int temp = arr[i];
			arr[i] = arr[min_index];
			arr[min_index] = temp;
		}
		++i;  
	}
}

int CountingSort(int *arr, size_t size)
{
	size_t range = 0;
	int min = 0;
	int *histogram = NULL;
	int ret_val = 1;
	
	assert(NULL != arr);
	
	min = FindMin(arr, size);
	range = FindMax(arr, size) - min + 1;
	histogram = (int *) calloc(range, sizeof(int));
	
	if (NULL != histogram)
	{
		int *sort_arr = (int *) calloc(size, sizeof(int));
		
		if (NULL == sort_arr)
		{
			FREE(histogram);
		}
		else
		{
			CountingImpl(arr,
						 sort_arr,
					     size,
						 histogram,
						 range,
						 -1,
						 0,
					     min);	 
		 	FREE(sort_arr);
		 	FREE(histogram);
		 
		 	ret_val = 0;
		}
	}
		
	return ret_val;
}
	
int RadixSort(int *arr, size_t size, size_t n_bits)
{
	int mask = (1 << n_bits) - 1;
	int *histogram = NULL;
	int ret_val = 1;
	
	assert(NULL != arr);
	
	histogram = (int *) calloc(SIZEOF_INT, (mask + 1));
	
	if (NULL != histogram)
	{
		int *output = (int *) calloc(SIZEOF_INT, size);
		
		if (NULL == output)
		{
			FREE(histogram);
		}
		else
		{
			size_t i = 0;
			int shift = 0;
			
			for (; i < SIZEOF_INT * BITS_IN_BYTE / n_bits; ++i)
			{
				shift = i * n_bits;
				
				CountingImpl(arr,
							output,
							size,
						    histogram,
							(size_t)mask + 1,
							mask,
						    shift,
							0);	
			}
			FREE(histogram);
			FREE(output);
			
			ret_val = 0;
		}
	}
	
	return ret_val;
}
/********************* Recursive Sorts & Search *******************************/

/********************* Binary Search Iterative & Recursive ********************/
int *IterBinarySearch(int *array, size_t size, int num_to_find)
{
	size_t start = 0;
	size_t end = size;
	int *res = NULL;
	
	assert(array);
		
	while (start <= end && NULL == res)
	{
		size_t middle = (end + start) / 2;
		
		if (array[middle] == num_to_find)
		{
			res  = (array + middle);
		}
		else if (array[middle] < num_to_find)
		{
			start = middle + 1;
		}
		else
		{
			end = middle;
		}
	}
	
	return res;
}

int *RecBinarySearch(int *array, size_t size, int num_to_find)
{
	assert(array);
	
	return RecBinarySearchImpl(array, 0, size - 1, num_to_find);
}
int *RecBinarySearchImpl(int *array,
						 size_t start,
						 size_t end,
						 int num_to_find)
{	int middle = 0;

	if (start > end)
	{
		return NULL;
	}
	
	middle = (start +  end) / 2;
	
	if (array[middle] == num_to_find)
	{
		return (array + middle);
	}
	if (array[middle] > num_to_find)
	{
		return RecBinarySearchImpl(array, start, middle - 1, num_to_find);
	}
	
	return RecBinarySearchImpl(array, middle + 1, end, num_to_find);
}						 

/**************************** Merge Sort **************************************/

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	assert(arr_to_sort);
		
	return MergeSortImpl(arr_to_sort, 0, num_elements);
}

static int MergeSortImpl(int *arr, size_t left, size_t right)
{
	size_t middle = 0;
	int alloc_flag = 1;
	
	if (1 >= right - left)
	{
		return 0;
	}	
	
	middle = (left + right) / 2;

	MergeSortImpl(arr, left, middle); 
		
	MergeSortImpl(arr, middle, right);
		
	alloc_flag = Merge(arr, left, middle, right);
	
	return alloc_flag; 
}

static int Merge(int *arr, size_t left, size_t middle, size_t right)
{
	size_t left_index = 0;
	size_t right_index = 0;
	size_t i = left;
	
	/*calculating sub array sizes*/
	size_t left_arr_size = middle - left; 
    size_t right_arr_size = right - middle; 
	
	/*allocating sub arrays*/
	int *left_arr = (int *)malloc(left_arr_size * sizeof(int));
	int *right_arr = NULL;
	
	if (NULL != left_arr)
	{
		right_arr = (int *)malloc(right_arr_size * sizeof(int));
		
		if (NULL == right_arr)
		{
			FREE(left_arr);
			
			return (1);
		}
	}
	else
	{
		return (1);
	}
	

	for (left_index = 0; left_index < left_arr_size; ++left_index) 
	{
		left_arr[left_index] = arr[left + left_index]; 
	}
	
	for (right_index = 0; right_index < right_arr_size; ++right_index) 
	{
		right_arr[right_index] = arr[middle + right_index];	
	}
	
	
	     /*fill original array while sorting*/	
	for (right_index = 0, left_index = 0;
		 left_index < left_arr_size && right_index < right_arr_size; ++i) 
	{ 
		if (left_arr[left_index] <= right_arr[right_index]) 
		{ 
			arr[i] = left_arr[left_index++]; 
		} 
		else 
		{ 
			arr[i] = right_arr[right_index++]; 
		} 
	}
	
	/*moving all the rest if exist*/
	while (left_index < left_arr_size) 
	{ 
		arr[i++] = left_arr[left_index++]; 
	} 

	/*moving all the rest if exist*/
	while (right_index < right_arr_size) 
	{ 
		arr[i++] = right_arr[right_index++]; 
	} 

	FREE(left_arr);
	FREE(right_arr);
	
	return (0);
}

/******************************** Quick Sort **********************************/

void Qsort(void *base,
           size_t nmemb,
           size_t size,
           int (*compar)(const void *, const void *))
{
	QSortRec((char *)base, 0, nmemb, size, compar);
}

static void QSortRec(char *base, size_t start, size_t end, size_t size, 
                     int (*compar)(const void *, const void *))
{
	size_t pivot_index = 0;
	
	assert(base);
	assert(compar);
	
	if (1 < end - start)
	{
		pivot_index = Partition(base, start, end , size, compar);
		
		QSortRec(base, start, pivot_index, size, compar);
		
		QSortRec(base, pivot_index + 1, end, size, compar); 
	}
}  
              
static size_t Partition(char *base,
						size_t start,
						size_t end, 
						size_t size, 
						int (*compar)(const void *, const void *))
{
	size_t pivot = end - 1;
	size_t i = start ;
	size_t j = start;
	
	assert(base);
	assert(compar);
	
	for (; j < end - 1; ++j)
	{
		if (0 > compar(base + (j * size), base + (pivot * size)))
		{
			SwapContent(base + (i * size), base + (j * size), size);
			++i;
		}
	}
	
	SwapContent(base + (i * size), base + (size * pivot), size);
	
	return i;
}

static void SwapContent(char *one, char *other, size_t size)
{
	size_t i =0;
	
	assert(one);
	assert(other);
	
	for (i = 0; i < size; ++i)
	{
		char tmp = one[i];
		one[i] =  other[i];
		other[i] = tmp;
	}
}
						                            
/******************************************************************************/

static void CountingImpl(int *input,
					     int *output,
					     size_t size,
					     int *histogram,
					     size_t range,
					     int mask,
					     int shift,
					     int min)
{	
	size_t i = 0;

	assert(NULL != input);
	assert(NULL != output);
	assert(NULL != histogram);
	
	for (i = 0; i < range ; ++i)
	{
		histogram[i] = 0;
	}
	
	for (i = 0; i< size; ++i)
	{
		++(histogram[((input[i] - min) >> shift) & mask]);
	}
	
	for (i = 1; i < range; ++i)
	{
		 histogram[i] += histogram[i - 1];
	}
	
	for (i = size - 1; 0 <= (long)i; --i)
	{
		int index = ((input[i] - min) >> shift) & mask;
		
		--(histogram[index]);
		output[histogram[index]] = input[i];
	}
	
	for (i = 0;  size > i; ++i)
	{
		input[i] = output[i];
	}
	
}					   
static int FindMin(int *arr, size_t size)
{
	int min = arr[0];
	size_t i = 0;
	
	for (i = 1; i < size; ++i)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	
	return min;
}

static int FindMax(int *arr, size_t size)
{
	int max = arr[0];
	size_t i = 0;
	
	for (i = 1; i < size; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}	
