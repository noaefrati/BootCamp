/*************************************************************************** 
 * Description: Implement ADS Stack's functions.                           *
 * Author: Noa Efrati                                                      *
 * Reviewer: Yuval Ben Ari                                                 *
 * Date: 18.11.20                                                          *
 * Infinity Labs OL97                                                      *
 ***************************************************************************/

#include <stdlib.h>                 /*malloc*/
#include <string.h>                 /*memcpy*/
#include <assert.h>                 /*assert*/
#include "stack.h"                  /* stack functions */

struct stack
{
	void *stack_data;
	size_t element_size;
	size_t capacity;
	size_t top;
};

/*
 * Create an empty stack with the given capacity.
 * If it fails (memory allocation failure), it will return NULL.
 */
stack_t *StackCreate(size_t element_size, size_t capacity)
{
	stack_t *new_stack = (stack_t *)malloc(sizeof(stack_t));
	
	assert(0 != element_size && 0 != capacity);
	
	/*If allocation failed*/
	if (NULL == new_stack)
	{
		return (NULL);
	}

	new_stack->stack_data = malloc(capacity * element_size);
	
	/*If allocation failed*/
	if (NULL == new_stack->stack_data)
	{
		return (NULL);
	}
	
	new_stack->capacity = capacity;
	new_stack->element_size = element_size;
	new_stack->top = 0;
	
	return (new_stack);
}

/*
 * Free the memory allocated to the stack, 
 * and turn the stack to NULL.
 * If stack is NULL, behaviour is undefined.
 */
void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	
	free(stack->stack_data);
	stack->stack_data = NULL;
	free(stack);	
}

/*
 * Remove the top element from the stack.
 * If the remove was successful, return 0,
 * if the stack was empty, return anything but 0.
 * If stack is NULL, behaviour is undefined.
 */
int StackPop(stack_t *stack)
{
	assert(NULL != stack);
	
	/* If stack is empty */
	if (0 == stack->top)
	{
		return (1);
	}
	stack->top -= 1;
	
	return (0);
}

/*
 * Push the given element on top of the stack.
 * Upon success, return 0, otherwise (stack is full),
 * return anything but 0.
 * If stack or element are NULL, behaviour is undefined.
 */
int StackPush(stack_t *stack, const void *element)
{
	void *stack_insert_location = NULL;
	
	assert(NULL != stack && NULL != element);
	
	     /* If stack is full */
	if (stack->capacity == stack->top)
	{
		return (1);
	}
	stack_insert_location = (void *) ((size_t)stack->stack_data +
	                                 (stack->top * (stack->element_size)));
	
	memcpy(stack_insert_location, element, stack->element_size);
	stack->top += 1; 
	
	return (0);
}

/*
 * Returns the value of the top element of the stack, 
 * without changing the stack.
 * If the stack is empty, return NULL; It is the user's responsibility
 * to make sure that the value is really 0, and it didn't
 * return 0 because the stack was empty.
 * If stack is NULL, behaviour is undefined.
 */
void *StackPeek(const stack_t *stack)
{
	void *stack_top_element = NULL;
	
	assert(NULL != stack);
	
	if (1 == StackIsEmpty(stack))
	{
		return (NULL);
	}
	
	stack_top_element = (void *) ((size_t)stack->stack_data + 
	                           ((stack->top - 1) * (stack->element_size)));
	
	return (stack_top_element);	
}

/*
 * Return the current size of the stack, i.e. the index of its 'top'.
 * If the stack is empty, it will return 0.
 * If stack is NULL, behaviour is undefined.
 */
size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	
	/*If the stack is empty, it will return 0.*/
	if (1 == StackIsEmpty(stack))
	{
		return (0);
	}
	
	return (stack->top);
}

/*
 * Returns 1 if the stack is empty, and 0 otherwise.
 * If stack is NULL, behaviour is undefined.
 */
int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->top ? 0:1);
}

/*
 * Returns the capacity of the stack.
 * If stack is NULL, behaviour is undefined.
 */
size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->capacity);
}
