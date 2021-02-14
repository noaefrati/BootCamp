/****************************************************************************** 
 * Description: Implementation of sort a file using multithreading            *
 * Author: Noa Efrati                                                         *
 * Reviewer: Carolina Kats                                                    *
 * Date: 07.02.2021                                                           *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/
/******************************************************************************/
/***                              Includes                                  ***/
/******************************************************************************/

#include <pthread.h>                        /* pthread_create, pthread_join   */
#include <stdlib.h>                         /* malloc                         */
#include <assert.h>                         /* assert                         */
#include <string.h>                         /* strcmp                         */
#include <stdio.h>                          /* printf, perror                 */
#include "shuff_and_sort_utils.h"            /* shared_library API             */

/******************************************************************************/
/***                               Define                                   ***/
/******************************************************************************/

#define NUM_OF_THREADS 4

/******************************************************************************/
/***                         Struct & typedefs                              ***/
/******************************************************************************/

typedef struct thread_args
{
	char **start_address;
	size_t start_ind;
	size_t num_of_elements;
	size_t offset;
	
} thread_args_t;

/******************************************************************************/
/***                      Sort Function Declarations                        ***/
/******************************************************************************/

static int MainSortProgram(buffer_args_t *argv);

/* Create, join, and the preaperation for thread work */
static void *ThreadQSort(void *args);

static int SortCmpFunc(const void *one, const void *other);

static int SortByThreads(buffer_args_t *argv, thread_args_t *thread_args);

static thread_args_t *InitThreadsArgs(size_t num_elements, 
                                      size_t num_lines,
                                      char **arr_of_ptr);
/* Merge functions*/
void Copy(char **dest, char **src, size_t amount);

static void MergeSortRec(size_t left_thread_ind, 
                         size_t right_thread_ind, 
                         char **_result, 
                         thread_args_t *params);

static void MergeAndCopy(char **start_address, 
                         size_t left, 
                         size_t middle, 
                         size_t right, 
                         char **_result);

static char **MergeAfterThreadsWork(size_t num_of_lines, thread_args_t *params);

/******************************************************************************/
/***                               Main App                                 ***/
/******************************************************************************/

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		perror("Needed to be only 1 or 2 arguments!\n");
		return 1;
	}
	if (argc == 1)
	{
		char *file_name = CreateArrOfDataFromStdin(&MainSortProgram);
		remove(file_name);
	}
	else if (argc == 2)
	{
		CreateArrOfDataWithGivenPath(&MainSortProgram, argv[1]);
	}
	
	return 0;
}
/******************************************************************************/
/***                        Sort Fnctions Definitions                       ***/
/******************************************************************************/
static int MainSortProgram(buffer_args_t *argv)
{
	thread_args_t *thread_args = NULL;
	size_t num_elements = 0;
	
	num_elements = argv->num_of_lines/ NUM_OF_THREADS;
	
	thread_args = InitThreadsArgs(num_elements,
	                                     argv->num_of_lines,  argv->arr_of_ptr);
	
	if (NULL == thread_args)
	{
		perror("memory allocation error");
		
		FreeResources(argv);
		
		return 1;
	}
	if (0 != SortByThreads(argv, thread_args))
	{
		perror("memory allocation error");
		
		free(thread_args); thread_args = NULL;
		FreeResources(argv);
		
		return 1;
	}
	
	argv->arr_of_ptr = MergeAfterThreadsWork(argv->num_of_lines, thread_args);
	
	if (NULL == argv->arr_of_ptr)
	{
		perror("memory allocation error");
		
		free(thread_args); thread_args = NULL;
		FreeResources(argv);
		
		return 1;
	}
	
	PrintResult(argv->arr_of_ptr, argv->num_of_lines);
  	
  	FreeResources(argv);
	free(thread_args); thread_args = NULL;
	
	return 0;
	
}
/******************************************************************************/
static int SortByThreads(buffer_args_t *argv, thread_args_t *thread_args)
{
	size_t i = 0;
	pthread_t thread_ids[NUM_OF_THREADS] = {0};
	
	assert(argv);
	assert(argv->arr_of_ptr);

	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		if (0 != pthread_create(&thread_ids[i],
		                         NULL,
		                         ThreadQSort, 
		                         &thread_args[i]))
		{
			return 1;
		}
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		if (0 != pthread_join(thread_ids[i], NULL))
		{
			return 1;
		}
	}
	
	return 0;
}
/******************************************************************************/
static thread_args_t *InitThreadsArgs(size_t num_elements, 
                                      size_t num_lines,
                                      char **arr_of_ptr)
{
	thread_args_t *thread_args = NULL;
	size_t i = 0;
	
	assert(arr_of_ptr);
		
	thread_args = (thread_args_t *)malloc(sizeof(thread_args_t)*NUM_OF_THREADS);
	
	if (NULL == thread_args)
	{
		perror("memory allocation error");
		
		return NULL;
	}
	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		thread_args[i].start_ind = i;
		thread_args[i].num_of_elements = num_elements;
		thread_args[i].offset = i* num_elements;
		thread_args[i].start_address = arr_of_ptr + thread_args[i].offset;
	}
	
	thread_args[i - 1].num_of_elements += num_lines % NUM_OF_THREADS;
	
	return thread_args;
}

