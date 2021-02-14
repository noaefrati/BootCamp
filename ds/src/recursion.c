/******************************************************************************* 
 * Description: implementation of previous exercises with recursion.           *
 * Author: Noa Efrati                                                          *
 * Reviewer: Carolina Kats                                                     *
 * Date: 30.12.20                                                              *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/

#include <assert.h>      /*assert                                             */
#include "recursion.h"   /* recursion API                                     */

/******************************************************************************/
/***                     Private function declarations                      ***/
/******************************************************************************/
static void StackSortImpl(stack_t *stack, int value);
static int ImplFibonacciRec(int element_index, int first, int second);
static node_t *ImplFlipList(node_t *prev, node_t *current);
static size_t ImplStrLen(char *str, size_t size);

static char *ImplStrStr(const char *haystack,
				        const char *needle,
				        int hy_ind, 
				        int ndl_ind);
/******************************************************************************/
/******************************************************************************/

int FibonacciIter(int element_index)
{
	int i = 0;
	int first = 0;
	int second = 1;
	int third = 0;
	
	for (; element_index > i; ++i)
	{
		third = first + second;
		first = second;
		second = third;
	}
	return first;
}
static int ImplFibonacciRec(int element_index, int first, int second)
{
	if (1 == element_index)
	{
		return second;
	}
	if (0 == element_index)
	{
		return 0;
	}
	
	return ImplFibonacciRec(element_index - 1, second, first + second);
}

int FibonacciRec(int element_index)
{
	return  ImplFibonacciRec(element_index, 0, 1);
}
/******************************************************************************/

static node_t *ImplFlipList(node_t *prev, node_t *current)
{
	node_t *next = NULL;

	assert(current);
	
	next = current->next;
	current->next = prev;

	if (NULL == next)
	{
		return current;
	}
		
	return ImplFlipList(current, next);
}

node_t *FlipList(node_t *node)
{
	assert(node);
	
	return ImplFlipList(NULL, node);
}
/******************************************************************************/


static void StackSortImpl(stack_t *stack, int value)
{
	int top_element = 0;

    if (1 == StackIsEmpty(stack) || value < *(int *)StackPeek(stack))
    {
        StackPush(stack, (void *)&value);
        return;
    }
 

    top_element = *(int *)StackPeek(stack);
    StackPop(stack); 
    StackSortImpl(stack, value);
    StackPush(stack, (void *)&top_element);
}

int StackSort(stack_t *stack)
{
	 int top_element = 0;
	
	 assert(stack);
	 
	 if (1 == StackIsEmpty(stack)) 
	 {
       return (1);
     }
     
      top_element = *(int *)StackPeek(stack);
      StackPop(stack);
 	  StackSort(stack);
 	 
 	  StackSortImpl(stack, top_element);
 	  
 	  return (0);
}
/******************************************************************************/


static size_t ImplStrLen(char *str, size_t size)
{
	assert(str);
	
	if ('\0' == *str)
	{
		return (size);
	}
	
	return ImplStrLen(str + 1, size + 1);
}
size_t StrLen(const char *str)
{
	char *runner = NULL;
	
	assert(str);
	
	runner = (char *)str;
	   
	return ImplStrLen(runner, 0);
}
/******************************************************************************/


int StrCmp(const char *str1, const char *str2)
{	
	char *runner1 = NULL;
	char *runner2 = NULL;
	
	assert(str1);
	assert(str2);
	
	runner1 = (char *)str1;
	runner2 = (char *)str2;
	
	if (('\0' == *runner1) || (0 != *runner1 - *runner2))
	{
		return (*runner1 - *runner2);
	}
  	
  
    return StrCmp(runner1 + 1, runner2 + 1);
			
}
/******************************************************************************/

char *StrCpy(char *dest , const char *src)
{
	assert(src);
	assert(dest);
	
	*dest = *(char *)src;
	
	if ('\0' == *(char *)src)
	{
		return dest;
	}
	
	StrCpy(dest + 1, (char *)src + 1);
	
	return dest;
}	
/******************************************************************************/

char *StrCat(char *dest , const char *src)
{
	char *runner = NULL;
	
	assert(dest);
	assert(src);
	
	runner = dest + StrLen(dest);
	StrCpy(runner, (char *)src);
	
	return dest;

}
/******************************************************************************/

static char *ImplStrStr(const char *haystack,
				      const char *needle,
				      int hy_ind, 
				      int ndl_ind)
{
	assert(haystack);
	assert(needle);
	
	if ('\0' == needle[ndl_ind])
	{
		return (char *)haystack + hy_ind - ndl_ind;
	}
	
	if ('\0' == haystack[hy_ind])
	{
		return (NULL);
	}
	if (haystack[hy_ind] == needle[ndl_ind])
	{
		return (ImplStrStr(haystack, needle, hy_ind + 1, ndl_ind + 1));
	}
  	
  	return ImplStrStr(haystack, needle, hy_ind + 1, 0);
	
}
char *StrStr(const char *haystack, const char *needle)
{
	assert(haystack);
	assert(needle);
	
	if ('\0' == *needle)
	{
		return (char *)haystack;
	}
	
	return ImplStrStr((char *)haystack, (char *)needle, 0, 0); 
}
/******************************************************************************/
