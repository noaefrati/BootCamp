/******************************************************************************* 
 * Description: Implemention of Binary Sorted Tree                             *
 * Author: Noa Efrati                                                          *
 * Reviewer: Oryan Shimoni                                                     *
 * Date: 22.12.20                                                              *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/

#include <stdlib.h>      /* malloc, free                                      */
#include <assert.h>      /* assert                                            */
#include "bst.h"         /* bst api                                           */

#define FREE(node) free(node); node = NULL;
/******************************************************************************/
/***                       Structs & Typedefs                               ***/
/******************************************************************************/

struct node
{
	void *data;
	node_t *parent;
	node_t *right;
	node_t *left;
};

struct bst
{
	node_t *dummy;
	int (*cmp_func)(const void *data, const void *input);
};

typedef enum 
{
	LEFT,
	RIGHT
}side_t;	

/******************************************************************************/
/***                         Static Functions                               ***/
/******************************************************************************/
static int IsRoot(bst_iter_t iter);
static int IsLeaf(bst_iter_t iter);
static int IsTail(bst_iter_t iter);
static int IsBegin(bst_iter_t iter);

static int HasOneChild(bst_iter_t iter);	
static int IsLeftChild(bst_iter_t iter);
static int IsRightChild(bst_iter_t iter);

static void RemoveRoot(bst_iter_t iter);
static void RemoveLeaf(bst_iter_t iter);
static void RemoveNodeWithOneChild(bst_iter_t iter);
static void RemoveNodeWithTwoChild(bst_iter_t iter);

static bst_iter_t FindMin(bst_iter_t iter);
static bst_iter_t FindMax(bst_iter_t iter);
static bst_iter_t GetRoot(bst_iter_t iter);
static bst_iter_t FindParent(bst_t *tree, void *data);
static int IncreamentSizeBy1(void *data, void *size);
		    

static void NodeSetData(bst_iter_t iter,
					    void *data,
					    bst_iter_t  parent,
					    bst_iter_t  left,
					    bst_iter_t  right);

static void UpdateNewParent(bst_t *tree,
							node_t *parent,
							const void *data, 
							bst_iter_t child);					    

static void InsertToEmptyTree(bst_t *tree,
                              bst_iter_t new_iter,
                              const void *data);	

static side_t GetFinalPosition(const bst_t *tree,
					           const bst_iter_t iter,
							   const void *data);
							   
static void InsertToTree(bst_t *tree, bst_iter_t new_iter, const void *data);	
						   
/******************************************************************************/
/***                                                                        ***/
/******************************************************************************/

/**************************** Create and Destroy ******************************/

bst_t *BSTCreate(int (*cmp_func)(const void *data, const void *input))
{
	bst_t *new_tree = NULL;
	
	assert(NULL != cmp_func);
	
	new_tree = (bst_t *) malloc(sizeof(bst_t));
	
	if (NULL != new_tree)
	{
		new_tree->dummy = (node_t *)malloc(sizeof(node_t));
		if (NULL == new_tree->dummy)
		{
			FREE(new_tree);
		}
		else
		{
			NodeSetData(new_tree->dummy, NULL, NULL, NULL, NULL);		
			new_tree->cmp_func = cmp_func;	
		}
	}		
	
	return new_tree;	
}
 
void BSTDestroy(bst_t *tree)
{
	bst_iter_t runner = NULL;
	
	assert(NULL != tree);
	
	runner = GetRoot(tree->dummy);	
	
	while (NULL != runner)
	{
		if (NULL != runner->right)
		{
			runner = runner->right;
		}
		else if (NULL != runner->left)
		{
			runner = runner->left;
		}
		else /* runner is leaf */
		{
			bst_iter_t parent = runner->parent;
			
			if (NULL != parent)
    		{
        		if (1 == IsLeftChild(runner))
        		{
            		parent->left = NULL;
        		}
        		else if (1 == IsRightChild(runner))
        		{
            		parent->right = NULL;
        		}
    		}
			
			FREE(runner);
			runner = parent;
		}		
	}
	
	FREE(tree);	
} 

/****************************** Insert and Remove *****************************/

bst_iter_t BSTInsert(bst_t *tree, const void *data)
{
	bst_iter_t new_iter = NULL;
	
	assert(NULL != tree);
	
	new_iter = (node_t *) malloc(sizeof(node_t));
	
	if (NULL != new_iter)
	{

		if (1 == BSTIsEmpty(tree))
		{
			InsertToEmptyTree(tree, new_iter, data);
		}
		else
		{
			InsertToTree(tree, new_iter, data);	
		}
	}
		
	return new_iter;
}

/*
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
 
void BSTRemove(bst_iter_t iter)
{
	assert(NULL != iter);
	
	if (1 == IsLeaf(iter))
	{
		RemoveLeaf(iter);
	}
	else if (1 == HasOneChild(iter))
	{
		if (1 == IsRoot(iter)) 
		{

			RemoveRoot(iter);
		}
		else
		{
			RemoveNodeWithOneChild(iter);
		}
	}
	else /* iter has two children */
	{
		RemoveNodeWithTwoChild(iter);
	}
	
	FREE(iter);
}

