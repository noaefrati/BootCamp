/****************************************************************************** 
 * Description: Implement Sorted linked list                                  *
 * Author: Noa Efrati                                                         *
 * Reviewer: Gal Dahan                                                        *
 * Date: 2.12.20                                                              *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/
/******************************************************************************/
#include <stdlib.h>                     /* malloc, free                       */
#include <assert.h>                     /* assert                             */
#include "sorted_list.h"                /* sorted list functions              */
#include "dlist.h"                      /* doubly list functions              */
/******************************************************************************/
/******************************************************************************/
struct srtlst 
{
	dllist_t *list;
	int (*cmp_func)(const void *one, const void *other);
};

/******************************************************************************/
/****************************Utility Functions*********************************/

/* static function to update debug field                                      */
static srtlst_iter_t CreateIter(const srtlst_t *lst);

/* 
 * Search in dest, from the current dest_runner untill:
 * (1) found the first node which is bigger than the value of
 * the current src_runner. 
 * OR
 * (2) dest_runner got to tail
*/
static srtlst_iter_t FindForSplice(const srtlst_t *lst,
                                  srtlst_iter_t from, 
                                  const void *value);
                                  
/******************************************************************************/                                 
/******************************************************************************/

srtlst_t *SRTLSTCreate(int (*cmp_func)(const void *one, const void *other))
{
	srtlst_t *srt_lst = NULL;
	
	assert(NULL != cmp_func);
	
	srt_lst = (srtlst_t *) malloc(sizeof(srtlst_t));
	if (NULL != srt_lst)
	{	
		if (!(srt_lst->list = (dllist_t *)DLLCreate()))
		{
			free(srt_lst); srt_lst = NULL;
			return NULL;
		}
		srt_lst->cmp_func = cmp_func;	
	}
	return srt_lst;
}

void SRTLSTDestroy(srtlst_t *lst)
{
	assert(NULL != lst);
	
	DLLDestroy(lst->list);
	free(lst); lst = NULL;
}

size_t SRTLSTSize(const srtlst_t *lst)
{
	assert(NULL != lst);
	
	return (size_t)DLLSize(lst->list);
}

int SRTLSTIsEmpty(const srtlst_t *lst)
{
	assert(NULL != lst);
	
	return DLLIsEmpty(lst->list);
}

int SRTLSTIsSameIter(srtlst_iter_t one, srtlst_iter_t other)
{
	assert(NULL != one.iter);
	assert(NULL != other.iter);
	
	return DLLIsSameIter(one.iter, other.iter);
}

srtlst_iter_t SRTLSTNext(srtlst_iter_t iter)
{
	assert(NULL != iter.iter);
	
	iter.iter = DLLNext(iter.iter);
	
	return iter;
}
 
srtlst_iter_t SRTLSTPrev(srtlst_iter_t iter)
{
	assert(NULL != iter.iter);
	
	iter.iter = DLLPrev(iter.iter);
	
	return iter;
}

srtlst_iter_t SRTLSTBegin(const srtlst_t *lst)
{
	srtlst_iter_t iter;
	
	assert(NULL != lst);
	
	iter = CreateIter(lst);
	iter.iter = DLLBegin(lst->list);
	
	return iter;
} 

srtlst_iter_t SRTLSTEnd(const srtlst_t *lst)
{
	srtlst_iter_t iter ;
	
	assert(NULL != lst);
	
	iter = CreateIter(lst);
	iter.iter = DLLEnd(lst->list);
	
	return iter;
}

void *SRTLSTGetData(srtlst_iter_t iter)
{
	assert(NULL != iter.iter);

	return DLLGetData(iter.iter);
}

int SRTLSTInsert(srtlst_t *lst, const void *data)
{
	srtlst_iter_t iter;
	
	assert(NULL != lst->list);
	assert(NULL != data);
	
	iter = SRTLSTBegin(lst);	
	
	for (; !SRTLSTIsSameIter(SRTLSTEnd(lst), iter) &&
		    0 >= lst->cmp_func(SRTLSTGetData(iter), data);
			iter = SRTLSTNext(iter))
	{
		/* empty */
	}
	
	return DLLInsertBefore(iter.iter, data);
}

