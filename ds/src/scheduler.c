/****************************************************************************** 
 * Description: Implement Scheduler functions                                 *
 * Author: Noa Efrati                                                         *
 * Reviewer: Avital Mordechaev                                                *
 * Date: 8.12.20                                                              *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/

/******************************************************************************/
/*                               Includes                                     */
/******************************************************************************/
#include <assert.h>          /* assert                                        */
#include <stdlib.h>          /* malloc, free                                  */
#include <unistd.h>          /* sleep                                         */
#include "scheduler.h"       /* scheduler api                                 */
#include "task.h"            /* task api                                      */
#include "priority_queue.h"  /* priority queue api                            */
/******************************************************************************/
/*                                                                            */
/******************************************************************************/

struct scheduler
{
	pq_t *pq;
	int stop_flag;
};

/******************************************************************************/
/***                        Static Functions                                ***/
/******************************************************************************/
static int CmpTimeToExec(const void *one, const void *other);
static int  IsMatchUid(const void *one, const void *other);
/******************************************************************************/
/***                                                                        ***/
/******************************************************************************/
sched_t *SchedCreate(void)
{
	sched_t *sched = (sched_t *) malloc(sizeof(sched_t));
	if (NULL != sched)
	{
		if (NULL == (sched->pq = PQCreate(&CmpTimeToExec)))
		{
			free(sched); sched = NULL;
		}
		else
		{
			sched->stop_flag = 0;
		}
	}
	
	return sched;
}

void SchedDestroy(sched_t *sch)
{
	assert(NULL != sch);
	
	SchedClear(sch);
	PQDestroy(sch->pq);
	sch->pq = NULL;
	
	free(sch); sch = NULL;
}

size_t SchedSize(const sched_t *sch)
{
	assert(NULL != sch);
	
	return PQSize(sch->pq);
}

int SchedIsEmpty(const sched_t *sch)
{
	assert(NULL != sch);
	
	return PQIsEmpty(sch->pq);
}

void SchedClear(sched_t *sch)
{
	assert(NULL != sch);

	while (!SchedIsEmpty(sch))
	{
		TaskDestroy((task_t *)PQDequeue(sch->pq));		
	}
}

ilrd_uid_t SchedAddTask(sched_t *sch, 
						int (*func_to_execute)(void *params),
				 		void *params, 
				 		size_t freq, 
				 		size_t time_to_exec,
				 		int (*destroy_params)(void *params))
{
	task_t *new_task = NULL;
	ilrd_uid_t uid = UIDGetBadUid();
		
	assert(NULL != sch);
	assert(NULL != func_to_execute);
	
	new_task = TaskCreate(func_to_execute,
						  params,
						  freq,
						  (time(NULL) + time_to_exec),
						  destroy_params);
	
	if (NULL != new_task)
	{	
		if (1 == PQEnqueue(sch->pq, new_task)) /* if enqueue failed */
		{
			TaskDestroy(new_task);
		}
		else
		{
			uid = TaskGetUid(new_task);
		}	
	}
	
	return uid;	
}		
	
int SchedRemoveTask(sched_t *sch, ilrd_uid_t uid)
{
	int ret_val = -1;
	void *found = NULL;
	assert(NULL != sch);
	
	found = PQErase(sch->pq, IsMatchUid, &uid);
	
	if (NULL != found)
	{
		TaskDestroy(found);
		ret_val = 0;
	}
	
	return ret_val;
}
				 
void SchedRun(sched_t *sch)
{
	task_t *tsk = NULL;
	assert(NULL != sch);
	
	sch->stop_flag = 0;
	
	while (!SchedIsEmpty(sch) && 1 != sch->stop_flag)
	{	
		unsigned int diff = 0;	
		tsk = (task_t *)PQDequeue(sch->pq);
		diff = TaskGetTimeToExec(tsk) - time(NULL);
		
		while (0 != diff)
		{
			 sleep(diff);
		}	
		if (1 == TaskExecute(tsk))
		{
			 TaskSetNextExecTime(tsk, time(NULL) + TaskGetFreq(tsk));
			
			if (1 == PQEnqueue(sch->pq, tsk)) /*PQEnqueue failed*/
			{
				TaskDestroy(tsk);
			}
		}
		else 
		{
			TaskDestroy(tsk);
		}		 
	}
	SchedStop(sch);	
}
void SchedStop(sched_t *sch)
{
	assert(NULL != sch);
	
	sch->stop_flag = 1;
}

static int CmpTimeToExec(const void *one, const void *other)
{
 	assert(NULL != one);
 	assert(NULL != other);
 	
 	one = (task_t *)one;
 	other = (task_t *)other;
 	
 	return (TaskGetTimeToExec(one) - TaskGetTimeToExec(other));	      
}
 static int IsMatchUid(const void *one, const void *other)
{
 	assert(NULL != one);
 	assert(NULL != other);
 	
 	return UIDIsSame(TaskGetUid((task_t *)one), *(ilrd_uid_t *)other);
}