/********************************* Basic Utility ******************************/

size_t BSTSize(const bst_t *tree)
{
	size_t size = 0;
	
	assert(NULL != tree);
	
	
	if (!BSTIsEmpty(tree))
	{
		BSTForEach(BSTBegin((bst_t *)tree),
			  	   BSTEnd((bst_t *)tree),
			       IncreamentSizeBy1,
			       &size);
	}
	
	
				  
   return size;
}

int BSTIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);
	
	return (NULL == tree->dummy->parent);
}

int BSTIsSameIter(bst_iter_t one, bst_iter_t other)
{
	return (one == other);
}

bst_iter_t BSTNext(bst_iter_t iter)
{
	assert(NULL != iter);
	
	if (NULL != iter->right)
	{
		return FindMin(iter->right);
	}
	
	if (iter != FindMax(GetRoot(iter))) /* runner is not tail */
	{ 
		for ( ; NULL != iter->parent && 1 == IsRightChild(iter); 
			  iter = iter->parent)
		{
			/* empty */
		}
		iter = iter->parent;
	}
	
	return iter;
}
 
bst_iter_t BSTPrev(bst_iter_t iter)
{
	assert(NULL != iter);
	
	if (NULL != iter->left)
	{
		return FindMax(iter->left);
	}
	
	/*iter is'nt the minimal value of the tree*/	
	if (0 == IsBegin(iter) && !IsTail(iter)) 
	{
		/* while iter is not the root and is left child      */
		while (NULL != iter->parent && 1 == IsLeftChild(iter)) 
		{
			iter = iter->parent;		
		}
		iter = iter->parent;	
	}
	else if ((NULL != iter->parent) && 
			(iter == FindMax(GetRoot(iter)))) 
	{
		 iter = iter->parent; 
	}
	 return iter;	
}

bst_iter_t BSTBegin(const bst_t *tree)
{
	assert(NULL != tree);
	
	if (BSTIsEmpty(tree))
	{
		return tree->dummy;
	}
	
	return (FindMin(GetRoot(tree->dummy)));
}

bst_iter_t BSTEnd(const bst_t *tree)
{
	assert(NULL != tree);
	
	return tree->dummy;
}

void *BSTGetData(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->data;
}

/******************************** Advanced ************************************/

int BSTForEach(bst_iter_t from,
               bst_iter_t to,
               int (*action)(void *data, void *params),
               void *params)
{
	int action_value = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	
	for (; !BSTIsSameIter(from, to) && !action_value; from = BSTNext(from))
	{
		action_value = action(from->data, params);
	}
	
	return action_value;
}

bst_iter_t BSTFind(const bst_t *tree,
                   const void *value)
{
	bst_iter_t from = NULL;
	bst_iter_t to = NULL;
	 
	assert(NULL != tree);
	
	
	to = BSTEnd(tree);
	
	for (from = BSTBegin(tree); 
		 !BSTIsSameIter(from, to) && (0 != tree->cmp_func(from->data, value));
	     from = BSTNext(from))
	{
		
		/* empty */
	}
	
	return from;
}

/******************************************************************************/
/******************************************************************************/

static int IsTail(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return (NULL == iter->data);
}

static int IsRightChild(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return BSTIsSameIter(iter, iter->parent->right);
}

static int IsLeftChild(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return BSTIsSameIter(iter, iter->parent->left);
}

static bst_iter_t FindMin(bst_iter_t iter)
{
	assert(NULL != iter);
	
	while (NULL != iter->left)
	{
		iter = iter->left;
	}
	
	return iter;
}

static bst_iter_t FindMax(bst_iter_t iter)
{
	assert(NULL != iter);
	
	
	while (NULL != iter->right)
	{
		iter = iter->right;
	}
	
	return iter;
}

static bst_iter_t GetRoot(bst_iter_t iter)
{
	assert(NULL != iter);
	
	for (; NULL != iter->parent; iter = iter->parent)
	{
		/* empty */
	} 
	
	return iter;
}

static bst_iter_t FindParent(bst_t *tree, void *data)
{
	int found = 1;
    bst_iter_t runner = NULL;
        
    assert(NULL != tree);
    
   runner = GetRoot(tree->dummy);
    
    while (found)
    {
        
         if ((NULL != runner->left) && (0 < tree->cmp_func(runner->data, data))) 
		{
			runner = runner->left;
		}
		else if (1 == BSTIsSameIter(runner->right, tree->dummy))
		{
			found = 0;
		}
		else if ((NULL != runner->right) && 
				(0 > tree->cmp_func(runner->data, data)))     
		{
			runner = runner->right;
		}
        
        else
        {
            found = 0;
        } 
    }
    
    return runner;   
}

/* return 0 after the increament completes*/
static int IncreamentSizeBy1(void *data, void *size)
{
	assert(NULL != size);
	
	(void)data;
	
	++(*(size_t *)size);
	
	return (0);
}

