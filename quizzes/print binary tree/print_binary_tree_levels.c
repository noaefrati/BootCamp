
                  10
               /      \
               7
/*----------------------------------------------------------------------------*/
#include <stdio.h>

typedef enum { LEFT = 0, RIGHT = 1, NUM_OF_CHILDREN = 2}child_t;

typedef struct node_tree
{
	struct node_tree *children[NUM_OF_CHILDREN];
}

typedef struct bst
{
	node_tree_t *root;
}bst_t;

#define MAX(a,b) (a < b) ? (b) : (a)

void PrintBinaryTreeByLevels(const bst_t *tree, int level)
{
	assert(tree);
	
	return PrintBinaryTreeByLevelsImpl((bst_t *)tree
}
void PrintBinaryTreeByLevelsImpl(const bst_t *tree, int level)
{
	
}

int GetTreeHeight(node_t *node)
{
	int left_height = 0, right_height = 0;
	
	if (NULL == node)
	{
		return (0);
	}
	
	left_height = GetTreeHeight(node->children[LEFT]);
	right_height = GetTreeHeight(node->childrent[RIGHT]);
	
	return 1 + MAX(left_height, right_height);	
}
