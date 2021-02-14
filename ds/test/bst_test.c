/*************************************************************************** 
 * Description: Testing of Implementations of Binary Sorted Tree (BST)
 * Author: Oriel Nofekh
 *
 * Infinity Labs OL97
 ***************************************************************************/


#include <stdio.h>     /* printf */
#include <assert.h>    /* assert */
#include "bst.h"       /* BST API */



/******************************************************************************/
/***                        Color Defines   		                      ***/
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

static int test_counter_g = 0;
static int success_counter_g = 0;

#define TEST(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEF, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)

#define TESTC(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %c, Expected: %c\n" DEF, name, __LINE__, (char) (real), (char) (expected)); \
    } while (0)

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)




struct node
{
	node_t *parent;
	node_t *left;
	node_t *right;
	void *data;
};

struct bst
{
	/* head is a node such that head.left is the root and head.right is the dummy end-node */
	node_t head;
	int (*cmp_func)(const void *data, const void *input);
};
/************************* Helper Functions *************************/

static int CompareInts(const void *one, const void *two)
{
	assert(one);
	assert(two);
	return (*(int *) one) - (*(int *) two);
}

static int IncrementInt(void *data, void *params)
{
	(void) params;
	++(*(int *) data);
	return 0;
}

static int AddToInt(void *data, void *params)
{
	(*(int *) data) += (*(int *) params);
	return 0;
}

static int IncrementIntIfNotZero(void *data, void *params)
{
	(void) params;
	if (0 != (*(int *) data))
	{
		++(*(int *) data);
		return 0;
	}
	else
	{
		return 1;
	}
}

/************************* Tests Functions *************************/

static void TestCreateDestroy(void)
{
	bst_t *tree = BSTCreate(&CompareInts);
	
	BSTDestroy(tree);
	
	printf(BOLDBLUE "Completed TestCreateDestroy\n" DEF);
}

static void Test0(void)
{
	
	
	int arr[] = {0,10,20,30,40,50,60,70,80,90};
	bst_iter_t iter = NULL;
	bst_t *tree = NULL;
	
	
	
	tree = BSTCreate(&CompareInts);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 1);
	TEST("Size", BSTSize(tree), 0);
	
	
	
	iter = BSTInsert(tree, arr+4);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 0);
	TEST("Size", BSTSize(tree), 1);
	

	iter = BSTInsert(tree, arr+5);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 0);
	
	TEST("Size", BSTSize(tree), 2);
	

	iter = BSTInsert(tree, arr+3);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 0);
	TEST("Size", BSTSize(tree), 3);
	
	
	
	
	iter = BSTBegin(tree);
	TEST("Data", *(int *) BSTGetData(iter), arr[3]);
	iter = BSTNext(iter);
	
	TEST("Data", *(int *) BSTGetData(iter), arr[4]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[5]);
	iter = BSTNext(iter);
	TEST("End Iter", BSTIsSameIter(iter, BSTEnd(tree)), 1);
	
	iter = BSTEnd(tree);
	
	iter = BSTPrev(iter);
	
	TEST("Data", *(int *) BSTGetData(iter), arr[5]);
	
	iter = BSTPrev(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[4]);
	iter = BSTPrev(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[3]);
	

	
	iter = BSTNext(BSTBegin(tree));
	TEST("Data", *(int *) BSTGetData(iter), arr[4]);
	BSTRemove(iter);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 0);
	TEST("Size", BSTSize(tree), 2);
	
	iter = BSTBegin(tree);
	TEST("Data", *(int *) BSTGetData(iter), arr[3]);
	BSTRemove(iter);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 0);
	TEST("Size", BSTSize(tree), 1);
	
	iter = BSTBegin(tree);
	TEST("Data", *(int *) BSTGetData(iter), arr[5]);
	BSTRemove(iter);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 1);
	TEST("Size", BSTSize(tree), 0);
	

	
	iter = BSTInsert(tree, arr+6);
	TEST("Data", *(int *) BSTGetData(iter), arr[6]);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 0);
	TEST("Size", BSTSize(tree), 1);


	
	BSTDestroy(tree);
	
	printf(BOLDBLUE "Completed Test0\n" DEF);
}

