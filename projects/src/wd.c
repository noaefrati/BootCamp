/******************************************************************************* 
 * Description : Implementation of Watchdog API                                *
 * Author: Noa Efrati                                                          *
 * Reviewer: Galit Vaknin                                                      *
 * Date: 26.01,2021                                                            *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/
/* Link with -pthread */

/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/

#define _POSIX_C_SOURCE 200112L  /*              sem_wait requirement         */
#include <signal.h>              /*                    kill                   */
#include <assert.h>              /*                   assert                  */
#include <unistd.h>              /*                getpid, getppid            */
#include <pthread.h>             /*        pthread_create, pthread_join       */
#include <semaphore.h>           /*  sem_t, sem_open, sem_init, sem_destroy   */
#include <stdlib.h>              /*              malloc, setenv               */
#include <stdio.h>               /*              perror, sprintf              */
#include <sys/types.h>           /*                  waitpid                  */
#include <sys/wait.h>            /*                  waitpid                  */

#include "watchdog.h"            /*            main/client watchdog API       */
#include "wd_utils.h"            /*              watchdog_utils API           */

#define SEM_BUF_SIZE 30
/******************************************************************************/
/***                     Private Functions Declerations                     ***/
/******************************************************************************/

static void *WDSetUp(void *arg);

static void CleanUp(watch_dog_params_t *params);

static int SetEnvVars(watch_dog_params_t *wd);

sem_t client_sem;
/******************************************************************************/
/***                            API Defenitions                             ***/
/******************************************************************************/

int WatchDogStart(watch_dog_params_t *params)
{
	watchdog_utils_t *wd_utl = NULL;
	pthread_t user_proc_thread = 0;

	assert(params);
	
	wd_utl = (watchdog_utils_t *) malloc(sizeof(watchdog_utils_t));
	if (NULL == wd_utl)
	{
		return 1;
	}
	
	params->_internal_params = wd_utl;
	
	wd_utl->thread_id = user_proc_thread;
	
	sem_init(&client_sem, 0, 0);
	
	
	if (NULL == getenv("USER_NAME"))
	{
		if (0 != SetEnvVars(params))
		{
			perror("memory allocation error");
			
			return 1;
		}
	}
	
	if (0 != pthread_create(&params->_internal_params->thread_id, 
	                                                     NULL, WDSetUp, params))
	{
		return 1;
	}
	
	sem_wait(&client_sem);
	
	return (0);
}

void WatchDogStop(const watch_dog_params_t *params)
{
	assert(params);
	
	kill(params->_internal_params->wd_pid, SIGUSR2);
	kill(getpid(), SIGUSR2); 
	
	waitpid(params->_internal_params->wd_pid, NULL, 0); 
	
	pthread_join(params->_internal_params->thread_id, NULL);
	
	CleanUp((watch_dog_params_t *)params);
}
/******************************************************************************/
static void CleanUp(watch_dog_params_t *params)
{
	assert(params);

	free(params->_internal_params); params->_internal_params = NULL;

	sem_unlink(SEM_NAME); /* unlink: remove named semaphore */
}

/******************************************************************************/
static void *WDSetUp(void *arg)
{
	watch_dog_params_t *client_proc = NULL;
	
	assert(arg);
	
	client_proc = (watch_dog_params_t *)arg;
	
	RebootWDProcess(client_proc);
	
	if (0 != WDInit(client_proc))
	{
		CleanUp(client_proc);
		sem_post(&client_sem);
				
		return NULL;
	}
	
	sem_wait(wd_sem);
	sem_post(&client_sem);
	WDSchedRunRoutine(client_proc); /* start run the scheduler */
	
	return NULL;
}

/******************************************************************************/
static int SetEnvVars(watch_dog_params_t *wd)
{
	char init_wait_time[SEM_BUF_SIZE] = {0};
	char user_signal_wait_time[SEM_BUF_SIZE] = {0};
	char wd_signal_wait_time[SEM_BUF_SIZE] = {0};
	char signal_missed_amt[SEM_BUF_SIZE] = {0};
	
	assert(wd);
	
	/*init_wait_time = malloc(sizeof(char) * 10);
	if (NULL == init_wait_time)
	{
		return 1;
	}
	
	user_signal_wait_time = malloc(sizeof(char) * 10);
	if (NULL == user_signal_wait_time)
	{
		return 1;
	}
	
	wd_signal_wait_time = malloc(sizeof(char) * 10);
	if (NULL == wd_signal_wait_time)
	{
		return 1;
	}
	
	signal_missed_amt = malloc(sizeof(char) * 10);
	if (NULL == signal_missed_amt)
	{
		return 1;
	}
*/
	sprintf(init_wait_time,"%ld",wd->init_wait_time);
	sprintf(signal_missed_amt, "%ld", wd->signal_missed_amt);
	sprintf(wd_signal_wait_time, "%ld", wd->wd_signal_wait_time);
	sprintf(user_signal_wait_time,"%ld",wd->user_signal_wait_time);
	
	if (0 != setenv("USER_NAME", wd->user_program_full_name, 1))
	{
		return 1;
	}
	wd->user_program_full_name = getenv("USER_NAME");
	
	if (0 != setenv("WD_NAME", wd->wd_program_full_name, 1))
	{
		return 1;
	}
	wd->wd_program_full_name = getenv("WD_NAME");
	
	if (0 != setenv("INIT_WAIT_TIME", init_wait_time, 1))
	{
		return 1;
	}
	wd->init_wait_time = (size_t)atoi(getenv("INIT_WAIT_TIME"));
	
	if (0 != setenv("U_SIG_WAIT", user_signal_wait_time, 1))
	{
		return 1;
	}
	wd->user_signal_wait_time = (size_t)atoi(getenv("U_SIG_WAIT"));
	
	if (0 != setenv("WD_SIG_WAIT", wd_signal_wait_time, 1))
	{
		return 1;
	}
	wd->wd_signal_wait_time = (size_t)atoi(getenv("WD_SIG_WAIT"));
	
	if (0 != setenv("SIG_MISSED_AMT", signal_missed_amt, 1))
	{
		return 1;
	}
	wd->signal_missed_amt = (size_t)atoi(getenv("SIG_MISSED_AMT"));
	
	/*free(init_wait_time); init_wait_time = NULL;
	free(user_signal_wait_time); user_signal_wait_time = NULL;
	free(wd_signal_wait_time); wd_signal_wait_time = NULL;
	free(signal_missed_amt); signal_missed_amt = NULL;
	*/
	return 0;
}


