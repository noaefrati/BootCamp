#ifndef __PRIORITY_QUEUE_H_OL97_ILRD__
#define __PRIORITY_QUEUE_H_OL97_ILRD__

/*******************************************************************************
 *
 * Header file Containing API Definitions for
 * Priority Queue ADT & its interface operations and declarations.
 * The Priority Queue implemented over heap.
 *
 * Infinity Labs - OL97                                                      
 ******************************************************************************/
 
/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h> /* size_t */

/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/
typedef struct pq pq_t;

/*
    Inside the implementation file:
    ==============================
    
    struct pq
    {
        heap_t *heap;
    };
*/

/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/
/*
 * Description: This function is used for Creating an empty PQ structure.
 * Return value: On success, the function returns pointer to the alocated queue 
 * structure. On failure to allocate memory, NULL will be returned.
 * The compare function which passed to the function should return: 
 *      = 0 		   - when (one - other = 0).
 *      > 0 (Positive) - when (one - other > 0).
 *      < 0 (Negative) - when (one - other < 0).
 * Time complexity: O(1).
 */
pq_t *PQCreate(int (*cmp_func)(const void *lhs, const void *rhs));
 
/*
 * Description: This function is used for destroying a given PQ pointed
 * by que (frees memory of all elements and the que itself).
 * Return value: None.
 * Time complexity: O(n).
 */
void PQDestroy(pq_t *que);
 
/*
 * Description: This function is used for getting the size of a given PQ 
 * pointed by que (amount of elements).
 * Return value: This function returns the number of elements in the PQ pointed 
 * to by que.
 * Time complexity: O(n).
 */
size_t PQSize(const pq_t *que);

/*
 * Description: This function returns whether the given PQ is empty.
 * Return value: 1 (true) if the size of PQ pointed by que is 0,
 * 0 (false) otherwise.
 * Time complexity: O(1).
 */ 
int PQIsEmpty(const pq_t *que);

/*
 * Description: This function is used for adding a value (new element) to the 
 * PQ pointed by que. The new element will be inserted in the 
 * correct location according to it's priority.
 * Return value: The function will return 1 on failure and 0 otherwise.
 * Time complexity: O(n).
 */
int PQEnqueue(pq_t *que, const void *data);
 
/*
 * Description: This function is used for getting a value from the front of the 
 * PQ pointed by que and removing the element holding it.
 * Return value: Returns the value of the element at the front of the queue.
 * UB: Dequeuing empty queue.
 * Time complexity: O(1).
 */
void *PQDequeue(pq_t *que);

/*
 * Description: This function is used for getting a value from the front of the 
 * PQ pointed by que.
 * Return value: On success returns the value itself, on failure returns NULL.
 * UB: Peeking into an empty queue.
 * Time complexity: O(1).
 */
void *PQPeek(pq_t *que);

/*
 * Description: This function is used for erasing the first element in PQ 
 * pointed by que in which the data is equal to the provided argument 
 * val_to_erase.
 * Return value: The function will return the value of the item that will be 
 * erased if it's found in the queue, if no item with the data equal to
 * val_to_erase was found the function will return NULL.
 * Time complexity: O(n).
 */
void *PQErase(pq_t *que, 
              int (*is_match)(const void *data, const void *to_erase),
              const void *to_erase);

/*
 * Description: This function is used for erasing all elements from a given PQ 
 * pointed by que. The queue will remain empty.
 * Note: USE WITH CAUTION: ALL DATA IN LIST WILL BE LOST!
 * Return value: None.
 * Time complexity: O(n).
 */
void PQClear(pq_t *que);

#endif /* __PRIORITY_QUEUE_H_OL97_ILRD__ */
