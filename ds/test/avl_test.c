/*************************************************************************** 
 * Description: Testing of Implementation of AVL
 * Author: Oriel Nofekh
 *
 * Infinity Labs OL97
 ***************************************************************************/


#include <stdio.h>     /* printf */
#include <assert.h>    /* assert */
#include "avl.h"       /* AVL API */



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




/************************* Helper Functions *************************/

static int CompareInts(const void *one, const void *two)
{
	assert(one);
	assert(two);
	return (*(int *) one) - (*(int *) two);
}

static int IsAlmostMatch(const void *data, const void *against)
{
	assert(data);
	assert(against);
	
	return ((*(int*) data - *(int*) against <= 2) &&  
	        (*(int*) against - *(int*) data <= 2));
}

/******************************************************************************/

static int static_arr[20];

static void ResetArray(void)
{
	size_t i = 0;
	size_t len = sizeof(static_arr) / sizeof(static_arr[0]);
	for (i = 0; i < len; ++i)
	{
		static_arr[i] = 0;
	}
}

static void PrintArray(int *arr, size_t len)
{
	size_t i = 0;
	for (i = 0; i < len; ++i)
	{
		printf("%d, ", arr[i]);
		if (arr[i] < 10)
		{
			printf(" ");
		}
	}
	printf("\n");
}

static int IsSameArray(int *arr)
{
	size_t i = 0;
	size_t len = sizeof(static_arr) / sizeof(static_arr[0]);
	for (i = 0; i < len; ++i)
	{
		if (static_arr[i] != arr[i])
		{
			printf("actual:   ");
			PrintArray(static_arr, len);
			printf("expected: ");
			PrintArray(arr, len);
			return 0;
		}
	}
	return 1;
}

static int PrintToIndex(void *data, void *params)
{
	static_arr[*(int *) params] = *(int *) data;
	++(*(int *) params);
	return 0;
}


static int PrintLeftEdge(void *data, void *prev_data)
{
	if ((int) 0xDEADBEEF != *(int*) prev_data)
	{
		if (*(int*) data < *(int*) prev_data)
		{
			printf("%d->%d   ", *(int*) prev_data, *(int*) data);
		}
	}
	else
	{
		printf("Root is: %d\n", *(int*) data);
		printf("Left Edges:\n");
	}
	*(int*) prev_data = *(int*) data;
	return 0;
}

static int PrintRightEdge(void *data, void *prev_data)
{
	if ((int) 0xDEADBEEF != *(int*) prev_data)
	{
		if (*(int*) data < *(int*) prev_data)
		{
			printf("%d->%d   ", *(int*) data, *(int*) prev_data);
		}
	}
	else
	{
		printf("Right Edges:\n");
	}
	*(int*) prev_data = *(int*) data;
	return 0;
}

static void PrintRootAndEdges(avl_t *tree)
{
	int param = 0;
	
	param = 0xDEADBEEF;
	AVLForEach(tree, &PrintLeftEdge, &param, PRE_ORDER);
	printf("\n");
	
	param = 0xDEADBEEF;
	AVLForEach(tree, &PrintRightEdge, &param, POST_ORDER);
	printf("\n");
}

/************************* Tests Functions *************************/

static void TestCreateDestroy(void)
{
	avl_t *tree = AVLCreate(&CompareInts);
	
	AVLDestroy(tree);
	
	printf(BOLDBLUE "Completed TestCreateDestroy\n" DEF);
}

