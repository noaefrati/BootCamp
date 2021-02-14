/*************************************************************************** 
 * Description: Implementations of stack functions
 * Author: Oriel Nofekh
 * Reviewer: 
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>              /* printf */
#include <stdlib.h>             /* malloc, free */
#include <string.h>             /* memcpy */
#include <assert.h>             /* assert */
#include "vector_ref.h"         /* vector_t and declarations of all its functions */

void TestVector(void)
{
	size_t initial_capacity = 2;
	vector_t *vector = VectorCreate(initial_capacity);
	
	int status = 0;
	int failure = 0;
	int elements[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
	int element_get = 0;
	
	static int push_pop_arr[] = {1, -1, 1, 1, 1, -1, 1, -1, 1, 1, -1, -1, -1, -1, -1};
	int push_pop_arr_len = sizeof(push_pop_arr) / sizeof(push_pop_arr[0]);
	static int push_pop_cumsum[25] = {0};
	int i = 0;
	push_pop_cumsum[0] = push_pop_arr[0];
	for (i = 1; i < push_pop_arr_len; ++i)
	{
		push_pop_cumsum[i] = push_pop_cumsum[i-1] + push_pop_arr[i];
	}
	
	printf("Vector was successfully created without crashing!\n\n");
	
	printf("Commencing Joint tests for:\n"
	       "(*) VectorPushBack\n"
	       "(*) VectorPopBack\n"
	       "(*) VectorSize\n"
	       "(*) GetAccessToElementAt\n\n");
	
	for (i = 0; i < push_pop_arr_len; ++i)
	{
		if (1 == push_pop_arr[i])
		{
			status = VectorPushBack(vector , (void *) &elements[i]);
			if (status != 0)
			{
				failure = 1;
				printf("    In iteration %d, PushBack status was different from 0, "
				       "should have been 0.\n", i);
			}
			
			element_get = *(int *) VectorGetAccessToElementAt(vector , VectorSize(vector) - 1);
			if (elements[i] != element_get)
			{
				failure = 1;
				printf("    In iteration %d, GetAcessToElementAt returned %d, "
				       "should have been %d.\n", i, element_get, elements[i]);
			}
		}
		else
		{
			status = VectorPopBack(vector);
			if (status != 0 && push_pop_cumsum[i] >= 0) 
			{
				failure = 1;
				printf("    In iteration %d, PopBack status was different from 0, "
				       "should have been 0.\n", i);
			}
			else if (status == 0 && push_pop_cumsum[i] < 0) 
			{
				failure = 1;
				printf("    In iteration %d, PopBack status was was 0, "
				       "should have been different from 0 (Pop on empty vector).\n", i);
			}
		}
		
		
		if (push_pop_cumsum[i] < 0)
		{
			push_pop_cumsum[i] = 0;
		}
		if (push_pop_cumsum[i] != (int) VectorSize(vector))
		{
			printf("    In iteration %d, VectorSize = %lu, "
			       "was expected to be %d, \n", i, VectorSize(vector), push_pop_cumsum[i]);
		}
		
	}
	
	if (0 == failure)
	{
		printf("Joint tests were all successful !!!\n");
	}
	
	printf("\nCompleted Joint tests for:\n"
	       "(*) VectorPushBack\n"
	       "(*) VectorPopBack\n"
	       "(*) VectorSize\n"
	       "(*) GetAccessToElementAt\n\n");
	
	/* int VectorReserve(vector_t *vector, size_t new_capacity) */
	
	VectorDestroy(vector);
	
	printf("Vector was successfully destroyed without crashing!\n");
}

int main(void)
{
	TestVector();
	
	return 0;
}




