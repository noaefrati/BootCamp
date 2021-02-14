/*************************************************************************** 
 * Description: Testing for Thread-Safe UID functions
 * Author: Oriel Nofekh
 * Reviewer: 
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>               /* printf */
#include <unistd.h>              /* getpid */
#include <assert.h>              /* assert */
#include <pthread.h>             /* pthread functions and typedefs */
#include "uid.h"





/******************************************************************************/
/***                        Color Defines   		                        ***/
/******************************************************************************/
#define DEF     "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

static int test_counter_g = 0;
static int success_counter_g = 0;

#define TEST(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEF, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)

#define TESTC(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %c, Expected: %c\n" DEF, name, __LINE__, (char) (real), (char) (expected)); \
    } while (0)

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)





static void TestSingleThread(void)
{
	ilrd_uid_t uids[6];
	size_t uids_len = sizeof(uids) / sizeof(uids[0]);
	size_t i = 0, j = 0;
	
	/* initialize array */
	for (i = 0; i < uids_len; ++i)
	{
		uids[i] = UIDCreate();
	}
	
	/* check array */
	for (i = 0; i < uids_len; ++i)
	{
		for (j = 0; j < uids_len; ++j)
		{
			if (i == j)
			{
				TEST("Same UID", UIDIsSame(uids[i], uids[j]), 1);
				TEST("Same UID", UIDIsSame(uids[j], uids[i]), 1);
			}
			else
			{
				TEST("Not Same UID", UIDIsSame(uids[i], uids[j]), 0);
				TEST("Not Same UID", UIDIsSame(uids[j], uids[i]), 0);
			}
		}
	}
	
	uids[0] = UIDGetBadUid();
	uids[1] = UIDGetBadUid();
	uids[2] = UIDGetBadUid();
	
	/* check array */
	for (i = 0; i < uids_len; ++i)
	{
		for (j = 0; j < uids_len; ++j)
		{
			if ((i == j) || (i <= 2 && j <= 2))
			{
				TEST("Same UID", UIDIsSame(uids[i], uids[j]), 1);
				TEST("Same UID", UIDIsSame(uids[j], uids[i]), 1);
			}
			else
			{
				TEST("Not Same UID", UIDIsSame(uids[i], uids[j]), 0);
				TEST("Not Same UID", UIDIsSame(uids[j], uids[i]), 0);
			}
		}
	}
	
	uids[0] = uids[5];
	uids[1] = uids[4];
	uids[2] = uids[3];
	
	/* check array */
	for (i = 0; i < uids_len; ++i)
	{
		for (j = 0; j < uids_len; ++j)
		{
			if ((i == j) || (i == uids_len - 1 - j))
			{
				TEST("Same UID", UIDIsSame(uids[i], uids[j]), 1);
				TEST("Same UID", UIDIsSame(uids[j], uids[i]), 1);
			}
			else
			{
				TEST("Not Same UID", UIDIsSame(uids[i], uids[j]), 0);
				TEST("Not Same UID", UIDIsSame(uids[j], uids[i]), 0);
			}
		}
	}
	
	printf(BOLDBLUE "TestSingleThread\n" DEF);
}



static const int with_mutex_flag = 0; 
static pthread_mutex_t mutex;
#define UIDS_PER_THREAD 50
#define NUM_THREADS 50
#define NUM_UIDS ((UIDS_PER_THREAD)*(NUM_THREADS))

static ilrd_uid_t uids[NUM_UIDS];
static pthread_t threads_buffer[NUM_THREADS];

static void *CreateUIDs(void *index_as_ptr)
{
	size_t thread_index = (size_t) index_as_ptr;
	size_t i = 0;
	for (i = thread_index*UIDS_PER_THREAD; 
	     i < (thread_index+1)*UIDS_PER_THREAD; 
	     ++i)
	{
		if (with_mutex_flag)
		{
			pthread_mutex_lock(&mutex);
			uids[i] = UIDCreate();
			pthread_mutex_unlock(&mutex);
		}
		else
		{
			uids[i] = UIDCreate();
		}
	}
	
	return NULL;
}

static void TestMultiThread(void)
{
	int status = 0;
	size_t i = 0, j = 0;
	
	pthread_mutex_init(&mutex, NULL);
	
	for (i = 0; i < NUM_THREADS; ++i)
	{
		status = pthread_create(threads_buffer + i, NULL, 
		                        &CreateUIDs, (void *) i);
		assert(0 == status);
	}
	
	for (i = 0; i < NUM_THREADS; ++i)
	{
		status = pthread_join(threads_buffer[i], NULL);
		assert(0 == status);
	}
	
	/* check array */
	for (i = 0; i < NUM_UIDS; ++i)
	{
		for (j = 0; j < NUM_UIDS; ++j)
		{
			if (i == j)
			{
				TEST("Same UID", UIDIsSame(uids[i], uids[j]), 1);
				TEST("Same UID", UIDIsSame(uids[j], uids[i]), 1);
			}
			else
			{
			
				TEST("Not Same UID", UIDIsSame(uids[i], uids[j]), 0);
				TEST("Not Same UID", UIDIsSame(uids[j], uids[i]), 0);
			}
		}
	}
	
	pthread_mutex_destroy(&mutex);
	
	printf(BOLDBLUE "TestMultiThread\n" DEF);
}



static void TestMain(void)
{
	TestSingleThread();
		
	TestMultiThread();	
	
	PASS;
}



int main(void)
{
	TestMain();
	
	return 0;
}



