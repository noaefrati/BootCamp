#ifndef __BST_H_OL97_ILRD__
#define __BST_H_OL97_ILRD__

/******************************************************************************
 * Header file Containing API Definition for BST interface operations and     *
 * declarations.                                                              *
 *                                                                            *
 * Infinity Labs - OL97                                                       *
 ******************************************************************************/
 
/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/

#include <stddef.h> /* size_t */

/******************************************************************************/
/***                               Typedfs                                  ***/
/******************************************************************************/

typedef struct bst bst_t;
typedef struct node node_t;
typedef node_t* bst_iter_t;

/*

Inside implementation file:
==========================

struct node
{
	void *data;
	node_t *parent;
	node_t *right;
	node_t *left;
};

struct bst
{
	node_t *XXXXXXX;
	int (*cmp_func)(const void *data, const void *input);
};

*/
/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/

/**************************** Create and Destroy ******************************/

/*
 * Description: This function is used for Creating an empty BST structure.
 * The compare function should return: 
 * return = 0 - when a perfect match is found,
 * return > 0 - when the first paramter is 'bigger' than the second, 
 * return < 0 - when the first paramter is 'smaller' than the second.
 * If cmp_func(a, b) < 0, then (a) should be positioned to the left of (b).
 * Return value: On success, the function returns pointer to the allocated  
 * BST structure. On failure to allocate memory, NULL will be returned.
 * Time complexity: O(1).
 */
bst_t *BSTCreate(int (*cmp_func)(const void *data, const void *input));
 
/*
 * Description: This function is used for destroying a given BST pointed
 * by tree (frees memory of all elements and the queue itself).
 * This invalidates all iterators in the user's posession.
 * Return value: none.
 * Time complexity: O(n).
 */
void BSTDestroy(bst_t *tree);

/****************************** Insert and Remove *****************************/

/*
 * Description: This function is used for inserting new data into the a given 
 * BST pointed by tree. The data will be inserted in the correct location
 * in a sorted manner, using the function provided by the user in BSTCreate.
 * If the function does not behave as instructed, the behaviour is undefined. 
 * Return value: Iterator to the newly inserted data. If insertion fails,
 * return the end-iterator.
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
bst_iter_t BSTInsert(bst_t *tree, const void *data);

/*
 * Description: This function is used for removing a given iterator.
 * Only the given iterator is removed, not its sub-tree.
 * Return value: Nothing.
 * UB: - attempting to remove the end iter.
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
void BSTRemove(bst_iter_t iter);

/********************************* Basic Utility ******************************/

/*
 * Description: This function is used for getting the size of a given BST.
 * pointed by tree (amount of elements).
 * Return value: This function returns the number of elements in the BST  
 * pointed to by tree.
 * Time complexity: O(n).
 */
size_t BSTSize(const bst_t *tree);

/*
 * Description: This function returns whether the given BST is empty.
 * Return value: 1 (true) if the size of BST pointed by tree is 0,
 * 0 (false) otherwise.
 * Time complexity: O(1).
 */ 
int BSTIsEmpty(const bst_t *tree);

/*
 * Description: This function returns whether two given iterators,
 * (bst_iter_t) are the same.
 * Return value: 1 (true) if same, 0 (false) otherwise.
 * Time complexity: O(1).
 */
int BSTIsSameIter(bst_iter_t one, bst_iter_t other);

/*
 * Description: This function is used for getting the next iterator 
 * (bst_iter_t) after the provided one.
 * Return value: The function will return the next iterator after the provided.
 * Calling BSTNext(BSTEnd(tree)) will yield itself.
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
bst_iter_t BSTNext(bst_iter_t iter);
 
/*
 * Description: This function is used for getting the previous iterator 
 * (bst_iter_t) before the provided one.
 * Return value: The function will return the prev iterator before the provided.
 * If the provided iterator is the first iter, the return itself.
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
bst_iter_t BSTPrev(bst_iter_t iter);

/*
 * Description: This function is used for getting the iterator holding minimal 
 * data (bst_iter_t) of the BST pointed by tree.
 * Return value: The function will return iterator holding minimal data.
 * If the tree is empty, return the end iterator.
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
bst_iter_t BSTBegin(const bst_t *tree); 

/*
 * Description: This function is used for getting the last iterator 
 * (bst_iter_t) of the BST.
 * Return value: A non-valid iterator marking the end of the tree.
 * Calling BSTPrev(BSTEnd(tree)) will yield the last valid iterator.
 * Time complexity: O(1).
 */
bst_iter_t BSTEnd(const bst_t *tree); 

/*
 * Description: This function is used for getting the data pointed by a given 
 * iterator (bst_iter_t).
 * Return value: The function will return pointer to the data, if provided.
 * Calling this function on an end iterator will reuturn NULL.
 * Calling this function on an iterator that has been removed is undefined.
 * The user should not change the data. If the data is changed, it will not
 * be resorted.
 * Time complexity: O(1).
 */
void *BSTGetData(bst_iter_t iter);

/******************************** Advanced ************************************/

/*
 * Description: This function is used for iterating over the given
 * range and performing an action on every node. 
 * The action user's action function should return 0 on success.
 * The function will call the passed action function on each iterator in
 * the range. If one of the calls to the activation function fails (returns a 
 * non 0 value), the iteration stops.
 * Return value: This function returns 0 on success, 1 on failure.
 * Pay attention! If the value of the field by which the tree is sorted will be 
 * changed the whole list is compromised!
 * UB: - if from is smaller than to.
 *     - if from and to are not of the same tree.
 * Time complexity: O(n).
 */
int BSTForEach(bst_iter_t from,
               bst_iter_t to,
               int (*action)(void *data, void *params),
               void *params);

/*
 * Description: Traverse the given tree and search for an exact match to value.
 * The search is done using the comparison function which was provided
 * by the user in BSTCreate.
 * Return value: This function returns the found iterator (which contains the
 * desired value) on success, if no match was found return the end iterator.
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
bst_iter_t BSTFind(const bst_t *tree,
                   const void *value);

#endif /* __BST_H_OL97_ILRD__ */