static void Test1(void)
{
	/* advanced test */
	
	int arr[] = {0,1,2,3,4,5,6,7,8,9,
	             10,11,12,13,14,15,16,17,18,19};
	bst_iter_t iter = NULL;
	bst_t *tree = NULL;
	
	/* create */
	
	tree = BSTCreate(&CompareInts);
	
	/* insert just a few, and check some edge cases:
	   prev(begin) should return itself
	   next(end) should return itself
	   prev(end) should return itself if the BST is empty */
	
	TEST("Prev(End)", BSTIsSameIter(BSTEnd(tree), BSTPrev(BSTEnd(tree))), 1);
	TEST("Next(End)", BSTIsSameIter(BSTEnd(tree), BSTNext(BSTEnd(tree))), 1);
	
	iter = BSTInsert(tree, arr+0);      /* 0 */
	TEST("Prev(Begin)", BSTIsSameIter(BSTBegin(tree), BSTPrev(BSTBegin(tree))), 1);
	TEST("Next(End)", BSTIsSameIter(BSTEnd(tree), BSTNext(BSTEnd(tree))), 1);
	
	iter = BSTInsert(tree, arr+3);      /* 0,3 */
	iter = BSTInsert(tree, arr+1);      /* 0,1,3 */
	iter = BSTInsert(tree, arr+2);      /* 0,1,2,3 */
	TEST("Prev(Begin)", BSTIsSameIter(BSTBegin(tree), BSTPrev(BSTBegin(tree))), 1);
	TEST("Next(End)", BSTIsSameIter(BSTEnd(tree), BSTNext(BSTEnd(tree))), 1);
	
	iter = BSTBegin(tree);
	BSTRemove(iter);                    /* 1,2,3 */
	iter = BSTBegin(tree);
	BSTRemove(iter);                    /* 2,3 */
	
	TEST("Prev(Begin)", BSTIsSameIter(BSTBegin(tree), BSTPrev(BSTBegin(tree))), 1);
	TEST("Next(End)", BSTIsSameIter(BSTEnd(tree), BSTNext(BSTEnd(tree))), 1);
	
	iter = BSTBegin(tree);
	BSTRemove(iter);                    /* 3 */
	iter = BSTBegin(tree);
	BSTRemove(iter);                    /* empty */
	
	TEST("Prev(End)", BSTIsSameIter(BSTEnd(tree), BSTPrev(BSTEnd(tree))), 1);
	TEST("Next(End)", BSTIsSameIter(BSTEnd(tree), BSTNext(BSTEnd(tree))), 1);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 1);
	
	/* insert and remove like a crazy person */
	
	iter = BSTInsert(tree, arr+5);      /* 5 */
	iter = BSTInsert(tree, arr+8);      /* 5,8 */
	BSTRemove(iter);                    /* 5 */
	
	iter = BSTBegin(tree);
	TEST("Size", BSTSize(tree), 1);
	TEST("Data", *(int *) BSTGetData(iter), arr[5]);
	
	iter = BSTInsert(tree, arr+4);      /* 4,5 */
	iter = BSTInsert(tree, arr+13);     /* 4,5,13 */
	BSTRemove(iter);                    /* 4,5 */
	
	iter = BSTBegin(tree);
	TEST("Size", BSTSize(tree), 2);
	TEST("Data", *(int *) BSTGetData(iter), arr[4]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[5]);
	
	iter = BSTInsert(tree, arr+3);      /* 3,4,5 */
	iter = BSTInsert(tree, arr+9);      /* 3,4,5,9 */
	BSTRemove(BSTBegin(tree));          /* 4,5,9 */
	
	iter = BSTBegin(tree);
	TEST("Size", BSTSize(tree), 3);
	TEST("Data", *(int *) BSTGetData(iter), arr[4]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[5]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[9]);
	
	iter = BSTInsert(tree, arr+2);      /* 2,4,5,9 */
	BSTRemove(iter);                    /* 4,5,9 */
	iter = BSTInsert(tree, arr+7);      /* 4,5,7,9 */
	iter = BSTInsert(tree, arr+6);      /* 4,5,6,7,9 */
	iter = BSTInsert(tree, arr+17);     /* 4,5,6,7,9,17 */
	
	BSTRemove(BSTBegin(tree));          /* 5,6,7,9,17 */
	
	iter = BSTBegin(tree);
	TEST("Size", BSTSize(tree), 5);
	TEST("Data", *(int *) BSTGetData(iter), arr[5]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[6]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[7]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[9]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[17]);
	
	BSTRemove(BSTNext(BSTBegin(tree))); /* 5,7,9,17 */
	BSTRemove(BSTBegin(tree));          /* 7,9,17 */
	iter = BSTInsert(tree, arr+3);      /* 3,7,9,17 */
	iter = BSTInsert(tree, arr+1);      /* 1,3,7,9,17 */
	BSTRemove(BSTPrev(BSTPrev(BSTEnd(tree))));   /* 1,3,7,17 */
	iter = BSTInsert(tree, arr+14);     /* 1,3,7,14,17 */
	iter = BSTInsert(tree, arr+0);      /* 0,1,3,7,14,17 */
	iter = BSTInsert(tree, arr+2);      /* 0,1,2,3,7,14,17 */
	iter = BSTInsert(tree, arr+5);      /* 0,1,2,3,5,7,14,17 */
	iter = BSTInsert(tree, arr+4);      /* 0,1,2,3,4,5,7,14,17 */
	iter = BSTInsert(tree, arr+6);      /* 0,1,2,3,4,5,6,7,14,17 */
	
	iter = BSTBegin(tree);
	TEST("Size", BSTSize(tree), 10);
	TEST("Data", *(int *) BSTGetData(iter), arr[0]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[1]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[2]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[3]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[4]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[5]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[6]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[7]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[14]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[17]);
	
	iter = BSTNext(BSTNext(BSTNext(BSTBegin(tree))));
	BSTRemove(iter);                    /* 0,1,2,4,5,6,7,14,17 */ 
	TEST("Size", BSTSize(tree), 9);
	
	iter = BSTNext((BSTBegin(tree)));
	BSTRemove(iter);                    /* 0,2,4,5,6,7,14,17 */ 
	TEST("Size", BSTSize(tree), 8);
	
	iter = BSTNext(BSTNext(BSTNext(BSTBegin(tree))));
	BSTRemove(iter);                    /* 0,2,4,6,7,14,17 */ 
	TEST("Size", BSTSize(tree), 7);
	
	iter = BSTBegin(tree);
	TEST("Data", *(int *) BSTGetData(iter), arr[0]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[2]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[4]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[6]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[7]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[14]);
	iter = BSTNext(iter);
	TEST("Data", *(int *) BSTGetData(iter), arr[17]);
	
	/* destroy */
	
	BSTDestroy(tree);
	
	printf(BOLDBLUE "Completed Test1\n" DEF);
}

