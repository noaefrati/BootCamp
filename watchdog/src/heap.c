/******************************************************************************
Description: Heap functions implementation
Author: Roi Peretz
Reviewer: David Horovitz
				
Infinity Labs OL97
*******************************************************************************/

/******************************************************************************/
/***                      Includes and Defines                              ***/
/******************************************************************************/

#include <assert.h>	   /* assert */
#include <stdlib.h>    /* malloc, free */

#include "heap.h"	       /* Heap API */
#include "vector_ref.h"	   /* Vector (by refernce) API */

#define INITIAL_CAPACITY 1
#define VECTOR heap->vector

#define PARENT(index) (((index) - 1) / 2)
#define LEFT_CHILD(index) (2 * (index) + 1)
#define RIGHT_CHILD(index) (2 * (index) + 2)

/******************************************************************************/
/***                    structs and function typedefs                       ***/
/******************************************************************************/

struct heap
{
	vector_t *vector;
	heap_cmp_func_t compare;
};

/******************************************************************************/
/***                   static functions declaration                         ***/
/******************************************************************************/

static size_t LastIndex(heap_t *heap);
static void Swap(heap_t *heap, size_t index_1, size_t index_2);
static void HeapifyBottomUp(heap_t *heap, size_t index);
static void HeapifyUpBottom(heap_t *heap, size_t index);
static int FindIndex(heap_t *heap, heap_match_func_t match, 
										const void *val_to_find, size_t *index);
int CompareWrapper(heap_t *heap, size_t lhs_index, size_t rhs_index);
                
/******************************************************************************/
/***                         API functions                                  ***/
/******************************************************************************/

/**************************** Create and Destroy ******************************/

heap_t *HeapCreate(heap_cmp_func_t compare)
{
	heap_t *heap = NULL;
	
	assert(compare);
	
	heap = (heap_t *) malloc(sizeof(heap_t));
	
	if (NULL != heap)
	{
		VECTOR = VectorCreate(INITIAL_CAPACITY);
		
		if (NULL != VECTOR)
		{
			heap->compare = compare;
		}
		
		else
		{
			free(heap); heap = NULL;
		}
	}
	
	return(heap);
}

void HeapDestroy(heap_t *heap)
{
	VectorDestroy(VECTOR); VECTOR = NULL;
	free(heap); heap = NULL;
}

/************************* Insertion & Deletion *******************************/

int HeapPush(heap_t *heap, const void *data)
{
	int push_ret = 0;
	
	assert(heap);
	
	push_ret = VectorPushBack(VECTOR, data);
	HeapifyBottomUp(heap, LastIndex(heap));
	
	return(push_ret);
}

void HeapPop(heap_t *heap)
{
	assert(heap);
	
	Swap(heap, 0, LastIndex(heap));
	VectorPopBack(VECTOR);
	HeapifyUpBottom(heap, 0);
}

void *HeapRemove(heap_t *heap, 
                 heap_match_func_t match, 
                 const void *val_to_remove)
{
	int found_flag = 0;
	size_t remove_index = 0;
	void *ret_ptr = NULL;
	
	assert(heap);
	
	found_flag = FindIndex(heap, match, val_to_remove, &remove_index);
	
	if (found_flag)
	{
		ret_ptr = VectorGetAccessToElementAt(VECTOR, remove_index); 
		Swap(heap, remove_index, LastIndex(heap));
				
		if (0 == remove_index || 
			CompareWrapper(heap, remove_index, PARENT(remove_index)) > 0)
		{	
			VectorPopBack(VECTOR);
			HeapifyUpBottom(heap, remove_index);
		}
		
		else
		{
			VectorPopBack(VECTOR);
			HeapifyBottomUp(heap, remove_index);
		}
		
	}  
    
    return(ret_ptr);
                
}

/****************************** Basic Utility *********************************/

size_t HeapSize(const heap_t *heap)
{
	assert(heap);
	
	return(VectorSize(VECTOR));
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(heap);
	
	return(0 == HeapSize(heap));
}

void *HeapPeek(const heap_t *heap)
{
	assert(heap);
	
	return(VectorGetAccessToElementAt(VECTOR, 0));
}

/******************************************************************************/
/***                         static functions                               ***/
/******************************************************************************/

/*
 * Description: swaps to value in the vector.
 * Return value: none
 */
static void Swap(heap_t *heap, size_t index_1, size_t index_2)
{
	void *tmp1 = NULL;
	void *tmp2 = NULL;
	
	assert(heap);
	
	tmp1 = VectorGetAccessToElementAt(VECTOR, index_1);
	tmp2 = VectorGetAccessToElementAt(VECTOR, index_2);
	
	VectorSetElementAt(VECTOR, index_1, tmp2);
	VectorSetElementAt(VECTOR, index_2, tmp1);
}

/*
 * Description: heapify to restore heap properties (bottom to up).
 * Return value: none.
 */
static void HeapifyBottomUp(heap_t *heap, size_t index)
{
	assert(heap);
	
	if (0 != index)
	{	
		size_t parent = PARENT(index);
		if (CompareWrapper(heap, index, parent) < 0)			
		{
			Swap(heap, index, parent);
			HeapifyBottomUp(heap, parent);	
		}
		
	}
}

/*
 * Description: heapify to restore heap properties (up to bottom).
 * Return value: none.
 */
static void HeapifyUpBottom(heap_t *heap, size_t index)
{
	size_t left = LEFT_CHILD(index);
	size_t right = RIGHT_CHILD(index);
	size_t smallest = index;
	
	assert(heap);
	
	if (left < HeapSize(heap) && CompareWrapper(heap, left, index) < 0)
		{
			smallest = left;
		}
		
	if (right < HeapSize(heap) && CompareWrapper(heap, right, smallest) < 0)
		{
			smallest = right;
		}
	
	if (smallest != index)
	{
		Swap(heap, index, smallest);
		HeapifyUpBottom(heap, smallest);
	}
}

/*
 * Description: searches the heap to find val_to_find.
 * Return value: index (as out param) of val_to_find if found, else -1;
 */
static int FindIndex(heap_t *heap, 
                 heap_match_func_t match, 
                 const void *val_to_find,
                 size_t *index)
{
	size_t i = 0;
	int found_flag = 0;
	
	assert(heap);
	assert(index);
	
	for (; i < HeapSize(heap) && !found_flag;  ++i) 
	{
		 found_flag =
		 	  match(VectorGetAccessToElementAt(VECTOR, i), val_to_find);
		 	  
		 if (found_flag)
		 {
		 	*index = i;
		 }
	}
	
	return(found_flag);
}

/*
 * Description: returns the last index in the array.
 * Return value: last index of array.
 */
static size_t LastIndex(heap_t *heap)
{
	assert(heap);
	
	return (HeapSize(heap) - 1);
}

/*
 * Description: wrapper for user compare function on to array elements.
 * Return value: compare function result.
 */
int CompareWrapper(heap_t *heap, size_t lhs_index, size_t rhs_index)
{
	assert(heap);
	
	return heap->compare(VectorGetAccessToElementAt(VECTOR, lhs_index),
					  	 VectorGetAccessToElementAt(VECTOR, rhs_index));
}


