#ifndef __CIRCULAR_BUFFER_H_OL97_ILRD__
#define __CIRCULAR_BUFFER_H_OL97_ILRD__

/******************************************************************************/
/***                            DESCRIPTION                                 ***/
/******************************************************************************/

#include <sys/types.h>   /* size_t, ssize_t */

/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/

typedef struct cbuffer cbuffer_t;

/*
struct cbuffer
{
	size_t read_index;
	size_t write_index;
	size_t capacity;
	char buffer[1];
};

*/

/******************************************************************************/
/***                      Public functions declarations                     ***/
/******************************************************************************/

/* Creates an empty circular buffer with the given fixed capacity.
   Upon success returns a pointer to the buffer,
   upon failure returns NULL.
   Complexity: O(1) */
cbuffer_t *CBufferCreate(size_t capacity);

/* Destroys the given buffer, freeing all its allocated memory.
   If buffer is NULL behaviour undefined.		
   Complexity: O(1) */
void CBufferDestroy(cbuffer_t *buffer);

/* Read 'count' bytes starting from buffer to 'dest'.
   Returns the number of bytes that were read.
   If buffer size < count, number of bytes read is same as size.
   If buffer or dest NULL behaviour undefined.	
   If dest size < count behaviour is undefined.	
   Complexity: O(n)  */
ssize_t CBufferRead(cbuffer_t *buffer, void *dest, size_t count);

/* Write 'count' bytes starting from src to buffer.
   Returns the number of bytes that were written.
   If buffer (capacity - size) < count, (capacity - size) bytes are written.
   If buffer or src is NULL behaviour undefined.	
   If src size < count behaviour is undefined.	
   Complexity: O(n)  */
ssize_t CBufferWrite(cbuffer_t *buffer, const void *src, size_t count);

/* Returns 1 if the buffer is empty, and 0 otherwise.
   If buffer is NULL behaviour undefined.		
   Complexity: O(1) */
int CBufferIsEmpty(const cbuffer_t *buffer);

/* Returns 1 if the buffer is full, and 0 otherwise.
   If buffer is NULL behaviour undefined.		
   Complexity: O(1) */
int CBufferIsFull(const cbuffer_t *buffer);

/* Returns the current size of the buffer
   If buffer is NULL behaviour undefined.		
   (the number of bytes that are stored).
   Complexity: O(1) */
size_t CBufferSize(const cbuffer_t *buffer);

/* Returns the current free space available for the buffer in bytes,
   i.e. its capacity minus current size.
   If buffer is NULL behaviour undefined.		
   Complexity: O(1) */
size_t CBufferFreeSpace(const cbuffer_t *buffer);

#endif /* __CIRCULAR_BUFFER_H_OL97_ILRD__ */
