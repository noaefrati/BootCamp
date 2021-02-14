#ifndef __SORT_H_OL97_ILRD__
#define __SORT_H_OL97_ILRD__

/*******************************************************************************
 * Description: Header file Containing Declarations for Searching and Sorting 
 * algorithms.
 *
 * Infinity Labs - OL97.
 ******************************************************************************/

/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h>     /* size_t */

/******************************************************************************/
/***                      Public functions declarations                     ***/
/******************************************************************************/

/*
 * Implementation of Bubble sort Algorithm.
 */
void BubbleSort(int *arr, size_t size);

/*
 * Implementation of Insertion sort Algorithm.
 */
void InsertionSort(int *arr, size_t size);

/*
 * Implementation of Selection sort Algorithm.
 */
void SelectionSort(int *arr, size_t size);

/*
 * Implementation of Counting sort Algorithm.
 * If Malloc failed returns 1, else if everything succeeded return 0.
 */
int CountingSort(int *arr, size_t size);

/*
 * Implementation of radix sort Algorithm.
 * If Malloc failed returns 1, else if everything succeeded return 0.
 * Given Assumption is that (sizeof(int) * CHAR_BIT) % nbits == 0.
 */
int RadixSort(int *arr, size_t size, size_t n_bits);

/*
 * Implementation of Iterative Binary Search Algorithm.
 * Returns the address of the element holding the value <num_to_find>, 
 * If no such element in the given array, null will be returned.
 */
int *IterBinarySearch(int *array, size_t size, int num_to_find);

/*
 * Implementation of Recursive Binary Search Algorithm.
 * Returns the address of the element holding the value <num_to_find>, 
 * If no such element in the given array, null will be returned.
 */
int *RecBinarySearch(int *array, size_t size, int num_to_find);

/*
 * Implementation of MergeSort Algorithm.
 * If Malloc failed returns 1, else if everything succeeded return 0.
 */
int MergeSort(int *arr_to_sort, size_t num_elements);

/*
 * Implementation of QuickSort Algorithm.
 */
void Qsort(void *base,
           size_t nmemb,
           size_t size,
           int (*compar)(const void *, const void *));

#endif /* __SORT_H_OL97_ILRD__ */
