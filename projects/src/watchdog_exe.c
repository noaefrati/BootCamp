/******************************************************************************* 
 * Description:                                                                *
 * Author: Noa Efrati                                                          *
 * Reviewer: Galit Vaknin                                                      *
 * Date: 26.01,2021                                                            *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/
#include <sys/types.h>	 /*        pid_t       */
#include <signal.h>
#include <stdlib.h>		 /*         atoi        */
#include <semaphore.h>	 /*       sem_post      */
#include <stdio.h>       /*       printf        */
#include <unistd.h>		 /*        pid_t        */
#include "watchdog.h"
#include "wd_utils.h"

#define UNUSED(X) (void)(X)

extern int g_count_amout_rounds;
extern int g_sched_state;

int main(int argc, char *argv[])
{
	watch_dog_params_t *wd = (watch_dog_params_t *) 
	                                         malloc(sizeof(watch_dog_params_t));
	watchdog_utils_t *wd_utl = NULL;
	
	if(NULL == wd)
	{
		return 1;
	}
	
	wd_utl = (watchdog_utils_t *) malloc(sizeof(watchdog_utils_t));
	if (NULL == wd_utl)
	{
		return 1;
	}
	if (NULL == wd_utl)
	{
		return 1;
	}
	

	UNUSED(argc);

	wd->user_program_full_name = getenv("USER_NAME");
	wd->wd_program_full_name = getenv("WD_NAME");

	wd->args = argv;
		
	wd->init_wait_time = atoi(getenv("INIT_WAIT_TIME"));
	wd->user_signal_wait_time = atoi(getenv("U_SIG_WAIT"));
	wd->wd_signal_wait_time = atoi(getenv("WD_SIG_WAIT"));
	wd->signal_missed_amt = atoi(getenv("SIG_MISSED_AMT"));
	
	wd->_internal_params = wd_utl;
	
	wd->_internal_params->wd_pid = getpid();
	wd->_internal_params->thread_id = getppid();
	wd->_internal_params->other_side_pid = getppid();	
	

	if (0 != WDInit(wd))
	{
		return 1;
	}
		
	sem_post(wd_sem);
	printf("\nWD end to init !\n");
	
	WDSchedRunRoutine(wd);
	
	free(wd->_internal_params); wd->_internal_params = NULL;
	free(wd); wd = NULL;
	
	return (0);
								
}

