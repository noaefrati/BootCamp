#ifndef __RECURSION_H_OL97_ILRD__
#define __RECURSION_H_OL97_ILRD__

/*******************************************************************************
 * Description: Header file Containing API Definition for Recursion interface  *
 *              operations and declarations.                                   *
 *                                                                             *
 * Infinity Labs - OL97                                                        *
 ******************************************************************************/
#include "stack.h"
/******************************************************************************/
typedef struct node
{
	void *data;
	struct node *next;
}node_t;
/******************************************************************************/ 
int FibonacciIter(int element_index);
int FibonacciRec(int element_index);
node_t *FlipList(node_t *node);
int StackSort(stack_t *stack);
size_t StrLen(const char *str);
int StrCmp(const char *str1, const char *str2);
char *StrCpy (char *dest , const char *src);
char *StrCat(char *dest , const char *src);
char *StrStr(const char *haystack, const char *needle);
/******************************************************************************/

#endif /* __RECURSION_H_OL97_ILRD__ */
