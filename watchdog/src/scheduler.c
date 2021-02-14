/******************************************************************************
Description: Scheduler functions
Author: Roi Peretz
Reviewer: Amir Tamir

Infinity Labs OL97
*******************************************************************************/
#include <assert.h>    /* assert */
#include <stdlib.h>    /* malloc, realloc, free */
#include <time.h>      /* time */
#include <unistd.h>    /* sleep */

#include "scheduler.h"       /* Scheduler API */
#include "priority_queue.h"  /* PQ API */
#include "task.h"            /* Task API */

struct scheduler
{
	pq_t *pq;
	int stop_flag;
};

enum run_flags {KEEP_RUNNING, STOP_RUNNING};

/******************************************************************************/
/***                  Static Functions Declaration                          ***/
/******************************************************************************/

static int CmpTimeToExec(const void *lhs, const void *rhs);
int CmpToErase(const void *data, const void *to_erase);
static int ClearTask(void *data);

/******************************************************************************/
/***                            API Definitions                             ***/
/******************************************************************************/

sched_t *SchedCreate(void)
{
	sched_t *new = (sched_t *)malloc(sizeof(sched_t));
	
	if (NULL != new)
	{
		new->stop_flag = KEEP_RUNNING;
		
		new->pq = PQCreate(CmpTimeToExec);
		if (NULL == new->pq)
		{
			free(new); new = NULL;
		}
	}
	return (new);
}

void SchedDestroy(sched_t *sch)
{
	assert(sch);
	assert(sch->pq);
	
	SchedClear(sch);
	PQDestroy(sch->pq); sch->pq = NULL;
	
	free(sch); sch = NULL;	
}

size_t SchedSize(const sched_t *sch)
{
	assert(sch);
	assert(sch->pq);
	
	return (PQSize(sch->pq));
}

int SchedIsEmpty(const sched_t *sch)
{
	assert(sch);
	assert(sch->pq);
	
	return (PQIsEmpty(sch->pq));
}

void SchedClear(sched_t *sch)
{
	assert(sch);
	assert(sch->pq);
	
	while(!SchedIsEmpty(sch))
    {
        ClearTask(PQDequeue(sch->pq));
    }
}

ilrd_uid_t SchedAddTask(sched_t *sch, 
						int (*func_to_execute)(void *params),
				 		void *params, 
				 		size_t freq, 
				 		size_t time_to_exec,
				 		int (*destroy_params)(void *params))
{	
	task_t *TaskToAdd = NULL;
	ilrd_uid_t return_uid = UIDGetBadUid();
	time_t now = time(NULL) + time_to_exec;
	
	assert(sch);
	assert(sch->pq);
	assert(func_to_execute);
	
	TaskToAdd = TaskCreate(func_to_execute, params, freq, now, destroy_params);
	
	if (NULL != TaskToAdd)
	{
		if (0 == PQEnqueue(sch->pq, (void *)TaskToAdd))
		{
			return_uid = TaskGetUid(TaskToAdd);	
		}
		
		else
		{
			TaskDestroy(TaskToAdd);
		}
	}
	
	return (return_uid);
}

int SchedRemoveTask(sched_t *sch, ilrd_uid_t uid)
{
	void *uid_to_erase = &uid;
	
	assert (sch);
	assert (sch->pq);
	
	return (ClearTask(PQErase(sch->pq, CmpToErase, uid_to_erase))); 
       
}
				 
void SchedRun(sched_t *sch)
{
	assert (sch);
	assert (sch->pq);
	
	sch->stop_flag = KEEP_RUNNING;
	
	while ((KEEP_RUNNING == sch->stop_flag) && (!PQIsEmpty(sch->pq)))
	{
		time_t run_time = time(NULL);
		time_t delay = 0;
		task_t *head_task = (task_t *)PQDequeue(sch->pq);
		
		delay = (TaskGetTimeToExec(head_task) - run_time);
		
		if (delay > 0)
		{
			do
			{
				delay = sleep(delay);
			}
			while (delay);
		}		
	 	
		if (1 == TaskExecute(head_task))
		{
			TaskSetNextExecTime(head_task, time(NULL) + TaskGetFreq(head_task));
			
			if (1 == PQEnqueue(sch->pq, head_task))
			{
				TaskDestroy(head_task);
				SchedStop(sch);
			}
		}
		
		else
		{
			TaskDestroy(head_task);
		}
	}
}

void SchedStop(sched_t *sch)
{
	assert (sch);
	
	sch->stop_flag = STOP_RUNNING;
}

/******************************************************************************/
/***                       Static Functions                                 ***/
/******************************************************************************/

/* compare function for PQ */
static int CmpTimeToExec(const void *lhs, const void *rhs)
{
    task_t *task_lhs = (task_t *)lhs;
    task_t *task_rhs = (task_t *)rhs;
    
    return (TaskGetTimeToExec(task_lhs) - TaskGetTimeToExec(task_rhs));
}

/* compare function for SchedRemoveTask */
int CmpToErase(const void *data, const void *to_erase)
{
	task_t *task_data = (task_t *)data;
	ilrd_uid_t uid_data = TaskGetUid(task_data);
	
	ilrd_uid_t uid_to_erase = *(ilrd_uid_t *)to_erase;
	
	return UIDIsSame(uid_to_erase, uid_data);
}

/* function that destroys tasks */
static int ClearTask(void *data)
{
	task_t *task = NULL;
	
    if(data == NULL)
    {
        return -1;
    }
    
	task = (task_t *)data;
	return TaskDestroy(task);
}

