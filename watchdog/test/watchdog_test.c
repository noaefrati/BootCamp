/******************************************************************************
Description: Watchdog functions test
Author: Roi Peretz
Reviewer: 

Infinity Labs OL97
*******************************************************************************/

/******************************************************************************/
/***                      Includes and Defines                              ***/
/******************************************************************************/

#include <assert.h>	   /* assert */
#include <unistd.h>    /* sleep */
#include <stdio.h>	   /* printf */
#include <stdlib.h>    /* malloc, free */

#include "watchdog.h"	   /* Watchdog API */

/******************************************************************************/
/***                   static functions declaration                         ***/
/******************************************************************************/
static void InitParams(watch_dog_params_t *params, char **argv);

/******************************************************************************/
/***                         API functions                                  ***/
/******************************************************************************/
int main(int argc, char **argv, char *envp[])
{	
	size_t i = 0;
	
	watch_dog_params_t *params = (watch_dog_params_t *)
								 malloc (sizeof(watch_dog_params_t));
	(void)argc;
	(void)envp;
									 
	InitParams(params, argv);
	
	WatchDogStart(params);
	
	for (i = 0; i < 50; ++i)
	{
		printf("UP: I am alaive! %lu\n", i);
		sleep(1);
	}
	
	printf("UP: DONE\n");
	WatchDogStop(params);
	printf("UP: Exiting\n");
	free(params);
	return 0;
}
/******************************************************************************/
/***                         static functions                               ***/
/******************************************************************************/

static void InitParams(watch_dog_params_t *params, char **argv)
{
	assert(params);

	/* Full path to user program executable. */
    params->user_program_full_name = "/home/roi/git/projects/watchdog/bin/release/wd_user.out";         
    
    /* Full path to wd program executable. */
    params->wd_program_full_name = "/home/roi/git/projects/watchdog/bin/release/wd.out";  
    	
	#ifndef NDEBUG
	/* Full path to user program executable. */
    params->user_program_full_name = "/home/roi/git/projects/watchdog/bin/debug/wd_user.out";         
    
    /* Full path to wd program executable. */
    params->wd_program_full_name = "/home/roi/git/projects/watchdog/bin/debug/wd.out";            
	#endif 
	
    /* Arguments to user program. */
    params->args = argv;
    
    /* 
     * Time watchdog / program waits for other side to init, 
     * before it revives it again.
     */ 
    params->init_wait_time = 6;
    
    /* Time that wd waits for user program to signal */
    params->user_signal_wait_time = 5;          
    
    /* Time that user program waits for wd to signal */
    params->wd_signal_wait_time = 5;           
    
    /* Missed signals limit, after witch the wd / program revives other side */
    params->signal_missed_amt = 3;
 
}

