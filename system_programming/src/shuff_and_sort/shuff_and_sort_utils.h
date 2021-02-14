#ifndef __SHARED_LIBRARY_H__
#define  __SHARED_LIBRARY_H__

/****************************************************************************** 
 * Description: Shared library of shuffle & sort utilities on files.          *
 * Author: Noa Efrati                                                         *
 * Reviewer: Carolina Kats                                                    *
 * Date: 07.02.2021                                                           *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/
#include <stddef.h>                                                 /* size_t */

/******************************************************************************/
typedef struct buffer_args
{
	int fd;
	size_t num_of_lines;
	long len;
	char *buf;
	char **arr_of_ptr;
}buffer_args_t;

typedef int (operation_t)(buffer_args_t *buffer);
/******************************************************************************/

char *CreateArrOfDataFromStdin(operation_t *operation_name);

char *CreateArrOfDataWithGivenPath(operation_t *operation_name, char *path);

int FreeResources(buffer_args_t *buffer);

void PrintResult(char **arr_of_ptr, size_t num_of_lines);

#endif /* __SHARED_LIBRARY_H__ */
