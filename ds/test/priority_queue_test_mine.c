/*****************************************************************************
* Description: Program to test Priority Queue implementation
* Author: Noa Efrati
* Reviewer:
*
* ILRD - OL97
******************************************************************************/

#include <stdio.h>      	/* printf()                                     */
#include "priority_queue.h"      	/* dlist core files                         */

#define RED     "\033[31m"	/* Red                                          */
#define DEF   "\033[0m"		/* DEFAULT                                      */
#define GREEN   "\033[32m"      /* Green */

#define TEST(name, real, expected) (((real) == (expected)) ? printf(GREEN "%s, SUCCESS on line %d\n" DEF, name, __LINE__): \
printf(RED "%s, failed on line %d\n" DEF, name, __LINE__))

struct student
{
	long *id;
	char *name;
};
typedef struct student student_t;

static int IsBiggerVal(const void *one, const void *other);
static void TestForSizeAndIsEmpty(void);
static void TestForCreateDestroy(void);
static void TestForSameIterAndBeginAndEnd(void);
static void TestForNextAndPrev(void);
static void TestForDataGet(void);
static void TestForInsertAndRemove(void);
static void TestForPopBack(void);
static void TestForPopFront(void);
static int Add10(void *num, void *params);
static void TestForEach(void);
static int NumEq(const void *data, const void *against);
static void TestForFindIf(void);
static void TestForFind(void);
static void TestForMerge(void);
int main(void)
{
	TestForCreateDestroy();
	TestForSizeAndIsEmpty();
	/*
	TestForSameIterAndBeginAndEnd();
	TestForNextAndPrev();
	TestForDataGet();
	TestForPopBack();
	TestForPopFront();
	TestForInsertAndRemove();
	TestForEach();
	TestForFind();
	TestForFindIf();
*/
	return 0;
}

static int IsBiggerVal(const void *one, const void *other)
{
	return  (*(const int *)one - *(const int *)other);
}
static void TestForCreateDestroy(void)
{
	pq_t *lst = PQCreate(IsBiggerVal);

	if (NULL != lst)
	{
		printf("create successed!\n");
		 PQDestroy(lst);
	}
	else
	{
		printf("create failed!\n");
	}
		
}
/*
 * Description: This function is used for getting the size of a given PQ 
 * pointed by que (amount of elements).
 * Return value: This function returns the number of elements in the PQ pointed 
 * to by que.
 * Time complexity: O(n).
 */
size_t PQSize(const pq_t *que);

/*
 * Description: This function returns whether the given PQ is empty.
 * Return value: 1 (true) if the size of PQ pointed by que is 0,
 * 0 (false) otherwise.
 * Time complexity: O(1).
 */ 
