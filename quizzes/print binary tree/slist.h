#ifndef __SLLIST_H_OL97_ILRD__
#define __SLLIST_H_OL97_ILRD__
/*******************************************************************************
 *
 * Definition of Singly Linked List ADT & its interface operations declarations
 *
 ******************************************************************************/

/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h>   /* size_t                                               */

/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/
typedef struct sllist sllist_t;
typedef struct node node_t;
typedef node_t* sllist_iter_t; 

/******************************************************************************/
/***                      Public functions declarations                     ***/
/******************************************************************************/
/*
 * Create an empty singly linked list structure.
 * If memory allocation fails the function will return NULL.
 * Time complexity: O(1).
 */
sllist_t *SLLCreate(void);

/*
 * Destroy a given Singly linked list (frees memory of all the elements 
 * inside the list and the memory for the list itself).
 * Time complexity: O(n).
 */
void SLLDestroy(sllist_t *lst);

/*
 * This function is used for inserting a value (element) before a given 
 * iterator. 
 * the given iter will be invalided because we change the data in it
 * return the iterator that hold the new data
 * if fail return end-iterator.
 * if iter is the end -iter , update the linked list 
 * Time complexity: O(1).
 */
sllist_iter_t SLLInsertBefore( sllist_t *lst ,sllist_iter_t iter, const void *data);

/*
 * This function is used for inserting a value as the last value (element).
 * Returns end -iter on failure or iterator for the new element on success.
 * Time complexity: O(1).
 */
sllist_iter_t SLLPushBack(sllist_t *lst, const void *data);

/*
 * This function is used for removing last element from the list (not the end -iter).
 * Pop on empty list will cause undefined behaviour
 * Time complexity: O(n).
 */
void SLLPopBack(sllist_t *lst);

/*
 * This function is used for searching the list for a specific value.
 * Return the first element holding it, if found, otherwise returns end -iter.
 * The is_match should return 0 when the values are equal and 1 otherwise.
 * Time complexity: O(n).
 */
sllist_iter_t SLLFind(const sllist_t *lst,
                   const void *value,
                   int (*is_match)(const void *one, const void *other));

/*
 * This function is used for removing an element - iter.
 * iter given will be invalided in function 
 * if iter is the end iterator -> undefined behaviour
 * Time complexity: O(1).
 */
void SLLRemove(sllist_t *lst, sllist_iter_t iter);

/*
 * This function Checks if a given list is empty or not.
 * Returns 1 on empty list & 0 on non empty list.
 * Time complexity: O(1).
 */
int SLLIsEmpty(const sllist_t *lst);

/*
 * This function sets data on a given iterator.
 * Returns 1 on error & 0 on success.
 * if iter is the end -iter -> undefined behaviour
 * Time complexity: O(1).
 */
int SLLSetData(sllist_iter_t iter, const void *data);

/*
 * This function gets pointer to data of a given iterator.
 * the data is compromised
 * Time complexity: O(1).
 */
void *SLLGetData(const sllist_iter_t iter);

/*
 * Return the next iter after a given iter, if no next iter, it returns end -iter.
 * Time complexity: O(1).
 */
sllist_iter_t SLLNext(const sllist_iter_t iter);

/*
 * Return the first element of the list, if the list is empty returns the end -iter.
 * Time complexity: O(1).
 */
sllist_iter_t SLLBegin(const sllist_t *lst);

/*
 * Return the last element of the list (the end -iter).
 * Time complexity: O(1).
 */
sllist_iter_t SLLEnd(const sllist_t *lst);

/*
 * Return if two iters that we have are the same one.
 * iters will we equal if their address is the same
 * 2 iters with the same data will not be equal 
 * Returns 1 if the same, 0 otherwise.
 * Time complexity: O(1).
 */
int SLLIsSameIter(const sllist_iter_t one, const sllist_iter_t other);

/*
 * The function receives a sllist and a range starting from start and ending
 * ending with end (inclusive), and action function which will be activated on
 * each element of the sllist in the range. If the action function encounters an
 * error while dealing with some element, it will return an error, in that case
 * ForEach will stop iteration and return the same error. if from > to behaviour
 * is undefined. 0 is used for success return status and shouldn't be used 
 * for any error code.
 * Time complexity: O(n).
 */
int SLLForEach(sllist_t *lst, 
                  sllist_iter_t from, 
                  sllist_iter_t to, 
                  int (*action)(void *data, void *params), void *params);

/* returns number of elements in the list 
* Time complexity: O(n).*/
size_t SLLSize(const sllist_t *lst);

/*
 * This function is used for appending src list to the tail of the dest list.
 * Returns dest list after src was appended.
 * Time complexity: O(1).
 */
sllist_t * SLLAppend(sllist_t *src_lst, sllist_t *dest_lst);

#endif   /* __SLLIST_H_OL97_ILRD__ */
