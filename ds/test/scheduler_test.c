/*************************************************************************** 
 * Description: Testing for doubly linked list functions
 * Author: Oriel Nofekh
 * Reviewer: 
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>         /* printf */
#include "scheduler.h"     /* scheduler API */





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





/******************************************************************************/
/***                   Helper Functions and Variables                       ***/
/******************************************************************************/

typedef struct
{
	sched_t *sch;
	int (*func)(void *params);
	void *params;
	size_t seconds;
} sched_task_t;

typedef struct
{
	sched_t *sch;
	ilrd_uid_t uid;
} sched_uid_t;

static int DoNothing(void *params)
{
	(void) params;
	return 0;
}

static int WaitNumSeconds(void *params)
{
	int num_seconds = *(int *) params;
	sched_t *sch = SchedCreate();
	SchedAddTask(sch, &DoNothing, NULL, 
	             0, num_seconds, NULL);
	SchedRun(sch);
	SchedDestroy(sch);
	return 0;
}

static int AddTaskToSchedule(void *params)
{
	sched_task_t *params_struct = (sched_task_t *) params;
	SchedAddTask(params_struct->sch, params_struct->func, 
	             params_struct->params, 
	             0, params_struct->seconds, NULL);
	return 0;
}

static int RemoveTaskFromSchedule(void *params)
{
	sched_uid_t *params_struct = (sched_uid_t *) params;
	SchedRemoveTask(params_struct->sch, params_struct->uid);
	return 0;
}

/***************************************************************/

static int PrintNumber(void *params)
{
	printf("%d ", *(int *) params);
	if (3 == *(int *) params)
	{
		printf("\n");
	}
	return 0;
}

/***************************************************************/

static int test_counter_3 = 0;

static int TestToExecute3(void *params)
{
	switch (test_counter_3)
	{
		case 0:
			TEST("TEST", (*(int *) params), 1);
			break;
		case 1:
			TEST("TEST", (*(int *) params), 9);
			break;
		case 2:
			TEST("TEST", (*(int *) params), 90);
			break;
		case 3:
			TEST("TEST", (*(int *) params), 102);
			break;
	}
	
	++test_counter_3;
	
	return 0;
}

static int test_counter_45 = 0;

static int TestToExecute45(void *params)
{
	switch (test_counter_45)
	{
		case 0:
			TEST("TEST", (*(int *) params), 0);
			break;
		case 1:
			TEST("TEST", (*(int *) params), 8);
			break;
		case 2:
			TEST("TEST", (*(int *) params), 80);
			break;
		case 3:
			TEST("TEST", (*(int *) params), 101);
			break;
	}
	
	++test_counter_45;
	
	return 0;
}

static int FuncToExecute1(void *params)
{
	(*(int *) params) += 1;
	
	return 0;
}

static int FuncToExecute2(void *params)
{
	(*(int *) params) += 2;
	
	return (8 > (*(int *) params));
}

static int FuncToExecute3(void *params)
{
	(*(int *) params) += 3;
	
	return (100 > (*(int *) params));
}

static int FuncToExecuteX10(void *params)
{
	(*(int *) params) *= 10;
	
	return 0;
}

static int FuncToExecuteStop(void *params)
{
	SchedStop((sched_t *) params);
	
	return 0;
}

static int DestroyParamSched(void *params)
{
	SchedDestroy((sched_t *) params);
	
	return 0;
}

/******************************************************************************/
/***                          Testing Functions                             ***/
/******************************************************************************/

static void TestCreateDestroy(void)
{
	sched_t *sch = SchedCreate();
	
	SchedDestroy(sch);
	
	printf(BOLDBLUE "Completed TestCreateDestroy\n" DEF);
}



static void Test0(void)
{
	/* tests all sorts of things without adding or removing tasks to/from the scheduler */
	 
	sched_t *sch = SchedCreate();
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	SchedClear(sch);
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	SchedRun(sch);
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	SchedStop(sch);
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	TEST("Remove", SchedRemoveTask(sch, UIDCreate()), -1);
	TEST("Remove", SchedRemoveTask(sch, UIDGetBadUid()), -1);
	
	SchedDestroy(sch);
	
	printf(BOLDBLUE "Completed Test0\n" DEF);
}



