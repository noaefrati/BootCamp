/*************************************************************************** 
 * Description: Testing stack function implementation.
 * Author: Oriel Nofekh
 * Reviewer: NONE
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>               /* printf, size_t */
#include "../include/stack.h"   /*stack and all its functions*/

/******************** Functions Declarations ********************/

void TestStackCreateDestroy(void);
void TestStackPush(void);
void TestStackPop(void);
void TestStackPeek(void);
void TestStackSize(void);
void TestStackIsEmpty(void);
void TestStackCapacity(void);
/*
static void PrintSuccesOrFailure(int is_success, char *function_name);
*/

/******************** main function ********************/

int main(void)
{
	
	TestStackCreateDestroy();
	TestStackPush();
	TestStackPop();
	TestStackPeek();
	TestStackSize();
	TestStackIsEmpty();
	TestStackCapacity();
	
	return 0;
}

/******************** Functions Implementations ********************/

void TestStackCreateDestroy(void)
{
	size_t element_size = 8;
	size_t capacity = 100;
	stack_t *stack = StackCreate(element_size, capacity);
	
	printf("Stack was created without crashing!\n");
	
	StackDestroy(stack);
	
	printf("Stack was destroyed without crashing!\n");
	
	printf("\n");
}

void TestStackPush(void)
{
	size_t element_size = 8;
	size_t capacity = 3;
	long num = 15;
	static int status[5];
	static int status_expected[5] = {0, 0, 0, 1, 1};
	int i = 0;
	int success = 1;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	printf("Attempting to push 5 times to a stack with a capacitiy of 3,\n"
	       "expected statuses are: 0, 0, 0, 1, 1.\n");
	
	for (i = 0; i < 5; ++i)
	{
		status[i] = StackPush(stack, &num);
		if (status[i] != status_expected[i])
		{
			success = 0;
		} 
	}
	
	if (success)
	{
		printf("StackPush test was success!\n");
	}
	else
	{
		printf("StackPush test has failed! --- --- --- --- ---\n");
		for (i = 0; i < 5; ++i)
		{
			printf("     StackPush finished with status %d\n", status[i]);
		}
	}
	printf("\n");
	
	StackDestroy(stack);
}

void TestStackPop(void)
{
	size_t element_size = 8;
	size_t capacity = 3;
	long num = 15;
	static int status[5];
	static int status_expected[5] = {0, 0, 0, 1, 1};
	int i = 0;
	int success = 1;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	StackPush(stack, &num);
	StackPush(stack, &num);
	StackPush(stack, &num);
	
	printf("Attempting to pop 5 times to a full stack with a capacitiy of 3,\n"
	       "expected statuses are: 0, 0, 0, 1, 1.\n");
	
	for (i = 0; i < 5; ++i)
	{
		status[i] = StackPop(stack);
		if (status[i] != status_expected[i])
		{
			success = 0;
		} 
	}
	
	if (success)
	{
		printf("StackPop test was success!\n");
	}
	else
	{
		printf("StackPop test has failed! --- --- --- --- ---\n");
		for (i = 0; i < 5; ++i)
		{
			printf("     StackPop finished with status %d\n", status[i]);
		}
	}
	printf("\n");
	
	StackDestroy(stack);
}



void TestStackPeek(void)
{
	size_t element_size = 8;
	size_t capacity = 3;
	long num[3] = {15, 27, -101};
	int i = 0;
	long tmp[3];
	int success = 1;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	for (i = 0; i < 3; ++i)
	{
		StackPush(stack, &(num[i]));
	}
	
	printf("Stack of size 3, with values: %ld, %ld, %ld,\n"
	       "each time we Peek and then Pop:\n", 
	       num[0], num[1], num[2]);
	
	for (i = 0; i < 3; ++i)
	{
		tmp[2 - i] = (*(long *) StackPeek(stack));
		
		StackPop(stack);
		if (tmp[2 - i] != num[2 - i])
		{
			success = 0;
		}
	}
	if (success)
	{
		printf("StackPeek main test was success!\n");
	}
	else
	{
		printf("StackPeek main test has failed! --- --- --- --- ---\n");
		for (i = 0; i < 3; ++i)
		{
			printf("     StackPeek returned a pointer that points to the value: %ld\n", tmp[i]);
		}
	}
	
	printf("\n");
	
	if (NULL == StackPeek(stack))
	{
		printf("StackPeek returned NULL, as expected\n");
	}
	else
	{
		printf("StackPeek did not return NULL, but it was expected to return NULL !!! --- --- --- --- ---\n");
	}
	
	printf("\n");
	
	StackDestroy(stack);
}

