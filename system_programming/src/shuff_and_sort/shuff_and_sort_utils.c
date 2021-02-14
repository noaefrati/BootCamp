/****************************************************************************** 
 * Description: Implementation of shuf_and_sort_utils functions               *
 * Author: Noa Efrati                                                         *
 * Reviewer: Carolina Kats                                                    *
 * Date: 07.02.2021                                                           *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/
/******************************************************************************/
/***                              Includes                                  ***/
/******************************************************************************/
#include <sys/mman.h>           /* mmap, munmap                               */
#include <unistd.h>             /* lseek, close                               */
#include <string.h>             /* strncmp                                    */
#include <stdlib.h>             /* malloc, free                               */
#include <fcntl.h>              /* open, O_RDONLY                             */
#include <stdio.h>              /* fprintf, EOF, scanf, perror, fopen, fclose */
#include <assert.h>             /* assert                                     */

#include "shuff_and_sort_utils.h"     /* shuf_and_sort_utils API              */

/* /usr/share/dict/american-english */

/******************************************************************************/
/***                        API Function Definitions                        ***/
/******************************************************************************/
char *CreateArrOfDataWithGivenPath(operation_t *operation_name, char *path)
{
	buffer_args_t *buffer = NULL;
 	int is_mmap = 0;
 	int i = 0, j = 0;
 	
   	if (NULL == path)
   	{
   		return NULL;
   	}
   	
   	buffer = (buffer_args_t *) calloc(1, sizeof(buffer_args_t));
   
	if (NULL == buffer)
   	{
   		return NULL;
   	}
   
   	if (0 > (buffer->fd = open(path, O_RDONLY)))
  	{
  	   perror("failed open file");
  	   
  	   free(buffer); buffer = NULL;
  	   
  	   return NULL;
	}

    if (0 <= (buffer->len = lseek(buffer->fd, 0, SEEK_END)))
    {
    	is_mmap = 1;
	}
	
	if (is_mmap)
    {		
  		buffer->buf = mmap(NULL,
  		                   buffer->len,
  		                   PROT_READ | PROT_WRITE,
  		                   MAP_PRIVATE,
  		                   buffer->fd,
  		                   0);
  		                   
    	if (buffer->buf == MAP_FAILED) 
    	{
			perror("failed mmap");    		
    		
    		free(buffer); buffer = NULL;
    		
    		return NULL;
        }
    }

	for (i = 0, buffer->num_of_lines = 0; i < buffer->len ; ++i)
	{
		if (buffer->buf[i] == '\n') 
		{
			buffer->buf[i] = '\0';
			++(buffer->num_of_lines);
		}	
	}

	if (0 < buffer->len && ('\0' != buffer->buf[buffer->len-1]))
	{
		free(buffer); buffer = NULL;
		
		return NULL;
	}
  	
  	buffer->arr_of_ptr = (char **) malloc(buffer->num_of_lines*sizeof(char *));
  	if (NULL == buffer-> arr_of_ptr)
  	{
  		perror("memory allocation error");
  		
  		free(buffer); buffer = NULL;
  		
  		return NULL;
  	}
  	
  	buffer->arr_of_ptr[0] = &buffer->buf[0];
  	for (i = 0, j = 1; i < buffer->len -1 ; ++i)
  	{
  		if (buffer->buf[i] == '\0')
  		{
  			++i;
  			buffer->arr_of_ptr[j++] = &buffer->buf[i];
  		}
  	}	
  	
 	operation_name(buffer);

 	return path;
}
/******************************************************************************/
char *CreateArrOfDataFromStdin(operation_t *operation_name)
{
	static char input_buffer[128] = {0};
    FILE *file_to_read_from = NULL;
	char *file_name = "temp_name.txt";
	
	assert(operation_name);
	
	if (NULL == (file_to_read_from = fopen(file_name, "w")))
	{
		perror("open error");
		
		return NULL;
	}
	
	while (scanf("%s", input_buffer) != EOF)
	{
		fprintf(file_to_read_from, "%s\n", input_buffer);
	}
	
	fclose(file_to_read_from);
	
	CreateArrOfDataWithGivenPath(operation_name, file_name);
	
	return file_name;

}
/******************************************************************************/
void PrintResult(char **arr_of_ptr, size_t num_of_lines)
{
	size_t i = 0;
	
	assert(arr_of_ptr);
	
	 for (i = 0; i < num_of_lines; ++i)
  	{
  		printf("%s\n", arr_of_ptr[i]);
  	}
}

/******************************************************************************/
int FreeResources(buffer_args_t *buffer)
{
	assert(buffer);

	if (munmap(buffer->buf, buffer->len) < 0)
	{
		perror("munmap failed");
		
		free(buffer->arr_of_ptr); buffer->arr_of_ptr = NULL;
 		free(buffer); buffer = NULL;
 	
		return 1;
	}
	
  	if (close(buffer->fd) < 0)
  	{
  		perror("close file descripto (fd) failed");
  		
  		free(buffer->arr_of_ptr); buffer->arr_of_ptr = NULL;
 		free(buffer); buffer = NULL;
 	
  		return 1;
  		
 	}
 	
 	free(buffer->arr_of_ptr); buffer->arr_of_ptr = NULL;
 	free(buffer); buffer = NULL;
 	
 	return 0;
}

