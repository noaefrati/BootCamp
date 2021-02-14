/******************************************************************************
Description: Thread Safe Uid list functions
Author: Roi Peretz
Reviewer: 

Infinity Labs OL97
*******************************************************************************/
#include <assert.h>    /* assert */
#include <stdlib.h>    /* malloc, realloc, free */
#include <unistd.h>    /* getptid */ 

#include "thread_safe_uid.h"       /* Uid API */

/*
 * Description: This function is used for creating new UID struct.
 * Return value: UID struct with initialized values.
 * Time complexity: O(1).
 */
ilrd_uid_t UIDCreate(void)
{
	static size_t count = 0;
	ilrd_uid_t uid = {0};
	
	uid.timestamp = time(NULL);
	if ((time_t)-1 == uid.timestamp)
	{
		return UIDGetBadUid();
	}
	
    uid.pid = getpid();
    
  	uid.counter = __sync_fetch_and_add(&count, 1);
  	
  	return (uid);
}

/*
 * Description: This function is used for comparing two UID structs (field by
 * field).
 * Return value: Returns true(1) if the structs are the same, false(0) 
 * otherwise.
 * Time complexity: O(1).
 */
int UIDIsSame(ilrd_uid_t lhs, ilrd_uid_t rhs)
{
	return ((lhs.counter == rhs.counter) && 
			(0 == difftime(lhs.timestamp,rhs.timestamp)) 
									&& (lhs.pid == rhs.pid));
												
}

/*
 * Description: This function is used for getting "dummy" UID of the system.
 * Return value: UID struct with dummy values.
 * Time complexity: O(1).
 */
ilrd_uid_t UIDGetBadUid(void)
{
	ilrd_uid_t bad_uid = {0};
	
	bad_uid.timestamp = (time_t)-1;
    bad_uid.pid = 0;
   	bad_uid.counter = 0;
  	
  	return (bad_uid);	
}







