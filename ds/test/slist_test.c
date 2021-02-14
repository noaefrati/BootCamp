#include <stdio.h>
#include "slist.h"

int SLLCreateDestroyTest(void);
int SLLPushBackTest(void);
int SLLSetDataTest(void);
int SLLInsertBeforeTest(void);
int SLLIsEmptyTest(void);
int SLLRemoveTest(void);
int SLLPopBackTest(void);
int SLLNextTest(void);
int SLLFindTest(void);
int SLLBeginAndEndTest(void);
int SLLForEachTest(void);
int SLLIsSame(void);

int main()
{
	SLLCreateDestroyTest();
	SLLPushBackTest();
	SLLSetDataTest();
	SLLInsertBeforeTest();
	SLLIsEmptyTest();
	SLLRemoveTest();
	SLLPopBackTest();
	SLLNextTest();
	SLLFindTest();
	SLLBeginAndEndTest();
	SLLForEachTest();
	SLLIsSame();
	return (0);
}
int SLListCreateDestroyTest(void)
{
	sllist_t *list = SLLCreate();
	
	if (NULL == list)
	{
		return (1); 
	}
	SLLDestroy(list);
	
	printf("\n Create and Destroy SUCCESSED!\n");
	
	return (0);
	
}
int SLLPushBackTest(void)
{ 
	sllist_t *list = SLLCreate();
	int a = 10;
	int b = 20;
	int c = 30;
	sllist_iter_t iter1 =  SLLPushBack(list, &a);
	sllist_iter_t iter2 =  SLLPushBack(list, &b);
	sllist_iter_t iter3 =  SLLPushBack(list, &c);
	
	if (a != *(int *)SLLGetData(iter1))
	{
		printf("SLListPushBack FAILED\n");
		SLLDestroy(list);
		return (1);
	}
	if (b != *(int *)SLLGetData(iter2))
	{
		printf("SLListPushBack FAILED\n");
		SLLDestroy(list);
		return (1);
	}
	if (c != *(int *)SLLGetData(iter3))
	{
		printf("SLListPushBack FAILED\n");
		SLLDestroy(list);
		return (1);
	}
	SLLDestroy(list);
	printf("\nSLListPushBack SUCCESSED\n");

	return (0);
}

int SLLSetDataTest(void)
{
	sllist_t *list = SLLCreate();
	int a = 10;
	int b = 20;
	int c = 30;
	sllist_iter_t iter1 =  SLLPushBack(list, &a);
	sllist_iter_t iter2 =  SLLPushBack(list, &b);
	sllist_iter_t iter3 =  SLLPushBack(list, &c);
		
	
	if (0 != SLLSetData(iter1, &b))
	{
		printf("\nSLListSetDataTest FAILED\n");
		SLLDestroy(list);
		return (1);
	}
	if (0 != SLLSetData(iter2, &c))
	{
		printf("\nSLListSetDataTest FAILED\n");
		SLLDestroy(list);
		return (1);
	}
	if (0 != SLLSetData(iter3, &a))
	{
		printf("\nSLListSetDataTest FAILED\n");
		SLLDestroy(list);
		return (1);
	}
	
	printf("\nSLListSetDataTest SUCCESSED\n");
	SLLDestroy(list);
	return (0);
	
}
int SLLInsertBeforeTest(void)
{
	sllist_t *list = SLLCreate();
	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;
	sllist_iter_t iter1 =  SLLPushBack(list, &a);
	sllist_iter_t iter2 =  SLLPushBack(list, &b);
	sllist_iter_t iter3 =  SLLPushBack(list, &c);
	
	if (0 != SLLInsertBefore(iter1,&b))
	{
		printf("\nSLListInsertBefore FAILED\n");
		SLLDestroy(list);
		return (1);		
	}
	if (0 != SLLInsertBefore(iter1,&c))
	{
		printf("\nSLListInsertBefore FAILED\n");
		SLLDestroy(list);
		return (1);		
	}
	if (0 != SLLInsertBefore(iter1,&d))
	{
		printf("\nSLListInsertBefore FAILED\n");
		SLLDestroy(list);
		return (1);		
	}
	SLLDestroy(list);
	printf("\nSLListInsertBefore SUCCESSED\n");
	return (0);
}

