/****************************************************************************** 
 * Description: Implementation of character counting application for files.   *
 * Author: Noa Efrati                                                         *
 * Reviewer: Yuval Krytzer                                                    *
 * Date: 02.02.2021                                                           *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/
/******************************************************************************/
/***                              Includes                                  ***/
/******************************************************************************/

#include <pthread.h>             /* pthread_create                            */
#include <stdio.h>               /* printf, getc,fopen, fseek                 */
#include <stdlib.h>              /* malloc, free                              */
#include <ctype.h>               /* tolower, isalpha                          */
#include <assert.h>              /* assert                                    */
#include <unistd.h>		         /* close                                     */
#include <sys/mman.h>            /* mmap                                      */
#include <sys/stat.h>            /* fstat                                     */	
#include <fcntl.h>               /* O_RDONLY                                  */

#include "multithread_cnt.h"     /* multi_threaded_cnt API                    */

/******************************************************************************/
/***                               Defines                                  ***/
/******************************************************************************/

#define NUM_ARGS 2
#define NUM_OF_THREADS 4
#define NUM_OF_LETTERS 26
/* #define DICT_PATH ("/usr/share/dict/american-english") */

/******************************************************************************/
/***                                Struct                                  ***/
/******************************************************************************/

typedef struct file_params
{
	size_t *histogram;
	char *input_buffer;
	size_t start_index;
	size_t end_index;
}file_params_t;

typedef struct
{
	char *buffer;
	size_t length;
} input_params_t;

/******************************************************************************/
/***                      Private Functions Declarations                    ***/
/******************************************************************************/

static void *ThreadWork(void *args);

static void PrintResult(size_t size);

static void FreeResultBuffer(size_t to);
static void FreeInputBuffer(input_params_t *buffer);

static error_types_t JoinThreadsAndDisplayResult(void);
static error_types_t CreateThreads(file_params_t *params);

static error_types_t AllocateResultBuffer(size_t num_threads,
                                          size_t num_letters);

static file_params_t *InitFileParams(char *input_buffer,
                                     size_t num_bytes_in_file);

static error_types_t AllocateInputBuffer(char *file_name, 
										 input_params_t *input_params);	

static error_types_t CountTotalBytesInFile(char *file_name, int *_count);

/******************************************************************************/
/***                       Static & Global Variables                        ***/
/******************************************************************************/

static pthread_t threads[NUM_OF_THREADS] = {0};
size_t **result_buffer = NULL;

/******************************************************************************/
/***                                  App                                   ***/
/******************************************************************************/

int main(int argc, char **argv)
{
	if (NUM_ARGS > argc)
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
/******************************************************************************/
/***                        API Function Definitions                        ***/
/******************************************************************************/

error_types_t PrintAppearances(char *file_name)
{
	input_params_t input_params = {0};
	int count = 0;
	error_types_t status = SUCCESS;
	file_params_t *params = NULL;
	
	assert(file_name);
	
	if (SUCCESS != (status = AllocateInputBuffer(file_name, &input_params)))
	{
		return status;
	}
	
	status = AllocateResultBuffer(NUM_OF_THREADS, 
	                              NUM_OF_LETTERS);
	if (SUCCESS != status)
	{
		FreeInputBuffer(&input_params);
		
		return status;
	}
		
	if (SUCCESS != (status = CountTotalBytesInFile(file_name, &count)))
	{
		FreeInputBuffer(&input_params);
		FreeResultBuffer(NUM_OF_THREADS);
		
		return status;
	}

	if (NULL == (params = InitFileParams(input_params.buffer, count)))
	{
		FreeInputBuffer(&input_params);
		FreeResultBuffer(NUM_OF_THREADS);
		
		return MEM_ALLOC_ERROR;
	}
	
	if (SUCCESS != (status = CreateThreads(params)))
	{
		free(params); params = NULL;
		FreeInputBuffer(&input_params);
		FreeResultBuffer(NUM_OF_THREADS);
		
		return status;
	}
	
	if (SUCCESS != (status = JoinThreadsAndDisplayResult()))
	{
		free(params); params = NULL;
		FreeInputBuffer(&input_params);
		FreeResultBuffer(NUM_OF_THREADS);
		
		return status;
	}
	
	free(params); params = NULL;
	FreeResultBuffer(NUM_OF_THREADS);
	FreeInputBuffer(&input_params);
	
	return status;
}
/******************************************************************************/
/***                     Private Functions Definitions                      ***/
/******************************************************************************/

static error_types_t AllocateResultBuffer(size_t num_threads,
                                          size_t num_letters)
{
	size_t i = 0;
	
	result_buffer = (size_t **)malloc(num_threads * sizeof(size_t *));
	
	if (NULL == result_buffer)
	{
		return MEM_ALLOC_ERROR;
	}
	
	for (i = 0; i < num_threads; ++i)
	{
		result_buffer[i] = (size_t *) calloc(num_letters, sizeof(size_t));
		
		if (NULL == result_buffer[i])
		{
			FreeResultBuffer(i); result_buffer = NULL;
			
			return MEM_ALLOC_ERROR;
		}
	}
	
	return SUCCESS;
}
/******************************************************************************/
static void FreeResultBuffer(size_t to)
{
	size_t i = 0;
	
	assert(result_buffer);
	
	for (i = 0; i < to; ++i)
	{
		free(result_buffer[i]); result_buffer[i] = NULL;
	}
	
	free(result_buffer);
	result_buffer = NULL;
}

/******************************************************************************/
static error_types_t AllocateInputBuffer(char *file_name, 
										 input_params_t *input_params) 	
{
	int fd = 0;
	void *mapped = NULL;
	struct stat file_stats;
	
	assert(file_name);
	assert(input_params);
	
	if (0 > (fd = open(file_name, O_RDONLY)))	
	{
		perror("open");
		return OPEN_FILE_ERROR;
	}
	
	if (0 < fstat(fd, &file_stats))
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
	
	return SUCCESS;	  
}
/******************************************************************************/	
static void FreeInputBuffer(input_params_t *buffer)
{
	assert(buffer);
	
	munmap(buffer->buffer, buffer->length);
}
/******************************************************************************/
static file_params_t *InitFileParams(char *input_buffer,
                                     size_t num_bytes_in_file)
{
	size_t start = 0, end = 0;
	size_t i = 0;
	size_t num_bytes_per_thread = num_bytes_in_file/NUM_OF_THREADS;
	file_params_t *params = NULL;
	
	assert(input_buffer);
	 
	params = (file_params_t *) calloc(NUM_OF_THREADS, sizeof(file_params_t)); 
	if (NULL == params)
	{
		return NULL;
	}                             
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		end = start + num_bytes_per_thread;
		params[i].histogram = result_buffer[i]; 
		params[i].input_buffer = input_buffer;
		params[i].start_index = start;
		params[i].end_index = end;
		start = end + 1;
	}
	
	params[i - 1].end_index += num_bytes_in_file % NUM_OF_THREADS;
	
	return params;
}

