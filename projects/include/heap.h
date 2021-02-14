#ifndef __OL_97__HEAP_H__
#define __OL_97__HEAP_H__

/******************************************************************************
 * Description: API For Heap ADT (The Implementation will be of Min Heap).    *
 *                                                                            *
 * Infinity Labs - OL97                                                       *
 ******************************************************************************/
#include <stddef.h> /* size_t */

/************************* Structures and Typedefs ****************************/
typedef struct heap heap_t;
typedef int (*heap_cmp_func_t)(const void *data, const void *input);
typedef int (*heap_match_func_t)(const void *data, const void *val_to_remove);

/*
Inside implementation file:
==========================
#include "vector_ref.h"

struct heap
{
	vector_t *vector;
	cmp_func_t compare;
};
*/
/***                                                                        ***/
/******************************** Functions ***********************************/
/***                                                                        ***/

/**************************** Create and Destroy ******************************/
/*
 * Description: Create a new empty Heap structure.
 * Return value: HeapCreate returns pointer to newly created heap or NULL if 
 * memory allocation failed.
 * The compare function will be used as part of the heapify method and 
 * should return: 
 *   0 -                  When both the parameters are equal.
 * > 0 (Positive value) - When first paramter is 'bigger' than the second.
 * < 0 (Negative value) - When first paramter is 'smaller' than the second.
 * Time Complexity: O(1).
 */
heap_t *HeapCreate(heap_cmp_func_t compare);

/*
 * Description: Destroy a given heap.
 * Return value: none.
 * Time Complexity: O(1).
 */
void HeapDestroy(heap_t *heap);

/******************************* Insertion ************************************/

/*
 * Description: Insert new value into given heap.
 * Return value: 0 if placement was successful, 1 otherwise.
 * Placement may be unsuccessful if memory allocation fails.
 * Time Complexity: Worst: O(n). Amortized: O(Log n).
 */
int HeapPush(heap_t *heap, const void *data);

/****************************** Basic Utility *********************************/
/*
 * Description: Get the total number of elements in the heap.
 * Return value: number of elements currently in the heap.
 * Time Complexity: O(1).
 */
size_t HeapSize(const heap_t *heap);

/*
 * Description: Check whether given heap has elements.
 * Return value: 1 if heap is empty, 0 otherwise.
 * Time Complexity: O(1).
 */
int HeapIsEmpty(const heap_t *heap);

/*
 * Description: Get the value of the minimal element of the heap.
 * Return value: The value of the minimal element or NULL if the heap is empty.
 * Time Complexity: O(1).
 */
void *HeapPeek(const heap_t *heap);

/*
 * Description: Remove element with the minimal value from the heap.
 * Return value: None.
 * UB: Trying to pop an empty heap.
 * Time Complexity: O(Log (n)).
 */
void HeapPop(heap_t *heap);

/*
 * Description: This function is searching an element with the value:
 * val_to_remove using the match function, upon finding the first such element,
 * its removed from the heap and it's value is returned to the caller. If no 
 * such element found in the heap, NULL is returned to the caller.
 * Return value: The value of the removed element or NULL if no element found.
 * The match function returns 1 on element match and 0 otherwise.
 * Time Complexity: O(n).
 */
void *HeapRemove(heap_t *heap, 
                 heap_match_func_t match, 
                 const void *val_to_remove);

#endif /* __OL_97__HEAP_H__ */
