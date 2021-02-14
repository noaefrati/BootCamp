/****************************************************************************** 
 * Description: Implement Task                                                *
 * Author: Noa Efrati                                                         *
 * Reviewer: Avital Mordechaev                                                *
 * Date: 8.12.20                                                              *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/

/******************************************************************************/
/*                               Includes                                     */
/******************************************************************************/
#include <assert.h>     /* assert                                             */
#include <stdlib.h>     /* malloc                                             */
#include <time.h>       /* time_t                                             */ 
#include "uid.h"        /* uid api                                            */
#include "task.h"       /* task api                                           */
/******************************************************************************/
/*                                                                            */
/******************************************************************************/

struct task
{
	ilrd_uid_t uid;
	int (*exec_func)(void *params);
	void *params;
	size_t freq;
	time_t time_to_exec;
	int (*destroy_params)(void *params);
};

/******************************************************************************/

task_t *TaskCreate(int (*exec_func)(void *params), 
                   void *params, 
                   size_t freq, 
                   time_t time_to_exec,
                   int (*destroy_params)(void *params))
{
	task_t *new_tsk = (task_t *) malloc(sizeof(task_t));
	if (NULL != new_tsk)
	{
		if (UIDIsSame(new_tsk->uid = UIDCreate(), UIDGetBadUid()))
		{
			new_tsk->destroy_params(params);
			free(new_tsk); new_tsk = NULL;
		}
		else
		{
			new_tsk->exec_func = exec_func;
			new_tsk->params = params;
			new_tsk->time_to_exec = time_to_exec;
			new_tsk->freq = freq;
			new_tsk->destroy_params = destroy_params;
		}
	}
	
	return new_tsk;
}


int TaskDestroy(task_t *task)
{
	int ret_val = 0;
	
	assert(NULL != task);
	
	if ( NULL != task->destroy_params)
	{
		ret_val = task->destroy_params(task->params); task->params = NULL;
	}
	
	free(task); task = NULL;
	
	return ret_val;
}

ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(NULL != task);
	
	return (task->uid);
}

size_t TaskGetFreq(const task_t *task)
{
	assert(NULL != task);
	
	return (task->freq);
}

time_t TaskGetTimeToExec(const task_t *task)
{
	assert(NULL != task);
	
	return (task->time_to_exec);
}

int TaskExecute(task_t *task)
{
	assert(NULL != task);
	
	return (task->exec_func(task->params));
}

void TaskSetNextExecTime(task_t *task, time_t new_exec_time)
{
	assert(NULL != task);
	
	task->time_to_exec = new_exec_time;
}
