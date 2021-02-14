/******************************************************************************
Description: Watchdog functions implementation
Author: Roi Peretz
Reviewer: Noa Efrati
				
Infinity Labs OL97
*******************************************************************************/

/******************************************************************************/
/***                      Includes and Defines                              ***/
/******************************************************************************/
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif /* _POSIX_C_SOURCE */

#include <assert.h>	   /* assert */
#include <unistd.h>    /* getpid */
#include <sys/wait.h>  /* waitpid */
#include <stdlib.h>    /* malloc, setenv */
#include <stdio.h>	   /* perror, spritf */
#include <pthread.h>   /* pthread_create, pthread_join */
#include <signal.h>    /* kill, sigaction, SIGUSR1, SIGUSR2 */

#include "watchdog.h"	      /* Watchdog API */
#include "watchdog_utils.h"	  /* Watchdog shared object API */

#define ENV_BUFFER_SIZE 30

/******************************************************************************/
/***                        Global Variables                                ***/
/******************************************************************************/

static int g_eror_flag = 0;
static int g_signal_recived = 0;
static int g_is_stoped = 0;

static sem_t sync_init = {0};
static sem_t *thread_is_ready = NULL;
static sem_t *wd_is_ready = NULL;

/******************************************************************************/
/***                   static functions declaration                         ***/
/******************************************************************************/

static void *ThreadWork(void *arguments);
static void SigactionInit(void);
static int InitSyncInit(sem_t *sync_init);
static int DistroySyncInit(sem_t *sync_init);
static void SetEnvVariables(watch_dog_params_t *params);
static void Sigusr1Handler(int signal);
static void Sigusr2Handler(int signal);

/******************************************************************************/
/***                         API functions                                  ***/
/******************************************************************************/

int WatchDogStart(watch_dog_params_t *params)
{
	assert(params);
	
	params->_internal_params = 
						(watchdog_utils_t *)malloc(sizeof(watchdog_utils_t));
	
	if (NULL == params->_internal_params)
	{
		perror("Malloc failed");
		return 1;
	}
	
	g_eror_flag = InitSyncInit(&sync_init);
		
	if (0 != pthread_create
	   (&params->_internal_params->thread_id, NULL, ThreadWork, (void *)params))
	{
		perror("Thread Creation Failed");
		return 1;
	}
	
	if (0 != sem_wait(&sync_init))
	{
		g_eror_flag = 1;
	}
	 
	g_eror_flag = DistroySyncInit(&sync_init);
	
	return g_eror_flag;
}

void WatchDogStop(watch_dog_params_t *params)
{
	int status = 0;
	pid_t wd_pid = params->_internal_params->wd_pid;
	sched_t *sched = params->_internal_params->thread_sched;
	
	assert(params);
		
	wd_pid = params->_internal_params->wd_pid;
	sched = params->_internal_params->thread_sched;
	
	kill(wd_pid, SIGUSR2);
	kill(getpid(), SIGUSR2);
	
	waitpid(wd_pid, &status, 0);

	if (0 != pthread_join(params->_internal_params->thread_id, NULL))
	{
		perror("Pthread Join Faild");
	} 
	
	cleanup(sched, USER_THREAD, params, thread_is_ready, wd_is_ready);
}

/******************************************************************************/
/***                         static functions                               ***/
/******************************************************************************/

/*
 * Description: Create and run the scheduler needed for the thread
 *              and execute the watch dog.
 * Return value: NULL.
 */
