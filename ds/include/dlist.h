/*****************************************************************************
 * Description: Header file for Doubly Linked List implementation            *
 * Authors: Carolina, Oriel, Ronny (Gal helped)                               *
 *                                                                           *
 * Infinity Labs - OL97                                                      *
 *****************************************************************************/
 
#ifndef __DLIST_H_OL97_ILRD__
#define __DLIST_H_OL97_ILRD__

#include <stddef.h> /* size_t */

/* Structure Declerations */
typedef struct dllist dllist_t;
typedef struct node node_t;
typedef node_t* dllist_iter_t;

/*
	Inside the implementation file:
	==============================
	struct dllist 
	{
		struct node head;
		struct node tail;
	} ;
	
	struct node
	{ 
		void *data;
		struct node *next;
		struct node *prev;
	} ;
*/


/******************************************************************************/
/***                          Function Declarations                         ***/
/******************************************************************************/

/************************** Creation and Desturction **************************/

/*
 * Create an empty DLL.
 * Return ptr to new list if creation succeeded; NULL if creation failed.
 * O(1)
 */
dllist_t *DLLCreate(void);

/*
 * Destroy given DLL.
 * Return nothing.
 * O(n)
 */
void DLLDestroy(dllist_t *lst);

/****************************** Basic Utilities *******************************/

/*
 * Retrieve current number of elements in given list.
 * Return list size.
 * O(n)
 */
size_t DLLSize(const dllist_t *lst);

/*
 * Boolean: check whether given list contains nothing.
 * Return 1 if empty; 0 if non-empty.
 * O(1)
 */
int DLLIsEmpty(const dllist_t *lst);

/*
 * Boolean: check whether two given iters are the same.
 * Return 1 if they are the same; 0 otherwise.
 * O(1)
 */
int DLLIsSameIter(const dllist_iter_t one, const dllist_iter_t other);

/*
 * Find iter after given iter.
 * Return iter of next iter; itself if given iter is the end iter.
 * O(1)
 */
dllist_iter_t DLLNext(const dllist_iter_t iter);
 
/*
 * Find iter before given iter.
 * Return iter of previous iter; return itself if iter is first valid iter.
 * O(1)
 */
dllist_iter_t DLLPrev(const dllist_iter_t iter);

/*
 * Return iter of first valid iter.
 * Returns dummy (end iter) if list is empty.       
 * O(1)
 */
dllist_iter_t DLLBegin(const dllist_t *lst); 

/*
 * Retrieve end iter.
 * Return iter of end iter. 
 * O(1)
 */
dllist_iter_t DLLEnd(const dllist_t *lst); 

/****************************** Get and Set Data ******************************/

/*
 * Retrieve data held by iter, given by iterator.
 * Return ptr to data in iter; NULL if iter is invalid or hold no data.
 * O(1)
 */
void *DLLGetData(const dllist_iter_t iter);

/*
 * Set data held by iter, given by an iterator, to new data source.
 * Return nothing.
 * O(1)
 */
void DLLSetData(dllist_iter_t iter, const void *data);


/*************************** Add and Remove Element ***************************/

/*
 * Insert new iter with given data before given iter, in given list.
 * if fail return 1 otherwise return 0.
 * O(1)
 */
int DLLInsertBefore(dllist_iter_t iter, const void *data);

/*
 * Insert new iter at the end iter of the given list, with new given data.
 * Return iter of new iter.
 * if fail return end iter.
 * O(1)
 */
dllist_iter_t DLLPushBack(dllist_t *lst, const void *data);

/*
 * Insert new iter at the head end of a given list, with new given data.
 * Return iter of new iter.
 * if fail return end iter.
 * O(1)
 */
dllist_iter_t DLLPushFront(dllist_t *lst, const void *data);

/*
 * Remove given iter from given list.
 * Return nothing.
 * This operation invalidates the original iter.
 * UB: attempting to remove end iter
 */
void DLLRemove(dllist_iter_t iter);

/*
 * Remove a iter from the end iter of a given list.
 * Return nothing.
 * UB: if list is empty.
 * O(1)
 */
void DLLPopBack(dllist_t *lst);

/*
 * Remove iter from the head end of a given list.
 * Return nothing.
 * UB: if list is empty.
 * O(1)
 */
void DLLPopFront(dllist_t *lst);

/***************************** Advanced Utilities *****************************/

/*
 * Perform a given function operation on each iter in range between two iters (not including "to").
 * If function uses no parameters, input NULL.
 * Return 0 if success; 1 if failure. (also "action" return 0 if success)
 * O(n)
 */
int DLLForEach(dllist_iter_t from, 
               dllist_iter_t to,
               int (*action)(void *data, void *params),
               void *params);

/*
 * Find the first iter matched by a given match function,
 * in the range of from to to (not including).
 * is_match is Boolean: Returns 1 when a match is found, 0 otherwise.
 * Return iter of first iter found; return "to" iter if value not found.
 * O(n)
 */
dllist_iter_t DLLFind(const dllist_iter_t from,
                      const dllist_iter_t to,
                      const void *value,
                      int (*is_match)(const void *data, const void *against));

/*
 * Find all iters in given list, matched by a given match function.
 * Matched iters are pushed back to dest.
 * is_match is Boolean: Returns 1 when a match is found, 0 otherwise.
 * Return 0 if success; 1 if failure.
 * Failure may occure due to failure of pushback.
 * O(n)
 */
int DLLMultiFind(const dllist_iter_t from,
                 const dllist_iter_t to,
                 dllist_t *dest,
				 const void *value,
                 int (*is_match)(const void *data, const void *against));

/*
 * Move iters in range between from and to (not including) from one list,
 * before target iter (could be same list).
 * Return nothing.
 * UB: from >= to
 *     from and to are from different lists 
 * 		target cannot be between from and to (including from and to)
 * O(1)
 */                       
void DLLSplice(dllist_iter_t from,
               dllist_iter_t to,
               dllist_iter_t target);

#endif /* __DLIST_H_OL97_ILRD__ */
/* =^._.^= */