static void Test1(void)
{
	/* a simple test - add tasks, then runs them in order */
	
	ilrd_uid_t uid = UIDGetBadUid();
	static int arr[] = {0, 0, 0, 0, 0,
	                    0, 0, 0, 0, 0};
	
	sched_t *sch = SchedCreate();
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	uid = SchedAddTask(sch, &FuncToExecute1, arr + 5, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &FuncToExecute1, arr + 5, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &FuncToExecuteX10, arr + 5, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &FuncToExecute1, arr + 5, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	TEST("Size", SchedSize(sch), 4);
	
	printf(BOLDMAGENTA "Running Scheduler will begin momentarily.\n"
	       "Expected running time is 2 seconds\n" DEF);
	
	SchedRun(sch);
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	SchedDestroy(sch);
	
	/* THIS IS THE MAIN TEST HERE */
	TEST("Check if correct value", arr[5], 21);
	
	printf(BOLDBLUE "Completed Test1\n" DEF);
}



static void Test2(void)
{
	/* similar to Test1, but with SchedStop in the middle */
	
	ilrd_uid_t uid = UIDGetBadUid();
	static int arr[] = {0, 0, 0, 0, 0,
	                    0, 0, 0, 0, 0};
	
	sched_t *sch = SchedCreate();
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	uid = SchedAddTask(sch, &FuncToExecute1, arr + 5, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &FuncToExecute1, arr + 5, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &FuncToExecuteX10, arr + 5, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	
	/* HERE WE ENTER A FUNCTION TO STOP THE RUN */
	uid = SchedAddTask(sch, &FuncToExecuteStop, sch, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	
	uid = SchedAddTask(sch, &FuncToExecute1, arr + 5, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	TEST("Size", SchedSize(sch), 5);
	
	
	printf(BOLDMAGENTA "Running Scheduler will begin momentarily.\n"
	       "Expected running time is 2 seconds\n" DEF);
	
	SchedRun(sch);
	
	TEST("IsEmpty", SchedIsEmpty(sch), 0);
	TEST("Size", SchedSize(sch), 1);
	
	SchedDestroy(sch);
	
	/* THIS IS THE MAIN TEST HERE */
	TEST("Check if correct value", arr[5], 20);
	
	printf(BOLDBLUE "Completed Test2\n" DEF);
}



static void Test3(void)
{
	/* here there are also some tasks that happen a few times (according to their frequencies) */
	
	ilrd_uid_t uid = UIDGetBadUid();
	static int arr[] = {0, 0, 0, 0, 0,
	                    0, 0, 0, 0, 0};
	
	sched_t *sch = SchedCreate();
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	uid = SchedAddTask(sch, &FuncToExecute1, arr + 0, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("IsEmpty", SchedIsEmpty(sch), 0);
	TEST("Size", SchedSize(sch), 1);
	
	uid = SchedAddTask(sch, &TestToExecute3, arr + 0, 1, 3, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("IsEmpty", SchedIsEmpty(sch), 0);
	TEST("Size", SchedSize(sch), 2);
	
	
	uid = SchedAddTask(sch, &FuncToExecute2, arr + 0, 1, 4, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 3);
	
	uid = SchedAddTask(sch, &TestToExecute3, arr + 0, 1, 9, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 4);
	
	
	uid = SchedAddTask(sch, &FuncToExecuteX10, arr + 0, 1, 10, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 5);
	
	uid = SchedAddTask(sch, &TestToExecute3, arr + 0, 1, 11, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 6);
	
	
	uid = SchedAddTask(sch, &FuncToExecute3, arr + 0, 1, 12, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 7);
	
	uid = SchedAddTask(sch, &TestToExecute3, arr + 0, 1, 18, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 8);
	
	
	printf(BOLDMAGENTA "Running Scheduler will begin momentarily.\n"
	       "Expected running time is 18 seconds\n" DEF);
	
	SchedRun(sch);
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	SchedDestroy(sch);
	
	test_counter_3 = 0;
	
	printf(BOLDBLUE "Completed Test3\n" DEF);
}



static void Test4(void)
{
	/* similar to Test3, but here we SchedClear in the middle of preparing the scheduler */
	
	ilrd_uid_t uid = UIDGetBadUid();
	static int arr[] = {0, 0, 0, 0, 0,
	                    0, 0, 0, 0, 0};
	
	sched_t *sch = SchedCreate();
	
	TEST("Size", SchedSize(sch), 0);
	
	uid = SchedAddTask(sch, &FuncToExecute1, arr + 1, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 1);
	
	uid = SchedAddTask(sch, &FuncToExecute1, arr + 1, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 2);
	
	SchedClear(sch); /************************************/
	
	uid = SchedAddTask(sch, &TestToExecute45, arr + 1, 1, 3, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 1);
	
	
	uid = SchedAddTask(sch, &FuncToExecute2, arr + 1, 1, 4, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 2);
	
	uid = SchedAddTask(sch, &TestToExecute45, arr + 1, 1, 9, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 3);
	
	
	uid = SchedAddTask(sch, &FuncToExecuteX10, arr + 1, 1, 10, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 4);
	
	uid = SchedAddTask(sch, &TestToExecute45, arr + 1, 1, 11, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 5);
	
	
	uid = SchedAddTask(sch, &FuncToExecute3, arr + 1, 1, 12, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 6);
	
	uid = SchedAddTask(sch, &TestToExecute45, arr + 1, 1, 27, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 7);
	
	
	printf(BOLDMAGENTA "Running Scheduler will begin momentarily.\n"
	       "Expected running time is 27 seconds\n" DEF);
	
	SchedRun(sch);
	
	TEST("Size", SchedSize(sch), 0);
	
	SchedDestroy(sch);
	
	test_counter_45 = 0;
	
	printf(BOLDBLUE "Completed Test4\n" DEF);
}



static void Test5(void)
{
	/* similar to Test4, but here we remove tasks while preparing the scheduler
	   using the SchedRemove function instead of SchedClear */
	
	ilrd_uid_t uid = UIDGetBadUid();
	ilrd_uid_t uid1 = UIDGetBadUid();
	ilrd_uid_t uid2 = UIDGetBadUid();
	ilrd_uid_t uid3 = UIDGetBadUid();
	static int arr[] = {0, 0, 0, 0, 0,
	                    0, 0, 0, 0, 0};
	
	sched_t *sch = SchedCreate();
	
	TEST("Size", SchedSize(sch), 0);
	
	uid1 = SchedAddTask(sch, &FuncToExecute1, arr + 2, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid1, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 1);
	
	uid2 = SchedAddTask(sch, &FuncToExecute1, arr + 2, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid2, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 2);
	
	uid = SchedAddTask(sch, &TestToExecute45, arr + 2, 1, 3, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 3);
	
	
	uid = SchedAddTask(sch, &FuncToExecute2, arr + 2, 1, 4, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 4);
	
	uid = SchedAddTask(sch, &TestToExecute45, arr + 2, 1, 9, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 5);
	
	
	uid3 = SchedAddTask(sch, &FuncToExecute1, arr + 2, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid3, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 6);
	
	
	uid = SchedAddTask(sch, &FuncToExecuteX10, arr + 2, 1, 10, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 7);
	
	uid = SchedAddTask(sch, &TestToExecute45, arr + 2, 1, 11, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 8);
	
	
	uid = SchedAddTask(sch, &FuncToExecute3, arr + 2, 1, 12, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 9);
	
	uid = SchedAddTask(sch, &TestToExecute45, arr + 2, 1, 27, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	TEST("Size", SchedSize(sch), 10);
	
	
	SchedRemoveTask(sch, uid2);
	SchedRemoveTask(sch, uid3);
	SchedRemoveTask(sch, uid1);
	TEST("Size", SchedSize(sch), 7);
	
	
	printf(BOLDMAGENTA "Running Scheduler will begin momentarily.\n"
	       "Expected running time is 27 seconds\n" DEF);
	
	SchedRun(sch);
	
	TEST("Size", SchedSize(sch), 0);
	
	SchedDestroy(sch);
	
	test_counter_45 = 0;
	
	printf(BOLDBLUE "Completed Test5\n" DEF);
}



static void Test6(void)
{
	/* here we add a task in the middle of the run, using another task that adds it */
	
	ilrd_uid_t uid = UIDGetBadUid();
	static int arr[] = {0, 0, 0, 0, 0,
	                    0, 0, 0, 0, 0};
	
	sched_t *sch = SchedCreate();
	
	sched_task_t sched_task = {NULL, &FuncToExecute1, arr + 5, 4};
	sched_task.sch = sch;
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	/*  add a task while running */
	uid = SchedAddTask(sch, &AddTaskToSchedule, &sched_task, 0, 6, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	
	uid = SchedAddTask(sch, &FuncToExecute1, arr + 5, 1, 8, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &FuncToExecuteX10, arr + 5, 1, 8, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &FuncToExecute1, arr + 5, 1, 8, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	TEST("Size", SchedSize(sch), 4);
	
	
	printf(BOLDMAGENTA "Running Scheduler will begin momentarily.\n"
	       "Expected running time is 10 seconds\n" DEF);
	
	SchedRun(sch);
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	SchedDestroy(sch);
	
	/* THIS IS THE MAIN TEST HERE */
	TEST("Check if correct value", arr[5], 12);   /* 12 = 1*10 + 1 + 1 */
	
	printf(BOLDBLUE "Completed Test6\n" DEF);
}



static void Test7(void)
{
	/* here we check that if 15 seconds have passed, 
	   then all tasks that were scheduled to less than 15 seconds ahead
	   will be performed immediately */
	
	ilrd_uid_t uid = UIDGetBadUid();
	static int arr[] = {1, 2, 3};
	size_t seconds = 15;
	
	sched_t *sch = SchedCreate();
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	/* wait 10 seconds at first */
	uid = SchedAddTask(sch, &WaitNumSeconds, &seconds, 
	                   0, 0, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &PrintNumber, arr + 0, 1, 0, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &PrintNumber, arr + 1, 1, 6, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &PrintNumber, arr + 2, 1, 12, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	TEST("Size", SchedSize(sch), 4);
	
	
	printf(BOLDMAGENTA "Running Scheduler will begin momentarily.\n"
	       "Expected running time is 15 seconds\n" DEF);
	printf(BOLDYELLOW "Pay Close Attention!!!\n"
	       "It should do nothing for 15 seconds, then immediately print: '1 2 3'\n" DEF);
	
	SchedRun(sch);
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	
	/* wait 10 seconds at first */
	uid = SchedAddTask(sch, &WaitNumSeconds, &seconds, 0, 0, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	/* HERE WE ENTER A FUNCTION TO STOP THE RUN */
	uid = SchedAddTask(sch, &FuncToExecuteStop, sch, 1, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &PrintNumber, arr + 0, 1, 0, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &PrintNumber, arr + 1, 1, 6, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	uid = SchedAddTask(sch, &PrintNumber, arr + 2, 1, 12, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	TEST("Size", SchedSize(sch), 5);
	
	
	printf(BOLDMAGENTA "Running Scheduler will begin momentarily.\n"
	       "Expected running time is 15 seconds\n" DEF);
	printf(BOLDYELLOW "Pay Close Attention!!!\n"
	       "It should do nothing for 15 seconds, then immediately print: '1 2 3'\n" DEF);
	
	SchedRun(sch);
	
	SchedRun(sch);   /* run again after the stop */
	
	SchedDestroy(sch);
	
	printf(BOLDBLUE "Completed Test7\n" DEF);
}



static void Test8(void)
{
	/* here we remove tasks while running, using other tasks that remove them */
	
	ilrd_uid_t uid = UIDGetBadUid();
	ilrd_uid_t uid1 = UIDGetBadUid();
	ilrd_uid_t uid2 = UIDGetBadUid();
	ilrd_uid_t uid3 = UIDGetBadUid();
	static int arr[] = {0, 0, 0, 0, 0,
	                    0, 0, 0, 0, 0};
	
	sched_t *sch = SchedCreate();
	
	sched_uid_t sched_uid1 = {NULL};
	sched_uid_t sched_uid2 = {NULL};
	sched_uid_t sched_uid3 = {NULL};
	sched_uid1.sch = sch;
	sched_uid2.sch = sch;
	sched_uid3.sch = sch;
	
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	uid1 = SchedAddTask(sch, &FuncToExecute1, arr + 5, 1, 18, NULL);
	TEST("Valid UID?", UIDIsSame(uid1, UIDGetBadUid()), 0);
	
	uid2 = SchedAddTask(sch, &FuncToExecuteX10, arr + 5, 1, 20, NULL);
	TEST("Valid UID?", UIDIsSame(uid2, UIDGetBadUid()), 0);
	
	uid3 = SchedAddTask(sch, &FuncToExecute1, arr + 5, 1, 22, NULL);
	TEST("Valid UID?", UIDIsSame(uid3, UIDGetBadUid()), 0);
	
	sched_uid1.uid = uid1;
	sched_uid2.uid = uid2;
	sched_uid3.uid = uid3;
	
	/*  remove a task while running */
	uid = SchedAddTask(sch, &RemoveTaskFromSchedule, &sched_uid1, 0, 0, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	/*  remove a task while running */
	uid = SchedAddTask(sch, &RemoveTaskFromSchedule, &sched_uid2, 0, 1, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	/*  remove a task while running */
	uid = SchedAddTask(sch, &RemoveTaskFromSchedule, &sched_uid3, 0, 2, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	TEST("Size", SchedSize(sch), 6);
	
	
	printf(BOLDMAGENTA "Running Scheduler will begin momentarily.\n"
	       "Expected running time is 2 seconds\n"
	       "(if it takes longer (~20 seconds), something is wrong)\n" DEF);
	
	SchedRun(sch);
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	SchedDestroy(sch);
	
	/* THIS IS THE MAIN TEST HERE */
	TEST("Check if correct value", arr[5], 0);
	
	printf(BOLDBLUE "Completed Test8\n" DEF);
}



static void Test9(void)
{
	/* here, at last, we check that the 'destroy_params' function is called properly when needed
	   (make sure to use valgrind to check this) */
	
	ilrd_uid_t uid = UIDGetBadUid();
	
	sched_t *sch = SchedCreate();
	sched_t *sch_param = NULL;
	
	TEST("IsEmpty", SchedIsEmpty(sch), 1);
	TEST("Size", SchedSize(sch), 0);
	
	sch_param = SchedCreate();
	uid = SchedAddTask(sch, &DoNothing, sch_param, 1, 1, &DestroyParamSched);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	SchedClear(sch);   /* let's see if Clear frees everything */
	
	sch_param = SchedCreate();
	uid = SchedAddTask(sch, &DoNothing, sch_param, 1, 2, &DestroyParamSched);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	TEST("Remove", SchedRemoveTask(sch, uid), 0);   /* let's see if Remove frees everything */
	
	/* these two will check if Run frees task and its params after they're used */
	sch_param = SchedCreate();
	uid = SchedAddTask(sch, &DoNothing, sch_param, 1, 3, &DestroyParamSched);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	sch_param = SchedCreate();
	uid = SchedAddTask(sch, &DoNothing, sch_param, 1, 4, &DestroyParamSched);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	/* we'll stop it before to end, to see if Destroy frees everything */
	uid = SchedAddTask(sch, &FuncToExecuteStop, sch, 1, 5, NULL);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	sch_param = SchedCreate();
	uid = SchedAddTask(sch, &DoNothing, sch_param, 1, 7, &DestroyParamSched);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	sch_param = SchedCreate();
	uid = SchedAddTask(sch, &DoNothing, sch_param, 1, 8, &DestroyParamSched);
	TEST("Valid UID?", UIDIsSame(uid, UIDGetBadUid()), 0);
	
	TEST("Size", SchedSize(sch), 5);
	
	printf(BOLDMAGENTA "Running Scheduler will begin momentarily.\n"
	       "Expected running time is 5 seconds\n" DEF);
	
	SchedRun(sch);
	
	TEST("IsEmpty", SchedIsEmpty(sch), 0);
	TEST("Size", SchedSize(sch), 2);
	
	SchedDestroy(sch);
	
	printf(BOLDBLUE "Completed Test9\n" DEF);
}



static void TestMain(void)
{
	TestCreateDestroy();
	
	Test0();
	
	Test1();
	
	Test2();
	
	Test3();
	
	Test4();
	
	Test5();
	
	Test6();
	
	Test7();
	
	Test8();
	
	Test9();
	
	PASS;
}



int main(void)
{
	TestMain();
	
	return 0;
}



