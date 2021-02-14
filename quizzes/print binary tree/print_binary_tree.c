/*
    Write a function that prints a binary tree by levels

    It first prints the root, then the two children of the root, 
   	then the 4 grand children and so on

	Complexity goal
	Time: As good as possible (possible to pass through each node only once)
	Space: no constraint
*/

#include <stdio.h>
#include "queue.h"

int PrintBinaryTree(node_t *root)
{
	queue_t *q = QCreate();
	size_t curr_row = 1, next_row = 0;
	
	if (NULL == q)
	{
		return 1;
	}
	
	QEnqueue(q, root);
	
	while (!QIsEmpty(q))
	{
		while (curr_row > 0)
		{
			node_t *temp = QDequeue(q);
			printf("%d", *(int *)temp->data);
			if (NULL != temp->left)
			{
				++next_row;
				QEnqueue(q, temp->left);
			}
			if (NULL != temp->right)
			{
				++next_row;
				QEnqueue(q, temp->right);
			}
			
			--curr_row;
		}
		curr_row = next_row;
		next_row = 0;
	}
	return 0;
	
}
int main()
{
	
}
