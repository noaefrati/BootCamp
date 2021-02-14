/*************************************************************************** 
 * Description: Implement Singley Linked List and it's functions.          *
 * Author: Noa Efrati                                                      *
 * Reviewer: Galit Vaknin                                                  *
 * Date: 23.11.20                                                          *
 * Infinity Labs OL97                                                      *
 ***************************************************************************/


#include <stdlib.h>      /* malloc                                         */
#include <assert.h>      /* assert                                         */
#include "slist.h"       /* singly linked list functions                   */
#include "queue.h"       /* queue functions                                */

struct queue
{
	sllist_t *list;
};

queue_t *QCreate(void)
{
	queue_t *new_queue = (queue_t *) malloc(sizeof(queue_t)); 

	if (NULL != new_queue)
	{
		if (!(new_queue->list = SLLCreate()))
		{
			
			free(new_queue); new_queue = NULL;
		
			return (NULL);
		}
	}

	return (new_queue);
}

void QDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLDestroy(queue->list);
	queue->list =  NULL;
	free(queue); 
	queue = NULL;
}

int QEnqueue(queue_t *queue, const void *value)
{
	sllist_iter_t ret_iter = NULL;
	assert(NULL != queue);
	
	ret_iter = SLLInsertBefore(queue->list, SLLEnd(queue->list), value);
	
	return ((ret_iter == SLLEnd(queue->list)) ? (1) : (0));
}

void *QDequeue(queue_t *queue)
{
	void *data = NULL;
	assert(NULL != queue);
	
	if (QIsEmpty(queue))
	{
		return NULL;
	}
	
	data = SLLGetData(SLLBegin(queue->list));
	SLLRemove(queue->list, SLLBegin(queue->list));
	
	return (data);
}

int QIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	
	return (SLLIsEmpty(queue->list));
}

size_t QSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	return (SLLSize(queue->list));
}

void *QPeek(const queue_t *queue)
{
	void *data = NULL;
	assert(NULL != queue);
	if (QIsEmpty(queue))
	{
		return (NULL);
	}
	data = SLLGetData(SLLBegin(queue->list));
	
	return  data;
}

queue_t *QAppend(queue_t *src_q, queue_t *dest_q)
{
	assert(NULL != src_q);
	assert(NULL != dest_q);
	assert(src_q != dest_q);
	
	dest_q->list = SLLAppend(src_q->list, dest_q->list);
	
	return dest_q;
		
}