static int IsLeaf(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return ((NULL == iter->left) && (NULL == iter->right)); 
}

static void NodeSetData(bst_iter_t iter,
					    void *data,
					    bst_iter_t  parent,
					    bst_iter_t  left,
					    bst_iter_t  right)
{
	assert(NULL != iter);
	
	iter->data = data;
	iter->parent = parent;
	iter->left = left;
	iter->right = right;	
}

static int HasOneChild(bst_iter_t iter)
{
	return ((NULL == iter->left && NULL != iter->right) || 
			(NULL == iter->right && NULL != iter->left));
}	

static int IsRoot(bst_iter_t iter)
{
	bst_iter_t runner = NULL;
	
	assert(NULL != iter);
	
	for (runner = iter; 
		 NULL != runner->parent; 
		 runner = runner->parent)
	{
		/* empty */
	} 
	
	return BSTIsSameIter(runner, iter);
}

static void RemoveLeaf(bst_iter_t iter)
{
	node_t *parent = iter->parent;
	
	if (1 == IsRightChild(iter))
	{
		parent->right = NULL;
	}
	else
	{
		parent->left = NULL;
	}
}

static void RemoveRoot(bst_iter_t iter)
{
	if (NULL != iter->right) /* has only right-child */
	{
		iter->right->parent = NULL;
		iter->right = NULL;
	}
	else  /* has only left-child */
	{
		iter->left->parent = NULL;
		iter->left = NULL;
	}
}

static void RemoveNodeWithOneChild(bst_iter_t iter)
{
	if (NULL != iter->right) /* iter has only right child*/
	{
		if (1 == IsRightChild(iter))
		{
			iter->parent->right = iter->right;
		}
		else /* iter is a left child*/
		{
			iter->parent->left = iter->right;
		}
		/* update new parent to iter left child*/
		iter->right->parent = iter->parent;
	}
	else /* iter has only left child*/
	{
		if (1 == IsRightChild(iter))
		{
			iter->parent->right = iter->left;
		}
		else /* iter is a left child*/
		{
			iter->parent->left = iter->left;
		}
		
		/* update new parent to iter left child*/
		iter->left->parent = iter->parent; 
	}
}

static void RemoveNodeWithTwoChild(bst_iter_t iter)
{
	node_t *new_parent = BSTPrev(iter);
		
	if (1 == IsRoot(iter))
	{
		iter->left->parent = NULL; /* left child becomes the new root*/
	}
	else
	{
		if (1 == IsRightChild(iter))
		{
			/* update left child  of iter as the right child of iter parent*/
			iter->parent->right = iter->left;
		}
		else /* when iter is left child */
		{
			/* update left child  of iter as the left child of iter parent*/
			iter->parent->left = iter->left;		
		}
		
		/* update the parent of iter->left to be the parent of iter    */
		iter->left->parent = iter->parent; 
	}
	
	/* update new parent (the node that is smaller than the current node and
	 * closest to it in terms of data. aka prev of iter) 
	 * to right child of iter       */
	iter->right->parent = new_parent;
	new_parent->right = iter->right;
	
}

static void InsertToEmptyTree(bst_t *tree, bst_iter_t new_iter, const void *data)
{
	NodeSetData(new_iter,(void *) data, NULL, NULL, BSTEnd(tree));
	tree->dummy->parent = new_iter;
}

static void InsertToTree(bst_t *tree, bst_iter_t new_iter, const void *data)
{
	node_t *future_parent = NULL;
	node_t *parent_right = NULL;
	
	future_parent = FindParent(tree, (void *)data);
	
	parent_right = future_parent->right; /* if right is tail*/
	
	UpdateNewParent(tree, future_parent, data, new_iter);
	
	if (1 == BSTIsSameIter(tree->dummy, parent_right) &&
		RIGHT == GetFinalPosition(tree, future_parent, data))
	{
		NodeSetData(new_iter, (void *)data, future_parent, NULL, parent_right);
		tree->dummy->parent = new_iter; /* update new max node*/
	}
	else
	{
		NodeSetData(new_iter, (void *)data, future_parent, NULL, NULL);
	}
}			    

static side_t GetFinalPosition(const bst_t *tree,
							   const bst_iter_t iter,
						       const void *data)
{
	side_t side = RIGHT;
	
	assert(NULL != tree);
	
	if (0 < tree->cmp_func(iter->data, data))
	{
		side = LEFT;
	}

	return side;
}

static int IsBegin(bst_iter_t iter)
{
	return BSTIsSameIter(iter, FindMin(GetRoot(iter)));
}

static void UpdateNewParent(bst_t *tree,
							bst_iter_t parent,
							const void *data, 
							bst_iter_t child)
{
	if (LEFT == GetFinalPosition(tree, parent, data))
	{
			parent->left = child;
	}
	else if (RIGHT == GetFinalPosition(tree, parent, data))
	{
		parent->right = child;
	}
}
