/****************************************************************************** 
 * Description: Implementation of shuffle a file                              *
 * Author: Noa Efrati                                                         *
 * Reviewer: Carolina Kats                                                    *
 * Date: 07.02.2021                                                           *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/
/******************************************************************************/
/***                              Includes                                  ***/
/******************************************************************************/
#include <time.h>                            /* time                          */
#include <stdlib.h>                          /* rand, srand                   */
#include <assert.h>                          /* assert                        */
#include <stdio.h>                           /* printf                        */
#include "shuff_and_sort_utils.h"                  /* shared_library API            */

/******************************************************************************/
/***                      Private Functions Declarations                    ***/
/******************************************************************************/

static int Shuffle(buffer_args_t *argv);
static int RandomShuffle(const void *a, const void *b);

/******************************************************************************/
/***                                  App                                   ***/
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
  		char *file_name =  CreateArrOfDataFromStdin(&Shuffle);
  		remove(file_name);
  	
  	}
  	else if (argc == 2)
  	{
  		CreateArrOfDataWithGivenPath(&Shuffle, argv[1]);
  
  	}
  	
  	return 0;
}
/******************************************************************************/
/***                     Private Functions Definitions                      ***/
/******************************************************************************/

static int Shuffle(buffer_args_t *argv)
{
	assert(argv);
	assert(argv->buf);
	
	srand(time(NULL));
  	
  	qsort((void *)argv->arr_of_ptr,
  	       argv->num_of_lines, 
  	       sizeof(char *), 
  	       &RandomShuffle);
  	
 	PrintResult(argv->arr_of_ptr, argv->num_of_lines);
 	FreeResources(argv);
  	
  	return 0;
}

/******************************************************************************/
/* 0 -1 1*/
static int RandomShuffle(const void *a, const void *b)
{
	(void)a;
	(void)b;
	return  (rand() % 3) -1;
}
