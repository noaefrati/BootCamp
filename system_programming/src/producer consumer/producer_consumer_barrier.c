/*----------------------------------------------------------------------------*/
/* Barrier - single producer, multiple consumers,                             */
/*	producer waits until all consumers read 1 time exactly                    */
/*	1 coditional variable, 1 mutex, 1 semaphore                               */
/*----------------------------------------------------------------------------*/

#include <stdio.h>       /*           printf          */
#include <stdlib.h>      /*           rand            */
#include <unistd.h>      /*           sleep           */
#include <pthread.h>     /* pthread_t, pthread_create */
#include <semaphore.h>   /*         semaphore         */


/*----------------------------------------------------------------------------*/

#define NUM_OF_CONSUMERS 2

/*----------------------------------------------------------------------------*/

int MainProgram(void);
void *ProducerRoutine(void *arg);
void *ConsumerRoutine(void *arg);

/*----------------------------------------------------------------------------*/

int waiting_threads = 0;
int producer_done = 1;
int global = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
sem_t sem = {0};

/*----------------------------------------------------------------------------*/

int main()
{
	return MainProgram();
}

/*----------------------------------------------------------------------------*/
int MainProgram(void)
{
	size_t i = 0;
	pthread_t producer = {0};
	pthread_t consumers[NUM_OF_CONSUMERS] = {0};
	
	
	sem_init(&sem, 0, 1);
	
	if (0 != pthread_create(&producer, NULL, &ProducerRoutine, NULL))
	{
		printf("FAILED at CREATE producer thread ! \n");
		return 1;
	}	
	
	
	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		if (0 !=  pthread_create(&consumers[i], NULL, &ConsumerRoutine, NULL))
		{
			printf("FAILED at CREATE consumer thread ! \n");
			return 1;
		}
	
	}	
	
	if (0 != pthread_join(producer, NULL))
	{
		printf("FAILED at JOIN producer thread ! \n");
		return 1;
	}
	
	pthread_mutex_lock(&lock);
	global = -1;
	pthread_mutex_unlock(&lock);
	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		if (0 != pthread_join(consumers[i], NULL))
		{
			printf("FAILED at JOIN consumer[%lu] thread ! \n", i);
			return 1;
		}
	}
	
	
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&condition);
	sem_close(&sem);
	
	sem_destroy(&sem);
	
	return (0);
}
void *ProducerRoutine(void *arg)
{
	size_t i = 0;

	while (1)
	{
		
		
		for (i = 0; i < NUM_OF_CONSUMERS; ++i)
		{
			sem_wait(&sem); /* wait untill al the consumers done consuming */
		}
		
		
		pthread_mutex_lock(&lock);
		
		++global;
		
		printf("Producer: %d\n", global);
		pthread_cond_broadcast(&condition);
		
		pthread_mutex_unlock(&lock);
	}
	
	puts("Produced");
	
	return arg;
}

void *ConsumerRoutine(void *arg)
{
	while (1)
	{
		int local = global;
		
		pthread_mutex_lock(&lock);
		sem_post(&sem);
		if (-1 == global)
		{
			pthread_mutex_unlock(&lock);
			break;
		}
		while (global == local)
		{
			pthread_cond_wait(&condition, &lock);
		}
		
		printf("\t\t\t\tConsumer : %d\n", local);
		
		pthread_mutex_unlock(&lock);
		
	}	
	
	puts("\t\t\tConsumed");
	
	return arg;
}

