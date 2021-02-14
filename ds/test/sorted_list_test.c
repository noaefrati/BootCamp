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
#include <ctype.h>    /* toupper */
#include <time.h>     /* time_t, time */
#include <assert.h>   /* assert */
#include "sorted_list.h"    /* sorted_list_t, node_t and sortlist_iter_t 
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

/* simple compare functions */

static int CompareChar(const void *one, const void *other)
{
	char *char1 = (char *) one;
	char *char2 = (char *) other;
	
	if (*char1 < *char2)
	{
		return -1;
	}
	else if (*char1 > *char2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* structs and their corresponding compare functions */

typedef struct
{
	int ID;
	char class;
} student_t;

static int CompareClass(const void *one, const void *other)
{
	student_t *student1 = (student_t *) one;
	student_t *student2 = (student_t *) other;
	
	if (student1->class < student2->class)
	{
		return -1;
	}
	else if (student1->class > student2->class)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

typedef struct
{
	int ID;
	char *first_name;
	char *last_name;
} person_t;

static int CompareName(const void *one, const void *other)
{
	person_t *person1 = (person_t *) one;
	person_t *person2 = (person_t *) other;
	
	/* we first sort by last name */
	int cmp_value = strcmp(person1->last_name, person2->last_name);
	if (0 > cmp_value)
	{
		return -1;
	}
	else if (0 < cmp_value)
	{
		return 1;
	}
	else
	{
		/* if last name is identical, we sort by first name */
		cmp_value = strcmp(person1->first_name, person2->first_name);
		if (0 > cmp_value)
		{
			return -1;
		}
		else if (0 < cmp_value)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}


/*****************************************************************************/

/* Used as "action" for the ForEach function */
static int ToUpper(void *data, void *params)
{
	(void) params;
	*(char *) data = toupper(*(char *) data);
	return 0;
}

/* Used as "action" for the ForEach function */
static int AddToValue(void *data, void *params)
{
	*(int *) params += (int) *(char *) data;
	return 0;
}

/* Used as "action" for the ForEach function */
static int IsSameCharAction(void *one, void *other)
{
	if ((*(char *) one) == (*(char *) other))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* Used as "is_match" for the FindIf function */
static int IsSameChar(const void *one, const void *other)
{
	if ((*(char *) one) == (*(char *) other))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* Used as "is_match" for the FindIf function */
static int IsSameClass(const void *one, const void *other)
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
static int IsListAsExpected(srtlst_t *lst, const char *expected)
{
	srtlst_iter_t iter = SRTLSTBegin(lst);
	srtlst_iter_t end_iter = SRTLSTEnd(lst);
	
	for (; !SRTLSTIsSameIter(iter, end_iter) && '\0' != *expected; 
	       iter = SRTLSTNext(iter), ++expected)
	{
		if (*(char *) SRTLSTGetData(iter) != *expected)
		{
			return 0;
		}
	}
	
	if (SRTLSTIsSameIter(iter, end_iter) && '\0' == *expected)
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
	srtlst_t *lst = SRTLSTCreate(&CompareChar);
	
	SRTLSTDestroy(lst);
}



static int Test1(void)
{
	/* 
	tests basic functions: 
	    Next, Prev, Begin, End,
	    IsEmpty, Size,
	    PopFront, PopBack, Remove, Insert,
	    GetData (is used inside "IsListAsExpected")
	*/
	
	int status = 0;
	
	char char_arr[] = {'a','b','c','d','e',
	                   'f','g','h','i','j',
	                   'k','l','m','n','o',
	                   'p','q','r','s','t'};
	
	srtlst_t *lst = SRTLSTCreate(&CompareChar);
	
	TEST("Size", SRTLSTSize(lst), 0);
	TEST("IsEmpty", SRTLSTIsEmpty(lst), 1);
	TEST("Is Begin and End are the same", SRTLSTIsSameIter(SRTLSTBegin(lst), SRTLSTEnd(lst)), 1);
	
	status = SRTLSTInsert(lst, char_arr + 10);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	
	TEST("Size", SRTLSTSize(lst), 1);
	TEST("IsEmpty", SRTLSTIsEmpty(lst), 0);
	TEST("Is Begin and End are the same", SRTLSTIsSameIter(SRTLSTBegin(lst), SRTLSTEnd(lst)), 0);
	TEST("IsListAsExpected", IsListAsExpected(lst, "k"), 1);
	
	status = SRTLSTInsert(lst, char_arr + 5);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	
	TEST("Size", SRTLSTSize(lst), 2);
	TEST("IsEmpty", SRTLSTIsEmpty(lst), 0);
	TEST("IsListAsExpected", IsListAsExpected(lst, "fk"), 1);
	
	status = SRTLSTInsert(lst, char_arr + 7);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	
	TEST("Size", SRTLSTSize(lst), 3);
	TEST("IsEmpty", SRTLSTIsEmpty(lst), 0);
	TEST("IsListAsExpected", IsListAsExpected(lst, "fhk"), 1);
	
	SRTLSTPopBack(lst);
	
	TEST("Size", SRTLSTSize(lst), 2);
	TEST("IsEmpty", SRTLSTIsEmpty(lst), 0);
	TEST("IsListAsExpected", IsListAsExpected(lst, "fh"), 1);
	
	SRTLSTPopFront(lst);
	
	TEST("Size", SRTLSTSize(lst), 1);
	TEST("IsEmpty", SRTLSTIsEmpty(lst), 0);
	TEST("IsListAsExpected", IsListAsExpected(lst, "h"), 1);
	
	status = SRTLSTInsert(lst, char_arr + 12);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	
	TEST("Size", SRTLSTSize(lst), 2);
	TEST("IsEmpty", SRTLSTIsEmpty(lst), 0);
	TEST("IsListAsExpected", IsListAsExpected(lst, "hm"), 1);
	
	status = SRTLSTInsert(lst, char_arr + 12);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	
	TEST("Size", SRTLSTSize(lst), 3);
	TEST("IsEmpty", SRTLSTIsEmpty(lst), 0);
	TEST("IsListAsExpected", IsListAsExpected(lst, "hmm"), 1);
	TEST("IsSameIter", SRTLSTIsSameIter(SRTLSTNext(SRTLSTBegin(lst)),
	                                    SRTLSTNext(SRTLSTNext(SRTLSTBegin(lst)))), 0);
	
	status = SRTLSTInsert(lst, char_arr + 11);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	
	TEST("Size", SRTLSTSize(lst), 4);
	TEST("IsEmpty", SRTLSTIsEmpty(lst), 0);
	TEST("IsListAsExpected", IsListAsExpected(lst, "hlmm"), 1);
	
	SRTLSTRemove(SRTLSTPrev(SRTLSTPrev(SRTLSTEnd(lst))));
	
	TEST("Size", SRTLSTSize(lst), 3);
	TEST("IsEmpty", SRTLSTIsEmpty(lst), 0);
	TEST("IsListAsExpected", IsListAsExpected(lst, "hlm"), 1);
	
	SRTLSTRemove(SRTLSTPrev(SRTLSTPrev(SRTLSTEnd(lst))));
	
	TEST("Size", SRTLSTSize(lst), 2);
	TEST("IsEmpty", SRTLSTIsEmpty(lst), 0);
	TEST("IsListAsExpected", IsListAsExpected(lst, "hm"), 1);
	
	SRTLSTDestroy(lst); lst = NULL;
	
	return 0;
}



static int Test2(void)
{
	/* tests the ForEach function */
	
	int status = 0;
	int param = 0;
	char c = '\0';
	
	char char_arr[] = {'a','b','c','d','e',
	                   'f','g','h','i','j',
	                   'k','l','m','n','o',
	                   'p','q','r','s','t'};
	
	srtlst_t *lst = SRTLSTCreate(&CompareChar);
	
	status = SRTLSTInsert(lst, char_arr + 3);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(lst, char_arr + 2);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(lst, char_arr + 4);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(lst, char_arr + 1);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(lst, char_arr + 0);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	
	TEST("IsListAsExpected", IsListAsExpected(lst, "abcde"), 1);
	
	/* action = ToUpper */
	status = SRTLSTForEach(SRTLSTBegin(lst), SRTLSTEnd(lst), &ToUpper, NULL);
	TEST("ForEach SUCCESS or FAILURE", status, 0);
	
	TEST("IsListAsExpected", IsListAsExpected(lst, "ABCDE"), 1);
	
	/* action = AddToValue */
	status = SRTLSTForEach(SRTLSTBegin(lst), SRTLSTPrev(SRTLSTEnd(lst)), &AddToValue, &param);
	TEST("ForEach SUCCESS or FAILURE", status, 0);
	
	TEST("IsListAsExpected", IsListAsExpected(lst, "ABCDE"), 1);
	TEST("IsParamAsExpected", param, (((0 + 'A') + 'B') + 'C') + 'D');
	
	/* action = IsSameCharAction */
	c = 'Z';
	status = SRTLSTForEach(SRTLSTBegin(lst), SRTLSTEnd(lst), &IsSameCharAction, &c);
	TEST("ForEach SUCCESS or FAILURE", status, 0);
	c = 'C';
	status = SRTLSTForEach(SRTLSTBegin(lst), SRTLSTEnd(lst), &IsSameCharAction, &c);
	TEST("ForEach SUCCESS or FAILURE", status, 1);
	c = 'E';
	status = SRTLSTForEach(SRTLSTBegin(lst), SRTLSTPrev(SRTLSTEnd(lst)), &IsSameCharAction, &c);
	TEST("ForEach SUCCESS or FAILURE", status, 0);
	
	SRTLSTDestroy(lst); lst = NULL;
	
	return 0;
}



static int Test3(void)
{
	/********************* Find and FindIf: Test A - IsSameChar *********************/
	
	int status = 0;
	long int i = 0;
	srtlst_iter_t iter;
	
	char char_arr[] = {'a','b','c','d','e'};
	size_t char_arr_len = sizeof(char_arr) / sizeof(char_arr[0]);
	char value = char_arr[1];
	
	srtlst_t *lst = SRTLSTCreate(&CompareChar);
	
	for (i = char_arr_len - 1; i >= 0 ; --i)
	{
		status = SRTLSTInsert(lst, char_arr + i);
		TEST("Insert SUCCESS or FAILURE", status, 0);
	}
	
	TEST("IsListAsExpected", IsListAsExpected(lst, "abcde"), 1);
	
	/* first, 'b' should be found */
	
	iter = SRTLSTFindIf(SRTLSTBegin(lst),
	                    SRTLSTEnd(lst),
	                    &IsSameChar,
	                    &value);
	TEST("FindIf", *(char *) SRTLSTGetData(iter), value);
	TEST("FindIf", SRTLSTIsSameIter(iter, SRTLSTNext(SRTLSTBegin(lst))), 1);
	
	printf("\n");
	
	iter = SRTLSTFind(lst,
	                  SRTLSTBegin(lst),
	                  SRTLSTEnd(lst),
	                  &value);
	
	TEST("Find", *(char *) SRTLSTGetData(iter), value);
	TEST("Find", SRTLSTIsSameIter(iter, SRTLSTNext(SRTLSTBegin(lst))), 1);
	
	/* now, 'b' should not be found */
	
	SRTLSTRemove(SRTLSTNext(SRTLSTBegin(lst)));
	
	iter = SRTLSTFindIf(SRTLSTNext(SRTLSTNext(SRTLSTBegin(lst))),
	                    SRTLSTEnd(lst),
	                    &IsSameChar,
	                    &value);
	TEST("FindIf", SRTLSTIsSameIter(iter, SRTLSTEnd(lst)), 1);
	
	iter = SRTLSTFind(lst,
	                  SRTLSTNext(SRTLSTNext(SRTLSTBegin(lst))),
	                  SRTLSTEnd(lst),
	                  &value);
	TEST("Find", SRTLSTIsSameIter(iter, SRTLSTEnd(lst)), 1);
	
	/* now we remove 'b', so it should no longer be found */
	
	SRTLSTRemove(SRTLSTNext(SRTLSTBegin(lst)));
	
	iter = SRTLSTFindIf(SRTLSTBegin(lst),
	                    SRTLSTEnd(lst),
	                    &IsSameChar,
	                    &value);
	TEST("FindIf", SRTLSTIsSameIter(iter, SRTLSTEnd(lst)), 1);
	
	iter = SRTLSTFind(lst,
	                  SRTLSTBegin(lst),
	                  SRTLSTEnd(lst),
	                  &value);
	TEST("Find", SRTLSTIsSameIter(iter, SRTLSTEnd(lst)), 1);
	
	SRTLSTDestroy(lst); lst = NULL;
	
	return 0;
}



static int Test4(void)
{
	/********************* Find: Test B - IsSameClass *********************/
	
	srtlst_t *lst = SRTLSTCreate(&CompareClass);
	student_t student_zero = {0, 'A'};   /* a student from class 'A' */
	student_t students[10];
	size_t students_len = sizeof(students) / sizeof(students[0]);
	size_t i = 0;
	int status = 0;
	srtlst_iter_t iter;
	for (i = 0; i < students_len; ++i)
	{
		students[i].ID = 1000 + i;
	}
	students[0].class = 'A';
	students[1].class = 'A';
	students[2].class = 'E';
	students[3].class = 'D';
	students[4].class = 'A';
	students[5].class = 'A';
	students[6].class = 'B';
	students[7].class = 'C';
	students[8].class = 'B';
	students[9].class = 'B';
	
	for (i = 0; i < students_len; ++i)
	{
		status = SRTLSTInsert(lst, students + i);
		TEST("Insert SUCCESS or FAILURE", status, 0);
		
	}
	TEST("Size", SRTLSTSize(lst), students_len);
	
	
	
	/************ We first use FindIf ************/
	
	student_zero.class = 'C';   /* ID = 1000 + 7 */
	
	
	iter = SRTLSTFindIf(SRTLSTBegin(lst),
	                    SRTLSTEnd(lst),
	                    &IsSameClass,
	                    &student_zero);
	if (SRTLSTIsSameIter(iter, SRTLSTEnd(lst)))
	{
		printf(RED "FindIf Failed to find what it should have found in line %d\n" DEF, __LINE__);
	}
	else
	{
		TEST("FindIf", ((student_t *) SRTLSTGetData(iter))->class, student_zero.class);
		TEST("FindIf", ((student_t *) SRTLSTGetData(iter))->ID, 1000 + 7);
		TEST("FindIf", SRTLSTIsSameIter(iter, SRTLSTPrev(SRTLSTPrev(SRTLSTPrev(SRTLSTEnd(lst))))), 1);
	}
	
	student_zero.class = 'D';   /* ID = 1000 + 3 */
	
	iter = SRTLSTFindIf(SRTLSTNext(iter),
	                    SRTLSTEnd(lst),
	                    &IsSameClass,
	                    &student_zero);
	if (SRTLSTIsSameIter(iter, SRTLSTEnd(lst)))
	{
		printf(RED "FindIf Failed to find what it should have found in line %d\n" DEF, __LINE__);
	}
	else
	{
		TEST("FindIf", ((student_t *) SRTLSTGetData(iter))->class, student_zero.class);
		TEST("FindIf", ((student_t *) SRTLSTGetData(iter))->ID, 1000 + 3);
		TEST("FindIf", SRTLSTIsSameIter(iter, SRTLSTPrev(SRTLSTPrev(SRTLSTEnd(lst)))), 1);
	}
	
	student_zero.class = 'C';   /* ID = 1000 + 7 */
	
	iter = SRTLSTFindIf(iter,
	                    SRTLSTEnd(lst),
	                    &IsSameClass,
	                    &student_zero);
	TEST("Should not have found", SRTLSTIsSameIter(iter, SRTLSTEnd(lst)), 1);
	
	
	
	/************ and now we use Find ************/
	
	student_zero.class = 'C';   /* ID = 1000 + 7 */
	
	
	iter = SRTLSTFind(lst,
	                  SRTLSTBegin(lst),
	                  SRTLSTEnd(lst),
	                  &student_zero);
	if (SRTLSTIsSameIter(iter, SRTLSTEnd(lst)))
	{
		printf(RED "Find Failed to find what it should have found in line %d\n" DEF, __LINE__);
	}
	else
	{
		TEST("Find", ((student_t *) SRTLSTGetData(iter))->class, student_zero.class);
		TEST("Find", ((student_t *) SRTLSTGetData(iter))->ID, 1000 + 7);
		TEST("Find", SRTLSTIsSameIter(iter, SRTLSTPrev(SRTLSTPrev(SRTLSTPrev(SRTLSTEnd(lst))))), 1);
	}
	
	student_zero.class = 'D';   /* ID = 1000 + 3 */
	
	iter = SRTLSTFind(lst,
	                  SRTLSTNext(iter),
	                  SRTLSTEnd(lst),
	                  &student_zero);
	if (SRTLSTIsSameIter(iter, SRTLSTEnd(lst)))
	{
		printf(RED "Find Failed to find what it should have found in line %d\n" DEF, __LINE__);
	}
	else
	{
		TEST("Find", ((student_t *) SRTLSTGetData(iter))->class, student_zero.class);
		TEST("Find", ((student_t *) SRTLSTGetData(iter))->ID, 1000 + 3);
		TEST("Find", SRTLSTIsSameIter(iter, SRTLSTPrev(SRTLSTPrev(SRTLSTEnd(lst)))), 1);
	}
	
	student_zero.class = 'C';   /* ID = 1000 + 7 */
	
	iter = SRTLSTFind(lst,
	                  iter,
	                  SRTLSTEnd(lst),
	                  &student_zero);
	TEST("Should not have found", SRTLSTIsSameIter(iter, SRTLSTEnd(lst)), 1);
	
	SRTLSTDestroy(lst); lst = NULL;
	
	return 0;
}



static int Test5(void)
{
	/* now let's test Merge */
	
	int status = 0;
	
	char char_arr[] = {'0','1','2','3','4',
	                   '5','6','7','8','9'};
	
	/* let's try to merge two empty lists */
	
	srtlst_t *dest = SRTLSTCreate(&CompareChar);
	srtlst_t *src = SRTLSTCreate(&CompareChar);
	
	TEST("IsListAsExpected", IsListAsExpected(dest, ""), 1);
	TEST("IsListAsExpected", IsListAsExpected(src, ""), 1);
	
	SRTLSTMerge(dest, src);
	
	TEST("IsListAsExpected", IsListAsExpected(dest, ""), 1);
	TEST("IsListAsExpected", IsListAsExpected(src, ""), 1);
	
	SRTLSTDestroy(dest); dest = NULL;
	SRTLSTDestroy(src); src = NULL;
	
	
	/* now let's try to merge empty 'dest' with non-empty 'src' */
	
	dest = SRTLSTCreate(&CompareChar);
	src = SRTLSTCreate(&CompareChar);
	
	status = SRTLSTInsert(src, char_arr + 7);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(src, char_arr + 2);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(src, char_arr + 4);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(src, char_arr + 9);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(src, char_arr + 0);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	
	TEST("IsListAsExpected", IsListAsExpected(dest, ""), 1);
	TEST("IsListAsExpected", IsListAsExpected(src, "02479"), 1);
	
	SRTLSTMerge(dest, src);
	
	TEST("IsListAsExpected", IsListAsExpected(dest, "02479"), 1);
	TEST("IsListAsExpected", IsListAsExpected(src, ""), 1);
	
	SRTLSTDestroy(dest); dest = NULL;
	SRTLSTDestroy(src); src = NULL;
	
	/* now let's try to merge non-empty 'dest' with empty 'src' */
	
	dest = SRTLSTCreate(&CompareChar);
	src = SRTLSTCreate(&CompareChar);
	
	status = SRTLSTInsert(dest, char_arr + 7);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(dest, char_arr + 2);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(dest, char_arr + 4);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(dest, char_arr + 9);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(dest, char_arr + 0);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	
	TEST("IsListAsExpected", IsListAsExpected(dest, "02479"), 1);
	TEST("IsListAsExpected", IsListAsExpected(src, ""), 1);
	
	SRTLSTMerge(dest, src);
	
	TEST("IsListAsExpected", IsListAsExpected(dest, "02479"), 1);
	TEST("IsListAsExpected", IsListAsExpected(src, ""), 1);
	
	SRTLSTDestroy(dest); dest = NULL;
	SRTLSTDestroy(src); src = NULL;
	
	/* now let's try to merge non-empty 'dest' with non-empty 'src' */
	
	dest = SRTLSTCreate(&CompareChar);
	src = SRTLSTCreate(&CompareChar);
	
	status = SRTLSTInsert(dest, char_arr + 7);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(dest, char_arr + 2);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(dest, char_arr + 4);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(dest, char_arr + 9);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(dest, char_arr + 0);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	TEST("IsListAsExpected", IsListAsExpected(dest, "02479"), 1);
	
	status = SRTLSTInsert(src, char_arr + 3);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(src, char_arr + 1);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(src, char_arr + 0);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(src, char_arr + 6);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	TEST("IsListAsExpected", IsListAsExpected(src, "0136"), 1);
	
	SRTLSTMerge(dest, src);
	
	TEST("IsListAsExpected", IsListAsExpected(dest, "001234679"), 1);
	TEST("IsListAsExpected", IsListAsExpected(src, ""), 1);
	
	SRTLSTDestroy(dest); dest = NULL;
	SRTLSTDestroy(src); src = NULL;
	
	return 0;
}



static void TestDurability(void)
{
	/* This test randomly adds and removes elements from the list,
	   and only checks two things while doing so:
	      (1) that the program doesn't crash
	      (2) that the size is correct
	   It stops when a big enough size is reached. */
	
	int status = 0;
	
	srtlst_t *lst = NULL;
	
	size_t i = 0;
	const size_t NUM_ITERATIONS = 20;
	
	size_t num_actions = 0;
	
	size_t size = 0;
	const size_t MAX_SIZE = 1000;
	
	char char_arr[] = {'a','b','c','d','e',
	                   'f','g','h','i','j',
	                   'k','l','m','n','o',
	                   'p','q','r','s','t'};
	size_t arr_len = sizeof(char_arr) / sizeof(char_arr[0]);
	
	/* for random generation */
	time_t t = time(NULL);
	srand((unsigned) time(&t));
	
	for (i = 0; i < NUM_ITERATIONS; ++i)
	{
		size = 0;
		
		lst = SRTLSTCreate(&CompareChar);
		
		while (size < MAX_SIZE)
		{
			if ((0 == size) || (rand() % 7) <= 3)
			{
				status = SRTLSTInsert(lst, char_arr + (rand() % arr_len));
				if (0 != status)
				{
					printf(RED "Insert Failed, at line %d, in iteration %lu, "
					       "when size of list was %lu\n\n" DEF, __LINE__, i, size);
					SRTLSTDestroy(lst); lst = NULL;
					return;
				}
				++size;
			}
			else
			{
				SRTLSTPopFront(lst);
				--size;
			}
			
			if (size != SRTLSTSize(lst))
			{
				printf(RED "Size of list is incorrect, at line %d, in iteration %lu, "
			       "when size of list was %lu, but should have been %lu\n\n" DEF, __LINE__, i, SRTLSTSize(lst), size);
				SRTLSTDestroy(lst); lst = NULL;
				return;
			}
			++num_actions;
		}
		
		SRTLSTDestroy(lst); lst = NULL;
		
	}
	printf("Durability Test total number of actions was: %lu\n\n", num_actions);
}



static void TestDebug(void)
{
	/* here we test that the special asserts that use the 'list' field of
	   the iter work properly. but we can only check one at a time,
	   so please change one "if (0)" to "if (1)" each time an run it. */
	
	int status = 0;

	char char_arr[] = {'a','b','c','d','e',
	                   'f','g','h','i','j',
	                   'k','l','m','n','o',
	                   'p','q','r','s','t'};
	
	srtlst_t *lst1 = SRTLSTCreate(&CompareChar);
	srtlst_t *lst2 = SRTLSTCreate(&CompareChar);
	
	status = SRTLSTInsert(lst1, char_arr + 3);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(lst1, char_arr + 2);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	
	status = SRTLSTInsert(lst2, char_arr + 4);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(lst2, char_arr + 1);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	status = SRTLSTInsert(lst2, char_arr + 0);
	TEST("Insert SUCCESS or FAILURE", status, 0);
	
	if (0)
	{
		printf("Call ForEach with 'from' and 'to' from different lists:\n"
		       "Should fail with message: 'Assertion `__________' failed'\n\n");
		SRTLSTForEach(SRTLSTBegin(lst1), SRTLSTBegin(lst2), &ToUpper, NULL);
	}
	
	if (0)
	{
		printf("Call FindIf with 'from' and 'to' from different lists:\n"
		       "Should fail with message: 'Assertion `__________' failed'\n\n");
		SRTLSTFindIf(SRTLSTBegin(lst1), SRTLSTBegin(lst2), &IsSameChar, char_arr + 4);
	}
	
	if (0)
	{
		printf("Call Find with 'to' not from the right list:\n"
		       "Should fail with message: 'Assertion `__________' failed'\n\n");
		SRTLSTFind(lst1, SRTLSTBegin(lst1), SRTLSTBegin(lst2), char_arr + 4);
	}
	
	if (0)
	{
		printf("Call Find with 'from' not from the right list:\n"
		       "Should fail with message: 'Assertion `__________' failed'\n\n");
		SRTLSTFind(lst2, SRTLSTBegin(lst1), SRTLSTBegin(lst2), char_arr + 4);
	}
	
	SRTLSTDestroy(lst1); lst1 = NULL;
	SRTLSTDestroy(lst2); lst2 = NULL;
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
	
	TestDurability();
	
	TestDebug();
	
	PASS;
}



int main(void)
{
	TestDList();
	
	return 0;
}