int PQIsEmpty(const pq_t *que);
static void TestForSizeAndIsEmpty(void)
{
	pq_t  *lst = PQCreate(IsBiggerVal);
	long id1 = 00001, id2 = 00010;
	
	
	TEST("TEST IsEmpty",PQIsEmpty(lst), 1);
	TEST("TEST Size",PQSize(lst), 0);
	
	/*
	SRTLSTInsert(lst, data2);
	SRTLSTInsert(lst, data);
	
	TEST("TEST IsEmpty :",SRTLSTIsEmpty(lst), 0);
	TEST("TEST Size :",SRTLSTSize(lst), 2);
	
	SRTLSTPopBack(lst);
	
	TEST("TEST IsEmpty :",SRTLSTIsEmpty(lst), 0);
	TEST("TEST Size :",SRTLSTSize(lst), 1);
		
	SRTLSTPopBack(lst);
	
	TEST("TEST IsEmpty :",SRTLSTIsEmpty(lst), 1);
	TEST("TEST Size :",SRTLSTSize(lst), 0);
	*/
	PQDestroy(lst);
}
/*
static void TestForSameIterAndBeginAndEnd(void)
{
	srtlst_t  *lst = SRTLSTCreate(IsBiggerVal);
	char *data1 = "00001";
	
	TEST("TestIsSameIter", SRTLSTIsSameIter(SRTLSTEnd(lst), SRTLSTBegin(lst)), 1);
	
	
	SRTLSTInsert(lst, data1);
	
	TEST("TestIsSameIter:", SRTLSTIsSameIter(SRTLSTEnd(lst), SRTLSTBegin(lst)), 0);
	
	SRTLSTDestroy(lst);	
}

static void TestForNextAndPrev(void)
{
	srtlst_t  *lst = SRTLSTCreate(IsBiggerVal);

	TEST("TestForNextAndPrev",SRTLSTIsSameIter(SRTLSTNext(SRTLSTEnd(lst)), SRTLSTEnd(lst)), 1);
	TEST("TestForEndBegin",SRTLSTIsSameIter((SRTLSTEnd(lst)), SRTLSTBegin(lst)), 1);
	


	SRTLSTDestroy(lst);	
}

static void TestForDataGet(void)
{
	srtlst_t  *lst = SRTLSTCreate(IsBiggerVal);
	int data2 = 00001, data1 = 00000;
	srtlst_iter_t iter;
	
	TEST("TestForGetData",SRTLSTGetData(SRTLSTEnd(lst)) , NULL);
	

	SRTLSTInsert(lst, &data1);
	iter = SRTLSTBegin(lst);
	TEST("TestForDataGet", *(int *)SRTLSTGetData(iter) , data1);
	
	SRTLSTInsert(lst, &data2);
	iter = SRTLSTBegin(lst);
	TEST("TestForDataGet", *(int *)SRTLSTGetData(iter) , data1);

	SRTLSTDestroy(lst);
}

static void TestForPopFront(void)
{
	srtlst_t  *lst = SRTLSTCreate(IsBiggerVal);
	srtlst_iter_t iter, iter2;
	int data = 10;
	int more_data = 20;
	
	TEST("TestForPopFont", SRTLSTInsert(lst, &data), 0);	
	iter = SRTLSTBegin(lst);
	TEST("TTestForPopFont", *(int *)SRTLSTGetData(iter) , data);
		
	TEST("TestForPopFont", SRTLSTInsert(lst, &more_data), 0);
	iter2 = SRTLSTNext(SRTLSTBegin(lst));
	TEST("TestForPopFont", *(int *)SRTLSTGetData(iter2) , more_data);

	SRTLSTPopFront(lst);
	SRTLSTPopFront(lst);	
	TEST("TestForPopFont",SRTLSTIsEmpty(lst), 1);
	
	SRTLSTDestroy(lst);
}

static void TestForPopBack(void)
{
	srtlst_t  *lst = SRTLSTCreate(IsBiggerVal);
	srtlst_iter_t iter, iter2;
	int data = 10;
	int more_data = 20;
	
	TEST("TestForPopBack", SRTLSTInsert(lst, &data), 0);	
	iter = SRTLSTBegin(lst);
	TEST("TTestForPopBack", *(int *)SRTLSTGetData(iter) , data);
		
	TEST("TestForPopBack", SRTLSTInsert(lst, &more_data), 0);
	iter2 = SRTLSTNext(SRTLSTBegin(lst));
	TEST("TestForPopBack", *(int *)SRTLSTGetData(iter2) , more_data);

	SRTLSTPopBack(lst);
	
	TEST("TestForPopBack", *(int *) SRTLSTGetData(SRTLSTBegin(lst)), data);
	TEST("TestForPopBack",SRTLSTIsEmpty(lst), 0);
	SRTLSTPopBack(lst);
		
	TEST("TestForPopBack",SRTLSTIsEmpty(lst), 1);
		
	SRTLSTDestroy(lst);
}

static void TestForInsertAndRemove(void)
{
	srtlst_t  *lst = SRTLSTCreate(IsBiggerVal);
	srtlst_iter_t iter, iter2;
	int data = 20;
	int more_data = 10;
	
	TEST("TestForInsert", SRTLSTInsert(lst, &data), 0);	
	iter = SRTLSTBegin(lst);
	TEST("TestForInsert", *(int *)SRTLSTGetData(iter) , data);
		
	TEST("TestForInsert", SRTLSTInsert(lst, &more_data), 0);
	iter2 = SRTLSTBegin(lst);
	TEST("TestForInsert", *(int *)SRTLSTGetData(iter2) , more_data);
	
	SRTLSTRemove(iter);
	SRTLSTRemove(iter2);
	TEST("TestRemove:", SRTLSTIsEmpty(lst), 1);
	TEST("TestRemove:", SRTLSTSize(lst), 0);
	
	SRTLSTDestroy(lst);
}

static void TestForFind(void)
{
	srtlst_t  *lst = SRTLSTCreate(IsBiggerVal);
	int data1[] = {10, 1, 20, 9};
	int value = 21;
	srtlst_iter_t iter, iter2;
	
	SRTLSTInsert(lst, &data1[0]);
	SRTLSTInsert(lst, &data1[1]);
	SRTLSTInsert(lst, &data1[2]);
	SRTLSTInsert(lst, &data1[3]);
	
	iter = SRTLSTFind(lst, SRTLSTBegin(lst),SRTLSTEnd(lst), &data1[2]);
	TEST("TestForFind",  SRTLSTIsSameIter(iter, SRTLSTEnd(lst)), 1);
	
	iter2 =  SRTLSTFind(lst, SRTLSTBegin(lst), SRTLSTEnd(lst), &value);
	TEST("TestForFind", SRTLSTIsSameIter(iter2, SRTLSTEnd(lst)), 0);
		
	SRTLSTDestroy(lst);
}

static int Add10(void *num, void *params)
{
	int *n = (int *)num;
	
	(void)params;
	
	*n += 10;
	
	return 0;
}

static void TestForEach(void)
{
	srtlst_t  *lst = SRTLSTCreate(IsBiggerVal);
	int value = 10;
	
	int data1[] = {10, 1, 20, 9};

	
	SRTLSTInsert(lst, &data1[0]);
	SRTLSTInsert(lst, &data1[1]);
	SRTLSTInsert(lst, &data1[2]);
	SRTLSTInsert(lst, &data1[3]);
	
	
	TEST("TestForEach", SRTLSTForEach(SRTLSTBegin(lst), SRTLSTEnd(lst), Add10, NULL), 0);
	
	TEST("TestForEach", *(int *) SRTLSTGetData(SRTLSTBegin(lst)), 11);
	
	TEST("TestForEach", *(int *) SRTLSTGetData(SRTLSTNext(SRTLSTBegin(lst))), 19);
		
	SRTLSTDestroy(lst);
}
static int NumEq(const void *data, const void *against)
{
	return (*(const int *)data == *(const int *)against);
}

static void TestForFindIf(void)
{
	srtlst_t  *lst = SRTLSTCreate(IsBiggerVal);
	int data1[] = {10, 1, 20, 9};
	
	SRTLSTInsert(lst, &data1[0]);
	SRTLSTInsert(lst, &data1[1]);
	SRTLSTInsert(lst, &data1[2]);
	SRTLSTInsert(lst, &data1[3]);


	TEST("TestForFindIf", SRTLSTFindIf(SRTLSTNext(SRTLSTBegin(lst)),
	     SRTLSTEnd(lst),
	     NumEq, &data1[1]),
	     SRTLSTEnd(lst));
	
	TEST("TestForFindIf", SRTLSTFind(SRTLSTBegin(lst),
	     SRTLSTEnd(lst),
	     NumEq, &data1[1]),
	     SRTLSTBegin(lst));
		
	SRTLSTDestroy(lst);	
}
/*
static void TestForMerge(void)
{
	srtlst_t  *src = SRTLSTCreate(IsBiggerVal);
	srtlst_t  *dst = SRTLSTCreate(IsBiggerVal);
	int data1[] = {10, 1, 20, 9};
	size_t size_src = 0, size_dst = 0;
	
	SRTLSTInsert(src, &data1[0]);
	SRTLSTInsert(src, &data1[1]);
	SRTLSTInsert(src, &data1[2]);
	SRTLSTInsert(src, &data1[3]);
	
	SRTLSTInsert(dst, &data1[0]);
	SRTLSTInsert(dst, &data1[1]);
	SRTLSTInsert(dst, &data1[2]);
	
	size_src = SRTLSTSize(src);
	size_dst = SRTLSTSize(dst);
	
	SRTLSTMerge(dst,src);
	
	TEST("TestMerge:", STRLSTIsEmpty(src), 1);
	TEST("TestMerge:", STRLSTIsEmpty(dst), 0);
	
	TEST("TestMerge:", SRTLSTSize(src), 0);
	TEST("TestMerge:", SRTLSTSize(dst), (size_src + size_dst));
	
	SRTLSTMerge(src, dst);	
	TEST("TestMerge:", STRLSTIsEmpty(src), 0);
	TEST("TestMerge:", STRLSTIsEmpty(dst), 1);
	
	TEST("TestMerge:", SRTLSTSize(dst), 0);
	TEST("TestMerge:", SRTLSTSize(src), (size_src + size_dst));

	STRLSTDestroy(src);
	STRLSTDestroy(dst);	

}

*/
