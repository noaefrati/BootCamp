/*************************************************************************** 
 * Description: Singley Linked List exersizes.                             *
 * Author: Noa Efrati                                                      *
 * Reviewer: Yuval Krytzer                                                 *
 * Date: 25.11.20                                                          *
 * Infinity Labs OL97                                                      *
 ***************************************************************************/

#include <stdlib.h>              /* malloc     */
#include <assert.h>              /* assert     */
#include <stdio.h>               /* printf     */
#define RED     "\033[31m"       /*  Red       */
#define GREEN   "\033[32m"       /* Green      */
#define LEN 6                    /* Arr length */
#define DEF   "\033[0m"

#define TEST(name, real, expected) (real == expected) ?\
printf(GREEN"%s, SUCCESS in line %d\n"DEF, name, __LINE__)\
: printf(RED"%s, FAIL in line %d\n"DEF, name, __LINE__)

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

/* Reverse the order of a given slist. */
node_t *Flip(node_t *head);

/* Tells whether a given slist has loop. */
int HasLoop(const node_t *head);

/* Returns a pointer to a first bode mutual to both slists, if any. */
node_t *FindIntersection(const node_t *head_1, const node_t *head_2);

/* Return the size of slist. */
static size_t LLGetSize(node_t *head);

int FlipTest(void);
int HasLoopTest(void);
int FindIntersectionTest(void);

int main()
{
	FindIntersectionTest();
	FlipTest();
	HasLoopTest();
	
	return (0);
}

/*Complexity: O(n)*/
int HasLoop(const node_t *head)
{
	node_t *slower = NULL;
	node_t *faster = NULL;
	int is_cycle = 0;

	assert(NULL != head);
	
	faster = (node_t *) head;
	slower = (node_t *) head;
	
	while ((NULL != faster->next) &&
		   (NULL != slower->next) &&
		   (NULL != faster->next->next))
	{
		faster = faster->next->next;
		slower = slower->next;
		
		if (faster == slower)
		{
			is_cycle = 1;
			break;
		}
			
	}
	
	return (is_cycle);
}

int HasLoopTest(void)
{
	int arr[LEN]= {1, 2, 3, 4, 5, 6};
	int status = 0;
	int expected = 1;
	int i = 0;
	
	node_t *head1 = malloc(sizeof(node_t)*sizeof(arr));
	if (NULL == head1)
	{
		return (-1);
	}
    
    
	for (; LEN -1 > i; ++i)
	{
		head1[i].data = &arr[i];
		head1[i].next = &head1[i+1];		
	}
	head1[i].data = &arr[i];
	head1[i].next =&head1[2];
	
	status = HasLoop(head1);
	
	TEST("HasLoopTest", status, expected);
	
	for (i = 0; LEN -1 > i; ++i)
	{
		head1[i].data = &arr[i];
		head1[i].next = &head1[i+1];		
	}
	head1[i].data = &arr[i];
	head1[i].next = NULL;
	
	status = HasLoop(head1);
	expected = 0;
	
	TEST("HasLoopTest", status, expected);
	free(head1);
	
	return (0);	
}

/*Complexity : O(n+m). n- size of first list, m- size of second list. */
node_t *FindIntersection(const node_t *head_1, const node_t *head_2)
{
	node_t *longer_lst = NULL;
	node_t *shorter_lst = NULL;
	size_t bigger_size = 0;
	size_t smaller_size = 0;
	int diff = 0;
	
	assert(NULL != head_1 && NULL != head_2);
	
	longer_lst = (node_t *)head_1;
	shorter_lst = (node_t *)head_2;
	bigger_size = LLGetSize(longer_lst);
	smaller_size = LLGetSize(shorter_lst);
	diff = bigger_size - smaller_size;
	
	if (0 < diff)
	{
		longer_lst = (node_t *)head_2;
		shorter_lst = (node_t *)head_1;
		diff *= -1;
	}
	
	for (;0 != diff; --diff, longer_lst= longer_lst->next)
	{
		if (NULL == longer_lst)
		{
			return (NULL);
		}
	} 
	
	while ((NULL != longer_lst) && (NULL != shorter_lst))
	{
		if (longer_lst == shorter_lst)
		{
			return (longer_lst);
		}
		longer_lst = longer_lst->next;
		shorter_lst = shorter_lst->next;
	}

	return (NULL);
}

int FindIntersectionTest(void)
{
	int arr[LEN]= {1, 2, 3, 4, 5, 6};
	int data[] = {66, 55, 44, 33};
	int i = 0;
	node_t *head2 = NULL;
	node_t *return_val = NULL;
	node_t *head1 = malloc(sizeof(node_t)*sizeof(arr));
	
	if (NULL == head1)
	{
		return (-1);
	}
    
   	head2 = malloc(sizeof(node_t)*sizeof(arr));
	if (NULL == head2)
	{
		return (-1);
	}
    
	for (; LEN - 1 > i; ++i)
	{
		head1[i].data = &arr[i];
		head1[i].next = &head1[i+1];		
	}
	head1[i].data = &arr[i];
	head1[i].next = NULL;
	
	for (i = 0; 4 > i; ++i)
	{
		head2[i].data = &data[i];
		head2[i].next = &head2[i+1];		
	}
	head2[i].data = &arr[i];
	head2[i].next = &head1[i+1];
	
	return_val = FindIntersection(head1, head2);
	TEST("FindIntersectionTest", return_val, &head1[i+1]);
	
	for (i = 0; LEN - 1 > i; ++i)
	{
		head2[i].data = &arr[i];
		head2[i].next = &head2[i+1];		
	}
	head2[i].data = &arr[i];
	head2[i].next = NULL;
	
	return_val = FindIntersection(head1, head2);
	TEST("FindIntersectionTest", return_val, NULL);
	
	free(head1);
	free(head2);
	
	return (0);		
}

/*Complexity: O(n)*/
node_t *Flip(node_t *head)
{
	node_t *next = NULL;
	node_t *prev = NULL;
	node_t *cur = NULL;	
	assert(NULL != head);
	
	cur = head;
	while(NULL != cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	head = prev;
	
	return head;	
}

size_t LLGetSize(node_t *head)
{
	size_t size = 0;
	assert(NULL != head);
	
	for (; NULL != head; head = head->next, ++size)
	{
		/*empty*/
	}
	return (size);
}

int FlipTest(void)
{
	int arr[LEN]= {1, 2, 3, 4, 5, 6};
	int expected_arr[LEN] = {6, 5, 4, 3, 2, 1};
	int status = 0;
	int expected = 0;
	int i = 0;
	
	node_t *head1 = malloc(sizeof(node_t)*sizeof(arr));
	if (NULL == head1)
	{
		return (-1);
	}
    
	for (; LEN -1 > i; ++i)
	{
		head1[i].data = &arr[i];
		head1[i].next = &head1[i+1];		
	}
	head1[i].data = &arr[i];
	head1[i].next = NULL;
	
	head1 = Flip(head1);	
	for (i = 0; LEN > i && NULL != head1->next; head1 = head1->next, ++i)
	{
		if (expected_arr[i] != *(int *)head1->data)
		{
			status = -1;
			break;
		}
	}
	
	TEST("FlipTest", status, expected);
	free(head1);	
	
	return (status);
}

