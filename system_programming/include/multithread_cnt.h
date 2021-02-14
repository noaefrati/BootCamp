#ifndef __MULTI_THREADED_CNT_H_RD97_ILRD__
#define __MULTI_THREADED_CNT_H_RD97_ILRD__

/******************************************************************************
 * Header file Containing API Definition for Multi-threaded count application *
 *                                                                            *
 * Infinity Labs - RD97                                                       *
 ******************************************************************************/
 
/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h>		/* size_t                                             */

/******************************************************************************/
/***                              Enumerations                              ***/
/******************************************************************************/
typedef enum
{
    SUCCESS,
    OPEN_FILE_ERROR,
    MEM_ALLOC_ERROR,
    THREAD_CREATE_ERROR,
    THREAD_JOIN_ERROR
} error_types_t;

/******************************************************************************/
/***                      Public function declarations                      ***/
/******************************************************************************/

/*
 * This function receives filename argument and desired number of threads and 
 * outputs the occurrence of each letter in the text file.
 * Return Value: SUCCESS (0) in case of success, detailed error number otherwise.
 */
error_types_t PrintAppearances(char *file_name);


#endif /* __MULTI_THREADED_CNT_H_RD97_ILRD__ */
