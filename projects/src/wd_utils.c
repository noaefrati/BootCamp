/******************************************************************************* 
 * Description : Implementation of Watchdog Utils API                          *
 * Author: Noa Efrati                                                          *
 * Reviewer: Galit Vaknin                                                      *
 * Date: 26.01,2021                                                            *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/

/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/

#define _POSIX_C_SOURCE 200809L  /*            sigaction requirement          */

#include <signal.h>              /*      kill, sigaction, SIGUSR1, SIGUSR2    */
#include <unistd.h>		         /*                 getpid                    */
#include <stdlib.h>		         /*                malloc, free               */
#include <semaphore.h>	         /*           sem_open, sem_wait              */
#include <fcntl.h>		         /*             O_* ocnstants                 */
#include <sys/stat.h>	         /*              mode constants               */
#include <assert.h>		         /*                  assert                   */
#include <stdio.h>               /*              printf, perror               */

#include "watchdog.h"            /*               watchdog API                */
#include "wd_utils.h"            /*               wd_utils API                */

/******************************************************************************/
/***                       Global & Static Variables                        ***/
/******************************************************************************/
sem_t *wd_sem = NULL;

static size_t g_count_amout_rounds = 0;
static int g_is_get_signal = 0;
int g_sched_state = RUN;
/******************************************************************************/
/***                     Private Functions Declerations                     ***/
/******************************************************************************/
static int TaskGetSig(void *param);
static int TaskSendSig(void *param);

static void Sigusr1Handler(int signal);
static void Sigusr2Handler(int signal);

static int WDInitSigHandlers(void);
static int WDInitSched(watch_dog_params_t *wd);

static who_am_i_t WhoAmI(watch_dog_params_t *wd);

static int RebootUserProc(watch_dog_params_t *wd);

static int AddTasksSched(watch_dog_params_t *wd, size_t sig_wait_time);
/******************************************************************************/
/***                            API Defenitions                             ***/
/******************************************************************************/

int WDInit(watch_dog_params_t *wd)
{
	assert(wd);
	
	if (0 != WDInitSched(wd))
	{	
		return 1;
	}

	if (0 != WDInitSigHandlers())
	{
		SchedDestroy(wd->_internal_params->sched); 
		wd->_internal_params->sched = NULL;
		
		perror("Sigaction failed");
		
		return 1;
	}
	
	wd_sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);
	if(NULL == wd_sem)
	{
		perror("Failed to sem_open");
		 
		return 1;
	}
	
	printf("\nEnd to init in proccess: (%d).\n", getpid());
	
	return 0;
}

int WDSchedRunRoutine(watch_dog_params_t *wd)
{
	assert(wd);

	printf("Sched Run. In process:  (%d).\n", getpid());
	
	SchedRun(wd->_internal_params->sched);
		
	printf("Sched Stop. In process: (%d).\n", getpid());
	SchedDestroy(wd->_internal_params->sched);
	
	return 0;
}

int RebootWDProcess(watch_dog_params_t *wd)
{
	pid_t child_pid = fork();
	
	assert(wd);
	
	if (0 > child_pid)
	{
		perror("failed to fork");
		
		return 1; 
	}
	
	/* in the child process */
	if (0 == child_pid)
	{
		execvp(wd->wd_program_full_name, wd->args);
		
		perror("fork fail");	
		
		return -1;
	}
	else /* in the parent process */
	{
		wd->_internal_params->wd_pid = child_pid;
		wd->_internal_params->other_side_pid = child_pid;
	}
	

	return 0; /* success ! */
}
/******************************************************************************/

