/*----------------------------------------------------------------------------*/
/* Ex1: time /a.out -O3:                       time /a.out :                  */
/* Ex2:*/
/* Ex3: O3 : |real  0m11.346s |user  0m0.364s |sys  0m1.820s |                */
/* Ex5 : perf stat ./a.out : to see performance                               */
/*----------------------------------------------------------------------------*/
#include <time.h>       /*        time        */
#include <stdio.h>      /*       printf       */
#include <unistd.h>	    /*       sleep        */
#include <pthread.h>	/*   pthread_create   */


#define SIZE (100000)
#define SIZE_EX4 (4)
#define NUM 1000000000
#define JUMP  ((size_t)(NUM/SIZE_EX4) + 1)

size_t arg_global[SIZE] = {0};

static void *StartRoutine(void *arg);
static int Ex1(void);
static int Ex2(void);
static int Ex3(void);
static int Ex4(void);
static int Ex5(void);
static void *HandlerEx4(void *arg);
static int Ex5(void);
static size_t SumOfDivisorsImp(void);

int main()
{
	/*Ex4();*/
	Ex5();
	
	return 0;
}
size_t SumOfDivisorsImp(void)
{
	size_t sum_of_divisors = 0;
	size_t i = 0;
	
	for (i = 1; i < NUM; ++i)
	{
		if (0 == NUM % i)
		{
			sum_of_divisors += i;
		}
	}


	return sum_of_divisors;
}

int Ex5(void)
{
	time_t start, end;
	size_t ans = 0;
	
	time(&start);
	
	ans = SumOfDivisorsImp();	

	time(&end);
	
	printf("\nSUCCESS.\nTime elapsed from start: %f.\n", difftime(end, start));
	printf("Sum divisors   : %lu\n", ans);
	printf("Num of threads : 1\n");

	return 0;
}

/* 		num = 20, 4 threds for the job.
 	 ______________________________________ 
	  |_num_thread_|_from_index_|_to_index_|
	  |     1      |      1     |     6    |
	  |     2      |      6     |    11    |
	  |     3      |     11     |    16    |
	  |     4      |     16     |    20    |
	  |____________|____________|__________|
	   
*/

void *SumOfDivisitors(void *arg)
{
	size_t sum_of_divisors = 0;
	size_t i = 1 + ((size_t )arg *JUMP);
	size_t end_of_range = ((size_t)(arg) + 1) * JUMP ;

	for (; i <= end_of_range && i < NUM; ++i)
	{
		if (0 == NUM % i)
		{
			sum_of_divisors += i;
		}
	}
	
	return (void *)(sum_of_divisors);
}
int Ex4(void)
{
	void *sum = NULL;
	size_t sum_of_divisors = 0;
	time_t start , end;
	size_t i = 0;
	pthread_t threads[SIZE] = {0};
	
	time(&start);
	
	for (i = 0; SIZE_EX4 > i; ++i)
	{
		pthread_create(&(threads[i]), NULL, SumOfDivisitors, (void *)i);
	}
	
	time(&end);
	sleep(10);
	
	for (i = 0; SIZE_EX4 > i; ++i)
	{
		pthread_join(threads[i], &sum);
		sum_of_divisors += (size_t)sum;
	}
	
	
	printf("\nSUCCESS\nTime from start : %f",difftime(end, start));
	printf("\nSum divisors   : %ld\n", sum_of_divisors);
	printf("Num of threads : %d\n", SIZE_EX4);
	
	return 0;
}
int Ex3(void)
{
	int status = 0;
	time_t start = {0}, end = {0};
	size_t i = 0;
	double diff = 0;
	pthread_t threads[SIZE];
	
	time(&start);
	
	for (i = 0; SIZE > i; ++i)
	{
		 /* the second argument is pthread_attr_t *, 
		  if it is null meaning the thread create with default attributes*/
		do
		{
			status = pthread_create(&(threads[i]), 
			                          NULL, 
			                          StartRoutine, 
			                          (void *)i);
			
			status += pthread_detach(threads[i]);                         
		} while (0 != status);
	}
	
	time(&end);
	sleep(10);
	
	for (i = 0; SIZE > i; ++i)
	{
		if (i != arg_global[i])
		{
			printf("\nThe value (%lu) not equal to its index (%lu)",
			                                                  arg_global[i], i);
			return 1;                                                  
		}
	}
	
	
	diff = difftime(end, start);
	
	printf("\nSUCCESS\n Time from start : %f",diff);
	return 0;
}
int Ex2(void)
{
	time_t start, end;
	size_t i = 0;
	pthread_t threads[SIZE];
	
	time(&start);
	
	for (i = 0; SIZE > i; ++i)
	{
		 /* the second argument is pthread_attr_t *, 
		  if it is null meaning the thread create with default attributes*/
		while (pthread_create(&(threads[i]), NULL, StartRoutine, (void *)i));
		
	}
	
	time(&end);
	sleep(10);
	
	for (i = 0; SIZE > i; ++i)
	{
		if (i != arg_global[i])
		{
			printf("\nThe value (%lu) not equal to its index (%lu)",
			                                                  arg_global[i], i);
			return 1;                                                  
		}
	}
	
	printf("\nSUCCESS\n Time from start : %f", difftime(end, start));

	return 0;
}
int Ex1(void)
{
	time_t start, end;
	size_t i = 0;
	double diff = 0;
	pthread_t threads[SIZE];
	
	time(&start);
	
	for (i = 0; SIZE > i; ++i)
	{
		 /* the second argument is pthread_attr_t *, 
		  if it is null meaning the thread create with default attributes*/
		
		pthread_create(&(threads[i]), NULL, StartRoutine, (void *)i);
		
	}
	
	time(&end);
	sleep(10);
	
	for (i = 0; SIZE > i; ++i)
	{
		if (i != arg_global[i])
		{
			printf("\nThe value (%lu) not equal to its index (%lu)",
			                                                  arg_global[i], i);
			return 1;                                                  
		}
	}
	
	
	diff = difftime(end, start);
	
	printf("\nSUCCESS\n Time from start : %f", diff);
	return 0;
}
static void *StartRoutine(void *arg)
{
	arg_global[(size_t)arg] = (size_t)arg;
	return arg;
}
