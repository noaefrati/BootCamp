/******************************************************************************
 * Definition of a stack data structure, 
 * and declarations of the functions that serve as its interface. 
 ******************************************************************************/

#ifndef __STACK_H_OL97_ILRD__
#define __STACK_H_OL97_ILRD__

#include <stddef.h>   /* size_t */

/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/

typedef struct stack stack_t;

/******************************************************************************/
/***                      Public functions declarations                     ***/
/******************************************************************************/

/*
 * Create an empty stack with the given capacity.
 * If it fails (memory allocation failure), it will return NULL.
 */
stack_t *StackCreate(size_t element_size, size_t capacity);

/*
 * Free the memory allocated to the stack, 
 * and turn the stack to NULL.
 * If stack is NULL, behaviour is undefined.
 */
void StackDestroy(stack_t *stack);

/*
 * Remove the top element from the stack.
 * If the remove was successful, return 0,
 * if the stack was empty, return anything but 0.
 * If stack is NULL, behaviour is undefined.
 */
int StackPop(stack_t *stack);

/*
 * Push the given element on top of the stack.
 * Upon success, return 0, otherwise (stack is full),
 * return anything but 0.
 * If stack or element are NULL, behaviour is undefined.
 */
int StackPush(stack_t *stack, const void *element);

/*
 * Returns the value of the top element of the stack, 
 * without changing the stack.
 * If the stack is empty, return NULL; It is the user's responsibility
 * to make sure that the value is really 0, and it didn't
 * return 0 because the stack was empty.
 * If stack is NULL, behaviour is undefined.
 */
void *StackPeek(const stack_t *stack);

/*
 * Return the current size of the stack, i.e. the index of its 'top'.
 * If the stack is empty, it will return 0.
 * If stack is NULL, behaviour is undefined.
 */
size_t StackSize(const stack_t *stack);

/*
 * Returns 1 if the stack is empty, and 0 otherwise.
 * If stack is NULL, behaviour is undefined.
 */
int StackIsEmpty(const stack_t *stack);

/*
 * Returns the capacity of the stack.
 * If stack is NULL, behaviour is undefined.
 */
size_t StackCapacity(const stack_t *stack);

#endif   /* __STACK_H_OL97_ILRD__ */






