/******************************************************************************/
static error_types_t CreateThreads(file_params_t *params)
{
	size_t i = 0;
	
	assert(params);
	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		if (0 != pthread_create(&threads[i], NULL, ThreadWork, &params[i]))
		{
			return THREAD_CREATE_ERROR;
		}
	}
	
	return SUCCESS;
}
/******************************************************************************/
static void *ThreadWork(void *args)
{
	size_t i = 0;
	file_params_t *params = NULL;
	
	assert(args);
	
	params = (file_params_t *)args;
	
	for (i = params->start_index; i < params->end_index; ++i)
	{
		char ch = (char )params->input_buffer[i];
		
		if (isalpha(ch))
		{
			++(params->histogram[(int)(tolower(ch) - 'a')]);
		}	
	}

	return NULL;
}
/******************************************************************************/
static error_types_t CountTotalBytesInFile(char *file_name, int *_count)
{
	FILE *fp = NULL;
	
	assert(file_name);
	
	fp = fopen(file_name, "r");
	if (NULL == fp)
	{
		return OPEN_FILE_ERROR;
	}
	
	fseek(fp, 0, SEEK_END); 
	*_count = ftell(fp);
	
	if (0 != fclose(fp))
	{
		
		return OPEN_FILE_ERROR;
	}
	
	return SUCCESS;
}
/******************************************************************************/
static error_types_t JoinThreadsAndDisplayResult(void)
{
	size_t i = 0, j = 0;
	
	assert(result_buffer);

	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
  		if (0 != pthread_join(threads[i], NULL))
  		{
  			return THREAD_JOIN_ERROR;
  		}
  	}

  	for(i = 0; i < NUM_OF_LETTERS; ++i)
  	{
  		for(j = 1 ; j < NUM_OF_THREADS; ++j)
  		{
  			result_buffer[0][i] += result_buffer[j][i];
  		}
  	}
	
  	PrintResult(NUM_OF_LETTERS);

  	return SUCCESS;
}
/******************************************************************************/
void PrintResult(size_t size)
{
	size_t i = 0;
	
	for(i = 0 ; i < size; ++i)
  	{
  			printf("[%c] appers [%ld] times in the file\n", 
  			                              (char)(i + 'a'), result_buffer[0][i]);
  	}
}
/******************************************************************************/
/***                     Comparing a number of threads                      ***/
/******************************************************************************/
/* 1 thread:
					real	0m0.031s
					user	0m0.022s
					sys	    0m0.009s
 
 * 2 threads: 		real	0m0.028s
					user	0m0.047s
					sys	    0m0.004s

 * 3 threads:		real	0m0.027s
					user	0m0.039s
					sys	    0m0.010s

 * 4 threads: 		real	0m0.027s
					user	0m0.043s
					sys  	0m0.005s

 * 8 threads: 		real	0m0.021s
					user	0m0.036s
					sys 	0m0.004s

 * 10 threads:		real	0m0.021s
					user	0m0.043s
					sys	    0m0.005s


 * 16 threads:	    real	0m0.020s
					user	0m0.046s
					sys  	0m0.005s

 * 17 threads:      real	0m0.008s
                    user	0m0.015s
                    sys 	0m0.000s

 * 18 threads:		real	0m0.021s
					user	0m0.036s
					sys 	0m0.005s

 
 
 * 20 threads: 		real	0m0.023s
				    user	0m0.041s
					sys 	0m0.009s

*/ 