int SLLPopBackTest(void)
{
	sllist_t *list = SLLCreate();
	int a = 10;
	int b = 20;
	int c = 30;
	size_t size_expected = 3;
	sllist_iter_t iter1 =  SLLPushBack(list, &a);
	sllist_iter_t iter2 =  SLLPushBack(list, &b);
	sllist_iter_t iter3 =  SLLPushBack(list, &c);
	
	if (size_expected !=  SLLSize(list))
	{
		printf("\nSLListSize FAILED\n");
		SLLDestroy(list);
		return (1);		
	}
	--size_expected;
	SLLPopBack(list);
	
	if (size_expected !=  SLLSize(list))
	{
		printf("\nSLListPopBack FAILED\n");
		SLLDestroy(list);
		return (1);		
	}
	--size_expected;
	SLLPopBack(list);
	
	if (size_expected !=  SLLSize(list))
	{
		printf("\nSLListPopBack FAILED\n");
		SLLDestroy(list);
		return (1);		
	}
	
	printf("\nSLListPopBack SUCCESSED\n");
	SLLDestroy(list);
	return (0);

}
int SLLRemoveTest(void)
{
	sllist_t *list = SLLCreate();
	int a = 10;
	int b = 20;
	int c = 30;
	sllist_iter_t iter1 =  SLLPushBack(list, &a);
	sllist_iter_t iter2 =  SLLPushBack(list, &b);
	sllist_iter_t iter3 =  SLLPushBack(list, &c);
	SLLRemove(list, iter1);
	SLLRemove(list, iter2);
	SLLRemove(list, iter3);
	
	if (0 != SLLIsEmpty(list))
	{
		printf("\nSLListRemove FAILED\n");
		SLLDestroy(list);
		return (1);		
	}
	
	SLLDestroy(list);
	printf("\nSLListRemove SUCCESSED\n");
	return (0);
	
}
int SLLIsEmptyTest(void)
{
	sllist_t *list = SLLCreate();
	if (0 != SLLIsEmpty(list))
	{
		printf("\nSLLIsEmpty FAILED\n");
		SLLDestroy(list);
		return (1);		
	}
	
	printf("\nSLLIsEmpty SUCCESSED\n");
	SLLDestroy(list);
	return (0);
}
int SLLNextTest(void)
{
	sllist_t *list = SLLCreate();
	int a = 10;
	int b = 20;
	int c = 30;
	sllist_iter_t iter1 =  SLLPushBack(list, &a);
	sllist_iter_t iter2 =  SLLPushBack(list, &b);
	sllist_iter_t iter3 =  SLLPushBack(list, &c);
	
	if (iter2 != SLLNext(iter1) && iter3 != SLLNext(iter2))
	{
		printf("\nSLListNext FAILED\n");
		SLLDestroy(list);
		return (1);	
	}
	if (NULL != SLLNext(iter3))
	{
		printf("\nSLListNext FAILED\n");
		SLLDestroy(list);
		return (1);	
	}
	
	SLLDestroy(list);
	printf("\nSLListNext SUCCESSED\n");
	return (1);	
}

int SLLBeginAndEndTest(void)
{
	sllist_t *list = SLLCreate();
	int a = 10;
	int b = 20;
	int c = 30;
	sllist_iter_t iter1;
	sllist_iter_t iter2;
	sllist_iter_t iter3;
	
	if (NULL != SLLBegin(list))
	{
		printf("\nSLListBegin FAILED\n");
		SLLDestroy(list);
		return (1);	
	}
	
	iter1 =  SLLPushBack(list, &a);
	iter2 =  SLLPushBack(list, &b);
	iter3 =  SLLPushBack(list, &c);
	
	if (iter1 != SLLBegin(list))
	{
		printf("\nSLListBegin FAILED\n");
		SLLDestroy(list);
		return (1);	
	}
	if(NULL != SLLEnd(list))
	{
		printf("\nSLListEnd FAILED\n");
		SLLDestroy(list);
		return (1);	
	}
	
	
	SLLDestroy(list);
	printf("\nSLListEnd  and SLListBegin SUCCESSED\n");
	return (0);	
}
int SLLIsSameTest(void)
{
	sllist_t *list = SLLCreate();
	int a = 10;
	int b = 20;
	int c = 30;
	sllist_iter_t iter1 =  SLLPushBack(list, &a);
	sllist_iter_t iter2 =  SLLPushBack(list, &b);
	sllist_iter_t iter3 =  SLLPushBack(list, &c);
	
	if (0 != SLLIsSame(iter1, iter2))
	{
		printf("\nSLListIsSame FAILED\n");
		SLLDestroy(list);
		return (1);	
	}
	if(1 != SLLIsSame(iter3, iter3))
	{
		printf("\nSLListIsSame FAILED\n");
		SLLDestroy(list);
		return (1);	
	}
	
	SLLDestroy(list);
	printf("\nSLListIsSame SUCCESSED\n");
	return (0);	
}	

int SLLFindTest(void)
{
	sllist_t *list = SLLCreate();
	char a = 'A';
	char b = 'B';
	char c = 'C';
	sllist_iter_t iter1 =  SLLPushBack(list, &a);
	sllist_iter_t iter2 =  SLLPushBack(list, &b);
	sllist_iter_t iter3 =  SLLPushBack(list, &c);
	
	if(0 !=  SLLFind(list, &a, &Is_Match(const void *one, const void *other)))
	{
		printf("\nSLListFind FAILED\n");
		SLLDestroy(list);
		return (1);	
	}
	SLLDestroy(list);
	printf("\nSLListFind SUCCESSED\n");
	
	return (0);	
}

int SLLForEachTest(void)
{
	sllist_t *list = SLLCreate();
	char a = 'A';
	char b = 'B';
	char c = 'C';
	char d = 'D';
	sllist_iter_t iter1 =  SLLPushBack(list, &a);
	sllist_iter_t iter2 =  SLLPushBack(list, &b);
	sllist_iter_t iter3 =  SLLPushBack(list, &c);
	sllist_iter_t iter4 =  SLLPushBack(list, &d);
	
	if ( 0 != SLLForEach(list, iter1, iter4, &PrintIter(void *data, void *params), void *params))
	{
		printf("\nSLListForEach FAILED\n");
		SLLDestroy(list);
		return (1);	
	}
	
	SLLDestroy(list);
	printf("\nSLListForEach SUCCESSED\n");
	return (0);	

}