/******************************************************************************/
static void *ThreadQSort(void *args)
{
	thread_args_t *input = NULL;
	
	assert(args);
	
	input = (thread_args_t *)args;; 
	
	qsort(input->start_address, input->num_of_elements, 
	                                              sizeof(char *), &SortCmpFunc);
	
	return NULL;
}
/******************************************************************************/
static int SortCmpFunc(const void *one, const void *other) 
{
	assert(one);
	assert(other);
	
	return (strcmp(*(char **)one, *(char **)other));			
}
/******************************************************************************/
char **MergeAfterThreadsWork(size_t num_of_lines, thread_args_t *params)
{
	char **_arr = NULL;
	
	assert(params);

	_arr = (char **) malloc(num_of_lines * sizeof(char *));
    if (NULL == _arr)
    {
		return NULL;
    }
	
	MergeSortRec(0, NUM_OF_THREADS - 1, _arr, params);
	
	free(_arr);_arr = NULL;
	
    return params[0].start_address;
}

/******************************************************************************/
static void MergeSortRec(size_t left_thread_ind, 
                         size_t right_thread_ind, 
                         char **_result, 
                         thread_args_t *params)
{
	
	size_t middle = 0;
	
	if (right_thread_ind == left_thread_ind)
	{
		return;
	}	
	
	middle = (left_thread_ind + right_thread_ind) / 2;

	if (1 < (right_thread_ind - left_thread_ind))
	{
		MergeSortRec(left_thread_ind, middle, _result, params); 
		
		MergeSortRec(middle + 1, right_thread_ind, _result, params);
	}
	
	left_thread_ind = params[left_thread_ind].offset;

    middle = params[middle].offset + params[middle].num_of_elements - 1;

    right_thread_ind  = params[right_thread_ind].offset + 
                                   params[right_thread_ind].num_of_elements - 1;
    
    MergeAndCopy(params[0].start_address, 
				 left_thread_ind, 
		         middle, 
				 right_thread_ind, 
				 _result);
		
}
/******************************************************************************/
static void MergeAndCopy(char **start_address,
                         size_t left, 
                         size_t middle, 
                         size_t right, 
                         char **_result)
{
	
	size_t left_runner = left;
    size_t right_runner = middle + 1;
    size_t i = 0;
    
    assert(start_address);
    assert(_result);
    
	     /*fill original array while sorting*/	
	  while (left_runner <= middle && right_runner <= right)
    {
		 if (0 >= SortCmpFunc(&(start_address[left_runner]), 
		                      &(start_address[right_runner])))
		{ 
			_result[i++] = start_address[left_runner++]; 
		} 
		else 
		{ 
			_result[i++] = start_address[right_runner++]; 
		} 
	}
       
    Copy(_result + i, start_address + left_runner, middle - left_runner + 1);
    Copy(_result + i, start_address + right_runner, right - right_runner + 1);
    Copy(start_address + left, _result, right - left + 1);
}
void Copy(char **dest, char **src, size_t amount)
{
    size_t i = 0;
    
    assert(dest);
    assert(src);
    
    for (; i < amount; ++i)
    {
        dest[i] = src[i];
    }
}