static void Test2(void)
{
	/* simple test for BSTFind */
	
	int arr[] = {0,10,20,30,40,50,60,70,80,90};
	bst_iter_t iter = NULL;
	bst_t *tree = NULL;
	
	/* create */
	
	tree = BSTCreate(&CompareInts);
	
	/* insert */
	
	iter = BSTInsert(tree, arr+8);
	iter = BSTInsert(tree, arr+4);
	iter = BSTInsert(tree, arr+5);
	iter = BSTInsert(tree, arr+3);
	iter = BSTInsert(tree, arr+1);
	iter = BSTInsert(tree, arr+2);
	iter = BSTInsert(tree, arr+7);
	iter = BSTInsert(tree, arr+6);
	
	/* find */
	
	iter = BSTFind(tree, arr+4);
	
	TEST("Data", *(int *) BSTGetData(iter), arr[4]);
	TEST("Data", *(int *) BSTGetData(BSTPrev(iter)), arr[3]);
	TEST("Data", *(int *) BSTGetData(BSTNext(iter)), arr[5]);
	
	iter = BSTFind(tree, arr+7);
	TEST("Data", *(int *) BSTGetData(iter), arr[7]);
	TEST("Data", *(int *) BSTGetData(BSTPrev(iter)), arr[6]);
	TEST("Data", *(int *) BSTGetData(BSTNext(iter)), arr[8]);
	
	iter = BSTFind(tree, arr+0);
	TEST("End Iter", BSTIsSameIter(iter, BSTEnd(tree)), 1);
	
	iter = BSTFind(tree, arr+9);
	TEST("End Iter", BSTIsSameIter(iter, BSTEnd(tree)), 1);
	
	iter = BSTFind(tree, arr+8);
	TEST("Data", *(int *) BSTGetData(iter), arr[8]);
	TEST("Data", *(int *) BSTGetData(BSTPrev(iter)), arr[7]);
	TEST("End Iter", BSTIsSameIter(BSTNext(iter), BSTEnd(tree)), 1);
	
	/* destroy */
	
	BSTDestroy(tree);
	
	printf(BOLDBLUE "Completed Test2\n" DEF);
}