static void Test1(void)
{
	/* insert test (no remove) */
	
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int arr_copy[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int *data = NULL;
	
	avl_t *tree = AVLCreate(&CompareInts);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 1);
	TEST("Size", AVLSize(tree), 0);
	TEST("Height", AVLHeight(tree), -1);
	
	AVLInsert(tree, arr+9);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 0);
	TEST("Size", AVLSize(tree), 1);
	TEST("Height", AVLHeight(tree), 0);
	
	AVLInsert(tree, arr+4);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 0);
	TEST("Size", AVLSize(tree), 2);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLInsert(tree, arr+14);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 0);
	TEST("Size", AVLSize(tree), 3);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLInsert(tree, arr+2);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 0);
	TEST("Size", AVLSize(tree), 4);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+6);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 0);
	TEST("Size", AVLSize(tree), 5);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+12);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 0);
	TEST("Size", AVLSize(tree), 6);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+16);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 0);
	TEST("Size", AVLSize(tree), 7);
	TEST("Height", AVLHeight(tree), 2);
	
	/* Find */
	
	data = (int *) AVLFind(tree, arr_copy+9);
	TEST("Find", *data, 9);
	TEST("Find", data, arr+9);
	
	data = (int *) AVLFind(tree, arr_copy+4);
	TEST("Find", *data, 4);
	TEST("Find", data, arr+4);
	
	data = (int *) AVLFind(tree, arr_copy+12);
	TEST("Find", *data, 12);
	TEST("Find", data, arr+12);
	
	data = (int *) AVLFind(tree, arr_copy+13);
	TEST("Find", data, NULL);
	
	AVLDestroy(tree);
	
	printf(BOLDBLUE "Completed Test1\n" DEF);
}

static void Test2(void)
{
	/* insert and remove test */
	
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int arr_copy[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int *data = NULL;
	
	avl_t *tree = AVLCreate(&CompareInts);
	
	AVLInsert(tree, arr+9);
	AVLRemove(tree, arr+9);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 1);
	TEST("Size", AVLSize(tree), 0);
	TEST("Height", AVLHeight(tree), -1);
	
	AVLInsert(tree, arr+9);
	AVLInsert(tree, arr+8);
	AVLRemove(tree, arr+9);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 0);
	TEST("Size", AVLSize(tree), 1);
	TEST("Height", AVLHeight(tree), 0);
	
	AVLInsert(tree, arr+6);
	AVLInsert(tree, arr+10);
	AVLRemove(tree, arr+8);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 0);
	TEST("Size", AVLSize(tree), 2);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLRemove(tree, arr+6);
	AVLRemove(tree, arr+10);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 1);
	TEST("Size", AVLSize(tree), 0);
	TEST("Height", AVLHeight(tree), -1);
	
	AVLInsert(tree, arr+9);
	AVLInsert(tree, arr+4);
	AVLInsert(tree, arr+14);
	AVLInsert(tree, arr+2);
	AVLInsert(tree, arr+6);
	AVLInsert(tree, arr+12);
	AVLInsert(tree, arr+16);
	
	AVLRemove(tree, arr+9);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 0);
	TEST("Size", AVLSize(tree), 6);
	
	AVLRemove(tree, arr+4);
	AVLRemove(tree, arr+14);
	
	TEST("IsEmpty", AVLIsEmpty(tree), 0);
	TEST("Size", AVLSize(tree), 4);
	
	/* Find */
	
	data = (int *) AVLFind(tree, arr_copy+2);
	TEST("Find", *data, 2);
	TEST("Find", data, arr+2);
	
	data = (int *) AVLFind(tree, arr_copy+6);
	TEST("Find", *data, 6);
	TEST("Find", data, arr+6);
	
	data = (int *) AVLFind(tree, arr_copy+12);
	TEST("Find", *data, 12);
	TEST("Find", data, arr+12);
	
	data = (int *) AVLFind(tree, arr_copy+14);
	TEST("Find", data, NULL);
	
	AVLDestroy(tree);
	
	printf(BOLDBLUE "Completed Test2\n" DEF);
}

