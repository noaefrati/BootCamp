#ifndef __WATCHDOG_UTILS_H_OL97_ILRD__
#define __WATCHDOG_UTILS_H_OL97_ILRD__

/******************************************************************************
 * Header file Containing API Definitions for  Watchdog shared object functions.                     
 *                                                                            *
 * Infinity Labs - OL97                                                       *
 ******************************************************************************/

/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/

#include <semaphore.h>        /* sem_t */

#include "scheduler.h"		  /* sched_t */
#include "watchdog.h"	      /* watch_dog_params_t */

/******************************************************************************/
/***                               structs                                  ***/
/******************************************************************************/

struct watchdog_utils
{
	pthread_t thread_id;
	pid_t wd_pid;
	sched_t *thread_sched;	
};

typedef enum 
{
	USER_THREAD,
	WD_PROCESS
}caller_t;

/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/

/*
 * Description: create the scheduler and add tasks 
 *              by caller (Users program / Watchdog).
 * Return value: If the scheduler was created successfully
 *               and all tasks were added a valid sched_t pointer will
 *				 be returned, otherwise NULL.
 */
sched_t *Constractor(watch_dog_params_t *args, 
					 caller_t caller,
					 int *signal_recived,
					 int *is_stoped,
					 sem_t *thread_is_ready, 
					 sem_t *wd_is_ready);
/*
 * Description: Send a signal to the other program (Users program / Watchdog).
 * Return value: The task returns 1 so that it will be recurring.
 */
int SendSignal(void *params);

/*
 * Description: Verify a signal to from the other program
 *              (Users program / Watchdog).
 * Return value: The task returns 1 so that it will be recurring.
 */
int ReceiveSignal(void *params);

/*
 * Description: Executes a progam as needed (Users program / Watchdog).            
 * Return value: 0 on success, 1 otherwise.
 */
void revive(void **params);

/*
 * Description: Destroys and frees all memory allocations.            
 * Return value: none.
 */
void cleanup(sched_t *sched, caller_t caller, 
			 watch_dog_params_t *args,
			 sem_t *thread_is_ready,
			 sem_t *wd_is_ready);

/*
 * Description: Executes a progam a new Watchdog.            
 * Return value: 0 on success, 1 otherwise.
 */	
int SpawnWD(watch_dog_params_t *args); 

/*
 * Description: Cleanup function for ReceiveSignal task.            
 * Return value: 0.
 */	
int DestroyReceiveSignalParams(void *receive_signal_params);

/*
 * Description: Opens all named semaphore needed.            
 * Return value: 0 on success, 1 otherwise.
 */	
int OpenNamedSemaphore(sem_t **thread_is_ready, sem_t **wd_is_ready);

/*
 * Description: Syncs the thread from the user program with 
 *              the watchdog process.            
 * Return value: 0 on success, 1 otherwise.
 */	
int SyncWDandProcess(sem_t *thread_is_ready,
					 sem_t *wd_is_ready,
					 caller_t caller, 
					 size_t init_time);


#endif /* __WATCHDOG_UTILS_H_OL97_ILRD__ */
