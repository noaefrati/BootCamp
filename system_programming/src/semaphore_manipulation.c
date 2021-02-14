#include <sys/stat.h>   /* for semaphore mode constants */
#include <fcntl.h>      /*           O_CREAT            */
#include <semaphore.h>	/*            sem_ops           */
#include <string.h> 	/*         strtok, strcmp       */
#include <stdio.h> 		/*             printf           */
#include <assert.h>		/*             assert           */
#include <stdlib.h>     /*              atoi            */


#define INPUT_LEN (256)
#define BUFFER_SIZE (20)

typedef void *(*sem_action)(void *);

static int undo_inc = 0; 
static int undo_dec = 0;
static int is_cleanup_time = 0;

static void CleanUp(sem_t *sem);
static void ViewCurrVal(sem_t *sem);
static void *Decrement(void *sem);
static void *Increment(void *sem);

int main(int argc, char *argv[])
{
	char *sem_name = NULL;
	int sem_init_val = 0;
	char input_buffer[BUFFER_SIZE] = {0};
	sem_t *sem = NULL;




	
	/*if user presented own name*/
	if(argc > 1)
	{
		sem_name = argv[1];
	
		/*create semaphore with user ang groups read write perms*/
		sem = sem_open(sem_name, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,
																 sem_init_val);
		if (SEM_FAILED == sem)
		{
			return -1;
		}														 
	}
	else
	{
		return -1;
	} 


	/* main loop */
	while (0 == is_cleanup_time)
	{
		char operation = 0;
		int num_of_operation = 0;
		int is_undo = 0;
		char *input = NULL;
		
		printf("D <number> [undo] (for decrement),I <number> [undo] (increment), V (view), X (exit)\n");
		fgets(input_buffer, INPUT_LEN, stdin);
		
		operation = *(char *)strtok(input_buffer, " ");
		input = strtok(NULL, " ");
		
		if (NULL != input)
		{
			num_of_operation = atoi(input);
		}
		
		input = strtok(NULL, "\n");
		if (NULL != input)
		{
			is_undo = !(strcmp(input, "undo"));
		}
		
		switch(operation)
		{
			case 'D':
				
				while (0 < num_of_operation)
				{
					Decrement(sem);
					--num_of_operation;
					undo_dec += is_undo;
				}
				break;
			
			case 'I':
				
				while (0 < num_of_operation)
				{
					Increment(sem);
					--num_of_operation;
					undo_inc += is_undo;
				}
				break;
			
			case 'V':
				
				ViewCurrVal(sem);
				break;
			
			case 'X':
				
				CleanUp(sem);
				break;
			
			default:
				break;
		}
		
	}

	ViewCurrVal(sem);

	sem_close(sem);

	return 0;
}


/*increment semaphore*/
static void *Increment(void *sem)
{
	assert(sem);
	
	if (sem_post((sem_t *)sem))
	{
		printf("Operation failed\n");
		return (void *) -1;
	}

	return (void *)0;
}

/*decrement semaphore*/
static void *Decrement(void *sem)
{
	assert(sem);
	
	if (sem_wait((sem_t *)sem))
	{
		printf("Operation failed\n");
		return (void *)-1;
	}

	return (void *)0;
}

/*prints semaphore current value*/
static void ViewCurrVal(sem_t *sem)
{
	int val = 0;

	assert(sem);

	sem_getvalue(sem, &val);

	printf("Semaphore current value: %d \n", val);
}

/*on exit calculate and peform 'undos'*/
static void CleanUp(sem_t *sem)
{
	is_cleanup_time = 1;
	
	assert(sem);
	
	while (undo_inc != undo_dec && 0 != undo_inc)
	{	
		if(undo_inc > undo_dec)
		{
			Decrement(sem);
			--undo_inc;
		}
		
		if(undo_dec > undo_inc)
		{
			Increment(sem);
			--undo_dec;
		}
	}
}


