/******************************************************************************
Description: Task functions
Author: Roi Peretz
Reviewer: Amir Tamir

Infinity Labs OL97
*******************************************************************************/

/******************************************************************************/
/***                      Includes and Defines                              ***/
/******************************************************************************/
#include <assert.h>    /* assert */
#include <stdlib.h>    /* malloc, realloc, free */

#include "thread_safe_uid.h"       /* Uid API */
#include "task.h"      /* Task API */


/******************************************************************************/
/***                    structs and function typedefs                       ***/
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
/***                         API functions                                  ***/
/******************************************************************************/

task_t *TaskCreate(int (*exec_func)(void *params), 
                   void *params, 
                   size_t freq, 
                   time_t time_to_exec,
                   int (*destroy_params)(void *params))
{

	task_t *new = NULL;
	
	assert(exec_func);
		
	new = (task_t *)malloc(sizeof(task_t));
	
	if (NULL != new)
	{
		new->uid = UIDCreate();
		if (!UIDIsSame(UIDGetBadUid(), new->uid))
		{
			new->exec_func = exec_func;
			new->params = params;
			new->freq = freq;
			new->time_to_exec = time_to_exec;
			new->destroy_params = destroy_params;
		}
		
		else
		{
			destroy_params(params); params = NULL;
			free(new); new = NULL;
		}
	}
	
	return (new);
}

int TaskDestroy(task_t *task)
{
	int flag = 0;
	
	assert(task);
	
	if (NULL != task->destroy_params)
	{
		flag = task->destroy_params(task->params);
	}
	
	free(task); task = NULL;
	
	return (flag);
}

ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(task);
	
	return (task->uid);
}

size_t TaskGetFreq(const task_t *task)
{
	assert(task);
	
	return (task->freq);
}

time_t TaskGetTimeToExec(const task_t *task)
{
	assert(task);
	
	return (task->time_to_exec);
}

int TaskExecute(task_t *task)
{
	assert(task);
	
	return(task->exec_func(task->params));
}

void TaskSetNextExecTime(task_t *task, time_t new_exec_time)
{
	assert(task);
	
	task->time_to_exec = new_exec_time;
}



