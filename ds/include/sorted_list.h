#ifndef __SORTED_LIST_H_OL97_ILRD__
#define __SORTED_LIST_H_OL97_ILRD__

/*******************************************************************************
 *
 * Header file Containing API Definitions for
 * Sorted Doubly Linked List ADT & its interface operations and declarations.
 *
 * Infinity Labs - OL97                                                      
 ******************************************************************************/
 
/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h> /* size_t */

#include "dlist.h"

/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/
typedef struct srtlst srtlst_t;

typedef struct srtlst_iter
{ 
	dllist_iter_t iter;
#ifndef NDEBUG		
	srtlst_t *list;
#endif		
}srtlst_iter_t;

/*
	Inside the implementation file:
	==============================
	
	struct srtlst 
	{
		dllist_t *list;
		int (*cmp_func)(const void *one, const void *other);
	};

*/


/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/
/*
 * Description: This function is used for Creating an empty SRTLST structure.
 * Return value: On success, the functions returns pointer to the alocated list 
 * structure. On failure to allocate memory, NULL will be returned.
 * The compare function should return: 
 *      return = 0 - when a perfect match is found,
 *      return > 0 - when the first paramter is 'bigger' than the second, 
 *      return < 0 - when the first paramter is 'smaller' than the second.
 * The list is sorted such that if compare(a,b) < 0, 
 * then a will appear before b in the list
 * (sort with ascending order).
 * If compare(a,b) = 0, the order of a and b in the list is arbitrary
 * (does not necessarily depend on the order that they were inserted).
 * Time complexity: O(1).
 */
srtlst_t *SRTLSTCreate(int (*cmp_func)(const void *one, const void *other));
 
/*
 * Description: This function is used for destroying a given SRTLST list pointed
 * by lst (frees memory of all elements and the list itself).
 * Return value: None.
 * Time complexity: O(n).
 */
void SRTLSTDestroy(srtlst_t *lst);
 
/*
 * Description: This function is used for getting the size of a given SRTLST 
 * list pointed by lst(amount of elements).
 * Return value: This function returns the number of elements in the SRTLST 
 * pointed to by lst.
 * Time complexity: O(n).
 */
size_t SRTLSTSize(const srtlst_t *lst);

/*
 * Description: This function returns whether the given SRTLST is empty.
 * Return value: 1 (true) if the size of SRTLST list pointed by lst is 0,
 * 0 (false) otherwise.
 * Time complexity: O(1).
 */ 
int SRTLSTIsEmpty(const srtlst_t *lst);

/*
 * Description: This function returns whether two given iterators.
 * (srtlst_iter_t) are the same.
 * Return value: 1 (true) if same, 0 (false) otherwise.
 * Time complexity: O(1).
 */ 
int SRTLSTIsSameIter(srtlst_iter_t one, srtlst_iter_t other);

/*
 * Description: This function is used for getting the next iterator 
 * (srtlst_iter_t) after the provided one.
 * Return value: The function will return the next iterator after the provided,
 * if the provided iterator is End-iter(Dummy), the function will return it.
 * Time complexity: O(1).
 */
srtlst_iter_t SRTLSTNext(srtlst_iter_t iter);
 
/*
 * Description: This function is used for getting the previous iterator 
 * (srtlst_iter_t) before the provided one.
 * Return value: The function will return the prev iterator before the provided,
 * if the provided iterator is the first valid iter (the first holds valid data)
 * the function will return it.
 * Time complexity: O(1).
 */
srtlst_iter_t SRTLSTPrev(srtlst_iter_t iter);

/*
 * Description: This function is used for getting the first valid iterator 
 * (srtlst_iter_t) of the SRTLST list pointed by lst.
 * valid iterator is first iterator which holding valid user data (not dummy).
 * Return value: The function will return first valid iterator.
 * Time complexity: O(1).
 */
srtlst_iter_t SRTLSTBegin(const srtlst_t *lst); 

/*
 * Description: This function is used for getting the last iterator 
 * (srtlst_iter_t) of the SRTLST list pointed by lst (The End-dummy).
 * Return value: The function will return End-iter of the given list.
 * Time complexity: O(1).
 */
srtlst_iter_t SRTLSTEnd(const srtlst_t *lst); 