static void Test3(void)
{
	/* insert with re-balance test (no remove) */
	
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int arr_copy[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int *data = NULL;
	
	avl_t *tree = AVLCreate(&CompareInts);
	
	TEST("Size", AVLSize(tree), 0);
	TEST("Height", AVLHeight(tree), -1);
	
	AVLInsert(tree, arr+1);
	
	TEST("Size", AVLSize(tree), 1);
	TEST("Height", AVLHeight(tree), 0);
	
	AVLInsert(tree, arr+3);
	
	TEST("Size", AVLSize(tree), 2);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLInsert(tree, arr+5);
	
	TEST("Size", AVLSize(tree), 3);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLInsert(tree, arr+7);
	
	TEST("Size", AVLSize(tree), 4);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+9);
	
	TEST("Size", AVLSize(tree), 5);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+11);
	
	TEST("Size", AVLSize(tree), 6);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+13);
	
	TEST("Size", AVLSize(tree), 7);
	TEST("Height", AVLHeight(tree), 2);
	
	/* Find */
	
	data = (int *) AVLFind(tree, arr_copy+1);
	TEST("Find", *data, 1);
	TEST("Find", data, arr+1);
	
	data = (int *) AVLFind(tree, arr_copy+5);
	TEST("Find", *data, 5);
	TEST("Find", data, arr+5);
	
	data = (int *) AVLFind(tree, arr_copy+11);
	TEST("Find", *data, 11);
	TEST("Find", data, arr+11);
	
	AVLDestroy(tree);
	
	/* again, opposite direction */
	
	tree = AVLCreate(&CompareInts);
	
	TEST("Size", AVLSize(tree), 0);
	TEST("Height", AVLHeight(tree), -1);
	
	AVLInsert(tree, arr+13);
	
	TEST("Size", AVLSize(tree), 1);
	TEST("Height", AVLHeight(tree), 0);
	
	AVLInsert(tree, arr+11);
	
	TEST("Size", AVLSize(tree), 2);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLInsert(tree, arr+9);
	
	TEST("Size", AVLSize(tree), 3);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLInsert(tree, arr+7);
	
	TEST("Size", AVLSize(tree), 4);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+5);
	
	TEST("Size", AVLSize(tree), 5);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+3);
	
	TEST("Size", AVLSize(tree), 6);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+1);
	
	TEST("Size", AVLSize(tree), 7);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLDestroy(tree);
	
	/* simple right-left */
	
	tree = AVLCreate(&CompareInts);
	
	TEST("Size", AVLSize(tree), 0);
	TEST("Height", AVLHeight(tree), -1);
	
	AVLInsert(tree, arr+9);
	
	TEST("Size", AVLSize(tree), 1);
	TEST("Height", AVLHeight(tree), 0);
	
	AVLInsert(tree, arr+13);
	
	TEST("Size", AVLSize(tree), 2);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLInsert(tree, arr+11);
	
	TEST("Size", AVLSize(tree), 3);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLDestroy(tree);
	
	/* simple left-right */
	
	tree = AVLCreate(&CompareInts);
	
	TEST("Size", AVLSize(tree), 0);
	TEST("Height", AVLHeight(tree), -1);
	
	AVLInsert(tree, arr+9);
	
	TEST("Size", AVLSize(tree), 1);
	TEST("Height", AVLHeight(tree), 0);
	
	AVLInsert(tree, arr+5);
	
	TEST("Size", AVLSize(tree), 2);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLInsert(tree, arr+7);
	
	TEST("Size", AVLSize(tree), 3);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLDestroy(tree);
	
	/* advanced right-left / left-right */
	
	tree = AVLCreate(&CompareInts);
	
	TEST("Size", AVLSize(tree), 0);
	TEST("Height", AVLHeight(tree), -1);
	
	AVLInsert(tree, arr+9);
	
	TEST("Size", AVLSize(tree), 1);
	TEST("Height", AVLHeight(tree), 0);
	
	AVLInsert(tree, arr+13);
	
	TEST("Size", AVLSize(tree), 2);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLInsert(tree, arr+5);
	
	TEST("Size", AVLSize(tree), 3);
	TEST("Height", AVLHeight(tree), 1);
	
	AVLInsert(tree, arr+7);
	
	TEST("Size", AVLSize(tree), 4);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+3);
	
	TEST("Size", AVLSize(tree), 5);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+4);
	
	TEST("Size", AVLSize(tree), 6);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLInsert(tree, arr+2);
	
	TEST("Size", AVLSize(tree), 7);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLDestroy(tree);
	
	printf(BOLDBLUE "Completed Test3\n" DEF);
}

