/*----------------------------------------------------------------------------*/

#include <stdio.h>   /*           printf          */
#include <stdlib.h>  /*           rand            */
#include <unistd.h>  /*           sleep           */
#include <pthread.h> /* pthread_t, pthread_create */
#include "slist.h"

/*----------------------------------------------------------------------------*/

#define THREAD_NUM 2
#define BUF_SIZE 10

/*----------------------------------------------------------------------------*/
static int buff[BUF_SIZE] = {0};
static sllist_t *list = NULL;
static pthread_mutex_t mutex_buffer =  PTHREAD_MUTEX_INITIALIZER ;

/*----------------------------------------------------------------------------*/

int MainProgram1(void);
void *ProducerRoutine(void *arg);
void *ConsumerRoutine(void *arg);


/*----------------------------------------------------------------------------*/

int main()
{
	return MainProgram1();
}

/*----------------------------------------------------------------------------*/
int MainProgram1(void)
{
	size_t i = 0;
	int exit_sign = -1;
	pthread_t producers[THREAD_NUM] = {0};
	pthread_t consumers[THREAD_NUM] = {0};
	
	list = SLLCreate();
	
	if (NULL == list)
	{
		return 1;
	}
	
	for (i = 0; BUF_SIZE > i; ++i)
	{
		buff[i] = i + 1 ;
	}
	
	
	for (i = 0; i < THREAD_NUM; ++i)
	{
		if (0 != pthread_create(&producers[i], NULL, &ProducerRoutine, NULL))
		{
			printf("FAILED at CREATE producer thread ! \n");
			return 1;
		}

		if (0 !=  pthread_create(&consumers[i], NULL, &ConsumerRoutine, NULL))
		{
			printf("FAILED at CREATE consumer thread ! \n");
			return 1;
		}
	
	}	
	
	for (i = 0; i < THREAD_NUM; ++i)
	{
		pthread_join(producers[i], NULL);
	}
	
	pthread_mutex_lock(&mutex_buffer);
	
	SLLPushBack(list, &exit_sign);
	
	pthread_mutex_unlock(&mutex_buffer);
	
	for (i = 0; i < THREAD_NUM; ++i)
	{
		pthread_join(consumers[i], NULL);

	}
	
	pthread_mutex_destroy(&mutex_buffer);	
	SLLDestroy(list);
	
	return (0);
}
void *ProducerRoutine(void *arg)
{
	size_t i = 0;
	int insert = 0;
		
	for (i = 0; i < BUF_SIZE ; ++i)
	{
		pthread_mutex_lock(&mutex_buffer);
		
		insert = *(int *)SLLGetData(SLLPushBack(list,(void *) &buff[i]));
		printf("insert: %d\n", insert);
		
		pthread_mutex_unlock(&mutex_buffer);
			
		sleep(1);
		
	}

	puts("produced");
	
	return arg;
}

void *ConsumerRoutine(void *arg)
{
	int to_read = 0;
	

	sleep(1);
	
	/* -1 = exit sign, when push from the main -1 into the buffer */
	/* -1 = exit sign, when push from the main -1 into the buffer */
	while (buff[0] != -1)
	{
		pthread_mutex_lock(&mutex_buffer);
		
		if (SLLIsEmpty(list))
		{
			pthread_mutex_unlock(&mutex_buffer);
			continue;
		}
		
		to_read = *(int *)SLLGetData(SLLBegin(list));
		printf("read : %d\n", to_read);
		SLLRemove(list, SLLBegin(list));
			
		if (-1 == to_read) /* read the fist element */
		{
			buff[0] = -1;
		}
		
		pthread_mutex_unlock(&mutex_buffer);
		
		sleep(1);
	}	
	puts("consumed");
	return arg;
}