/*
 * Description: This function is used for getting the data pointed by a given 
 * iterator (srtlst_iter_t).
 * Return value: The function will return pointer to the data, if provided
 * invalid iter (dummy), NULL will be returned.
 * Pay attention! the data is compromised, if the value of the field
 * by which the list is sorted will be changed the whole list is compromised!
 * Time complexity: O(1).
 */
void *SRTLSTGetData(srtlst_iter_t iter);

/*
 * Description: This function is used for inserting new data into the a given 
 * SRTLST list pointed by lst. The data will be inserted in the correct location
 * in a sorted manner.. 
 * If compare(a,b) = 0, the order of a and b in the list is arbitrary.
 * Return value: The function will return 1 on failure and 0 otherwise.
 * Time complexity: O(n).
 */
int SRTLSTInsert(srtlst_t *lst, const void *data);

/*
 * Description: This function is used for removing a given iterator 
 * (srtlst_iter_t).
 * UB: attempting to remove the end-iter.
 * Return value: None.
 * Time complexity: O(1).
 */
void SRTLSTRemove(srtlst_iter_t iter);

/*
 * Description: This function is used for removing last valid iterator from 
 * SRTLST list pointed by lst. 
 * UB: Trying to remove from an empty list.
 * Return value: None.
 * Time complexity: O(1).
 */
void SRTLSTPopBack(srtlst_t *lst);

/*
 * Description: This function is used for removing first valid iterator from 
 * SRTLST list pointed by lst. 
 * UB: Trying to remove from an empty list.
 * Return value: None.
 * Time complexity: O(1).
 */
void SRTLSTPopFront(srtlst_t *lst);

/*
 * Description: This function is used for iterating through the range given by
 * <from> (Inclusive) and <to> (Exclusive) Iterators (srtlst_iter_t).
 * The function will call the passed activation function on each iterator in
 * the range. If one of the calls to the activation function fails (returns a 
 * non 0 value), the iteration stops.
 * Return value: This function returns 0 on success, 1 on failure.
 * Pay attention! if the value of the field by which the list is sorted will be 
 * changed the whole list is compromised!
 * UB: 
 * 		In case <from> is larger then <to>.
 * 		if <from> and <to> aren't from the same list.
 * Time complexity: O(n).
 */
int SRTLSTForEach(srtlst_iter_t from, 
           		  srtlst_iter_t to,
               	  int (*action)(void *data, void *params),
               	  void *params);

/*
 * Description: This function is used for searching the range given by
 * <from> (Inclusive) and <to> (Exclusive) Iterators (srtlst_iter_t) for the 
 * provided value. The search is done using the comparison function which was
 * provided upon list creation by the user.
 * Return value: This function returns the found iterator (which contains the
 * desired value) on success, if the value isn't in the given range the function
 * will return <to> iterator.
 * UB: 
 * 		In case <from> is larger then <to>.
 * 		if <from> and <to> aren't from the same list.
 * Time complexity: O(n).
 */
srtlst_iter_t SRTLSTFind(const srtlst_t *lst,
                         srtlst_iter_t from, 
                         srtlst_iter_t to,
                         const void *value);

/*
 * Description: This function is used for searching the range given by
 * <from> (Inclusive) and <to> (Exclusive) Iterators (srtlst_iter_t) for the 
 * provided value. The search is done using the provided boolean search 
 * function. 
 * Return value: This function returns the found iterator (which contains the
 * desired value) on success, if the value isn't in the given range the function
 * will return <to> iterator.
 * UB: 
 * 		In case <from> is larger then <to>.
 * 		if <from> and <to> aren't from the same list.
 * Time complexity: O(n).
 */
srtlst_iter_t SRTLSTFindIf(srtlst_iter_t from,
                           srtlst_iter_t to,
                           int (*is_match)(const void *data, 
                                           const void *against),
                           const void *against);

/*
 * Description: This function is used for merging two given SRTLST lists pointed 
 * by lst1 and lst2.
 * 'src' will become an empty list. 'dest' will contain nodes from 'src' and 
 * 'dest'.
 * Warning: comparison function for 'src' and 'dest' must have the same 
 * comparison logic.
 * UB: lists are the same.
 * UB: comparison function logic not the same. 
 * Return value: none.
 * Time complexity: O(n).
 */
void SRTLSTMerge(srtlst_t *dest, srtlst_t *src);

#endif /* __SORTED_LIST_H_OL97_ILRD__ */
