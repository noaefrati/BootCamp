/*************************************************************************** 
 * Description: Implement Singley Linked List and it's functions.          *
 * Author: Noa Efrati                                                      *
 * Reviewer: Yuval Krytzer                                                 *
 * Date: 23.11.20                                                          *
 * Infinity Labs OL97                                                      *
 ***************************************************************************/


#include <stdlib.h>      /* malloc                                         */
#include <assert.h>      /* assert                                         */
#include "slist.h"       /* singly linked list functions                   */

struct node
{
    void *data;
    struct node *next;
};

struct sllist 
{
	struct node *head;
	struct node *tail;  /*the dummy */
};

sllist_t *SLLCreate(void)
{
	sllist_t *list = (sllist_t *) malloc(sizeof(sllist_t));
	node_t *dummy = NULL;
	
	if (NULL == list)
	{
	    return (NULL);
	}
	
	dummy = (node_t *) malloc(sizeof(node_t));
	if (NULL == dummy)
	{
		free(list);
		return (NULL);
	}
	
	dummy->next = NULL;
	dummy->data = NULL;
	list->tail = dummy;
	list->head = dummy;
	
	return list;
}

void SLLDestroy(sllist_t *lst)
{
	node_t *current = NULL; 
   	
   	assert(NULL != lst);
	
	current = lst->head;
   	while (current != NULL)  
   	{ 
       	node_t *next = current->next; 
       	free(current);
       	current = NULL; 
     	current = next; 
   	} 
	free(lst);	
}

sllist_iter_t SLLInsertBefore(sllist_t *lst,
                              sllist_iter_t iter,
                              const void *data)
{
	sllist_iter_t tmp_iter = NULL;
	
	assert(NULL != lst);
	assert(NULL != data);
	
	tmp_iter = (node_t *) malloc(sizeof(node_t));
	if (NULL == tmp_iter)
	{
		return lst->tail;
	}
	
	tmp_iter->data = iter->data;
	tmp_iter->next = iter->next;
	SLLSetData(iter, data);
	iter->next = tmp_iter;
	
	if (SLLIsSameIter(iter, SLLEnd(lst)))
	{
		lst->tail = tmp_iter;
	}

	return (iter);	 	
}

sllist_iter_t SLLPushBack(sllist_t *lst, const void *data)
{
	assert(NULL != lst);
	assert(NULL != data);
	
	return (SLLInsertBefore(lst, SLLEnd(lst), data));
}

void SLLPopBack(sllist_t *lst)
{
	node_t *current = NULL;
	node_t *prev = NULL;

	assert(NULL != lst);
	
	/* if the list is empty, no nodes to pop */
	if (1 == SLLIsEmpty(lst))
	{
		return;
	}
	
	current = lst->head; 
	while (1 != SLLIsSameIter(current, SLLEnd(lst)))
	{
		prev = current;
		current = current->next;	
	}	
	
	SLLRemove(lst, prev);
}

sllist_iter_t SLLFind(const sllist_t *lst,
                      const void *value,
                      int (*is_match)(const void *one, const void *other))
{
	sllist_iter_t iter = NULL;

	assert(NULL != lst);
	assert(NULL != value);
	
	iter = lst->head;		
	while (SLLEnd(lst) != iter)
	{
		if (0 == is_match(value, iter->data)) /* when find a match, break*/
		{
			break;
		}
		
		iter = iter->next;		
	}
	
	return (iter);
}

void SLLRemove(sllist_t *lst, sllist_iter_t iter)
{
	sllist_iter_t iter_tmp = NULL;
	
	assert(NULL != lst);
	assert(SLLEnd(lst) != iter->data);
	
	if (iter->next == lst->tail)/* if iter->next is the tail, update the tail*/
	{
		lst->tail = iter;
	}
	
	iter_tmp = iter->next;	
	iter->data = iter_tmp->data;
	iter->next = iter_tmp->next;
	iter_tmp->data = NULL;
	iter_tmp->next = NULL;
		
	free(iter_tmp);
}
/* A boolean function, returns 1 if the expression is true, else returns 0 */
int SLLIsEmpty(const sllist_t *lst)
{
	assert(NULL != lst);
	
	return SLLIsSameIter(SLLEnd(lst), SLLBegin(lst));
}

int SLLSetData(sllist_iter_t iter, const void *data)
{
	assert(NULL != iter);
	assert(NULL != data);
	
	iter->data = (void *) data;
	
	return (0);
}

void *SLLGetData(const sllist_iter_t iter)
{	
	assert(NULL != iter);
		
	return (iter->data);
}

sllist_iter_t SLLNext(const sllist_iter_t iter)
{
	assert(NULL != iter);
	
	return ((NULL == iter->next) ? (iter) : (iter->next));
}

sllist_iter_t SLLBegin(const sllist_t *lst)
{
	assert(NULL != lst);
	
	return (lst->head);
}

sllist_iter_t SLLEnd(const sllist_t *lst)
{
	assert(NULL != lst);
	
	return (lst->tail);
}

/* A boolean function, returns 1 if the expression is true, else returns 0 */
int SLLIsSameIter(const sllist_iter_t one, const sllist_iter_t other)
{
	return (one == other);
}

int SLLForEach(sllist_t *lst, 
                  sllist_iter_t from, 
                  sllist_iter_t to, 
                  int (*action)(void *data, void *params), void *params)
{
	int action_value = 0;
	
	assert(NULL != lst);
		
	while ((from != to) && (1 != action_value))
	{
		action_value = action(from->data, params);
		from = from->next;
	}
	
	return (action_value);
}  

size_t SLLSize(const sllist_t *lst)
{
	node_t *runner = NULL;
	size_t size = 0;
	
	assert(NULL != lst);
	
	runner = lst->head;	
	while (SLLEnd(lst) != runner)
	{
		runner = runner->next;
		++size;
	}
	
	return (size);
}

sllist_t *SLLAppend(sllist_t *src_lst, sllist_t *dest_lst)
{
	assert(src_lst != dest_lst);
	assert(NULL != src_lst);
	assert(NULL != dest_lst);
	
	if (1 == SLLIsEmpty(src_lst))
	{
		return dest_lst;
	}
	
	/* copy src next ptr and data ptr into dst tail */
	dest_lst->tail->next = src_lst->head->next;
	dest_lst->tail->data = src_lst->head->data;
	
	dest_lst->tail = src_lst->tail;
	
	/* update src->head pointers to be NULL (and to be an empty list). */
	src_lst->head->data = NULL;
	src_lst->head->next = NULL;
	src_lst->tail = src_lst->head;

	return dest_lst;
}
