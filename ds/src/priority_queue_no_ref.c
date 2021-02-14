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
#include "sorted_list.h"                /* sorted list functions              */
#include "dlist.h"                      /* doubly list functions              */
/******************************************************************************/
/******************************************************************************/
struct pq
{
	srtlst_t *list;
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
		if (!(new_pq->list = SRTLSTCreate(cmp_func)))
		{
			free(new_pq); new_pq = NULL;
		}
	}
	
	return new_pq;	
}

void PQDestroy(pq_t *que)
{
	assert(NULL != que);
	
	SRTLSTDestroy(que->list);
	free(que); que = NULL;
}

size_t PQSize(const pq_t *que)
{
	assert(NULL != que);
	
	return SRTLSTSize(que->list);
}

int PQIsEmpty(const pq_t *que)
{
	assert(NULL != que);
	
	return SRTLSTIsEmpty(que->list);
}

int PQEnqueue(pq_t *que, const void *data)
{
	assert(NULL != que);
	assert(NULL != data);
	
	return SRTLSTInsert(que->list, data);	
}
 
void *PQDequeue(pq_t *que)
{
	void *data = NULL;
	
	assert(NULL != que);
	
	data = PQPeek(que);
	SRTLSTPopFront(que->list);
	
	return data;
}

void *PQPeek(pq_t *que)
{
	assert(NULL != que);
	
	return SRTLSTGetData(SRTLSTBegin(que->list));
}

void *PQErase(pq_t *que, 
              int (*is_match)(const void *data, const void *to_erase),
              const void *to_erase)
{
	srtlst_iter_t iter;
	void *data_to_return = NULL;
	
	assert(NULL != que);
	assert(NULL != is_match);
	
	iter = SRTLSTFindIf(SRTLSTBegin(que->list),
						SRTLSTEnd(que->list),
						is_match,
						to_erase);
	
	if (!SRTLSTIsSameIter(SRTLSTEnd(que->list), iter))
	{
		data_to_return = SRTLSTGetData(iter);
		SRTLSTRemove(iter); 
	}
	
	return data_to_return;
}

void PQClear(pq_t *que)
{
	assert(NULL != que);
	
	while (!PQIsEmpty(que))
	{
		PQDequeue(que);
	}
}
