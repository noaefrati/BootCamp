#ifndef __QUEUE_H_OL97_ILRD__
#define __QUEUE_H_OL97_ILRD__
/*******************************************************************************
 *
 * Definition of Queue ADT & its interface operations declarations
 *
 ******************************************************************************/

/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h>   /* size_t                                               */

/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/
typedef struct queue queue_t;

/*
	Inside the implementation file:
	==============================
	should include slist.h and be compiled with the slist.c as well.
	
	struct queue
	{
		sllist_t *list;
	};
*/

/******************************************************************************/
/***                      Public functions declarations                     ***/
/******************************************************************************/
/*
 * Create an empty queue structure.
 * If memory allocation fails the function will return NULL.
 * Time complexity: O(1).
 */
queue_t *QCreate(void);

/*
 * Destroy a given queue (frees memory of all the elements of the queue 
 * and the memory of the queue itself.
 * If queue argument is NULL, behaviour is undefined.
 * Time complexity: O(n).
 */
void QDestroy(queue_t *queue);

/*
 * This function is used for adding a value (new element) to the back 
 * of the queue. On success returns 0 and on failure returns 1.
 * If queue argument is NULL, behaviour is undefined.
 * Time complexity: O(1).
 */
int QEnqueue(queue_t *queue, const void *value);

/*
 * This function is used for getting a value from the front of the queue. 
 * On success returns the value itself, on failure returns NULL.
 * It is the user's responsibility to make sure that the value is really 0, 
 * and it didn't return 0 because the queue was empty.
 * If queue argument is NULL, behaviour is undefined.
 * Time complexity: O(1).
 */
void *QDequeue(queue_t *queue);

/*
 * This function is used for checking if the queue is empty. 
 * returns 1 if the queue is empty, otherwise 0.
 * If queue argument is NULL, behaviour is undefined.
 * Time complexity: O(1).
 */
int QIsEmpty(const queue_t *queue);

/*
 * This function is used for checking the amount of elements in the queue. 
 * If queue argument is NULL, behaviour is undefined.
 * Time complexity: O(n).
 */
size_t QSize(const queue_t *queue);

/*
 * Returns the value on the element on the front of the queue, without 
 * dequeueing it. If the queue is empty, return NULL; It is the user's 
 * responsibility to make sure that the value is really 0, and it didn't
 * return 0 because the queue was empty.
 * If queue argument is NULL, behaviour is undefined.
 * Time complexity: O(1).
 */
void *QPeek(const queue_t *queue);

/*
 * This function is used for appending src queue to the back of the dest queue.
 * Returns dest queue after src was appended. src becomes and empty queue.
 * If either of the queue arguments is NULL, Or if src = dest behaviour is 
 * undefined. 
 * Time complexity: O(1).
 */
queue_t *QAppend(queue_t *src_q, queue_t *dest_q);

#endif   /* __QUEUE_H_OL97_ILRD__ */