static int WDInitSched(watch_dog_params_t *wd)
{
	sched_t *sched = NULL;
	
	assert(wd);
	
	sched = SchedCreate();
	
	if (NULL == sched)
	{
		perror("Memory allocation error");
		
		return 1; 
	}
	
	wd->_internal_params->sched = sched;	
	
	if (USER == WhoAmI(wd) && 0 != AddTasksSched(wd, wd->user_signal_wait_time))
	{    
	  
		SchedDestroy(wd->_internal_params->sched);
		wd->_internal_params->sched = NULL;
			
		perror("Failed to add task");
			
		return 1;				
		
	}
	else
	{
		 if (0 != AddTasksSched(wd, wd->wd_signal_wait_time))
		{
			SchedDestroy(wd->_internal_params->sched);
			wd->_internal_params->sched = NULL;
			
			perror("Failed to add task");
			
			return 1;				
		}	
	}

	return 0; /* success ! */				 
}
/******************************************************************************/
static int AddTasksSched(watch_dog_params_t *wd, size_t sig_wait_time)
{
	ilrd_uid_t bad_uid = UIDGetBadUid();
  	ilrd_uid_t current_uid = {0};
  	
	assert(wd);
	
	current_uid = SchedAddTask(wd->_internal_params->sched,
											   TaskSendSig,
											            wd,
											 sig_wait_time, 
									    wd->init_wait_time,
											         NULL);
							   
	if (UIDIsSame(bad_uid, current_uid))
	{
		return 1;
	}
	                    
	current_uid = SchedAddTask(wd->_internal_params->sched,
							                    TaskGetSig,
							                            wd,
							                 sig_wait_time, 
							            wd->init_wait_time,
							                         NULL);
	
	if (UIDIsSame(bad_uid, current_uid))
	{
		return 1;
	}						   
	   
	return 0;
}
static int TaskSendSig(void *param)
{
	watch_dog_params_t *wd = NULL;
	
	assert(param);
	
	wd = (watch_dog_params_t *) param;
	
	if(g_sched_state == STOP)
	{
		SchedStop(wd->_internal_params->sched);
		
		return 0; /* not to reapet this task */
	}
	
	if (g_sched_state == RUN)
	{
		kill(wd->_internal_params->other_side_pid, SIGUSR1);
	}
	
	printf("Task send signal in (%d) to (%d).\n", 
	                            getpid(), wd->_internal_params->other_side_pid);
	return 1;
}
/******************************************************************************/
static int TaskGetSig(void *param)
{
	watch_dog_params_t *wd = NULL;

	assert(param);

	wd = (watch_dog_params_t *) param;
	
	printf("Task get signal in  (%d) to (%d).\n", 
	                            getpid(), wd->_internal_params->other_side_pid);
	
	if (g_sched_state == STOP)
	{
		SchedClear(wd->_internal_params->sched);
		return 0;
	}
	
	if (!g_is_get_signal)
	{
		++g_count_amout_rounds;
		
		if (g_count_amout_rounds >= wd->signal_missed_amt)
		{
			g_count_amout_rounds = 0;
			g_is_get_signal = 1;
			
			if (WD == WhoAmI(wd))
			{
				SchedStop(wd->_internal_params->sched);
				printf("Reboot USER process (%d), by WD process (%d).\n",
				                 wd->_internal_params->other_side_pid,getpid());
				RebootUserProc(wd);
			}
			else
			{
				printf("Reboot WD process (%d), by USER process (%d).\n", 
				                 wd->_internal_params->other_side_pid,getpid());
				RebootWDProcess(wd);
			}
		}
	}
	else
	{
		g_is_get_signal = 0;
	}
	
	return 1; /* the task is recurring */
}
/******************************************************************************/

static int RebootUserProc(watch_dog_params_t *wd)
{
	assert(wd);
	
	if (-1 ==  execv(wd->user_program_full_name, wd->args))
	{
		perror("Fork failed");	
		return -1;
	}

	return 0;
}
static who_am_i_t WhoAmI(watch_dog_params_t *wd)
{
	assert(wd);
	
	if (getpid() == wd->_internal_params->wd_pid)
	{
		return WD;
	}
	
	return USER;
}
static int WDInitSigHandlers(void)
{
	struct sigaction first_sig = {0};
	struct sigaction second_sig = {0};
	
	first_sig.sa_handler = Sigusr1Handler;
	first_sig.sa_flags = 0;
	
	if (0 != sigaction(SIGUSR1, &first_sig, NULL))
	{
		return 1;
	}
	
	second_sig.sa_handler = Sigusr2Handler;
	second_sig.sa_flags = 0;
	
	if (0 != sigaction(SIGUSR2, &second_sig, NULL))
	{
		return 1;
	}
	
	return 0;
}
/******************************************************************************/
static void Sigusr1Handler(int signal)
{
	UNUSED(signal);
	
	write(2, "Handler1", 8);
	
	g_count_amout_rounds = 0;
	g_is_get_signal = 1;
}
/******************************************************************************/
static void Sigusr2Handler(int signal)
{
	UNUSED(signal);
	
	write(2, "Handler2--", 10);
	
	g_sched_state = STOP;
}
/******************************************************************************/