static void Test3(void)
{
	/* test 1 for BSTForEach */
	
	int arr[] = {-50,-40,-30,-20,-10,0,10,20,30,40,50};
	int copy_arr[] = {-50,-40,-30,-20,-10,0,10,20,30,40,50};
	int status = 0;
	bst_iter_t iter = NULL;
	bst_t *tree = NULL;
	
	/* create */
	
	tree = BSTCreate(&CompareInts);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 1);
	TEST("Size", BSTSize(tree), 0);
	
	/* insert */
	
	iter = BSTInsert(tree, arr+8);
	iter = BSTInsert(tree, arr+9);
	iter = BSTInsert(tree, arr+10);
	iter = BSTInsert(tree, arr+6);
	iter = BSTInsert(tree, arr+7);
	iter = BSTInsert(tree, arr+2);
	iter = BSTInsert(tree, arr+1);
	iter = BSTInsert(tree, arr+0);
	iter = BSTInsert(tree, arr+3);
	iter = BSTInsert(tree, arr+4);
	iter = BSTInsert(tree, arr+5);
	(void) iter;
	
	/* for each */
	
	status = BSTForEach(BSTBegin(tree), BSTEnd(tree),
                        &IncrementInt, NULL);
	
	TEST("ForEach", status, 0);
	TEST("ForEach", arr[0], copy_arr[0] + 1);
	TEST("ForEach", arr[1], copy_arr[1] + 1);
	TEST("ForEach", arr[2], copy_arr[2] + 1);
	TEST("ForEach", arr[3], copy_arr[3] + 1);
	TEST("ForEach", arr[4], copy_arr[4] + 1);
	TEST("ForEach", arr[5], copy_arr[5] + 1);
	TEST("ForEach", arr[6], copy_arr[6] + 1);
	TEST("ForEach", arr[7], copy_arr[7] + 1);
	TEST("ForEach", arr[8], copy_arr[8] + 1);
	TEST("ForEach", arr[9], copy_arr[9] + 1);
	TEST("ForEach", arr[10], copy_arr[10] + 1);
	
	/* destroy */
	
	BSTDestroy(tree);
	
	printf(BOLDBLUE "Completed Test3\n" DEF);
}

