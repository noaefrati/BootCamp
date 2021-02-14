/************************************ Description ******************************
* Description: Implementation of character counting application for files.
* Authour: Carolina Kats
* Reviewer: Noa Efrati 
*******************************************************************************/

#include <stdlib.h>		/* malloc */
#include <assert.h>		/* assert */
#include <fcntl.h>		/* O_RDONLY */
#include <sys/mman.h>	/* mmap */
#include <stdio.h>		/* printf */
#include <unistd.h>		/* close */
#include <sys/stat.h>	/* fstat */	
#include <pthread.h>	/* Posix thread API */

#include "multithread_cnt.h"

/*********************************** Declarations *****************************/
typedef struct
{
	char *buffer;
	size_t length;
} input_params_t;

typedef struct
{
	char *input_buffer;
	size_t *result_buffer;
	size_t data_length;
} thread_params_t;

static const int NUM_ARGS = 2;
static const int NUM_THREADS = 2;
static const size_t ASCII_MAX = 255;

error_types_t PrintAppearances(char *file_name);
static error_types_t AllocateInputBuffer(char *file_name, 
										 input_params_t *input_params); 	
static void FreeInputBuffer(input_params_t *input_params);
static size_t **AllocateResultBuffer(size_t num_threads, size_t num_chars);
static void FreeResultBuffer(size_t **buffer, size_t allocated);
static void FreeResources(input_params_t *input_params, size_t **result_buffer, 
						  size_t num_threads);
static void InitThreadParams(size_t thread_num, size_t num_threads,
							 input_params_t *input, size_t **result_buffer,
							 thread_params_t *_thread_params);
static error_types_t PrepareResourcesForThreads(size_t num_threads, 
									   pthread_t **thread_ids,
									   thread_params_t **thread_params);
static void FreeResourcesForThreads(pthread_t *thread_ids, 
							   thread_params_t *thread_params);
static error_types_t RunCountingThreads(size_t num_threads, 
									    pthread_t *thread_ids,
									    thread_params_t *thread_params,
							 			input_params_t *input_params, 
							 			size_t **result_buffer);
static error_types_t CountAppearncesByChunk(size_t num_threads, 
											input_params_t *input,
											size_t **result_buffer);
static void *CalcAppearancesSingleChunk(void *args);
static void MergeCountingThreadsResults(size_t num_threads, 
										size_t **result_buffer);
static void DisplayCountingResult(size_t *result_buffer);

/************************************** Main **********************************/
int main(int argc, char **argv)
{
	if (NUM_ARGS != argc)
	{
		printf("Error. Received %d arguments instead of %d\n. Exiting\n",
			   argc, NUM_ARGS);
		return 1;
	}

	if (SUCCESS != PrintAppearances(argv[1]))
	{
		printf("Failed to print character appearances\n");
		return 1;
	}
	
	return 0;	
}

/******************************** API Functions *******************************/
error_types_t PrintAppearances(char *file_name)
{	
	size_t **result_buffer = NULL;
	input_params_t input_params = {0};
	error_types_t status = SUCCESS;
	
	assert(file_name);
	
	if (SUCCESS != (status = AllocateInputBuffer(file_name, &input_params)))
	{
		return status;
	}
	
	if (NULL == (result_buffer = AllocateResultBuffer(NUM_THREADS, ASCII_MAX)))
	{
		FreeInputBuffer(&input_params);
		return MEM_ALLOC_ERROR;
	}
	
	if (SUCCESS == (status = CountAppearncesByChunk(NUM_THREADS, &input_params,
										 		   result_buffer)))
	{
		MergeCountingThreadsResults(NUM_THREADS, result_buffer);
		DisplayCountingResult(result_buffer[0]);
	}					
	
	FreeResources(&input_params, result_buffer, NUM_THREADS);	

	return status;
}


/***************************** Static Functions *******************************/
static error_types_t CountAppearncesByChunk(size_t num_threads, 
											input_params_t *input,
											size_t **result_buffer)
{
	pthread_t *thread_ids = NULL;
	thread_params_t *thread_params = NULL;
	error_types_t status = SUCCESS;
		
	assert(input);
	assert(result_buffer);
	
	if (SUCCESS == (status = PrepareResourcesForThreads(num_threads, 		
							 							&thread_ids, 		
							 							&thread_params)))
	{
		status =  RunCountingThreads(num_threads, thread_ids, thread_params, 
									input, result_buffer);							
		FreeResourcesForThreads(thread_ids, thread_params);
	}
	
	return status;
}									

static error_types_t RunCountingThreads(size_t num_threads, 
									    pthread_t *thread_ids,
									    thread_params_t *thread_params,	
							 			input_params_t *input_params, 
							 			size_t **result_buffer)
{
	size_t i = 0, j = 0;
	error_types_t status = SUCCESS;
	
	assert(thread_ids);
	assert(thread_params);
	assert(input_params);
	assert(result_buffer);

	for (i = 0; i < num_threads; ++i)
	{
		InitThreadParams(i, num_threads, input_params, result_buffer, 	
				    	 &thread_params[i]);
		if (0 != pthread_create(&thread_ids[i], NULL, 
			&CalcAppearancesSingleChunk, &thread_params[i]))		    	 
		{
			fprintf(stderr, "failed creating thread %lu", i);
			status = THREAD_CREATE_ERROR;
			break;
		}	
	}
	
	for (j = 0; j < i; ++j)
	{
		if (0 != pthread_join(thread_ids[j], NULL))
		{
			fprintf(stderr, "failed joining thread %lu", i);
			status = THREAD_JOIN_ERROR;
		}
	}
	
	return status;
}										
										
