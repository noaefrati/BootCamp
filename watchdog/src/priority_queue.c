/******************************************************************************
Description: Priority queue functions (Refactored to heap) 
Author: Roi Peretz
Reviewer: Ronny Efronny 

Infinity Labs OL97
*******************************************************************************/
#include <assert.h>         /* assert */
#include <stdlib.h>         /* malloc, free */

#include "priority_queue.h" /* priority queue list API */
#include "heap.h"

#define HEAP que->heap

struct pq
{
	heap_t *heap;
};
    
pq_t *PQCreate(int (*cmp_func)(const void *lhs, const void *rhs))
{
	pq_t *que = NULL;
	
	assert(cmp_func);
	
	que = (pq_t *)malloc(sizeof(pq_t));
	if (NULL != que)
	{
		HEAP = HeapCreate(cmp_func);
		if (NULL == HEAP)
		{
			free(que); que = NULL;
		}
	}
	
	return (que);
}

void PQDestroy(pq_t *que)
{
	assert(que);
	assert(HEAP);
	
	HeapDestroy(HEAP); HEAP = NULL;
	 
	free(que); que = NULL;
}

size_t PQSize(const pq_t *que)
{
	assert(que);
	assert(HEAP);
	
	return (HeapSize(HEAP));
}


int PQIsEmpty(const pq_t *que)
{
	assert(que);
	assert(HEAP);
	
	return (HeapIsEmpty(HEAP));
}


int PQEnqueue(pq_t *que, const void *data)
{
	assert(que);
	assert(HEAP);
	
	return (HeapPush(HEAP, data));
}

void *PQDequeue(pq_t *que)
{
	void *data = NULL;
	
	assert(que);
	assert(HEAP);
	
	data = PQPeek(que);
	HeapPop(HEAP);
	
	return (data);
}

void *PQPeek(pq_t *que)
{
	assert(que);
	assert(HEAP);
	
	return (HeapPeek(HEAP));
}

void *PQErase(pq_t *que, 
              int (*is_match)(const void *data, const void *to_erase),
              const void *to_erase)
{
	
	assert(que);
	assert(HEAP);
	assert(is_match);
	
	return (HeapRemove(HEAP, is_match, to_erase)); 
}

void PQClear(pq_t *que)
{
	assert(que);
	
	while (!PQIsEmpty(que))
	{
		PQDequeue(que);
	}
}
