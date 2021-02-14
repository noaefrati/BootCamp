/*************************************************************************** 
 * Description: Implement Circular Buffer                                  *
 * Author: Noa Efrati                                                      *
 * Reviewer: Snir Cohen                                                    *
 * Date: 29.11.20                                                          *
 * Infinity Labs OL97                                                      *
 ***************************************************************************/

#include <stdlib.h>                     /* malloc                          */
#include <assert.h>                     /* assert                          */
#include "circular_buffer.h"            /* circualr buffer functions       */ 

#define MIN(a,b) ((a < b) ? (a) : (b)) /* macro to find mini value         */

struct cbuffer
{
	size_t read_index;
	size_t write_index;
	size_t capacity;
	char buffer[1];
};

/* To differentiate between a state where the buffer is full and a state where
   the buffer is empty, then + 1 must be added to the capacity.
   Buffer is full: when the write index will be one index before the read index.
   Buffer is empty: when the read index is equal to the write index.         */
cbuffer_t *CBufferCreate(size_t capacity)
{
	cbuffer_t *new_cb = (cbuffer_t *) malloc
					    (sizeof(cbuffer_t) + capacity);
					   
	if (NULL != new_cb)
	{
		new_cb->capacity = capacity;
		new_cb->read_index = 0;
		new_cb->write_index = 0;	
	}

	return new_cb;
}

void CBufferDestroy(cbuffer_t *buffer)
{
	assert(NULL != buffer);
	free(buffer); buffer = NULL;
}

ssize_t CBufferRead(cbuffer_t *buffer, void *dest, size_t count)
{
	size_t i = 0;
	
	assert(NULL != buffer);
	assert(NULL != dest);
	
	count = MIN(count,CBufferSize(buffer));

	for (; count > i; ++i)
	{
		((char *)dest)[i] = buffer->buffer[buffer->read_index];
	
		/* increase an index in a wrap around manner */
		buffer->read_index = (buffer->read_index + 1) % (buffer->capacity+ 1);
		
	}
	
	return (ssize_t)count;
}
 
ssize_t CBufferWrite(cbuffer_t *buffer, const void *src, size_t count)
{
	size_t i = 0;
	
	assert(NULL != buffer);
	assert(NULL != src);

	count = MIN(count, CBufferFreeSpace(buffer));
	

	for (; count > i; ++i)
	{
		buffer->buffer[buffer->write_index] = ((char *)src)[i];
		
		/* increase an index in a wrap around manner */
		buffer->write_index = (buffer->write_index + 1) %
							  (buffer->capacity + 1);		
	}
	
	return (ssize_t)count;
}

/* CBufferIsEmpty: return true when read_index and write_index are equale. */
int CBufferIsEmpty(const cbuffer_t *buffer)
{
	assert(NULL != buffer);

	return ((buffer->capacity - CBufferSize(buffer)) == buffer->capacity);
}

/* CBufferIsFull: return true when write_index is one index before read_index */
int CBufferIsFull(const cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	return (buffer->capacity == CBufferSize(buffer));
}

/* Returns the number of bytes that are stored. */
size_t CBufferSize(const cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	return ((buffer->write_index - buffer->read_index + buffer->capacity + 1) %
		    (buffer->capacity + 1));
}

size_t CBufferFreeSpace(const cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	return (buffer->capacity - CBufferSize(buffer));
}

