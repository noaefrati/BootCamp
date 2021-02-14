/****************************************************************************** 
 * Description: Implement UID                                                 *
 * Author: Noa Efrati                                                         *
 * Reviewer: Inbal Shukrun                                                    *
 * Date: 6.12.20                                                              *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/

#include <pthread.h>   /*     pthread_mutex_t, pthread_mutex_lock/unlock      */
#include <unistd.h>    /*                     getpid()                        */
#include "uid.h"       /*                  uid functions                      */

/******************************************************************************/

pthread_mutex_t lock =  PTHREAD_MUTEX_INITIALIZER;
ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t new_uid = {0};
	static size_t count = 0;

	new_uid.timestamp = time(NULL);
	if (-1 == new_uid.timestamp)
	{
		return UIDGetBadUid();
	}
	
	pthread_mutex_lock(&lock);
	
	new_uid.pid = getpid();
	count += 1;
	new_uid.counter = count;
	
	pthread_mutex_unlock(&lock);
	
	return new_uid; 	
}

int UIDIsSame(ilrd_uid_t lhs, ilrd_uid_t rhs)
{

	return (lhs.timestamp == rhs.timestamp &&
	         lhs.pid == rhs.pid &&
	         lhs.counter == rhs.counter) ; 	 
}

ilrd_uid_t UIDGetBadUid(void)
{
	ilrd_uid_t bad_uid = {0};
	
	bad_uid.timestamp = (time_t)-1;
	bad_uid.pid = -1;
	bad_uid.counter = 0;
		
	return bad_uid;
}

