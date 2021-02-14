/*************************************************************************** 
 * Description: Implement Doubly linked list                               *
 * Author: Noa Efrati                                                      *
 * Reviewer: Inbal Shukrun                                                 *
 * Date: 30.11.20                                                          *
 * Infinity Labs OL97                                                      *
 ***************************************************************************/

#include <stdlib.h>                     /* malloc, free                    */
#include <assert.h>                     /* assert                          */
#include "dlist.h"                      /* Doubly linked list functions    */ 


struct node
{ 
	void *data;
	struct node *next;
	struct node *prev;
};

struct dllist 
{
	struct node head;
	struct node tail;
};
/************************** Creation and Desturction **************************/

dllist_t *DLLCreate(void)
{
	dllist_t *dlist = (dllist_t *) malloc(sizeof(dllist_t));
	if (NULL != dlist)
	{
		dlist->head.data = NULL;
		dlist->head.prev = NULL;
		
		dlist->tail.data = NULL;
		dlist->tail.next = NULL;
		
		dlist->tail.prev = &(dlist->head);
		dlist->head.next = &(dlist->tail);
	}
	return dlist;
}

void DLLDestroy(dllist_t *lst)
{
	dllist_iter_t current = NULL; 
   	dllist_iter_t next = NULL;
  
   	assert(NULL != lst);
	
	current = DLLBegin(lst);
   	while (NULL != current->next)  
   	{ 
       	next = current->next; 
      	current->next = NULL;
		current->prev = NULL;
		current->data = NULL;
       	free(current); current = NULL; 
     	current = next; 
   	} 
   	lst->tail.prev = NULL;
   	lst->head.next = NULL;  	
	free(lst); lst = NULL;		
}

/****************************** Basic Utilities *******************************/

size_t DLLSize(const dllist_t *lst)
{
	dllist_iter_t runner = NULL;
	dllist_iter_t end = NULL;
	size_t size = 0;
	
	assert(NULL != lst);
	
	end = DLLEnd(lst);
	runner = DLLBegin(lst);	
	
	for (; !DLLIsSameIter(end, runner); runner = DLLNext(runner), ++size)
	{
		/* empty */
	}
	
	return size;
}

int DLLIsEmpty(const dllist_t *lst)
{
	assert(NULL != lst);
	
	return (lst->head.next == DLLEnd(lst));
}

int DLLIsSameIter(const dllist_iter_t one, const dllist_iter_t other)
{
	assert(NULL != one);
	assert(NULL != other);
	
	return (one == other);
}

dllist_iter_t DLLNext(const dllist_iter_t iter)
{
	assert(NULL != iter);
	
	return (NULL == iter->next ? (iter) : (iter->next));
}
 
dllist_iter_t DLLPrev(const dllist_iter_t iter)
{
	assert(NULL != iter);
	
	return (NULL == iter->prev->prev) ? (iter) : (iter->prev);	
}

dllist_iter_t DLLBegin(const dllist_t *lst)
{
	assert(NULL != lst);
	
	return (lst->head.next);
}


dllist_iter_t DLLEnd(const dllist_t *lst)
{
	assert(NULL != lst);
	
	return (dllist_iter_t)(&(lst->tail));
}

/****************************** Get and Set Data ******************************/

void *DLLGetData(const dllist_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->data;
}

void DLLSetData(dllist_iter_t iter, const void *data)
{
	assert(NULL != iter);
	
	iter->data = (void *) data;
}

/*************************** Add and Remove Element ***************************/

int DLLInsertBefore(dllist_iter_t iter, const void *data)
{
	dllist_iter_t new_iter = NULL;
	int ret_val = 1;
	
	assert(NULL != iter);
	assert(NULL != data);
	
	new_iter = (node_t *) malloc(sizeof(node_t));
	if (NULL != new_iter)
	{
		DLLSetData(new_iter, data);
		iter->prev->next = new_iter;
		new_iter->next = iter;
		new_iter->prev = iter->prev;
		iter->prev = new_iter;		
		ret_val = 0;
	}
	
	return ret_val;
}

dllist_iter_t DLLPushBack(dllist_t *lst, const void *data)
{
	assert(NULL != lst);
	assert(NULL != data);
	
	return  (DLLInsertBefore(DLLEnd(lst), data)) ?
	        (DLLEnd(lst)) :
	        (DLLPrev(DLLEnd(lst)));
}

dllist_iter_t DLLPushFront(dllist_t *lst, const void *data)
{

	assert(NULL != lst);
	
	return (DLLInsertBefore(DLLBegin(lst), data)) ?
	       (DLLEnd(lst)) :
	       (DLLBegin(lst));
}

void DLLRemove(dllist_iter_t iter)
{
	assert(NULL != iter);	
	
	/* connecting iter prev to iter next, and iter next to iter prev */
	iter->prev->next = iter->next;
	iter->next->prev = iter->prev;
	
	/* Disconnection iter and free the memory */
	iter->next = NULL;
	iter->prev = NULL;
	iter->data = NULL;
	free(iter); iter = NULL;
}

void DLLPopBack(dllist_t *lst)
{
	assert(NULL != lst);
	
	DLLRemove(DLLPrev(DLLEnd(lst)));	
}

void DLLPopFront(dllist_t *lst)
{
	assert(NULL != lst);
		
	DLLRemove(DLLBegin(lst));
}

/***************************** Advanced Utilities *****************************/

int DLLForEach(dllist_iter_t from, 
               dllist_iter_t to,
               int (*action)(void *data, void *params),
               void *params)
{
	int action_value = 0;
	dllist_iter_t from_runner = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	
	from_runner = (dllist_iter_t) from;
	
	for(; !DLLIsSameIter(from_runner, to) &&
		  (1 != action_value);
	      from_runner = DLLNext(from_runner))
	{
		action_value = action(DLLGetData(from_runner), params);
	}
	
	return action_value;
}

dllist_iter_t DLLFind(const dllist_iter_t from,
                      const dllist_iter_t to,
                      const void *value,
                      int (*is_match)(const void *data, const void *against))
{
	
	dllist_iter_t runner =  NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != value);
	
	
	for (runner = from; to != runner; runner =  DLLNext(runner))
	{
		if (1 == is_match(value, DLLGetData(runner)))
		{		
			break;
		}
	}
	
	return runner;
}

int DLLMultiFind(const dllist_iter_t from,
                 const dllist_iter_t to,
                 dllist_t *dest,
				 const void *value,
                 int (*is_match)(const void *data, const void *against))
{
	dllist_iter_t runner= NULL;
	int is_multi_find = 1;
	
	assert(NULL != from);
	assert(NULL != dest);
	assert (NULL != is_match);
	runner = (dllist_iter_t) from;
	for (;to != (runner = DLLFind(runner, to, value, is_match));
	     runner = DLLNext(runner))
	{
		     /* checking if pushback failed, then break */
			if (DLLPushBack(dest, runner->data) == DLLEnd(dest)) 
			{
				is_multi_find = 0;
				break;
			}
	}
	return !(is_multi_find);
}
                     
void DLLSplice(dllist_iter_t from,
               dllist_iter_t to,
               dllist_iter_t target)
{
	dllist_iter_t original_to_prev = NULL;
	
	assert(from);
	assert(to);
	assert(target);
	
	original_to_prev = to->prev;
	
	/* update removal of nodes */
	to->prev = from->prev;
	from->prev->next = to;
	
	/* update insertion of nodes */
	from->prev = target->prev;
	target->prev->next = from;
	target->prev = original_to_prev;
	original_to_prev->next = target;
}
