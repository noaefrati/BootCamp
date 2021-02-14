#ifndef __WATCHDOG_H_OL97_ILRD__
#define __WATCHDOG_H_OL97_ILRD__

/******************************************************************************
 * Header file Containing API Definitions for Watchdog.                       *
 *                                                                            *
 * Infinity Labs - OL97                                                       *
 ******************************************************************************/

/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h>     /* size_t */

/******************************************************************************/
/***                               Typedfs                                  ***/
/******************************************************************************/

typedef struct watchdog_utils watchdog_utils_t;

typedef struct 
{
	/* Full path to user program executable. */
    char *user_program_full_name;           
    
    /* Full path to wd program executable. */
    char *wd_program_full_name;             
    
    /* Arguments to user program. */
    char **args;
    
    /* 
     * Time watchdog / program waits for other side to init, 
     * before it revives it again.
     */ 
    size_t init_wait_time;
    
    /* Time that wd waits for user program to signal */
    size_t user_signal_wait_time;           
    
    /* Time that user program waits for wd to signal */
    size_t wd_signal_wait_time;             
    
    /* Missed signals limit, after witch the wd / program revives other side */
    size_t signal_missed_amt;
 
    /* outparam that the function start sets, not to be touched by user*/   

    watchdog_utils_t *_internal_params;
                
} watch_dog_params_t;

/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/

/*
 * On success: returns  0, otherwise returns 1.
 */
int WatchDogStart(watch_dog_params_t *params);

/*
 * Return value: None.
 */
void WatchDogStop(watch_dog_params_t *params);

#endif /* __WATCHDOG_H_OL97_ILRD__ */
