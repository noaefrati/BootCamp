#ifndef __AVL_H_OL97_ILRD__
#define __AVL_H_OL97_ILRD__

/******************************************************************************
 * Header file Containing API Definition for AVL interface operations and     *
 * declarations.                                                              *
 *                                                                            *
 * Infinity Labs - OL97                                                       *
 ******************************************************************************/
 
/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h> /* size_t */
#include "dlist.h"
/******************************************************************************/
/***                               Typedfs                                  ***/
/******************************************************************************/

typedef struct avl avl_t;
typedef enum traversal
{
	IN_ORDER,
	PRE_ORDER,
	POST_ORDER
}traversal_t;

/*

Inside implementation file:
==========================

typedef struct node
{
	void *data;
	avl_node_t *children[2];
	int height;
}avl_node_t;

typedef enum direction
{
	LEFT,
	RIGHT
}direction_t;

struct avl
{
	avl_node_t *root;
	int (*cmp_func)(const void *data, const void *input);
};

*/
/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/

/**************************** Create and Destroy ******************************/

/*
 * Description: This function is used for Creating an empty AVL structure.
 * The compare function should return: 
 * return = 0 - when a perfect match is found,
 * return > 0 - when the first paramter is 'bigger' than the second, 
 * return < 0 - when the first paramter is 'smaller' than the second.
 * If cmp_func(a, b) < 0, then (a) should be positioned to the left of (b).
 * Return value: On success, the function returns pointer to the allocated  
 * AVL structure. On failure to allocate memory, NULL will be returned.
 * Time complexity: O(1).
 */
avl_t *AVLCreate(int (*cmp_func)(const void *data, const void *input));
 
/*
 * Description: This function is used for destroying a given AVL pointed
 * by tree (frees memory of all elements and the tree itself).
 * Return value: none.
 * Time complexity: O(n).
 */
void AVLDestroy(avl_t *tree);

/****************************** Insert and Remove *****************************/

/*
 * Description: This function is used for inserting new data into the a given 
 * AVL pointed by tree. The data will be inserted in the correct location
 * in a sorted manner, using the function provided by the user in AVLCreate.
 * If the function does not behave as instructed, the behaviour is undefined. 
 * Return value: 0 for success and 1 for failure.
 * Time complexity: Average: O(log n), Worst: O(log n). 
 */
int AVLInsert(avl_t *tree, const void *data);

/*
 * Description: This function is used for removing a given data from tree.
 * Only the given data is removed, not its sub-tree.
 * Return value: none.
 * Time complexity: Average: O(log n), Worst: O(log n). 
 */
void AVLRemove(avl_t *tree, const void *data);

/********************************* Basic Utility ******************************/

/*
 * Description: This function is used for getting the size of a given AVL,
 * pointed by tree (amount of elements).
 * Return value: This function returns the number of elements in the AVL  
 * pointed to by tree.
 * Time complexity: O(n).
 */
size_t AVLSize(const avl_t *tree);

/*
 * Description: This function is used for getting the height of a given AVL tree
 * pointed by tree (Height of root).
 * Return value: Height of root. If tree is empty height is -1.
 * Time complexity: O(1).
 */
int AVLHeight(const avl_t *tree);

/*
 * Description: This function returns whether the given AVL is empty.
 * Return value: 1 (true) if the size of AVL pointed by tree is 0,
 * 0 (false) otherwise.
 * Time complexity: O(1).
 */ 
int AVLIsEmpty(const avl_t *tree);

/*
 * Description: This function is used for iterating over the given
 * tree and performing an action on every node. 
 * The action user's action function should return 0 on success.
 * The function will call the passed action function on each node in
 * the tree. If one of the calls to the activation function fails (returns a 
 * non 0 value), the iteration stops.
 * Return value: This function returns 0 on success, 1 on failure.
 * Pay attention! If the value of the field by which the tree is sorted will be 
 * changed the whole list is compromised!

 * Time complexity: O(n).
 */
int AVLForEach(avl_t *tree, int (*action)(void *data, void *params),
									void *params, traversal_t traverse_method);
/*
 * Description: Traverse the given tree and search for an exact match to value.
 * The search is done using the comparison function which was provided
 * by the user in AVLCreate.
 * Return value: This function returns void pointer to data if found,
 * else return NULL;
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
void *AVLFind(const avl_t *tree, const void *value);

/******************************** Advanced ************************************/
int AVLMultiFind(dllist_t *return_list, avl_t *tree, const void *value,
                      int (*is_match)(const void *data, const void *against));
						
int AVLMultiRemove(dllist_t *return_list, avl_t *tree, const void *remove_key,
               int (*should_remove)(const void *data, const void *remove_key));
#endif /* __AVL_H_OL97_ILRD__ */

