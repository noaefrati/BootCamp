#ifndef __SCHED_H_OL97_ILRD__
#define __SCHED_H_OL97_ILRD__

/*******************************************************************************
 *
 * Header file Containing API Definition for scheduler interface operations and 
 * declarations.
 *
 * Infinity Labs - OL97                                                      
 ******************************************************************************/
 
/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h>     /* size_t */
#include <time.h>       /* time_t */

#include "uid.h"       /* uid api */
/******************************************************************************/
/***                               Typedfs                                  ***/
/******************************************************************************/

typedef struct scheduler sched_t;

/*

Inside implementation file:
==========================

struct scheduler
{
	pq_t *pq;
	int stop_flag;
};
*/
/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/
/*
 * Description: This function is used for Creating an empty schduler structure.
 * Return value: On success, the function returns pointer to the alocated  
 * scheduler structure. On failure to allocate memory, NULL will be returned.
 * Time complexity: O(1).
 */
sched_t *SchedCreate(void);
 
/*
 * Description: This function is used for destroying a given scheduler pointed
 * by sch (frees memory of all elements and the queue itself).
 * Return value: non.
 * Time complexity: O(n).
 */
void SchedDestroy(sched_t *sch);
 
/*
 * Description: This function is used for getting the size of a given scheduler.
 * pointed by sch (amount of elements).
 * Return value: This function returns the number of elements in the scheduler  
 * pointed to by sch.
 * Time complexity: O(n).
 */
size_t SchedSize(const sched_t *sch);

/*
 * Description: This function returns whether the given scheduler is empty.
 * Return value: 1 (true) if the size of scheduler pointed by sch is 0,
 * 0 (false) otherwise.
 * Time complexity: O(1).
 */ 
int SchedIsEmpty(const sched_t *sch);


/*
 * Description: This function is used for erasing all elements from a given  
 * scheduler pointed by Sch. The scheduler will remain empty.
 * Note: USE WITH CAUTION: ALL DATA IN LIST WILL BE LOST!
 * user can 
 * Return value: None.
 * Time complexity: O(n).
 */
void SchedClear(sched_t *sch);

/*
 * Description: This function is used for adding a task to the scheduler
 * pointed by Sch.
 * destroy_params is a function that can be sent by the user to free any
 * memory allocated to params.
 * time_to_exec - time in seconds to execute the task after task was added.
 * Return value: The function will return the uid of the added task,
 * return BadUID if failed.
 * If SchedAddTask fails params will be destroyed.
 * Time complexity: O(n).
 */
ilrd_uid_t SchedAddTask(sched_t *sch, 
						int (*func_to_execute)(void *params),
				 		void *params, 
				 		size_t freq, 
				 		size_t time_to_exec,
				 		int (*destroy_params)(void *params));

/*
 * Description: This function is used for removing a task from the scheduler    
 * pointed by Sch.
 * Return value: 0 in success and -1 if task is not found.
 * Time complexity: O(n).
 */
int SchedRemoveTask(sched_t *sch, ilrd_uid_t uid);
				 
/*
 * Description: This function is used for running the scheduler pointed    
 * by sch. 
 * The next task in queue is executed and return 1 if it is recurring.
 * In that case the task will be reschduled and push back into queue.
 * If enqueue failed - the task needs to be destroyed.
 * The task returns 0 if it is non - recurring.
 * Time complexity: depends on each tasks complexity.
 * UB - if func_to_execute returns 1 and freq is 0.
 */
void SchedRun(sched_t *sch);

/*
 * Description: This function is used for stoping the scheduler pointed    
 * by Sch. 
 * Time complexity: O(1).
 */
void SchedStop(sched_t *sch);

#endif /* __SCHED_H_OL97_ILRD__ */
