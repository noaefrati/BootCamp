/******************************************************************************
Description: Watchdog shared object functions implementation
Author: Roi Peretz
Reviewer: Noa Efrati
				
Infinity Labs OL97
*******************************************************************************/

/******************************************************************************/
/***                      Includes and Defines                              ***/
/******************************************************************************/
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif /* _POSIX_CSOURCE */ 
 
#include <stdio.h>   /* peror */
#include <errno.h>   /* errno */
#include <string.h>  /* memcpy */ 
#include <assert.h>  /* assert */
#include <time.h>    /* clock_gettime */
#include <signal.h>  /* kill , SIGUSR1 */
#include <fcntl.h>   /* For O* constants */
#include <unistd.h>  /* getppid, fork, exec */
#include <stdlib.h>  /* abort, malloc, free, printf (debug only) */
 
#include "watchdog.h"	      /* Watchdog API */
#include "watchdog_utils.h"	  /* Watchdog shared object API */

#define SIGNAL_PARAMS_SIZE 7

/******************************************************************************/
/***                   static functions declaration                         ***/
/******************************************************************************/

static int AddTasks(void **receive_signal_params);
static void DestroySemaphore(sem_t *thread_is_ready, sem_t *wd_is_ready);

/******************************************************************************/
/***                         API functions                                  ***/
/******************************************************************************/

sched_t *Constractor(watch_dog_params_t *args, 
					 caller_t caller,
					 int *signal_recived,
					 int *is_stoped,
					 sem_t *thread_is_ready, 
					 sem_t *wd_is_ready)
{
	sched_t *sched = NULL;
	void **receive_signal_params = NULL;
	assert(args);
	assert(signal_recived);
	assert(is_stoped);
	assert(thread_is_ready);
	assert(wd_is_ready);
	  
	receive_signal_params = malloc(sizeof(void *) * SIGNAL_PARAMS_SIZE);
	if (NULL == receive_signal_params)
	{
		perror("Malloc failed");
		return (NULL);
  	}
  
  	sched = SchedCreate();
  	if (NULL == sched)
  	{
    	  DestroyReceiveSignalParams(receive_signal_params);
    	  perror("Sched failed");
    	  return (NULL);
    	  
  	}
  
	receive_signal_params[0] = (void *)args;
	receive_signal_params[1] = (void *)caller;
	receive_signal_params[2] = (void *)signal_recived;
	receive_signal_params[3] = (void *)sched;
	receive_signal_params[4] = (void *)is_stoped;
	receive_signal_params[5] = (void *)thread_is_ready;
	receive_signal_params[6] = (void *)wd_is_ready;
	
	if (1 == AddTasks(receive_signal_params))
	{
		SchedDestroy(sched);
		DestroyReceiveSignalParams(receive_signal_params);
    	perror("Add tasks failed");
    	return (NULL);
	}
	
  	return (sched);      
}

int SendSignal(void *params)
{
	pid_t pid = 0;
	
	if (NULL == params)
	{
		pid = getppid();
		#ifndef NDEBUG
		printf("WD - sendind signal!\n");
		#endif 
	}
	
	else
	{
		pid = *(pid_t *)params;
		#ifndef NDEBUG
		printf("UP - sendind signal!\n");
		#endif
	}
	
	kill(pid, SIGUSR1);
	
	return 1;
}

int ReceiveSignal(void *params)
{
	static void *recive_signal_params[SIGNAL_PARAMS_SIZE] = {0, 0, 0, 0};
	int *signal_recived = NULL;
	int *is_stoped = NULL;
	sched_t *sched = NULL;
	
	assert(params);
		
	memcpy(recive_signal_params, params, SIGNAL_PARAMS_SIZE * sizeof(void *));
	
	signal_recived = (int *)(recive_signal_params[2]);
	sched = (sched_t *)(recive_signal_params[3]);
	is_stoped = (int *)(recive_signal_params[4]);
	
	if (1 == *is_stoped)
	{
		SchedStop(sched);
		return 0;
	}
	
	if (1 == *signal_recived)
	{
		#ifndef NDEBUG
		caller_t caller = (caller_t)(recive_signal_params[1]);
		if (USER_THREAD == caller)
		{
			printf("UP - received signal!\n");
		}
		else
		{
			printf("WD - received signal!\n");
		}
		#endif 
		*signal_recived = 0;
	}
	
	else 
	{
		revive(recive_signal_params);				
	}
	
	return 1;		
}

void revive(void **params)
{
	watch_dog_params_t *args = NULL;
	sched_t *sched = NULL;
	caller_t caller = 0;
	sem_t *thread_is_ready = NULL; 
	sem_t *wd_is_ready = NULL;
	
	assert(params);
	
	args = (watch_dog_params_t *)(params[0]);
	caller = (caller_t)(params[1]);
	sched = (sched_t *)(params[3]);
	thread_is_ready = (sem_t *)(params[5]);
	wd_is_ready = (sem_t *)(params[6]);
	
	if (WD_PROCESS == caller)
	{
		char *program_full_name = args->user_program_full_name;
		char **arg_list = args->args + 1;
	
		SchedStop(sched);
		cleanup(sched, WD_PROCESS, args, thread_is_ready, wd_is_ready);
		
		execv(program_full_name, arg_list);
		perror("Execv failed");
	 	abort();	
	}
	
	else
	{
		#ifndef NDEBUG
		printf("revived wd!\n");
		#endif
		 
		SpawnWD(args);
		SyncWDandProcess(thread_is_ready, wd_is_ready, USER_THREAD,
											 args->init_wait_time);
	}		

}