static void Test4(void)
{
	/* test 2 for BSTForEach */
	
	int arr[] = {-50,-40,-30,-20,-10,0,10,20,30,40,50};
	int copy_arr[] = {-50,-40,-30,-20,-10,0,10,20,30,40,50};
	int params = 5;
	int status = 0;
	bst_iter_t iter = NULL;
	bst_t *tree = NULL;
	
	/* create */
	
	tree = BSTCreate(&CompareInts);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 1);
	TEST("Size", BSTSize(tree), 0);
	
	/* insert */
	
	iter = BSTInsert(tree, arr+8);
	iter = BSTInsert(tree, arr+9);
	iter = BSTInsert(tree, arr+10);
	iter = BSTInsert(tree, arr+6);
	iter = BSTInsert(tree, arr+7);
	iter = BSTInsert(tree, arr+2);
	iter = BSTInsert(tree, arr+1);
	iter = BSTInsert(tree, arr+0);
	iter = BSTInsert(tree, arr+3);
	iter = BSTInsert(tree, arr+4);
	iter = BSTInsert(tree, arr+5);
	(void) iter;
	
	/* for each */
	
	status = BSTForEach(BSTBegin(tree), 
	                    BSTNext(BSTNext(BSTNext(BSTBegin(tree)))),
                        &AddToInt, &params);
	
	TEST("ForEach", status, 0);
	TEST("ForEach", arr[0], copy_arr[0] + params);
	TEST("ForEach", arr[1], copy_arr[1] + params);
	TEST("ForEach", arr[2], copy_arr[2] + params);
	TEST("ForEach", arr[3], copy_arr[3]);
	TEST("ForEach", arr[4], copy_arr[4]);
	TEST("ForEach", arr[5], copy_arr[5]);
	TEST("ForEach", arr[6], copy_arr[6]);
	TEST("ForEach", arr[7], copy_arr[7]);
	TEST("ForEach", arr[8], copy_arr[8]);
	TEST("ForEach", arr[9], copy_arr[9]);
	TEST("ForEach", arr[10], copy_arr[10]);
	
	status = BSTForEach(BSTPrev(BSTPrev(BSTPrev(BSTEnd(tree)))),
	                    BSTEnd(tree),
                        &AddToInt, &params);
	
	TEST("ForEach", status, 0);
	TEST("ForEach", arr[0], copy_arr[0] + params);
	TEST("ForEach", arr[1], copy_arr[1] + params);
	TEST("ForEach", arr[2], copy_arr[2] + params);
	TEST("ForEach", arr[3], copy_arr[3]);
	TEST("ForEach", arr[4], copy_arr[4]);
	TEST("ForEach", arr[5], copy_arr[5]);
	TEST("ForEach", arr[6], copy_arr[6]);
	TEST("ForEach", arr[7], copy_arr[7]);
	TEST("ForEach", arr[8], copy_arr[8] + params);
	TEST("ForEach", arr[9], copy_arr[9] + params);
	TEST("ForEach", arr[10], copy_arr[10] + params);
	
	/* destroy */
	
	BSTDestroy(tree);
	
	printf(BOLDBLUE "Completed Test4\n" DEF);
}

static void Test5(void)
{
	/* test 1 for BSTForEach */
	
	int arr[] = {-50,-40,-30,-20,-10,0,10,20,30,40,50};
	int copy_arr[] = {-50,-40,-30,-20,-10,0,10,20,30,40,50};
	int status = 0;
	bst_iter_t iter = NULL;
	bst_t *tree = NULL;
	
	/* create */
	
	tree = BSTCreate(&CompareInts);
	
	TEST("IsEmpty", BSTIsEmpty(tree), 1);
	TEST("Size", BSTSize(tree), 0);
	
	/* insert */
	
	iter = BSTInsert(tree, arr+8);
	iter = BSTInsert(tree, arr+9);
	iter = BSTInsert(tree, arr+10);
	iter = BSTInsert(tree, arr+6);
	iter = BSTInsert(tree, arr+7);
	iter = BSTInsert(tree, arr+2);
	iter = BSTInsert(tree, arr+1);
	iter = BSTInsert(tree, arr+0);
	iter = BSTInsert(tree, arr+3);
	iter = BSTInsert(tree, arr+4);
	iter = BSTInsert(tree, arr+5);
	(void) iter;
	
	/* for each */
	
	status = BSTForEach(BSTBegin(tree), BSTEnd(tree),
                        &IncrementIntIfNotZero, NULL);
	
	TEST("ForEach", status, 1);
	TEST("ForEach", arr[0], copy_arr[0] + 1);
	TEST("ForEach", arr[1], copy_arr[1] + 1);
	TEST("ForEach", arr[2], copy_arr[2] + 1);
	TEST("ForEach", arr[3], copy_arr[3] + 1);
	TEST("ForEach", arr[4], copy_arr[4] + 1);
	TEST("ForEach", arr[5], copy_arr[5]);
	TEST("ForEach", arr[6], copy_arr[6]);
	TEST("ForEach", arr[7], copy_arr[7]);
	TEST("ForEach", arr[8], copy_arr[8]);
	TEST("ForEach", arr[9], copy_arr[9]);
	TEST("ForEach", arr[10], copy_arr[10]);
	
	/* destroy */
	
	BSTDestroy(tree);
	
	printf(BOLDBLUE "Completed Test5\n" DEF);
}

/************************* main function *************************/

int main(void)
{
	TestCreateDestroy();
	Test0();
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	PASS;
	
	return 0;
}




















