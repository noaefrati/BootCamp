/*----------------------------------------------------------------------------*/

#include <stdio.h>   /*           printf          */
#include <stdlib.h>  /*           rand            */
#include <unistd.h>  /*           sleep           */
#include <pthread.h> /* pthread_t, pthread_create */

/*----------------------------------------------------------------------------*/

#define THREAD_NUM 2
#define BUF_SIZE 10

/*----------------------------------------------------------------------------*/

static int signal_busy = 0;
static int counter = 0;
static int buffer[BUF_SIZE] = {0};

/*----------------------------------------------------------------------------*/

int MainProgram1(void);
void *ProducerRoutine(void *arg);
void *ConsumerRoutine(void *arg);
void Produce(void);
void Consume(void);

/*----------------------------------------------------------------------------*/

int main()
{
	return MainProgram1();
}

/*----------------------------------------------------------------------------*/
int MainProgram1(void)
{
	pthread_t threads[THREAD_NUM] = {0};

	size_t i = 0;
	
	for (; i < THREAD_NUM; ++i)
	{
		if (0 == i % 2)
		{
			if (0 != pthread_create(&threads[i], NULL, &ProducerRoutine, NULL))
			{
				printf("FAILED at CREATE producer thread ! \n");
				return 1;
			}
		}
		else
		{
			if (0 !=  pthread_create(&threads[i], NULL, &ConsumerRoutine, NULL))
			{
				printf("FAILED at CREATE consumer thread ! \n");
				return 1;
			}
		}
	}	
	
	for (i = 0; i < THREAD_NUM; ++i)
	{
		if (0 != pthread_join(threads[i], NULL))
		{
			printf("FAILED to JOIN thread ! \n");
			return 1;
		}
	}
	
		
	
	return (0);
}
void *ProducerRoutine(void *arg)
{
	while (1)
	{
		while (1 == signal_busy);
		
		sleep(1);
		signal_busy = 1;
		Produce();
		signal_busy = 0;
		if (counter == 2)
		{
			break;
		}
		
	}
	return arg;
}

void *ConsumerRoutine(void *arg)
{
	while (1)
	{
		while (1 == signal_busy);
		
		sleep(1);
		signal_busy = 1;
		Consume();
		signal_busy = 0;
		if (2 == counter)
		{
			break;
		}	
		
	}
	return arg;
}
void Produce(void)
{
	size_t i = 0;
	for (i = 0; i < BUF_SIZE; ++i)
	{
		int x = rand() % 100;
		buffer[i] = x;
	}
	++counter; 
}
void Consume(void)
{
	size_t index = 0;
	for (index = 0; index < BUF_SIZE; ++index)
	{
		int x = buffer[index];
		printf("index : %lu val : %d\n", index, x);
		buffer[index] = -1;
		
	}
}
