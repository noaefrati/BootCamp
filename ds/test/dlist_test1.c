/*****************************************************************************
 * Description: Test file for the Double Linked List exercise                *
 * Author: Ronny                                                             *
 *                                                                           *
 * Infinity Labs - OL97                                                      *
 *****************************************************************************/

#include <stdio.h>  /* printf, size_t */
#include <string.h> /* strlen, strcmp */
#include "dlist.h"
#include "tests.h"

/* function declerations */
void TestBasics(void);
void TestExtremes(void);
static int FindI(const void *data, const void *against);
static int CopyLetters(void *data, void *params);

int main()
{
    TestBasics();
    TestExtremes();
    PASS;
    return 0;
}

void TestBasics(void)
{
    dllist_t *lst = DLLCreate();
    dllist_t *i_lst = DLLCreate();
    char *str = "This is an ineffable string such that you cannot deny!";
    char dest[200];
    char i_dest[5];
    size_t n = strlen(str) + 1; /* including terminator */
    size_t i = 0;
    dllist_iter_t manual_i = NULL;
    char letter = 'i';
    
    TEST("Create", (NULL == lst), 0);
    TEST("Create", (NULL == i_lst), 0);
    TEST("Empty/Size", DLLSize(lst), 0);
    TEST("Empty/Is", DLLIsEmpty(lst), 1);
    TEST("Being == End", DLLBegin(lst), DLLEnd(lst));
    
    for (; n > i; ++i)
    {
        TEST("PushBack", (NULL != DLLPushBack(lst, str + i)), 1);
    }
    
    /* i should be at the third node */
    manual_i = DLLBegin(lst);
    manual_i = DLLNext(manual_i);
    manual_i = DLLNext(manual_i);
    TEST("Size", DLLSize(lst), n);
    TEST("SameIter/Find",
         DLLFind(DLLBegin(lst), DLLEnd(lst), &letter, FindI),
         manual_i);
    TEST("MultiFind",
         DLLMultiFind(DLLBegin(lst), DLLEnd(lst), i_lst, &letter, FindI),
         0);
    TEST("Find Size", DLLSize(i_lst), 4);
    TEST("ForEach",
         DLLForEach(DLLBegin(lst), DLLEnd(lst), CopyLetters, dest),
         0);
    TEST("ForEach", strcmp(str, dest), 0);
    
    manual_i = DLLEnd(i_lst);
    for (i = 0; 4 > i; ++i)
    {
        manual_i = DLLPrev(manual_i);
        i_dest[i] = *(char *)DLLGetData(manual_i);
    }
    i_dest[4] = '\0';
    TEST("Get/Prev", strcmp(i_dest, "iiii"), 0);
    DLLSplice(DLLBegin(lst), DLLEnd(lst), DLLEnd(i_lst));
    TEST("Splice", DLLIsEmpty(lst), 1);
    TEST("Splice", DLLSize(i_lst), n + 4);
    
    DLLDestroy(lst);
    DLLDestroy(i_lst);
}

void TestExtremes(void)
{
    dllist_t *lst = DLLCreate();
    char j = 'j';
    char str[] = "civic"; /* a nice palinrome */
    char dest[6] = {'a', 'b', 'c', 'd', 'e', '\0'};
    size_t n = strlen(str);
    size_t i = 0;
    dllist_iter_t iter = NULL;
    
    TEST("Size at Creation", DLLSize(lst), 0);
    /*
     * DLLPopBack(lst);
     * DLLPopFront(lst);
     */
    TEST("Size After Pop Empty", DLLSize(lst), 0);
    TEST("Find Nothing",
         DLLFind(DLLBegin(lst), DLLEnd(lst), &j, FindI),
         DLLEnd(lst));
         
    for (; n > i; ++i)
    {
        TEST("PushFront", (NULL != DLLPushFront(lst, str + i)), 1);
    }
    
    iter = DLLBegin(lst);
    for (i = 0; n > i; ++i)
    {
        *(str + i) = *(char *)DLLGetData(iter);
        iter = DLLNext(iter);
    }
    TEST("Looped iter", iter, DLLEnd(lst));
    TEST("Get", strcmp(str, "civic"), 0);
    DLLSplice(DLLBegin(lst), DLLNext(DLLBegin(lst)), iter);
    iter = DLLBegin(lst);
    for (i = 0; n > i; ++i)
    {
        *(dest + i) = *(char *)DLLGetData(iter);
        iter = DLLNext(iter);
    }
    TEST("Inner Splice", strcmp(dest, "ivicc"), 0);
    
    DLLDestroy(lst);
}

static int FindI(const void *data, const void *against)
{
    return *(char *)data == *(char *)against;
}

static int CopyLetters(void *data, void *params)
{
    /* params is a char pointer to a string array */
    static size_t l = 0;
    *((char *)params + l) = *(char *)data;
    ++l;
    
    return 0;
}