static void Test4(void)
{
	/* insert and remove with re-balance test (no remove) */
	
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int arr_copy[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	
	avl_t *tree = AVLCreate(&CompareInts);
	
	TEST("Size", AVLSize(tree), 0);
	TEST("Height", AVLHeight(tree), -1);
	
	AVLInsert(tree, arr+9);   /* first level */
	AVLInsert(tree, arr+14);  /* second level */
	AVLInsert(tree, arr+4);   /* second level */
	AVLInsert(tree, arr+2);   /* third level */
	AVLInsert(tree, arr+6);   /* third level */
	AVLInsert(tree, arr+12);  /* third level */
	AVLInsert(tree, arr+16);  /* third level */
	AVLInsert(tree, arr+1);   /* 4th level */
	AVLInsert(tree, arr+3);   /* 4th level */
	AVLInsert(tree, arr+5);   /* 4th level */
	AVLInsert(tree, arr+7);   /* 4th level */
	AVLInsert(tree, arr+11);  /* 4th level */
	AVLInsert(tree, arr+13);  /* 4th level */
	AVLInsert(tree, arr+15);  /* 4th level */
	AVLInsert(tree, arr+17);  /* 4th level */
	
	TEST("Size", AVLSize(tree), 15);
	TEST("Height", AVLHeight(tree), 3);
	
	AVLRemove(tree, arr_copy+16);
	AVLRemove(tree, arr_copy+17);
	AVLRemove(tree, arr_copy+13);
	AVLRemove(tree, arr_copy+12);
	AVLRemove(tree, arr_copy+11);
	AVLRemove(tree, arr_copy+15);
	AVLRemove(tree, arr_copy+14);
	AVLRemove(tree, arr_copy+9);
	
	TEST("Size", AVLSize(tree), 7);
	TEST("Height", AVLHeight(tree), 2);
	
	AVLDestroy(tree);
	
	printf(BOLDBLUE "Completed Test4\n" DEF);
}

static void Test5(void)
{
	/* in-order, pre-order, post-order */
	
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int arr_in_order[] = {1,2,3,4,5,6,7,9,11,12,13,14,15,16,17,0,0,0,0,0};
	int arr_pre_order[] = {9,4,2,1,3,6,5,7,14,12,11,13,16,15,17,0,0,0,0,0};
	int arr_post_order[] = {1,3,2,5,7,6,4,11,13,12,15,17,16,14,9,0,0,0,0,0};
	int params = 0;
	
	avl_t *tree = AVLCreate(&CompareInts);
	
	TEST("Size", AVLSize(tree), 0);
	TEST("Height", AVLHeight(tree), -1);
	
	AVLInsert(tree, arr+9);   /* first level */
	AVLInsert(tree, arr+14);  /* second level */
	AVLInsert(tree, arr+4);   /* second level */
	AVLInsert(tree, arr+2);   /* third level */
	AVLInsert(tree, arr+6);   /* third level */
	AVLInsert(tree, arr+12);  /* third level */
	AVLInsert(tree, arr+16);  /* third level */
	AVLInsert(tree, arr+1);   /* 4th level */
	AVLInsert(tree, arr+3);   /* 4th level */
	AVLInsert(tree, arr+5);   /* 4th level */
	AVLInsert(tree, arr+7);   /* 4th level */
	AVLInsert(tree, arr+11);  /* 4th level */
	AVLInsert(tree, arr+13);  /* 4th level */
	AVLInsert(tree, arr+15);  /* 4th level */
	AVLInsert(tree, arr+17);  /* 4th level */
	
	TEST("Size", AVLSize(tree), 15);
	TEST("Height", AVLHeight(tree), 3);
	
	ResetArray();
	params = 0;
	AVLForEach(tree, &PrintToIndex, &params, IN_ORDER);
	TEST("In Order", IsSameArray(arr_in_order), 1);
	
	ResetArray();
	params = 0;
	AVLForEach(tree, &PrintToIndex, &params, PRE_ORDER);
	TEST("Pre Order", IsSameArray(arr_pre_order), 1);
	
	ResetArray();
	params = 0;
	AVLForEach(tree, &PrintToIndex, &params, POST_ORDER);
	TEST("Post Order", IsSameArray(arr_post_order), 1);
	
	AVLDestroy(tree);
	
	printf(BOLDBLUE "Completed Test5\n" DEF);
}



/************************* main function *************************/

int main(void)
{
	/* just Creates and Destroys */
	TestCreateDestroy();
	
	/* insert test */
	Test1();
	
	/* insert and remove test */
	Test2();
	
	/* insert with re-balance */
	Test3();
	
	/* insert and remove with re-balance */
	Test4();
	
	/* in-order, pre-order, post-order */
	Test5();
	
	
	PASS;
	
	return 0;
}




















