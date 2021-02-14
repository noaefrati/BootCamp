/****************************************************************************** 
 * Description: Implement Priority Queue                                      *
 * Author: Noa Efrati                                                         *
 * Reviewer: Gal Dahan                                                        *
 * Date: 3.12.20                                                              *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/
/******************************************************************************/
#include <stdlib.h>                     /* malloc, free                       */
#include <assert.h>                     /* assert                             */
#include "priority_queue.h"             /* pq functions                       */
#include "heap.h"                      /* heap functions                      */
/******************************************************************************/
/******************************************************************************/
struct pq
{
	heap_t *heap;
};
/******************************************************************************/
/******************************************************************************/

pq_t *PQCreate(int (*cmp_func)(const void *lhs, const void *rhs))
{
	pq_t *new_pq = NULL;
	
	assert(NULL != cmp_func);
	
	new_pq = (pq_t *) malloc(sizeof(pq_t));
	if (NULL != new_pq)
	{
		if (!(new_pq->heap = HeapCreate(cmp_func)))
		{
			free(new_pq); new_pq = NULL;
		}
	}
	
	return new_pq;	
}

void PQDestroy(pq_t *que)
{
	assert(NULL != que);
	
	HeapDestroy(que->heap);
	free(que); que = NULL;
}

size_t PQSize(const pq_t *que)
{
	assert(NULL != que);
	
	return HeapSize(que->heap);
}

int PQIsEmpty(const pq_t *que)
{
	assert(NULL != que);
	
	return HeapIsEmpty(que->heap);
}

int PQEnqueue(pq_t *que, const void *data)
{
	assert(NULL != que);
	
	return HeapPush(que->heap, data);	
}
 
void *PQDequeue(pq_t *que)
{
	void *data = NULL;
	
	assert(NULL != que);
	
	data = PQPeek(que);
	HeapPop(que->heap);
	
	return data;
}

void *PQPeek(pq_t *que)
{
	assert(NULL != que);
	
	return HeapPeek(que->heap);
}

void *PQErase(pq_t *que, 
              int (*is_match)(const void *data, const void *to_erase),
              const void *to_erase)
{
	assert(NULL != que);
	assert(NULL != is_match);
	
	return HeapRemove(que->heap, is_match, to_erase);
}

void PQClear(pq_t *que)
{
	assert(NULL != que);
	
	while (!PQIsEmpty(que))
	{
		HeapPop(que->heap);
	}
}
