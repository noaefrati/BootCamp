/*****************************************************************************
 * Description: Tests for Sorted Lists                                       *
 * Author: Ronny                                                             *
 *                                                                           *
 * Infinity Labs - OL97                                                      *
 *****************************************************************************/
#include <stdio.h>
#include "tests.h"
#include "sorted_list.h"



/* function declerations */
void Tests(void);
static int SortAscending(const void *one, const void *other);
static int CompareSorting(void *value, void *params);
static int SimpleCompare(const void *one, const void *other);

int main()
{
    Tests();
    PASS;
    return 0;
}

/* general test function, test all non-trivial sorted list functions */
void Tests(void)
{
    srtlst_t *lst = SRTLSTCreate(SortAscending);
    srtlst_t *merge_src_lst = SRTLSTCreate(SortAscending);
    srtlst_iter_t expected_node;
    int src[10] = {1, 2, 30, 4, 400, 56, 7, 49, 900, 420};
    int to_merge[3] = {0, 69, 1000};
    int sorted_src[10] = {1, 2, 4, 7, 30, 49, 56, 400, 420 ,900};
    int another = 3;
    size_t i = 0;
    
    TEST("Create", (NULL != lst), 1);
    TEST("Create", (NULL != merge_src_lst), 1);
    TEST("Size of Empty", SRTLSTSize(lst), 0);
    TEST("Is Empty", SRTLSTIsEmpty(lst), 1);
    TEST("Size of Empty", SRTLSTSize(merge_src_lst), 0);
    TEST("Is Empty", SRTLSTIsEmpty(merge_src_lst), 1);
    
    for (; 10 > i; ++i)
    {
        TEST("Inserts", SRTLSTInsert(lst, src + i), 0);
    }
    
    TEST("Size", SRTLSTSize(lst), 10);
    TEST("Is Not Empty", SRTLSTIsEmpty(lst), 0);
    TEST("Sorted Inserts Correctly",
         SRTLSTForEach(SRTLSTBegin(lst),
                       SRTLSTEnd(lst),
                       CompareSorting,
                       sorted_src),
         0);
    TEST("Insert", SRTLSTInsert(lst, &another), 0);
    expected_node = SRTLSTNext(SRTLSTNext(SRTLSTBegin(lst)));
    TEST("Size", SRTLSTSize(lst), 11);
    TEST("Find If",
         SRTLSTIsSameIter(SRTLSTFindIf(SRTLSTBegin(lst),
                                       SRTLSTEnd(lst),
                                       SimpleCompare,
                                       &another),
                          expected_node),
         1);
    TEST("Insert", *(int *)SRTLSTGetData(expected_node), 3);
    TEST("Find",
         SRTLSTIsSameIter(SRTLSTFind(lst,
                                     SRTLSTBegin(lst),
                                     SRTLSTEnd(lst),
                                     src + 8),
                          SRTLSTPrev(SRTLSTEnd(lst))),
         1);
    
    for (i = 0; 3 > i; ++i)
    {
        TEST("Inserts", SRTLSTInsert(merge_src_lst, to_merge + i), 0);
    }
    TEST("Size", SRTLSTSize(merge_src_lst), 3);
    SRTLSTMerge(lst, merge_src_lst);
    TEST("Size of Source", SRTLSTSize(merge_src_lst), 0);
    TEST("Source Is Empty After Merge", SRTLSTIsEmpty(merge_src_lst), 1);
    TEST("Size of Merge Destination", SRTLSTSize(lst), 14);
    
    expected_node = SRTLSTPrev(SRTLSTEnd(lst));
    TEST("Find Last",
         SRTLSTIsSameIter(SRTLSTFind(lst,
                                     SRTLSTBegin(lst),
                                     SRTLSTEnd(lst),
                                     to_merge + 2),
                          expected_node),
         1);
    TEST("Find If",
         SRTLSTIsSameIter(SRTLSTFindIf(SRTLSTBegin(lst),
                                       SRTLSTEnd(lst),
                                       SimpleCompare,
                                       to_merge + 2),
                          expected_node),
         1);
    SRTLSTPopBack(lst);
    TEST("Find If",
         SRTLSTIsSameIter(SRTLSTFindIf(SRTLSTBegin(lst),
                                       SRTLSTEnd(lst),
                                       SimpleCompare,
                                       to_merge + 2),
                          SRTLSTEnd(lst)),
         1);
    SRTLSTPopFront(lst);
    TEST("Find If",
         SRTLSTIsSameIter(SRTLSTFindIf(SRTLSTBegin(lst),
                                       SRTLSTEnd(lst),
                                       SimpleCompare,
                                       to_merge),
                          SRTLSTEnd(lst)),
         1);
    TEST("Size", SRTLSTSize(lst), 12);
    
    SRTLSTDestroy(lst);
     SRTLSTDestroy(merge_src_lst);
}

/* HELPER - sort in ascending order function */
static int SortAscending(const void *one, const void *other)
{
    /* one is the new value, other is inside the nodes */
    return *(int *)one - *(int *)other;
}

/* HELPER - compare sorted list to sorted source array */
static int CompareSorting(void *value, void *params)
{
    /*
     * here, params is the sorted_src array
     * value is the data from each node
     * comparison would yield 1 if equal
     * function should return 0 if successful, thus the ! symbol
     */
    static int sort_i = 0;
    
    ++sort_i;
    
    return !(*(int *)value == *((int *)params + (sort_i - 1)));
}

/* HELPER - simply compare node value with another value */
static int SimpleCompare(const void *one, const void *other)
{
    return *(int *)other == *(int *)one;
}
/* υ´• ﻌ •`υ */
