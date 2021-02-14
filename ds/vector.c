/*************************************************************************** 
 * Description: Implement Dynamic Vector's functions.                      *
 * Author: Noa Efrati                                                      *
 * Reviewer: Oryan Shimoni                                                 *
 * Date: 18.11.20                                                          *
 * Infinity Labs OL97                                                      *
 ***************************************************************************/

#include <stdlib.h>                  /*malloc*/
#include <string.h>                  /*memcpy*/
#include <assert.h>                 /*assert*/
#include "vector.h"            /* stack functions */

#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 0.5

struct vector
{
	void *buffer;
	size_t capacity;         /* maximum elements that the vector holds*/
	size_t element_size;    /* the element size sent by the user */
	size_t vector_size;	/* the current size of the vector */
};

vector_t *VectorCreate(size_t element_size,  size_t initial_capacity)
{
	vector_t *vector = (vector_t *) malloc(sizeof(vector_t));
	
	assert(0 < element_size); 
	assert(0 < initial_capacity);
	
	/*If allocation failed, free vector and return null*/
	if (NULL == vector)
	{
		return NULL;
	}
	
	vector->capacity = initial_capacity;
	vector->element_size = element_size;
	vector->vector_size = 0;
	
	vector->buffer = malloc(element_size * initial_capacity);
	
	/*If allocation failed, free vector->buffer and return null*/
	if (NULL == vector->buffer)
	{
		free(vector);
		return NULL;
	}
	
	return vector;
}

void VectorDestroy(vector_t *vector)
{
	/* If vector is NULL, behaviour is undefined.*/
	assert(NULL != vector);
	
	free(vector->buffer);
	free(vector);
}

size_t VectorSize(const vector_t *vector)
{
	/* If vector is NULL, behaviour is undefined.*/
	assert(NULL != vector);
	
	return (vector->vector_size);
}

/*
 * Returns the pointer to the element at the requested index.
 * If index is invalid (larger or equal to size) the array will be updated with
 * the value, but there is no guarantees about the future of the value (could
 * be changed later by push & pop).
 * If vector is NULL behaviour is undefined.
 */
void *VectorGetAccessToElementAt(const vector_t *vector , size_t index)
{
	void *requested_element = NULL;
	
	/* If vector is NULL, behaviour is undefined.*/
	assert(NULL != vector);
	
	if (vector->capacity < index)
	{
		return NULL;
	}
	
	requested_element = (void *)((size_t)vector->buffer + 
	                                     (index * (vector->element_size)));
	
	return requested_element;
}

/*
 * Add the element to the next free position pointed to by size. 
 * if reach full capacity we enlarge using realloc to Capacity * growth factor. 
 * The growth factor is = 2.
 * If memory realocation failes return 1,  else 0 (sucess).
 */						 			
int VectorPushBack(vector_t *vector , const void *element)
{
	void *insert_location = NULL;
	int is_success = 0;
	
	assert((NULL != vector) && (NULL != element));
	
	/* If the vector is full, then resize. */
	if(vector->vector_size >= vector->capacity)
	{	
		is_success = VectorReserve(vector, 
		                           vector->capacity * GROWTH_FACTOR );
		
		/* If allocation FAILED :                  */
		/* free the allocated memory and return 1. */
		if (1 == is_success)
		{
			VectorDestroy(vector);
			return (1);
		}
	}
	
	insert_location = (void *)((size_t)vector->buffer + 
	                     ((vector->vector_size) * (vector->element_size)));
	
	vector->vector_size += 1;
	memcpy(insert_location, element, vector->element_size);
	
	return is_success;
}

/*
 * Removes element from position pointed to by size. 
 * If size reaches shrink factor of capacity (4 * vector_size = capacity),
 * shrink capacity by factor of 2.
 * This function will return 0
 * on successful realloc and 1 otherwise.
 */	
int VectorPopBack(vector_t *vector)
{
	int is_success = 0;
	
	assert(NULL != vector);
	
	/*if the vector is already empty*/
	if (0 == vector->vector_size)
	{
		return (1);
	}
	
	vector->vector_size -= 1;
	
	if (vector->capacity == vector->vector_size * 
	                                         GROWTH_FACTOR * GROWTH_FACTOR)
	{
		is_success = VectorReserve(vector,
		                          vector->capacity * SHRINK_FACTOR);
		
		/* If allocation FAILED :                  */
		/* free the allocated memory and return 1. */
		if (1 == is_success)
		{
			VectorDestroy(vector);
			return (1);
		}	 
	}
	
	return is_success;
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	assert((NULL != vector));
	
	vector->buffer = realloc(vector->buffer,
	                        vector->element_size * new_capacity);
	
	if (NULL == vector->buffer)
	{
		free(vector->buffer);
		return (1);
	}
	
	vector->capacity = new_capacity;
	
	if (vector->vector_size > new_capacity)
	{
		vector->vector_size = new_capacity;
	}
	
	return (0);
}