void SRTLSTRemove(srtlst_iter_t iter)
{
	assert(NULL != iter.iter);
	
	DLLRemove(iter.iter);
}

void SRTLSTPopBack(srtlst_t *lst)
{
	assert(NULL != lst->list);
	
	DLLPopBack(lst->list);
}

void SRTLSTPopFront(srtlst_t *lst)
{
	assert(NULL != lst->list);
	
	DLLPopFront(lst->list);
}

int SRTLSTForEach(srtlst_iter_t from, 
           		  srtlst_iter_t to,
               	  int (*action)(void *data, void *params),
               	  void *params)
{
	assert(NULL != from.iter);
	assert(NULL != to.iter);
	assert(NULL != action);
	assert (from.list == to.list);	
	
	return DLLForEach(from.iter, to.iter, action, params);
}

srtlst_iter_t SRTLSTFind(const srtlst_t *lst,
                         srtlst_iter_t from, 
                         srtlst_iter_t to,
                         const void *value)
{
	int result = 0;
	
	assert(NULL != lst);
	assert (from.list == to.list);	
	assert(NULL != from.iter);
	assert(NULL != to.iter);
	assert(NULL != value);
	
	
	for (; !SRTLSTIsSameIter(to, from) &&
		    0 > (result = lst->cmp_func(SRTLSTGetData(from), value));
			from = SRTLSTNext(from))
	{
		/* empty */
	}

	return (!result) ? (from) : (to);
}

srtlst_iter_t SRTLSTFindIf(srtlst_iter_t from,
                           srtlst_iter_t to,
                           int (*is_match)(const void *data, 
                                           const void *against),
                           const void *against)
{
	assert(NULL != from.iter);
	assert(NULL != to.iter);
	assert (from.list == to.list);	
	assert(NULL != against);
	assert(NULL != is_match);
	
	to.iter = DLLFind(from.iter, to.iter, against, is_match);
	
	return to;
}

void SRTLSTMerge(srtlst_t *dest, srtlst_t *src)
{
	srtlst_iter_t src_runner = {NULL};
	srtlst_iter_t to = {NULL};
	srtlst_iter_t dest_runner = {NULL};
	srtlst_iter_t src_tail = {NULL};
	srtlst_iter_t dest_tail = {NULL};
	
	assert(NULL != dest);
	assert(NULL != src);
		
	src_runner = SRTLSTBegin(src);
	dest_runner = SRTLSTBegin(dest);	
	src_tail = SRTLSTEnd(src);
	dest_tail = SRTLSTEnd(dest);
	
	while (!SRTLSTIsSameIter(src_runner, src_tail) &&
		   !SRTLSTIsSameIter(dest_runner, dest_tail))
	{
				
		dest_runner = FindForSplice(dest,
									dest_runner,
									SRTLSTGetData(src_runner));
				
		to = SRTLSTNext(src_runner);
		DLLSplice(src_runner.iter, to.iter, dest_runner.iter);
		src_runner= to;
	}	
	
	/* if src is not empty, splice the rest of it */
	if (!SRTLSTIsEmpty(src))
	{
		DLLSplice(src_runner.iter, src_tail.iter, dest_runner.iter);
	}		        
}

/******************************************************************************/
static srtlst_iter_t CreateIter(const srtlst_t *lst)
{
	srtlst_iter_t iter;
	
	assert(NULL != lst);
	
	iter.iter = NULL; 
	
	#ifndef NDEBUG 
	iter.list = (srtlst_t *)lst;
	#else
	(void)lst;
	#endif
	
	return iter;	
}

/******************************************************************************/
static srtlst_iter_t FindForSplice(const srtlst_t *lst,
                                  srtlst_iter_t from, 
                                  const void *value)
{
	srtlst_iter_t runner;
	
	assert(NULL != lst);
	assert(NULL != from.iter);
	assert(NULL != value);
	
	runner = from;
	
	for(; !SRTLSTIsSameIter(runner, SRTLSTEnd(lst)) &&
	      0 > lst->cmp_func(SRTLSTGetData(runner), value);
	      runner = SRTLSTNext(runner))
	      {
	      	/* empty */
	      }
	
	return runner;
}
/******************************************************************************/