static error_types_t PrepareResourcesForThreads(size_t num_threads, 
									   pthread_t **thread_ids,
									   thread_params_t **thread_params)
{
	assert(thread_ids);
	assert(thread_params);
	
	*thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * num_threads);
	if (NULL == *thread_ids)
	{
		return MEM_ALLOC_ERROR;
	}
	
	*thread_params = 
			(thread_params_t *)malloc(sizeof(thread_params_t) * num_threads);
	if (NULL == *thread_params)
	{
		free(*thread_ids); *thread_ids = NULL;
		return MEM_ALLOC_ERROR;
	}		
	
	return SUCCESS;
}									   
									   
static void FreeResourcesForThreads(pthread_t *thread_ids, 
							   thread_params_t *thread_params)

{
	free(thread_ids); thread_ids = NULL;
	free(thread_params); thread_params = NULL;
}

static void InitThreadParams(size_t thread_num, size_t num_threads,
							 input_params_t *input, size_t **result_buffer,
							 thread_params_t *_thread_params)
{
	assert(input);
	assert(result_buffer);
	assert(_thread_params);
	
	_thread_params->result_buffer = result_buffer[thread_num];
	_thread_params->data_length = input->length / num_threads;
	_thread_params->input_buffer = 
					input->buffer + _thread_params->data_length * thread_num;

	if (thread_num == num_threads - 1)
	{
		_thread_params->data_length += input->length % num_threads;
	}
}


static size_t **AllocateResultBuffer(size_t num_threads, size_t num_chars)
{
	size_t **buffer = NULL;
	size_t i = 0;
	
	buffer = (size_t **)malloc(num_threads * sizeof(* buffer));
	if (NULL == buffer)
	{
		return NULL;
	}
	
	for (i = 0; i < num_threads; ++i)
	{
		buffer[i] = (size_t *)calloc(sizeof(*buffer), num_chars);
		if (NULL == buffer[i])
		{
			FreeResultBuffer(buffer, i); buffer = NULL;
			break;
		}
	}
	
	return buffer;
}

static void FreeResultBuffer(size_t **buffer, size_t allocated)
{
	size_t i = 0;
	
	assert (buffer);
	
	for (i = 0; i < allocated; ++i)
	{
		free(buffer[i]); buffer[i] = NULL;
	}
	
	free(buffer); buffer = NULL;
}

static error_types_t AllocateInputBuffer(char *file_name, 
										 input_params_t *input_params) 	
{
	int fd = 0;
	void *mapped = NULL;
	struct stat file_stats;
	
	assert(file_name);
	assert(input_params);
	
	if (-1 == (fd = open(file_name, O_RDONLY)))	
	{
		perror("open");
		return OPEN_FILE_ERROR;
	}
	
	if (-1 == fstat(fd, &file_stats))
	{
		close(fd);
		perror("stat");
		return OPEN_FILE_ERROR;
	}
	
	mapped = mmap(NULL, file_stats.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == mapped)
	{
		close(fd);
		perror("mmap");
		return MEM_ALLOC_ERROR;
	}							
	
	close(fd);
	input_params->buffer = (char *)mapped;
	input_params->length = file_stats.st_size;
	printf("size : %lu\n", input_params->length);
	return SUCCESS;	  
} 

static void FreeInputBuffer(input_params_t *input_params)
{
	assert(input_params);
	
	munmap(input_params->buffer, input_params->length);
}

static void FreeResources(input_params_t *input_params, size_t **result_buffer, 
						  size_t num_threads)
{
	FreeInputBuffer(input_params);
	FreeResultBuffer(result_buffer, num_threads);
}						  

static void *CalcAppearancesSingleChunk(void *args)
{
	thread_params_t *params = (thread_params_t *)args;
	size_t i = 0;
	
	assert(args);
	assert(params->input_buffer);
	assert(params->result_buffer);
	
	for (i = 0; i < params->data_length; ++i)
	{
		unsigned char character = params->input_buffer[i];
		++(params->result_buffer[(int)character]);
	}
	
	return NULL;
}

static void MergeCountingThreadsResults(size_t num_threads, 
										size_t **result_buffer)
{
	size_t thread_index = 0, char_index = 0;
	
	assert(result_buffer);

	for (char_index = 0; ASCII_MAX > char_index; ++char_index)
	{
		for (thread_index = 1; thread_index < num_threads; ++thread_index)
		{
			result_buffer[0][char_index] += 
									result_buffer[thread_index][char_index];
		}
	}
}										

static void DisplayCountingResult(size_t *result_buffer)
{
	size_t i = 0;
	
	assert(result_buffer);
	
	for (i = 0; ASCII_MAX > i; ++i)
	{
		printf("%c: %lu\n", (char)i, result_buffer[i]);
	}
}







