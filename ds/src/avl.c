/******************************************************************************* 
 * Description: Implemention of AVL                                            *
 * Author: Noa Efrati                                                          *
 * Reviewer: David Horovitz                                                    *
 * Date: 31.12.20                                                              *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/

#include <stdlib.h>      /* malloc, free                                      */
#include <assert.h>      /* assert                                            */
#include "avl.h"         /* avl api                                           */

#define FREE(node) free(node); node = NULL;
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define NUM_OF_ORDERS 3

/******************************************************************************/
/***                         structs & typedef                              ***/
/******************************************************************************/

typedef struct node
{
	void *data;
	struct node *children[2];
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

typedef int (*action_t)(void *data, void *params);
typedef int (*traversal_function_t)(avl_node_t *root, action_t, void *params);

traversal_function_t lut_traversal[NUM_OF_ORDERS];
/******************************************************************************/
/***                         static functions                               ***/
/******************************************************************************/
static void InitTraversalLUT(void);

static int IsLeaf(avl_node_t *node);	

static int GetHeight(avl_node_t *node);
static int GetBalance(avl_node_t *node);
static avl_node_t *GetChild(avl_node_t *node, direction_t side);

static void SetRotation(avl_node_t *node);
static void LeftRotation(avl_node_t *node);
static void RightRotation(avl_node_t *node);
static void UpdateHeight(avl_node_t *tree_node);

static int HasRightChild(avl_node_t *node);
static int HasLeftChild(avl_node_t * node);

static avl_node_t *FindSuccessor(avl_node_t *node);
static void SwapData(avl_node_t *one, avl_node_t *other);	
static avl_node_t *FindMostLeftOrRight(avl_node_t *node, direction_t side);

static avl_node_t *CreateNodeImp(const void *data);

static void DestroyPostorderImpl(avl_node_t *node);

static int IncreamentSizeBy1(void *data, void *size);
 
static int AVLInsertImpl(const avl_t *tree, avl_node_t *node, void *data);

static void AVLRemoveImpl(avl_t *tree,
						  avl_node_t *parent,
						  direction_t direction,
						  avl_node_t *node,
						  const void *data);

static void RemoveLeaf(avl_t *tree, 
					   avl_node_t *parent,
					   avl_node_t *node,
					   direction_t direction);

static int PreOrder(avl_node_t *root,
						   int (*action)(void *data, void *params),
						   void *params);

static int InOrder(avl_node_t *root,
                          int (*action)(void *data, void *params),
						  void *params);

static int PostOrder(avl_node_t *root,
                          int (*action)(void *data, void *params),
						  void *params);

static avl_node_t *AVLFindImpl(avl_node_t *tree_node,
						 const void *value,
						 int (*cmp_func)(const void *data, const void *input));			   					
/******************************************************************************/
/***                                                                        ***/
/**************************** Create and Destroy ******************************/

avl_t *AVLCreate(int (*cmp_func)(const void *data, const void *input))
{
	avl_t *new_tree = NULL;
	
	assert(NULL != cmp_func);
	
	new_tree = (avl_t *) malloc(sizeof(avl_t));
	
	if (NULL != new_tree)
	{
		new_tree->root = NULL;
		new_tree->cmp_func = cmp_func;
		InitTraversalLUT();

	}		
		return new_tree;	
}
 

/*
 * Destroy in Post-Order meanining : from leaves up, 
 * till leaf is reached on every subtree, while starting from left 
 */
void AVLDestroy(avl_t *tree)
{
	assert(tree);
	
	DestroyPostorderImpl(tree->root);
	tree->root = NULL;
	FREE(tree);
	
}

/****************************** Insert and Remove *****************************/

int AVLInsert(avl_t *tree, const void *data)
{
 	int ret_val = 0;
 	
 	assert(tree);
 	 	
 	/* when tree is empty- the first node to be the root */
 	if(1 == AVLIsEmpty(tree))
	{
		tree->root =  CreateNodeImp((void *)data);
			
		if (NULL == tree->root)
		{
			ret_val = 1;
		}
	}	
	else if (1 == AVLInsertImpl(tree, tree->root, (void *)data))
	{
		ret_val = 1; /* 1 means AVLInsertImpl failed*/
	}
	
   return  ret_val;   
}                                                

void AVLRemove(avl_t *tree, const void *data)
{
	assert(tree);
	assert(data);
	
	if (!AVLIsEmpty(tree))
	{
		AVLRemoveImpl(tree, NULL, 0, tree->root, data);
		return;
	}
}

/********************************* Basic Utility ******************************/

size_t AVLSize(const avl_t *tree)
{	
	size_t size = 0;
	assert(tree);
	
	AVLForEach((avl_t *)tree, IncreamentSizeBy1, &size, IN_ORDER);

	return size;
}

int AVLHeight(const avl_t *tree)
{
	assert(NULL != tree);	
	
	if (AVLIsEmpty(tree))
	{
		return (-1);
	}
	return (tree->root->height);
}

int AVLIsEmpty(const avl_t *tree)
{
	assert(tree);
	
	return (NULL == tree->root);
}

int AVLForEach(avl_t *tree, int (*action)(void *data, void *params),
									void *params, traversal_t traverse_method)
{
	assert(tree);
    assert(action);
   
	return lut_traversal[traverse_method](tree->root, action, params);	
}

void *AVLFind(const avl_t *tree, const void *value)
{
	avl_node_t *place_to_find = NULL;
	 
	assert(tree);
	
	place_to_find = AVLFindImpl(tree->root, value, tree->cmp_func);
	
	return (NULL == place_to_find) ? (NULL) : (place_to_find->data);
}



/******************************** Advanced ************************************/
int AVLMultiFind(dllist_t *return_list, avl_t *tree, const void *value,
                      int (*is_match)(const void *data, const void *against));
						
int AVLMultiRemove(dllist_t *return_list, avl_t *tree, const void *remove_key,
               int (*should_remove)(const void *data, const void *remove_key));
                      
/************************ Static Function Defenition **************************/                    

static void InitTraversalLUT(void)
{
	lut_traversal[IN_ORDER] = &InOrder;
	lut_traversal[PRE_ORDER] = &PreOrder;
	lut_traversal[POST_ORDER] = &PostOrder;
}

static int PostOrder(avl_node_t *root,
                          int (*action)(void *data, void *params),
						  void *params)
{
	assert(action);
	
	if (NULL == root)
	{
		return (0); /*success*/
	}
	
	return (0 != PostOrder(root->children[LEFT], action, params)) ||
		   (0 != PostOrder(root->children[RIGHT], action, params)) ||
		   (0 != action(root->data, params));
}		
static int PreOrder(avl_node_t *root,
						   int (*action)(void *data, void *params),
						   void *params)
{
	assert(action);
	
	if (NULL == root)
	{
		return (0); /*success*/
	}
	
	return (0 != action(root->data, params)) ||
		   (0 != PreOrder(root->children[LEFT], action, params)) ||
		   (0 != PreOrder(root->children[RIGHT], action, params));
}
static int InOrder(avl_node_t *root,
                          int (*action)(void *data, void *params),
						  void *params)
{
	assert(action);
	
	if (NULL == root)
	{
		return (0); /*success*/
	}
	
	return (0 != InOrder(root->children[LEFT], action, params)) ||
		   (0 != action(root->data, params)) ||
		   (0 != InOrder(root->children[RIGHT], action, params));
}	
static int IncreamentSizeBy1(void *data, void *size)
{
	assert(size);
	
	(void)data;
	
	++(*(size_t *)size);
	
	return (0);
}
static void DestroyPostorderImpl(avl_node_t *node)
{
	/*CALL recursivly to DestroyPostorder:*/
	/*first to the left subtree of the root, and second to the right subtree*/
	
	if (NULL != node)
	{
		DestroyPostorderImpl(node->children[LEFT]);
		DestroyPostorderImpl(node->children[RIGHT]);
		free(node);
	}
		
	
}
static node_t *CreateNodeImp(const void *data)
{
	avl_node_t *new_node = NULL;
	
	assert(data);
	
	new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	
	if (NULL != new_node)
	{
		new_node->data = (void *)data;
		new_node->children[LEFT] = NULL;
		new_node->children[RIGHT] = NULL;
		new_node->height = 0;
	}
	
	return new_node;	
}

static void AVLRemoveImpl(avl_t *tree, 
						  avl_node_t *parent,
                          direction_t direction, 
                          avl_node_t *node,
                          const void *data)

{
	/* if found a match: then */
	if (0 == tree->cmp_func(node->data, data))
	{
		if (IsLeaf(node))
		{
			RemoveLeaf(tree, parent, node, direction);
			return;		
		}
		else if(HasRightChild(node))
		{
			SwapData(node, FindSuccessor(node));
			AVLRemoveImpl(tree, node, RIGHT, node->children[RIGHT], data);			
		}
		else
		{
			SwapData(node, FindSuccessor(node));
			AVLRemoveImpl(tree, node, LEFT, node->children[LEFT], data);
		}
	}
	else if(0 < tree->cmp_func(node->data, data) && HasLeftChild(node))
	{
		AVLRemoveImpl(tree, node, LEFT, node->children[LEFT], data);

	}
	else if(0 > tree->cmp_func(node->data, data) && HasRightChild(node))
	{
			AVLRemoveImpl(tree, node, RIGHT, node->children[RIGHT], data);		
	}
	
	UpdateHeight(node);
	SetRotation(node);
}
static int AVLInsertImpl(const avl_t *tree, avl_node_t *node, void *data)
{
	direction_t side = 0 < tree->cmp_func(node->data, data) ? LEFT : RIGHT;
	
	/*node has no child in this side*/
	if (NULL == GetChild(node, side)) 
	{
		node->children[side] = CreateNodeImp(data);
		
		if (NULL == node->children[side])
		{
			return (1); /* allocation failed */
		}
		
		UpdateHeight(node);
	}
	else
	{
		if (1 == AVLInsertImpl(tree, GetChild(node, side), data))
		{
			return (1); 
		}
		
		UpdateHeight(node);
		SetRotation(node);
	}
	
	return (0);
}
static avl_node_t *AVLFindImpl(avl_node_t *tree_node,
						 const void *value,
						 int (*cmp_func)(const void *data, const void *input))
{
	/* when the root==NULL means data not found.
	* when the cmp_func return 0 means that the data has found 
	* Both cases return tree_node*/ 
	if (NULL == tree_node || 0 == cmp_func(tree_node->data, value))
	{
		return tree_node;
	}
	else if (0 < cmp_func(tree_node->data, value))
	{
		tree_node = AVLFindImpl(tree_node->children[LEFT],value, cmp_func);
	}
	else
	{
		tree_node = AVLFindImpl(tree_node->children[RIGHT],value, cmp_func);
	}
	
	return tree_node;
} 
static void RightRotation(avl_node_t *node)
{
	avl_node_t *right_child = GetChild(node, RIGHT);

	SwapData(node,right_child);
	
	node->children[RIGHT] = GetChild(right_child, RIGHT);
	
	right_child->children[RIGHT] = GetChild(right_child, LEFT);
	right_child->children[LEFT] = GetChild(node, LEFT);
	
	node->children[LEFT] = right_child;
	
	UpdateHeight(right_child);
	UpdateHeight(node);
}

static void LeftRotation(avl_node_t *node)
{	
	avl_node_t *left_child = GetChild(node, LEFT);

	SwapData(node, left_child);
	
	node->children[LEFT] =  GetChild(left_child, LEFT);
	
	left_child->children[LEFT] = GetChild(left_child, RIGHT);
	left_child->children[RIGHT] = GetChild(node, RIGHT);
	
	node->children[RIGHT] = left_child;
	
	UpdateHeight(left_child);
	UpdateHeight(node);

}
/*
* Types of rotations :
* LL: The balance factor in the node is 2, and the balance factor in its left
*     child is 0 or 1.
* LR: The balance factor in the node is 2, and the balance factor in its left
*      child is -1.
* RR: The balance factor in the node is -2, and the balance factor in its right
*     child is 0 or -1.
* RL: The balance factor in the node is -2, and the balance factor in its right
*     child is 1.
*/
static void SetRotation(avl_node_t *node)
{
	assert(node);
	
	switch(GetBalance(node))
	{
		case 2:				
				switch(GetBalance(GetChild(node, LEFT)))
				{
					case -1:
					
					RightRotation(GetChild(node, LEFT));
					break;
				}
				
				LeftRotation(node); 
				break;
		
		case -2:
				
				switch(GetBalance(GetChild(node, RIGHT)))
				{
					case 1:
					
					LeftRotation(GetChild(node, RIGHT));
					break;
				}
				
				RightRotation(node); 
				break;
	}							
}
static int GetHeight(avl_node_t *node)
{	
	if (NULL == node)
	{
		return 0;
	}
	
	return node->height;
}
static avl_node_t *GetChild(avl_node_t *node, direction_t side)
{
	assert(node);
	
	return node->children[side];
}
static int GetBalance(avl_node_t *node)
{
	int left = -1, right = -1;
	
	assert(node);
	
	if (NULL ==  node)
	{
		return (0);
	}
	
	if (HasLeftChild(node))
	{
		left = GetHeight(GetChild(node, LEFT));
	}
	if (HasRightChild(node))
	{
		right = GetHeight(GetChild(node,RIGHT));
	}
	
	return (left - right);
}
static int IsLeaf(avl_node_t *node)
{
	assert(node);
	
	return !HasRightChild(node) && !HasLeftChild(node);
}
static int HasRightChild(avl_node_t *node)
{
	assert(node);
	
	return (NULL != node->children[RIGHT]);
}
static int HasLeftChild(avl_node_t * node)
{
	assert(node);
	
	return (NULL != node->children[LEFT]);
}
static void SwapData(avl_node_t *one, avl_node_t *other)
{
	void *one_data = NULL;
	
	assert(one);
	assert(other);
	
	one_data = one->data;
	one->data = other->data;
	other->data = one_data;
	
}
static avl_node_t *FindMostLeftOrRight(avl_node_t *node, direction_t side)
{
	if (NULL == GetChild(node, side))
	{
		return node;
	}
	return FindMostLeftOrRight(GetChild(node, side), side);
}

static avl_node_t *FindSuccessor(avl_node_t *node)
{	
	assert(node);
	
	if (HasRightChild(node))
	{
		return FindMostLeftOrRight(GetChild(node, RIGHT), LEFT);
	}
	
	return FindMostLeftOrRight(GetChild(node, LEFT), RIGHT);
	
	
}
static void RemoveLeaf(avl_t *tree, 
					   avl_node_t *parent ,
					   avl_node_t *node,
					   direction_t direction)
{
	assert(node);
	assert(tree);
	
	if (NULL == parent)
	{
		tree->root = NULL;
		
	}
	else
	{
		parent->children[direction] = NULL;
	}
	FREE(node);
	
}
static void UpdateHeight(avl_node_t *tree_node)
{
	/* if the node does not have any children, the height is 0 */
	if(NULL == tree_node->children[LEFT] && NULL == tree_node->children[RIGHT])
	{
		tree_node->height = 0;
	}
	else
	{
		tree_node->height = 1 + MAX(GetHeight(tree_node->children[LEFT]), 
									GetHeight(tree_node->children[RIGHT]));
	}	
}
				
