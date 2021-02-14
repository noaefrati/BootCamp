#ifndef __UID_H_OL97_ILRD__
#define __UID_H_OL97_ILRD__

/*******************************************************************************
 *
 * Header file Containing API Definition for UID interface operations and 
 * declarations.
 *
 * Infinity Labs - OL97                                                      
 ******************************************************************************/
 
/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h>     /* size_t */
#include <time.h>       /* time_t */
#include <sys/types.h>  /* pid_t */

/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/
typedef struct uid 
{
	time_t timestamp;
    pid_t pid;
    size_t counter;
}ilrd_uid_t;
    
/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/

/*
 * Description: This function is used for creating new UID struct.
 * Return value: UID struct with initialized values.
 * Time complexity: O(1).
 */
ilrd_uid_t UIDCreate(void);

/*
 * Description: This function is used for comparing two UID structs (field by
 * field).
 * Return value: Returns true(1) if the structs are the same, false(0) 
 * otherwise.
 * Time complexity: O(1).
 */
int UIDIsSame(ilrd_uid_t lhs, ilrd_uid_t rhs);

/*
 * Description: This function is used for getting "dummy" UID of the system.
 * Return value: UID struct with dummy values.
 * Time complexity: O(1).
 */
ilrd_uid_t UIDGetBadUid(void);

#endif /* __UID_H_OL97_ILRD__ */
