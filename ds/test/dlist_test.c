/*************************************************************************** 
 * Description: Testing for doubly linked list functions
 * Author: Oriel Nofekh
 * Reviewer: 
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>    /* printf */
#include <stdlib.h>   /* malloc, free */
#include <string.h>   /* strlen */
#include <assert.h>   /* assert */
#include "dlist.h"    /* dllist_t, node_t and dllist_iter_t 
                                  and declarations of all its functions */
/*#include "tests.h"*/              /* tools for easy and nicely styled testing */





/******************************************************************************/
/***                        Color Defines   		                        ***/
/******************************************************************************/
#define DEF     "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

/******************************************************************************/
/***                      Public functions declarations                     ***/
/******************************************************************************/
static int test_counter_g = 0;
static int success_counter_g = 0;

#define TEST(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEF, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)





/*****************************************************************************/


typedef struct
{
	int ID;
	char class;
} student_t;


/*****************************************************************************/


/* Used as "action" for the ForEach function */
int Print(void *data, void *params)
{
	(void) params;
	printf("Data = %d\n", *(int *) data);
	return 0;
}

/* Used as "action" for the ForEach function */
int Power3Times(void *data, void *params)
{
	*(int *) data = (*(int *) params) * 
	                (*(int *) data) * (*(int *) data) * (*(int *) data);
	return 0;
}