static void *ThreadWork(void *arguments)
 {
  	watch_dog_params_t *args = NULL;
 
  	assert(arguments);
 	
 	args = (watch_dog_params_t *) arguments;

  	SetEnvVariables(args);
	g_eror_flag |= OpenNamedSemaphore(&thread_is_ready, &wd_is_ready);
 	g_eror_flag |= SpawnWD(args); 

   	if (0 == g_eror_flag)
 	{
  		sched_t *sched = 
  		Constractor(args, USER_THREAD, &g_signal_recived, &g_is_stoped,
  										 thread_is_ready, wd_is_ready);
 		
 		if (NULL == sched)
 		{
 			g_eror_flag = 1;
 		} 
 		
 		else
 		{
 			SigactionInit();
 			
			g_eror_flag = SyncWDandProcess(thread_is_ready, wd_is_ready, 
										   USER_THREAD, args->init_wait_time);
			
			if (0 != sem_post(&sync_init))
			{
				perror("Sem post Failed");
				g_eror_flag = 1;
			}
			
			if (0 == g_eror_flag)
			{
 				SchedRun(sched);
 			}
		}
  		 		
 	}

	return NULL;
}

/*
 * Description: Init signal handlers.
 * Return value: none.
 */
static void SigactionInit(void)
{
	struct sigaction siguser1 = {0};
	struct sigaction siguser2 = {0};
				
	siguser1.sa_handler = Sigusr1Handler;
	siguser1.sa_flags = 0;
	
	siguser2.sa_handler = Sigusr2Handler;
	siguser2.sa_flags = 0;
	
	sigaction(SIGUSR1, &siguser1, NULL);  			
	sigaction(SIGUSR2, &siguser2, NULL);  	
}

/*
 * Description: Initialize the SyncInit semaphore which is used to confirm that
 *              the user thread and the watchdog are ready,           
 * Return value: 0 on success, 1 otherwise.
 */
static int InitSyncInit(sem_t *sync_init)
{
	if (0 != sem_init(sync_init, 0,0))
		{
			perror("Sem init (sync_init) failed");
			return 1;
		} 
		
	return 0;
}

/*
 * Description: Destroy the SyncInit semaphore which is used to confirm that
 *              the user thread and the watchdog are ready,           
 * Return value: 0 on success, 1 otherwise.
 */
static int DistroySyncInit(sem_t *sync_init)
{
	if (0 != sem_destroy(sync_init))
		{
			perror("Sem Dystroy (sync_init) failed");
			return 1;
		} 
		
	return 0;
}

/*
 * Description: Set the environment variables needed from the 
 *              watch_dog_params_t struct.
 * Return value: none.
 */
static void SetEnvVariables(watch_dog_params_t *params)
{
	static char init_wait_time[ENV_BUFFER_SIZE];
	static char user_signal_wait_time[ENV_BUFFER_SIZE];
	static char wd_signal_wait_time[ENV_BUFFER_SIZE];
	static char signal_missed_amt[ENV_BUFFER_SIZE];
	
	assert(params);
	
	setenv("USER_PROGRAM_FULL_NAME", params->user_program_full_name, 1);
	
	setenv("WD_PROGRAM_FULL_NAME", params->wd_program_full_name, 1);
	         
    sprintf(init_wait_time, "%ld", params->init_wait_time);   
    setenv("INIT_WAIT_TIME", init_wait_time, 1);
    
    sprintf(user_signal_wait_time,"%ld", params->user_signal_wait_time);  
    setenv("USER_SIGNAL_WAIT_TIME", user_signal_wait_time, 1);
    
    sprintf(wd_signal_wait_time,"%ld", params->wd_signal_wait_time);  
    setenv("WD_SIGNAL_WAIT_TIME", wd_signal_wait_time, 1);
    
    sprintf(signal_missed_amt,"%ld", params->signal_missed_amt);  
    setenv("SIGNAL_MISSED_AMT", signal_missed_amt, 1);
}

/*
 * Description: Handler for SIGUSR1 signal.
 * Return value: none.
 */
static void Sigusr1Handler(int signal)
{
	(void) signal;   
 	g_signal_recived = 1;
}

/*
 * Description: Handler for SIGUSR2 signal.
 * Return value: none.
 */
static void Sigusr2Handler(int signal)
{
	(void)signal;
	g_is_stoped = 1;
}
