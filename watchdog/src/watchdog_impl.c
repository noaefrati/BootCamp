/******************************************************************************
Description: Watchdog functions implementation
Author: Roi Peretz
Reviewer: Noa Efrati
				
Infinity Labs OL97
*******************************************************************************/

/******************************************************************************/
/***                      Includes and Defines                              ***/
/******************************************************************************/

#include <assert.h>	   /* assert */
#include <stdio.h>	   /* perror */
#include <signal.h>    /* sigaction, SIGUSR1, SIGUSR2 */
#include <stdlib.h>    /* atoi, getenv, malloc, printf (debug only) */

#include "watchdog_utils.h"	  /* Watchdog shared object API */

/******************************************************************************/
/***                        Global Variables                                ***/
/******************************************************************************/
static int g_eror_flag = 0;
static int g_signal_recived = 0;
static int g_is_stoped = 0;

static sem_t *thread_is_ready = NULL;
static sem_t *wd_is_ready = NULL;

/******************************************************************************/
/***                   static functions declaration                         ***/
/******************************************************************************/
static void SigactionInit(void);
static void FillParamsFromEnv(watch_dog_params_t *params, char **argv);
static void Sigusr1Handler(int signal);
static void Sigusr2Handler(int signal);

/******************************************************************************/
/***                         API functions                                  ***/
/******************************************************************************/

int main(int argc, char **argv, char **envp)
{
	watch_dog_params_t *params = NULL;
	sched_t *sched = NULL;
	
	assert(argv);
	(void)envp;
	(void)argc;
	
	#ifndef NDEBUG
	printf("WD: I am alaive!\n");
	#endif
	
	params = (watch_dog_params_t *)malloc(sizeof(watch_dog_params_t));
	
	if (NULL == params)
	{
		perror("Malloc failed");
		return 1;
	}
	
	FillParamsFromEnv(params, argv);
	g_eror_flag = OpenNamedSemaphore(&thread_is_ready, &wd_is_ready);
	
	sched = Constractor(params, WD_PROCESS, &g_signal_recived, 
						&g_is_stoped, thread_is_ready, wd_is_ready);
	
	if (NULL == sched)
	{
		perror("Sched failed");
		return 1;
	} 
	
	else
	{
		SigactionInit();		
				
		g_eror_flag = SyncWDandProcess(thread_is_ready, wd_is_ready,
									   WD_PROCESS, params->init_wait_time);
				
		if (0 == g_eror_flag)
		{
 			SchedRun(sched);
			cleanup(sched, WD_PROCESS, params, thread_is_ready, wd_is_ready);
 		}
		
	}
 
	return 0;
}

/******************************************************************************/
/***                         static functions                               ***/
/******************************************************************************/

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
 * Description: Fill the watch_dog_params_t struct with the
 *              needed parameters from the environment variables.
 * Return value: none.
 */
static void FillParamsFromEnv(watch_dog_params_t *params, char **argv)
{
	assert(params);
	assert(argv);
	
	params->user_program_full_name = getenv("USER_PROGRAM_FULL_NAME");
	
	params->wd_program_full_name = getenv("WD_PROGRAM_FULL_NAME");
	
	params->args = argv;
	
	params->init_wait_time = atoi(getenv("INIT_WAIT_TIME"));
	
	params->user_signal_wait_time = atoi(getenv("USER_SIGNAL_WAIT_TIME"));
	
	params->wd_signal_wait_time = atoi(getenv("WD_SIGNAL_WAIT_TIME"));
	
	params->signal_missed_amt = atoi(getenv("SIGNAL_MISSED_AMT"));
	
	params->_internal_params = NULL;	
}

/*
 * Description: Handler for SIGUSR1 signal.
 * Return value: none.
 */
static void Sigusr1Handler(int signal)
{
	(void)signal;   
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

