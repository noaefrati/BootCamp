/******************************************************************************* 
 * Description: Implemention of DS Heap                                        *
 * Author: Noa Efrati                                                          *
 * Reviewer: Ronny Efrrony                                                     *
 * Date: 07.01,2021                                                            *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/

#include <assert.h>      /* assert                                            */
#include <stdlib.h>      /* free                                              */
#include "vector_ref.h"  /* vector_ref API                                    */
#include "heap.h"        /* heap ds API                                       */

#define FREE(x) free(x); x = NULL;
#define VECTOR_SIZE 20
#define ROOT_INDEX (0)
#define PARENT_OF(child_index) ((child_index - 1)/2)
#define LEFT_OF(parent_index) ((2 * parent_index) + 1)
#define RIGHT_OF(parent_index) ((2 * parent_index) + 2) 

/******************************************************************************/
/***                            Structs & Typedefs                          ***/
/******************************************************************************/

struct heap
{
	vector_t *vector;
	heap_cmp_func_t compare;
};

/******************************************************************************/
/***                     Private function declarations                      ***/
/******************************************************************************/

static size_t FindMatch(heap_t *heap,
					    heap_match_func_t match,
					    const void *val_to_find);
					    
static void	HeapifyUp(heap_t *heap, size_t index);
static void HeapifyDown(heap_t *heap, size_t index);
static void Swap(heap_t *heap, size_t one_index, size_t other_index); 
static int HeapCmpFuncResult(heap_t *heap, size_t one, size_t  other);

/******************************************************************************/
/***                       Public function definitions                      ***/
/******************************************************************************/
/**************************** Create and Destroy ******************************/

heap_t *HeapCreate(heap_cmp_func_t compare)
{
	heap_t *heap = NULL;
	
	assert (compare);
	
	heap = (heap_t *)malloc(sizeof(heap_t));
	
	if (NULL != heap)
	{
		heap->vector = VectorCreate(VECTOR_SIZE);
		
		if (NULL == heap->vector)
		{
			FREE(heap);
		}
		else
		{
			heap->compare = compare;
		}
	}
	
	return heap;
}

void HeapDestroy(heap_t *heap)
{
	assert (heap);
	
	VectorDestroy(heap->vector);
	
	heap->compare = NULL;
	
	FREE(heap);
}

/******************************* Insertion ************************************/

int HeapPush(heap_t *heap, const void *data)
{
	/* adding element in the last spot of the vector */
	if (1 == VectorPushBack(heap->vector, data))
	{
		return 1; /* failed at allocation*/
	}
	
	/*heapifies if needed*/
	HeapifyUp(heap, HeapSize(heap) - 1);
	
	return (0);	
}

/****************************** Basic Utility *********************************/

size_t HeapSize(const heap_t *heap)
{
	assert(heap);
	
	return VectorSize(heap->vector);
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(heap);
	
	return (0 == HeapSize(heap));
}

void *HeapPeek(const heap_t *heap)
{
	assert (heap);
	
	return HeapIsEmpty(heap) ? NULL : 
						   VectorGetAccessToElementAt(heap->vector, ROOT_INDEX);
}

void HeapPop(heap_t *heap)
{
	assert(heap);
	assert(!HeapIsEmpty(heap));

	if (HeapSize(heap) > 1)
	{
		Swap(heap, ROOT_INDEX, HeapSize(heap) - 1);
	}
	
	VectorPopBack(heap->vector);
	
	if (HeapSize(heap) > 1)
	{
		HeapifyDown(heap, ROOT_INDEX);
	}	
}

void *HeapRemove(heap_t *heap, 
                 heap_match_func_t match, 
                 const void *val_to_remove)
{
	size_t heap_size = 0;
	size_t ret_index = 0;
	void *data_to_swap = NULL;
	
	assert(heap);
	assert(match);
	
	heap_size = HeapSize(heap);
	ret_index = FindMatch(heap, match, val_to_remove);
	
	if (heap_size != ret_index)
	{
		
		data_to_swap =  VectorGetAccessToElementAt(heap->vector, ret_index);
		
		/* Swapping between the last element and val_to_remove .*/
		Swap(heap, ret_index, heap_size - 1); 
		
		/* Deleting the requested element */
		VectorPopBack(heap->vector);
		
		HeapifyDown(heap, ret_index);
		HeapifyUp(heap, ret_index);
	}
	
	return data_to_swap;
}
               
/******************************************************************************/
/***                      Private function definitions                      ***/
/******************************************************************************/

static void Swap(heap_t *heap, size_t one_index, size_t other_index)
{
	void *one_element = NULL;
	void *other_element = NULL;
	
	assert(heap);
	
	one_element = VectorGetAccessToElementAt(heap->vector, one_index);
	other_element = VectorGetAccessToElementAt(heap->vector, other_index);
	
	VectorSetElementAt(heap->vector, one_index, other_element);
	VectorSetElementAt(heap->vector, other_index ,one_element);
}

static void HeapifyDown(heap_t *heap, size_t index)
{
	int is_bigger = 1;

	assert(heap);
	
	while ( 0 < is_bigger && LEFT_OF(index) < HeapSize(heap))
	{
		size_t smaller_child_index = LEFT_OF(index);
	
		/* if index has  also a right child, then:
		 * check if right child data is smaller than the left child data */	
		if (RIGHT_OF(index) < HeapSize(heap) &&
		    0 > HeapCmpFuncResult(heap,RIGHT_OF(index), LEFT_OF(index)))
		{	
			smaller_child_index = RIGHT_OF(index);
		}	
		
		is_bigger =  HeapCmpFuncResult(heap, index, smaller_child_index);        
		         
		if (0 < is_bigger)
		{
			Swap(heap, index, smaller_child_index);
			index = smaller_child_index;
		}
		   
	}
	

}

static void	HeapifyUp(heap_t *heap, size_t index)
{
	assert(heap);
	
	if (ROOT_INDEX == index ||
		0 < HeapCmpFuncResult(heap, index, PARENT_OF(index)))
	{
		return;
	}
	
	Swap(heap, PARENT_OF(index), index);
	HeapifyUp(heap, PARENT_OF(index));
}

/* return the index that match in success, else return the size of vector*/
static size_t FindMatch(heap_t *heap,
					   heap_match_func_t match,
					   const void *val_to_find)
{
	size_t heap_size = 0;
	size_t index = 0;
	
	assert(heap);
	assert(match);
	
	heap_size = HeapSize(heap);
	
	for (index = ROOT_INDEX;
		index < heap_size 
		&& !match(val_to_find,VectorGetAccessToElementAt(heap->vector, index)); 
		++index)
	{
		/**empty*/                
	}	

	return index;
}

static int HeapCmpFuncResult(heap_t *heap, size_t one, size_t  other)
{
	void *one_data = NULL;
	void *other_data = NULL;
	
	assert(heap);
	
	one_data = VectorGetAccessToElementAt(heap->vector, one);
	other_data = VectorGetAccessToElementAt(heap->vector, other);
	
	return heap->compare(one_data, other_data);
}
