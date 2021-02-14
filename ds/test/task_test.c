/*****************************************************************
* Description: Program to test UID
* Author: Oryan Shimoni
* Reviewer:
*
* ILRD - OL97
******************************************************************/

#include <stdio.h>	/* printf() */
#include <stdlib.h> /* malloc */

#include "task.h"

#define RED     "\033[31m"	/* Red */
#define DEF   "\033[0m"		/* DEFAULT */

#define TEST(name, real, expected) (((real) == (expected)) ? 0 : \
printf(RED "%s, failed on line %d\n" DEF, name, __LINE__))

#define NTEST(name, real, expected) (((real) != (expected)) ? 0 : \
printf(RED "%s, failed on line %d\n" DEF, name, __LINE__))

static void TestForCreateAndDestroy(void);
static void TestForTaskExecute(void);
static void TestForTaskSetNextExecTime(void);

int FuncExec(void *params);
int DestroyParams(void *params);
int DestroyFail(void *params);

int main(void)
{
	TestForCreateAndDestroy();
	
	TestForTaskExecute();
	TestForTaskSetNextExecTime();
	
	return 0;
}

static void TestForTaskSetNextExecTime(void)
{
    int *p = (int *) malloc(sizeof(int));
    size_t freq = 6;
    time_t time_exec = { 0 };
    time_t time_ref = { 0 };
    task_t *t = TaskCreate(FuncExec, p, freq, time_exec, DestroyParams);
    *p = 1; 
    
    time_ref = time(NULL);
    TaskSetNextExecTime(t, time_ref);
    TEST("TaskSetNextExecTime", TaskGetTimeToExec(t), time_ref);

    TEST("TaskSetNextExecTime", TaskDestroy(t), 0);
}

static void TestForTaskExecute(void)
{
    int *p = (int *) malloc(sizeof(int));
    size_t freq = 6;
    time_t time_exec = { 0 };
    task_t *t = TaskCreate(FuncExec, p, freq, time_exec, DestroyParams);
    *p = 1; 
    
    TEST("TaskExecute", TaskExecute(t), 1);
    
    *p = 0;
    
    TEST("TaskExecute", TaskExecute(t), 0);
    
    TEST("TaskExecute", TaskDestroy(t), 0);
}

/* test with valgrind */
static void TestForCreateAndDestroy(void)
{
    int *p = (int *) malloc(sizeof(int));
    int another_param = 1;
    size_t freq = 6;
    time_t time_exec = { 0 };
    task_t *t = TaskCreate(FuncExec, p, freq, time_exec, DestroyParams);
    *p = 1; /* repeated */
    
    TEST("Create Test", UIDIsSame(TaskGetUid(t), UIDGetBadUid()), 0);
    TEST("Create Test", TaskGetFreq(t), freq);
    TEST("Create Test", TaskGetTimeToExec(t), time_exec);
   
    TEST("Destroy Test", TaskDestroy(t), 0);
    
    t = TaskCreate(FuncExec, &another_param, freq, time_exec, NULL);
    TEST("Destroy Test", TaskDestroy(t), 0);
    
    t = TaskCreate(FuncExec, &another_param, freq, time_exec, DestroyFail);
    TEST("Destroy Test", TaskDestroy(t), 1);
  
}

int FuncExec(void *params)
{
    return (*(int *)params);
}

int DestroyParams(void *params)
{
    free(params); params = NULL;
    return 0;
}

int DestroyFail(void *params)
{
    (void) params;
    return 1;
}