void cleanup(sched_t *sched, caller_t caller, watch_dog_params_t *args,
			 					sem_t *thread_is_ready, sem_t *wd_is_ready)
{
	assert(sched);
	assert(args);
	
	DestroySemaphore(thread_is_ready, wd_is_ready);	
	SchedDestroy(sched);
	
	if (WD_PROCESS == caller)
	{
		free(args); args = NULL;
	}
	
	if (USER_THREAD == caller)
	{
		free(args->_internal_params); args->_internal_params = NULL;
	}
	
}

int SpawnWD(watch_dog_params_t *args) 
{
	char *program_full_name = NULL;
	pid_t child_pid = 0;

	assert(args);
	
	program_full_name = args->wd_program_full_name; 
	child_pid = fork();

	if (child_pid < 0)
	{
 		perror("Fork failed");
		return 1;
 	}
 
	if (0 == child_pid)
	{
	 	execvp (program_full_name, args->args + 1);
	 	perror("an error occurred in execvp\n\n");
	 	abort();
	}

	else
	{
		args->_internal_params->wd_pid = child_pid;
	}

	return 0;
}

int DestroyReceiveSignalParams(void *receive_signal_params)
{
	assert(receive_signal_params);
	
	free(receive_signal_params); receive_signal_params = NULL;
	
	return 0;
}

int OpenNamedSemaphore(sem_t **thread_is_ready, sem_t **wd_is_ready)
{
	assert(thread_is_ready);
	assert(wd_is_ready);
	
	*wd_is_ready = sem_open("/wd_is_ready_OL97_ILRD_", O_CREAT, 0666, 0);
	*thread_is_ready = 
					sem_open("/thread_is_ready_OL97_ILRD_", O_CREAT, 0666, 0);
	
	if (SEM_FAILED == *wd_is_ready || SEM_FAILED == *thread_is_ready)
	{
		perror("Sem open failed");
		return 1;
	}
	
	return 0;
}


int SyncWDandProcess(sem_t *thread_is_ready,
					 sem_t *wd_is_ready, caller_t caller, size_t init_time)
{
	struct timespec time = {0};
	int status = 0;
	
	assert(thread_is_ready);
	assert(wd_is_ready);
	
	if (-1 == clock_gettime(CLOCK_REALTIME, &time)) 
	{
		perror("clock_gettime");
		return 1;
	}
	
	time.tv_sec += init_time;
	
	if (USER_THREAD == caller)
	{
		if (0 != sem_post(thread_is_ready))
		{
			perror("Sem post failed");
			return 1;
		}
	
		while (-1 == (status = sem_timedwait(wd_is_ready, &time))
												 && errno == EINTR)
		{
			continue;       /* Restart if interrupted by handler */
		}
	}
	
	else if (WD_PROCESS == caller)
	{
		if (0 != sem_post(wd_is_ready))
		{
			perror("Sem post failed");
			return 1;
		} 
			
		while (-1 == (status = sem_timedwait(thread_is_ready, &time))
													 && errno == EINTR)
		{
	   		continue;       /* Restart if interrupted by handler */
		}
	}
	
	return status;
}

/******************************************************************************/
/***                         static functions                               ***/
/******************************************************************************/

/*
 * Description: Adds the relevant tasks to the scheduler.
 * Return value:  0 on success, 1 otherwise.
 */
static int AddTasks(void **receive_signal_params)
{
	watch_dog_params_t *args = NULL;
	caller_t caller = 0;
	sched_t *sched = NULL;
	size_t signal_missed_amt = 0;
	size_t signal_wait_time = 0;
  	ilrd_uid_t bad_uid = UIDGetBadUid();
  	ilrd_uid_t current_uid = {0};
  	
  	assert(receive_signal_params);
  	
  	args = (watch_dog_params_t *)(receive_signal_params[0]);
  	caller = (caller_t)(receive_signal_params[1]);
	sched = (sched_t *)(receive_signal_params[3]);
  	
	signal_missed_amt = args->signal_missed_amt;
	
	if (USER_THREAD == caller)
	{
    	args->_internal_params->thread_sched = sched;
    	signal_wait_time = args->wd_signal_wait_time;
    	
    	current_uid = SchedAddTask(sched, SendSignal,
    							  (void *)&(args->_internal_params->wd_pid),
    							   signal_wait_time, 0, NULL);
       	if (UIDIsSame(bad_uid, current_uid))
    	{
   			return 1; 		
    	}
	}
	
	else
	{
    	signal_wait_time = args->user_signal_wait_time;
		
		current_uid = SchedAddTask(sched, SendSignal, NULL,
								   signal_wait_time, 0, NULL);
    	if (UIDIsSame(bad_uid, current_uid)) 
    	{
   	   		return 1; 		
    	}
	}		
	
	current_uid = SchedAddTask(sched, ReceiveSignal,
							  (void *)(receive_signal_params), 
				     		   signal_wait_time * signal_missed_amt,
							   signal_wait_time * signal_missed_amt,
							   DestroyReceiveSignalParams);
	if (UIDIsSame(bad_uid, current_uid))
    {
   	  	return 1; 		
    }
    
    return 0;
}

/*
 * Description: Destroys the semaphores.
 * Return value: none.
 */
static void DestroySemaphore(sem_t *thread_is_ready, sem_t *wd_is_ready)
{
	assert(thread_is_ready);
	assert(wd_is_ready);
	
	sem_unlink("/wd_is_ready_OL97_ILRD_");
	sem_unlink("/thread_is_ready_OL97_ILRD_");
	
	if (0 != sem_close(thread_is_ready))
	{
		perror("Sem closed (thread_is_ready) failed");
	}
	
	if (0 != sem_close(wd_is_ready))
	{
		perror("Sem closed (wd_is_ready) failed");
	}
}
