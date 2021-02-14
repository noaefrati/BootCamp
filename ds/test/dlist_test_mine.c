/*************************************************************************** 
 * Description: Testing for doubly linked list functions
 * Author: Noa
 * Reviewer: 
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdlib.h>            /* malloc, free                             */
#include <string.h>            /* strlen                                   */
#include <assert.h>            /* assert                                   */
#include <stdio.h>             /* printf                                   */
#include "dlist.h"             /*  dubly linked list functions             */
#include "tests.h"             /* tools for easy and nicely styled testing */

void DLLCreateDestroyTest(void);
void DLLTest1(void);
int main ()
{
	DLLCreateDestroy();
	DLLTest1();
	return 0;
}

void DLLCreateDestroyTest(void)
{
	dllist_t *dlst = DLLCreate();
	if (NULL == dlst)
	{
		printf("DLLCreate FAILED!\n");
	}
	else
	{
		printf("DLLCreate SUCCESS!\n");
	}
	DLLDestroy(dlst);
	
}

void DLLTest1(void)
{
	char str[] = "hello multiverse!";
	dllist_iter_t iter = NULL;
	
	dllist_t *lst = DLLCreate();
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 1);
	TEST("DLLSize", DLLSize(lst), 0);
	
	iter = DLLPushBack(lst, str + 0);
	if (DLLIsSameIter(DLLEnd(lst), iter))
	{
		printf("PushBack Failed in line %d\nExiting Test1\n", __LINE__);
		DLLDestroy(lst);
		return ;
	}
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 1);
	TEST("Contents of List", IsDLListAsExpected(lst, "h"), 1);
	
	iter = DLLPushFront(lst, str + 1);
	if (DLLIsSameIter(DLLEnd(lst), iter))
	{
		printf("PushFront Failed in line %d\nExiting Test1\n", __LINE__);
		DLLDestroy(lst);
		return ;
	}
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 2);
	TEST("Contents of List", IsDLListAsExpected(lst, "eh"), 1);
	
	DLLPopBack(lst);
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 1);
	TEST("Contents of List", IsDLListAsExpected(lst, "e"), 1);
	
	DLLPopFront(lst);
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 1);
	TEST("DLLSize", DLLSize(lst), 0);
	TEST("Contents of List", IsDLListAsExpected(lst, ""), 1);
	
	iter = DLLPushBack(lst, str + 2);
	if (DLLIsSameIter(DLLEnd(lst), iter))
	{
		printf("PushBack Failed in line %d\nExiting Test1\n", __LINE__);
		DLLDestroy(lst);
		return ;
	}
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 1);
	TEST("Contents of List", IsDLListAsExpected(lst, "l"), 1);
	
	DLLSetData(iter, str + 6);
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 1);
	TEST("Contents of List", IsDLListAsExpected(lst, "m"), 1);
	
	iter = DLLPushBack(lst, str + 3);
	if (DLLIsSameIter(DLLEnd(lst), iter))
	{
		printf("PushBack Failed in line %d\nExiting Test1\n", __LINE__);
		DLLDestroy(lst);
		return ;
	}
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 2);
	TEST("Contents of List", IsDLListAsExpected(lst, "ml"), 1);
	
	iter = DLLPushFront(lst, str + 4);
	if (DLLIsSameIter(DLLEnd(lst), iter))
	{
		printf("PushFront Failed in line %d\nExiting Test1\n", __LINE__);
		DLLDestroy(lst);
		return ;
	}
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 3);
	TEST("Contents of List", IsDLListAsExpected(lst, "oml"), 1);
	
	if (0 != DLLInsertBefore(DLLPrev(DLLPrev(DLLEnd(lst))), str + 5))
	{
		printf("InsertBefore Failed in line %d\nExiting Test1\n", __LINE__);
		DLLDestroy(lst);
		return ;
	}
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 4);
	TEST("Contents of List", IsDLListAsExpected(lst, "o ml"), 1);
	
	DLLRemove(DLLNext(DLLBegin(lst)));
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 3);
	TEST("Contents of List", IsDLListAsExpected(lst, "oml"), 1);
	
	DLLRemove(DLLNext(DLLBegin(lst)));
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 2);
	TEST("Contents of List", IsDLListAsExpected(lst, "ol"), 1);
	
	DLLSetData(DLLBegin(lst), str + 7);
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 2);
	TEST("Contents of List", IsDLListAsExpected(lst, "ul"), 1);
	
	DLLSetData(DLLPrev(DLLEnd(lst)), str + 9);
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 2);
	TEST("Contents of List", IsDLListAsExpected(lst, "ut"), 1);
	
	DLLDestroy(lst);
	
}
	