void TestStackSize(void)
{
	size_t element_size = 8;
	size_t capacity = 3;
	long num = 15;
	size_t sizes[5];
	size_t sizes_expected[5] = {3, 2, 1, 0, 0};
	int success = 1;
	int i = 0;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	StackPush(stack, &num);
	StackPush(stack, &num);
	StackPush(stack, &num);
	
	printf("Stack of size 3, each time we get the size then we Pop,\n"
	       "expected sizes are: 3, 2, 1, 0, 0.\n");
	
	for (i = 0; i < 5; ++i)
	{
		sizes[i] = StackSize(stack);
		StackPop(stack);
		
		if (sizes[i] != sizes_expected[i])
		{
			success = 0;
		}
	}
	
	if (success)
	{
		printf("StackSize test was success!\n");
	}
	else
	{
		printf("StackSize test has failed! --- --- --- --- ---\n");
		for (i = 0; i < 5; ++i)
		{
			printf("     StackSize = %lu\n", sizes[i]);
		}
	}
	
	printf("\n");
	
	StackDestroy(stack);
}

void TestStackIsEmpty(void)
{
	size_t element_size = 8;
	size_t capacity = 3;
	long num = 15;
	size_t empties[5];
	size_t empties_expected[5] = {0, 0, 0, 1, 1};
	int success = 1;
	int i = 0;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	StackPush(stack, &num);
	StackPush(stack, &num);
	StackPush(stack, &num);
	
	printf("Stack of size 3, each time we check if empty and then we Pop,\n"
	       "expected results are: 0, 0, 0, 1, 1.\n");
	
	for (i = 0; i < 5; ++i)
	{
		empties[i] = StackIsEmpty(stack);
		StackPop(stack);
		
		if (empties[i] != empties_expected[i])
		{
			success = 0;
		}
	}
	
	if (success)
	{
		printf("StackIsEmpty test was success!\n");
	}
	else
	{
		printf("StackIsEmpty test has failed! --- --- --- --- ---\n");
		for (i = 0; i < 5; ++i)
		{
			printf("     StackIsEmpty = %lu\n", empties[i]);
		}
	}
	
	printf("\n");
	
	StackDestroy(stack);
}

void TestStackCapacity(void)
{
	size_t element_size = 8;
	size_t capacity = 3;
	long num = 15;
	size_t caps[5];
	size_t caps_expected[5] = {3, 3, 3, 3, 3};
	int success = 1;
	int i = 0;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	StackPush(stack, &num);
	StackPush(stack, &num);
	StackPush(stack, &num);
	
	printf("Stack of size 3, each time we get the capacitiy then we Pop,\n"
	       "expected capacities are: 3, 3, 3, 3, 3.\n");
	
	for (i = 0; i < 5; ++i)
	{
		caps[i] = StackCapacity(stack);
		StackPop(stack);
		
		if (caps[i] != caps_expected[i])
		{
			success = 0;
		}
	}
	
	if (success)
	{
		printf("StackCapacity test was success!\n");
	}
	else
	{
		printf("StackCapacity test has failed! --- --- --- --- ---\n");
		for (i = 0; i < 5; ++i)
		{
			printf("     StackCapacity = %lu\n", caps[i]);
		}
	}
	
	printf("\n");
	
	StackDestroy(stack);
}

/*
static void PrintSuccesOrFailure(int is_success, char *function_name)
{
	if (is_success)
	{
		printf("%s test was a SUCCESS\n", function_name);
	}
	else
	{
		printf("%s test was a FAILURE   !!!   !!!   !!!\n", function_name);
	}
}
*/












