/******************************************************************************
 * Description: Tests for Scheduler Implementation                            *
 * Author: Ronny                                                              *
 *                                                                            *
 * Infinity Labs - OL97                                                       *
 ******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include "tests.h"
#include "scheduler.h"

char LUT[26] = {'a', 'b', 'c', 'd', 'e',
                'f', 'g', 'h', 'i', 'j',
                'k', 'l', 'm', 'n', 'o',
                'p', 'q', 'r', 's', 't',
                'u', 'v', 'w' ,'x', 'y', 'z'};

/*************************** Function Declarations ****************************/
void Tests(void);
static int Task1(void *params);
static int Task2(void *params);
static int Task3(void *params);
static int Task3Destroy(void *params);
static int Task4(void *params);

int main()
{
    Tests();
    PASS;
    return 0;
}

/******************************** Functions ***********************************/

void Tests(void)
{
    char *letter_array = (char *)malloc(26);
    sched_t *sch = SchedCreate();
    int t2_counter = 0;
    
    TEST("Create", (NULL != sch), 1);
    TEST("Size", SchedSize(sch), 0);
    TEST("Is Empty", SchedIsEmpty(sch), 1);
    
    /* 
     * 2 long tasks and one shor task are put into scheduler
     * the short task is non-recurring and will stop the scheduler
     * then a new short task will be put in the scheduler
     */
    SchedAddTask(sch, Task3, letter_array, 1, 1, Task3Destroy);
    SchedAddTask(sch, Task2, &t2_counter, 1, 2, NULL);
    SchedAddTask(sch, Task4, sch, 0, 7, NULL);
    
    TEST("Size", SchedSize(sch), 3);
    
    SchedRun(sch);
    TEST("Size", SchedSize(sch), 2);    
    SchedAddTask(sch, Task1, NULL, 1, 2, NULL);
    TEST("Size", SchedSize(sch), 3);
    
    SchedRun(sch);
    TEST("Size", SchedSize(sch), 0);
    TEST("Is Empty", SchedIsEmpty(sch), 1);
    
    SchedRun(sch);
    SchedDestroy(sch);
}

/* HELPER - task 1 count to 10 */
static int Task1(void *params)
{
    static int counter = 0;
    
    (void)params;
    ++counter;
    
    return (counter != 10);
}

/* HELPER - task 2 count to 15 with a parameter */
static int Task2(void *params)
{
    ++*(int *)params;
    
    return (15 != *(int *)params);
}

/* HELPER - task 3 run through all the alphabet */
static int Task3(void *params)
{
    static size_t counter = 0;
    
    *((char *)params + counter) = LUT[counter];
    ++counter;
    
    return ('z' != *((char *)params + (counter - 1)));
}

/* HELPER - task 3 free allocated array */
static int Task3Destroy(void *params)
{
       free(params); params = NULL;
       
       return 0;
}

/* HELPER - non recurring task 4 that stops schedule after 5 seconds */
static int Task4(void *params)
{
    SchedStop((sched_t *)params);
    
    return 0;
}
