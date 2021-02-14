/*----------------------------------------------------------------------------*/
/*                           Producer Consumer                                */
/*----------------------------------------------------------------------------*/

#include <stdio.h>               /*           printf          */
#include <stdlib.h>              /*           rand            */
#include <unistd.h>              /*           sleep           */
#include <pthread.h>             /* pthread_t, pthread_create */
#include <semaphore.h>           /*         semaphore         */

#define THREAD_NUM 10
#define BUF_SIZE 10

/*----------------------------------------------------------------------------*/
/*                       Global & Static Variables                            */
/*----------------------------------------------------------------------------*/

static int buff[BUF_SIZE] = {0};
static sem_t full , empty;
int read_index = 0, write_index = 0;
static pthread_mutex_t mutex_buffer =  PTHREAD_MUTEX_INITIALIZER ;

/*----------------------------------------------------------------------------*/
/*                        Main Functions Decleration                          */
/*----------------------------------------------------------------------------*/

int MainProgram(void);
void *ProducerRoutine(void *arg);
void *ConsumerRoutine(void *arg);

/*----------------------------------------------------------------------------*/
/***                               Main                                     ***/
/*----------------------------------------------------------------------------*/

int main()
{
	return MainProgram();
}

/*----------------------------------------------------------------------------*/
/***                       Main Functions Defenition                        ***/
/*----------------------------------------------------------------------------*/

int MainProgram(void)
{
	size_t i = 0;
	pthread_t producers[THREAD_NUM] = {0};
	pthread_t consumers[THREAD_NUM] = {0};
	
	sem_init(&full, 0, BUF_SIZE);
	sem_init(&empty, 0, 0);
	
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
	
	read_index = BUF_SIZE + 1;             /* ending the consumer activity */
	
	pthread_mutex_unlock(&mutex_buffer);
	
	for (i = 0; i < THREAD_NUM; ++i)
	{
		sem_post(&empty);
	}
	
	for (i = 0; i < THREAD_NUM; ++i)
	{
		pthread_join(consumers[i], NULL);
	}
	
	pthread_mutex_destroy(&mutex_buffer);	

	
	return (0);
}
/*----------------------------------------------------------------------------*/

void *ProducerRoutine(void *arg)
{
	size_t i = 0;

	for (i = 0; i < BUF_SIZE ; ++i)
	{
		sem_wait(&full); /* the call block until full is greater than 0*/
		
		pthread_mutex_lock(&mutex_buffer);
		
		buff[write_index] = i + 1;
		printf("Write: %d\n", buff[write_index]);
		++write_index;
		
		if (write_index == BUF_SIZE)
		{
			write_index = 0;
		}
		
		pthread_mutex_unlock(&mutex_buffer);
		
		sleep(1);
		
		sem_post(&empty); /* increament empty by  1 */
	}

	puts("Produced");
	
	return arg;
}
/*----------------------------------------------------------------------------*/

void *ConsumerRoutine(void *arg)
{
	while (1)
	{
		sem_wait(&empty); /* the call block until empty is greater than 0*/
		
		if (BUF_SIZE < read_index)
		{
			break;
		}
		
		pthread_mutex_lock(&mutex_buffer);
				printf("\t\t\t\tRead : %d\n", buff[read_index]);
		++read_index;
		
		if (read_index == BUF_SIZE)
		{
			read_index = 0;
		}
		
		pthread_mutex_unlock(&mutex_buffer);
		
		sleep(1);
		
		sem_post(&full);
	}	
	
	puts("\t\t\tConsumed");
	
	return arg;
}
/*----------------------------------------------------------------------------*/