/* Used as "action" for the ForEach function */
int IsNegative(void *data, void *params)
{
	(void) params;
	if (0 > (*(int *) data))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* Used as "is_match" for the Find function */
int IsMatchValue(const void *one, const void *other)
{
	if ((*(int *) one) == (*(int *) other))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* Used as "is_match" for the Find function */
int IsSameAddress(const void *one, const void *other)
{
	if ((*(int *) one) == (*(int *) other))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int IsSameClass(const void *one, const void *other)
{
	student_t *student1 = (student_t *) one;
	student_t *student2 = (student_t *) other;
	
	if (student1->class == student2->class)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*****************************************************************************/


/* assuming the 'data' in each element of the list is a pointer to char,
   this function checks whether the chars stored in the list are the same as 
   the ones stored in the n'th first characters of 'expected'. */
static int IsDLListAsExpected(dllist_t *lst, const char *expected)
{
	dllist_iter_t iter = DLLBegin(lst);
	dllist_iter_t end_iter = DLLEnd(lst);
	
	for (; !DLLIsSameIter(iter, end_iter) && '\0' != *expected; 
	       iter = DLLNext(iter), ++expected)
	{
		if (*(char *) DLLGetData(iter) != *expected)
		{
			return 0;
		}
	}
	
	if (DLLIsSameIter(iter, end_iter) && '\0' == *expected)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*****************************************************************************/


static void TestCreateDestroy(void)
{
	dllist_t *lst = DLLCreate();
	
	DLLDestroy(lst);
}



static int Test1(void)
{
	/* 
	tests basic functions: 
	    Next, Prev, Begin, End,
	    IsEmpty, Size,
	    PushBack, PopBack, PushFront, PopFront,
	    InsertBefore, Remove, 
	    SetData, GetData (is used inside "IsDLListAsExpected")
	*/
	
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
		return 1;
	}
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 1);
	TEST("Contents of List", IsDLListAsExpected(lst, "h"), 1);
	
	iter = DLLPushFront(lst, str + 1);
	if (DLLIsSameIter(DLLEnd(lst), iter))
	{
		printf("PushFront Failed in line %d\nExiting Test1\n", __LINE__);
		DLLDestroy(lst);
		return 1;
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
		return 1;
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
		return 1;
	}
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 2);
	TEST("Contents of List", IsDLListAsExpected(lst, "ml"), 1);
	
	iter = DLLPushFront(lst, str + 4);
	if (DLLIsSameIter(DLLEnd(lst), iter))
	{
		printf("PushFront Failed in line %d\nExiting Test1\n", __LINE__);
		DLLDestroy(lst);
		return 1;
	}
	
	TEST("DLLIsEmpty", DLLIsEmpty(lst), 0);
	TEST("DLLSize", DLLSize(lst), 3);
	TEST("Contents of List", IsDLListAsExpected(lst, "oml"), 1);
	
	if (0 != DLLInsertBefore(DLLPrev(DLLPrev(DLLEnd(lst))), str + 5))
	{
		printf("InsertBefore Failed in line %d\nExiting Test1\n", __LINE__);
		DLLDestroy(lst);
		return 1;
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
	
	return 0;
}



static int Test2(void)
{
	/* tests the ForEach function */
	
	int arr1[] = {1,2,3,4,5,6,7,8,9,10};
	int arr2[] = {1,2,3,4,5,6,7,8,9,10};
	int arr3[] = {10,80,270,640,1250,2160,3430,5120,7290,10000};
	size_t arr1_len = sizeof(arr1) / sizeof(arr1[0]);
	size_t i = 0;
	int status = 0;
	int param = 10;
	int minus = -5;
	dllist_iter_t iter = NULL;
	
	dllist_t *lst = DLLCreate();
	
	/********************* Test A - Power3Times *********************/
	
	for (i = 0; i < arr1_len; ++i)
	{
		iter = DLLPushBack(lst, arr1 + i);
	}
	
	/* check everything was entered as expected */
	iter = DLLBegin(lst);
	for (i = 0; i < arr1_len; ++i, iter = DLLNext(iter))
	{
		TEST("PushBack", *(int *) DLLGetData(iter), arr2[i]);
	}
	
	status = DLLForEach(DLLBegin(lst), 
                            DLLEnd(lst),
                            &Power3Times,
                            &param);
	if (0 != status)
	{
		printf("DLLForEach failed in line %d\nExiting Test2\n", __LINE__);
		DLLDestroy(lst);
		return 1;
	}
	
	iter = DLLBegin(lst);
	for (i = 0; i < arr1_len; ++i, iter = DLLNext(iter))
	{
		TEST("PushBack", *(int *) DLLGetData(iter), arr3[i]);
	}
	
	/********************* Test B - IsNegative *********************/
	
	status = DLLForEach(DLLBegin(lst), 
                            DLLEnd(lst),
                            &IsNegative,
                            NULL);
	TEST("DLLForEach", status, 0);   /* should not have failed, all is positive */
	
	DLLSetData(DLLNext(DLLBegin(lst)), &minus);
	
	status = DLLForEach(DLLBegin(lst), 
                            DLLEnd(lst),
                            &IsNegative,
                            NULL);
	TEST("DLLForEach", status, 1);   /* should have failed, not all is positive */
	
	status = DLLForEach(DLLNext(DLLNext(DLLBegin(lst))), 
                            DLLEnd(lst),
                            &IsNegative,
                            NULL);
	TEST("DLLForEach", status, 0);   /* should not have failed, all after begin->next is positive */
	
	arr1[6] = -7;
	
	status = DLLForEach(DLLBegin(lst), 
                            DLLEnd(lst),
                            &IsNegative,
                            NULL);
	TEST("DLLForEach", status, 1);   /* should have failed, not all is positive */
	
	/* Destroy list */
	DLLDestroy(lst);
	
	return 0;
}



static int Test3(void)
{
	/********************* Find: Test A - IsMatchValue *********************/
	
	int arr1[] = {10,80,270,640,1250,2160,3430,5120,7290,10000};
	int value = arr1[3];
	size_t arr1_len = sizeof(arr1) / sizeof(arr1[0]);
	size_t i = 0;
	dllist_iter_t iter = NULL;
	
	dllist_t *lst = DLLCreate();
	
	for (i = 0; i < arr1_len; ++i)
	{
		iter = DLLPushBack(lst, arr1 + i);
		if (DLLIsSameIter(DLLEnd(lst), iter))
		{
			printf("PushBack Failed in line %d\nExiting Test3\n", __LINE__);
			DLLDestroy(lst);
			return 1;
		}
	}
	
	iter = DLLFind(DLLBegin(lst),
	               DLLEnd(lst),
	               &value,
	               &IsMatchValue);
	TEST("DLLFind", *(int *) DLLGetData(iter), value);
	TEST("DLLFind", iter, DLLNext(DLLNext(DLLNext(DLLBegin(lst)))));
	
	DLLSetData(DLLBegin(lst), arr1 + 3);
	
	iter = DLLFind(DLLBegin(lst),
	               DLLEnd(lst),
	               &value,
	               &IsMatchValue);
	TEST("DLLFind", *(int *) DLLGetData(iter), value);
	TEST("DLLFind", iter, DLLBegin(lst));
	
	iter = DLLFind(DLLNext(DLLNext(DLLNext(DLLNext(DLLBegin(lst))))),
	               DLLPrev(DLLEnd(lst)),
	               &value,
	               &IsMatchValue);
	TEST("DLLFind", iter, DLLPrev(DLLEnd(lst)));
	
	DLLDestroy(lst);
	
	return 0;
}



static int Test4(void)
{
	/********************* Find: Test B - IsSameClass *********************/
	
	dllist_t *lst = DLLCreate();
	dllist_t *dest = DLLCreate();
	student_t student_zero = {0, 'A'};   /* a student from class 'A' */
	student_t students[10];
	size_t students_len = sizeof(students) / sizeof(students[0]);
	size_t i = 0;
	int status = 0;
	dllist_iter_t iter = NULL;
	for (i = 0; i < students_len; ++i)
	{
		students[i].ID = 1000 + i;
	}
	students[0].class = 'A';
	students[1].class = 'A';
	students[2].class = 'C';
	students[3].class = 'C';
	students[4].class = 'C';
	students[5].class = 'A';
	students[6].class = 'B';
	students[7].class = 'B';
	students[8].class = 'B';
	students[9].class = 'A';
	
	for (i = 0; i < students_len; ++i)
	{
		iter = DLLPushBack(lst, students + i);
		if (DLLIsSameIter(DLLEnd(lst), iter))
		{
			printf("PushBack Failed in line %d\nExiting Test4\n", __LINE__);
			DLLDestroy(lst);
			DLLDestroy(dest);
			return 1;
		}
	}
	
	TEST("PushBack", DLLSize(lst), students_len);
	
	
	
	/************ we will first use Find ************/
	
	iter = DLLFind(DLLBegin(lst),
	               DLLEnd(lst),
	               &student_zero,
	               &IsSameClass);
	if (DLLIsSameIter(iter, DLLEnd(lst)))
	{
		printf("Find Failed to find what it should have found in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	TEST("Find", ((student_t *) DLLGetData(iter))->class, student_zero.class);
	TEST("Find", ((student_t *) DLLGetData(iter))->ID, 1000 + 0);
	TEST("Find", iter, DLLBegin(lst));
	
	iter = DLLFind(DLLNext(iter),
	               DLLEnd(lst),
	               &student_zero,
	               &IsSameClass);
	if (DLLIsSameIter(iter, DLLEnd(lst)))
	{
		printf("Find Failed to find what it should have found in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	TEST("Find", ((student_t *) DLLGetData(iter))->class, student_zero.class);
	TEST("Find", ((student_t *) DLLGetData(iter))->ID, 1000 + 1);
	TEST("Find", iter, DLLNext(DLLBegin(lst)));
	
	iter = DLLFind(DLLNext(iter),
	               DLLEnd(lst),
	               &student_zero,
	               &IsSameClass);
	if (DLLIsSameIter(iter, DLLEnd(lst)))
	{
		printf("Find Failed to find what it should have found in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	TEST("Find", ((student_t *) DLLGetData(iter))->class, student_zero.class);
	TEST("Find", ((student_t *) DLLGetData(iter))->ID, 1000 + 5);
	TEST("Find", iter, DLLNext(DLLNext(DLLNext(DLLNext(DLLNext(DLLBegin(lst)))))));
	
	iter = DLLFind(DLLNext(iter),
	               DLLEnd(lst),
	               &student_zero,
	               &IsSameClass);
	if (DLLIsSameIter(iter, DLLEnd(lst)))
	{
		printf("Find Failed to find what it should have found in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	TEST("Find", ((student_t *) DLLGetData(iter))->class, student_zero.class);
	TEST("Find", ((student_t *) DLLGetData(iter))->ID, 1000 + 9);
	TEST("Find", iter, DLLPrev(DLLEnd(lst)));
	
	iter = DLLFind(DLLNext(iter),
	               DLLEnd(lst),
	               &student_zero,
	               &IsSameClass);
	TEST("Find", iter, DLLEnd(lst));
	
	
	
	/************ now we will use MultiFind ***********/
	
	status = DLLMultiFind(DLLBegin(lst),
	                      DLLEnd(lst),
	                      dest,
	                      &student_zero,
	                      &IsSameClass);
	if (0 != status)
	{
		printf("MultiFind Failed in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	
	TEST("MultiFind", DLLSize(lst), students_len);   /* make sure we didn't affect lst */
	TEST("MultiFind", DLLSize(dest), 4);
	iter = DLLBegin(dest);
	if (DLLIsSameIter(iter, DLLEnd(dest)))
	{
		printf("MultiFind Failed to find what it should have found in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	TEST("MultiFind", *(int *) DLLGetData(iter), 1000 + 0);
	iter = DLLNext(iter);
	if (DLLIsSameIter(iter, DLLEnd(dest)))
	{
		printf("MultiFind Failed to find what it should have found in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	TEST("MultiFind", *(int *) DLLGetData(iter), 1000 + 1);
	iter = DLLNext(iter);
	if (DLLIsSameIter(iter, DLLEnd(dest)))
	{
		printf("MultiFind Failed to find what it should have found in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	TEST("MultiFind", *(int *) DLLGetData(iter), 1000 + 5);
	iter = DLLNext(iter);
	if (DLLIsSameIter(iter, DLLEnd(dest)))
	{
		printf("MultiFind Failed to find what it should have found in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	TEST("MultiFind", *(int *) DLLGetData(iter), 1000 + 9);
	iter = DLLNext(iter);
	TEST("MultiFind", iter, DLLEnd(dest));
	
	for (i = 0; i < 4; ++i)
	{
		DLLPopBack(dest);
	}
	
	
	
	student_zero.class = 'B';   /************ now let's try this with B class ************/
	
	status = DLLMultiFind(DLLBegin(lst),
	                      DLLEnd(lst),
	                      dest,
	                      &student_zero,
	                      &IsSameClass);
	if (0 != status)
	{
		printf("MultiFind Failed in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	
	TEST("MultiFind", DLLSize(lst), students_len);   /* make sure we didn't affect lst */
	TEST("MultiFind", DLLSize(dest), 3);
	iter = DLLBegin(dest);
	if (DLLIsSameIter(iter, DLLEnd(dest)))
	{
		printf("MultiFind Failed to find what it should have found in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	TEST("MultiFind", *(int *) DLLGetData(iter), 1000 + 6);
	iter = DLLNext(iter);
	if (DLLIsSameIter(iter, DLLEnd(dest)))
	{
		printf("MultiFind Failed to find what it should have found in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	TEST("MultiFind", *(int *) DLLGetData(iter), 1000 + 7);
	iter = DLLNext(iter);
	if (DLLIsSameIter(iter, DLLEnd(dest)))
	{
		printf("MultiFind Failed to find what it should have found in line %d\nExiting Test4\n", __LINE__);
		DLLDestroy(lst);
		DLLDestroy(dest);
		return 1;
	}
	TEST("MultiFind", *(int *) DLLGetData(iter), 1000 + 8);
	iter = DLLNext(iter);
	TEST("MultiFind", iter, DLLEnd(dest));
	
	DLLDestroy(lst);
	DLLDestroy(dest);
	
	return 0;
}



static int Test5(void)
{
	/* now let's test Splice */
	
	char str1[] = "0123456789";
	size_t str1_len = strlen(str1);
	size_t i = 0;
	dllist_iter_t iter = NULL;
	
	dllist_t *lst1 = DLLCreate();
	dllist_t *lst2 = DLLCreate();
	
	for (i = 0; i < str1_len; ++i)
	{
		iter = DLLPushBack(lst1, str1 + i);
		if (DLLIsSameIter(DLLEnd(lst1), iter))
		{
			printf("PushBack Failed in line %d\nExiting Test3\n", __LINE__);
			DLLDestroy(lst1);
			return 1;
		}
		
		iter = DLLPushBack(lst2, str1 + i);
		if (DLLIsSameIter(DLLEnd(lst2), iter))
		{
			printf("PushBack Failed in line %d\nExiting Test3\n", __LINE__);
			DLLDestroy(lst2);
			return 1;
		}
	}
	
	/************ splice inside the same list ************/
	
	TEST("Size", DLLSize(lst1), str1_len);
	TEST("Contents of List", IsDLListAsExpected(lst1, "0123456789"), 1);
	
	DLLSplice(DLLBegin(lst1), DLLNext(DLLBegin(lst1)), DLLEnd(lst1));
	
	TEST("Size", DLLSize(lst1), str1_len);
	TEST("Contents of List", IsDLListAsExpected(lst1, "1234567890"), 1);
	
	DLLSplice(DLLBegin(lst1), DLLNext(DLLBegin(lst1)), DLLNext(DLLNext(DLLBegin(lst1))));
	
	TEST("Size", DLLSize(lst1), str1_len);
	TEST("Contents of List", IsDLListAsExpected(lst1, "2134567890"), 1);
	
	DLLSplice(DLLPrev(DLLPrev(DLLEnd(lst1))), DLLEnd(lst1), DLLPrev(DLLPrev(DLLPrev(DLLEnd(lst1)))));
	
	TEST("Size", DLLSize(lst1), str1_len);
	TEST("Contents of List", IsDLListAsExpected(lst1, "2134567908"), 1);
	
	/************ splice between two lists ************/
	
	DLLSplice(DLLBegin(lst1), DLLEnd(lst1), DLLEnd(lst2));
	
	TEST("Size", DLLSize(lst1), 0);
	TEST("Size", DLLSize(lst2), 2*str1_len);
	TEST("Contents of List", IsDLListAsExpected(lst2, "0123456789" "2134567908"), 1);
	
	DLLSplice(DLLNext(DLLBegin(lst2)), DLLPrev(DLLPrev(DLLEnd(lst2))), DLLEnd(lst1));
	
	TEST("Size", DLLSize(lst1), 2*str1_len - 3);
	TEST("Size", DLLSize(lst2), 3);
	TEST("Contents of List", IsDLListAsExpected(lst1, "123456789" "21345679"), 1);
	TEST("Contents of List", IsDLListAsExpected(lst2, "0" "08"), 1);
	
	DLLDestroy(lst1);
	DLLDestroy(lst2);
	
	return 0;
}



static void TestDList(void)
{
	int status = 0;
	
	TestCreateDestroy();
	
	status += Test1();
	
	status += Test2();
	
	status += Test3();
	
	status += Test4();
	
	status += Test5();
	
	if (0 == status)
	{
		PASS;
	}
}



int main(void)
{
	TestDList();
	
	return 0;
}



