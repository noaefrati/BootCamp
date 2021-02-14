#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t pong_sem, ping_sem;

void *DoPing(void *arg)
{
	while(1)
	{
		sem_wait(&pong_sem);
		printf("ping\n");
		sem_post(&ping_sem);	
		
	}
	return NULL;
}
void *DoPong(void *arg)
{
	while (1)
	{
		sem_wait(&ping_sem);
		printf("pong\n");
		sem_post(&pong_sem);
	}
	return NULL;
}

int main()
{
	pthread_t t1 = {0};
	pthread_t t2 = {0};
	
	sem_init(&ping_sem, 0, 1);
	sem_init(&pong_sem, 0, 0);
	
	pthread_create(&t1, NULL, &DoPing, NULL);
	pthread_create(&t2, NULL, &DoPong, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	sem_destroy(&ping_sem);
	sem_destroy(&pong_sem);
	
	return 0;
}
