#ifndef __TASK_H_OL97_ILRD__
#define __TASK_H_OL97_ILRD__

/*******************************************************************************
 *
 * Header file Containing the inner API of task - Definition of interface 
 * operations and suitable declarations.
 *
 * Infinity Labs - OL97                                                      
 ******************************************************************************/
 
/******************************************************************************/
/*                               Includes                                     */
/******************************************************************************/
#include <time.h>       /* time_t */ 
#include "uid.h"       /* uid api */
    
/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/
typedef struct task task_t;

/*  

Inside implementation file:
==========================
struct task
{
	ilrd_uid_t uid;
	int (*exec_func)(void *params);
	void *params;
	size_t freq;
	time_t time_to_exec;
	int (*destroy_params)(void *params);
};
*/

/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/
/*
 * Description: This function is used for creating new task_t struct containing 
 * all the metadata needed for this task maintainance.
 * exec_func - function to execute. returns 1 if execution should be repeated
 * 0 otherwise.
 * time_to_exec - absolute time to execute.
 * freq - time offset (in secounds) from the finish of execution of the task 
 * untill its nextexecution (No re-run marked with 0).
 * destroy_params - optional.
 * Return value: on success - returns a pointer to the allocated struct.
 * on failure destroyed params and returns NULL, when: allocation error,
 * invalid task (task with invalid uid) on other creation error.
 * Time complexity: O(1).
 */
task_t *TaskCreate(int (*exec_func)(void *params), 
                   void *params, 
                   size_t freq, 
                   time_t time_to_exec,
                   int (*destroy_params)(void *params));

/*
 * Description: This function is used for destroying a given task_t struct and 
 * its params (optional).
 * Return value: return 0 if destroy_params succeded, otherwise return 1.
 * Time complexity: O(1).
 */
int TaskDestroy(task_t *task);

/*
 * Description: This function is used for getting the uid of a given task.
 * Return value: uid of a given task.
 * Time complexity: O(1).
 */
ilrd_uid_t TaskGetUid(const task_t *task);

/*
 * Description: This function is used for getting the freq (in secound) of 
 * a given task.
 * Return value: freq of a given task.
 * Time complexity: O(1).
 */
size_t TaskGetFreq(const task_t *task);

/*
 * Description: This function is used for getting the execution time of a given 
 * task.
 * Return value: The execution time of a given task.
 * Time complexity: O(1).
 */
time_t TaskGetTimeToExec(const task_t *task);

/*
 * Description: This function is used for executing a given task.
 * Return value: returns 1 if execution should be repeated
 * 0 otherwise.
 * Time complexity: depending on the nature of task_func and params..
 */
int TaskExecute(task_t *task);

/*
 * Description: This function is used for generating the next schedule of 
 * execution of a given task.
 * new_exec_time - the function receives an absolute time.
 * Time complexity: O(1).
 */
void TaskSetNextExecTime(task_t *task, time_t new_exec_time);

#endif /* __TASK_H_OL97_ILRD__ */
