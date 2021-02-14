#ifndef __WATCHDOG_UTILS_H__
#define __WATCHDOG_UTILS_H__

/******************************************************************************
 * Header file Containing API Definitions for Watchdog Utils.                 *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************/
/***                              Includes                                  ***/
/******************************************************************************/
#include <semaphore.h>         /*      sem_t      */
#include "scheduler.h"         /*  scheduler API  */
#include "watchdog.h"
/******************************************************************************/
/***                         Typedfs & Defines                              ***/
/******************************************************************************/

#define SEM_NAME "MY_WD_OL97"
#define UNUSED(X) (void)(X)

typedef enum
{
	RUN = 0, 
	STOP
} sched_state_t;

typedef enum
{
	WD = 0,
	USER
}who_am_i_t;

/******************************************************************************/
/***                              Structs                                   ***/
/******************************************************************************/

struct watchdog_utils 
{
	pthread_t thread_id;
	pid_t wd_pid;
	pid_t other_side_pid;
	sched_t *sched;
};

/******************************************************************************/
/***                           Global Variables                             ***/
/******************************************************************************/
extern sem_t *wd_sem; 

extern int g_sched_state; 

/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/

int WDSchedRunRoutine(watch_dog_params_t *wd);

int WDInit(watch_dog_params_t *wd);

int RebootWDProcess(watch_dog_params_t *wd);

#endif /* __WATCHDOG_UTILS_H__ */
