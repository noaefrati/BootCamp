/******************************************************************************
Description: vector (by refernce) functions implementation
Author:
Reviewer: 
				
Infinity Labs OL97
*******************************************************************************/

/******************************************************************************/
/***                      Includes and Defines                              ***/
/******************************************************************************/

#include <assert.h>	   /* assert */
#include <stdlib.h>    /* malloc, free */

#include "vector_ref.h"	 /*   vector by refernce API */

#define GROWTH_FACTOR 2
#define DECREASE_FACTOR 0.25

/******************************************************************************/
/***                    structs and function typedefs                       ***/
/******************************************************************************/

struct vector
{
    void **buffer;
    size_t capacity;      
    size_t size;          
};

/******************************************************************************/
/***                         API functions                                  ***/
/******************************************************************************/

/*
 * Create an empty vector with the given capacity.
 * If memory allocation fails, the function will return NULL.
 */
vector_t *VectorCreate(size_t initial_capacity)
{
	vector_t *vector = NULL;
	
	assert(initial_capacity);
	
	vector = (vector_t *) malloc(sizeof(vector_t));
	if (NULL != vector)
	{
		vector->buffer = (void **) malloc(sizeof(void *) * initial_capacity);
		if (NULL != vector->buffer)
		{
			vector->capacity = initial_capacity;
			vector->size = 0;
		}
		
		else
		{
			free(vector); vector = NULL;
		}
		
	}
		
	return(vector);
}

/*
 * Free memory allocated for the vector, and change vector's pointer to NULL.
 * If vector is NULL, behaviour is undefined.
 */
void VectorDestroy(vector_t *vector)
{
	assert(vector);
	
	free(vector->buffer); vector->buffer = NULL;
	free(vector); vector = NULL;	
}

/*
 * Returns the number of already inserted elements.
 * If vector is NULL, behaviour is undefined.
 */
size_t VectorSize(const vector_t *vector)
{
	assert(vector);
	
	return (vector->size);
}

/*
 * Returns the the current capacity of the vector.
 * If vector is NULL, behaviour is undefined.
 */
size_t VectorCapacity(const vector_t *vector)
{
	assert(vector);
	
	return (vector->capacity);
}
					
/*
 * Returns the pointer to the element at the requested index
 * If index is invalid (larger or equal to size) the array will be updated with
 * the value, but there is no guarantees about the future of the value (could
 * be changed later by push & pop).
 * If vector is NULL behaviour is undefined.
 */
 
void *VectorGetAccessToElementAt(const vector_t *vector , size_t index)
{
	assert(vector);
	assert(vector->capacity > index);
	
	return vector->buffer[index];
}

/*
 * Update value of element at index.
 * If index is invalid (larger or equal to size) the array will be updated with
 * the value, but there is no guarantees about the future of the value (could
 * be changed later by push & pop).
 * UB: If vector is NULL. 
 */
void VectorSetElementAt(vector_t *vector, size_t index, void *element)
{
	assert(vector);

	vector->buffer[index] = element;
}
/*
 * Add the element to the next free position pointed to by size. 
 * if reach full capacity we enlarge using realloc to Capacity * growth factor. 
 * We agreed on growth factor = 2.
 * If memory realocation failes return 1,  else 0 (sucess).
 */						 			
int VectorPushBack(vector_t *vector , const void *element) 
{
    int ret_val = 0;
    
    assert(vector);
    assert(element);
    
    if (vector->capacity <= vector->size) 
    {
        ret_val = VectorReserve(vector, vector->capacity * GROWTH_FACTOR);
        
       /* if (1 == ret_val)
        {
        	VectorDestroy(vector);
        	return 1;
        }*/    
    }
    
    if (!ret_val)
    {
        vector->buffer[vector->size++] = (void *)element;
      
    }
        
    return ret_val;
}

	
/*
 * Removes element from position pointed to by size. 
 * If size reaches shrink factor of capacity we shring by factor of 2.
 * We agreed on shrink factor = 0.25 of capacity. This function will return 0
 * on successful realoc and 1 otherwise.
 */	
int VectorPopBack(vector_t *vector)
{
    int ret_val = 0;
    
    assert(vector);
    
    if (0 == vector->size) /* can't pop from empty vector */
    {
        ret_val = 1;
    }
    else
    {
        --(vector->size);
    
        /* if size is less than 0.25 from capacity */
        if (vector->size < (vector->capacity * DECREASE_FACTOR))
        {    
            ret_val = VectorReserve(vector, 
                                    vector->capacity / GROWTH_FACTOR);
        }
    }    
    
    return ret_val;
}

/*
 * resize the vector to given new_capacity.
 */
int VectorReserve(vector_t *vector, size_t new_capacity)
{
	int alloc_flag = 1;
	void **new_vector = NULL;
	
	assert (vector);
	
	if (0 != new_capacity)
	{
		new_vector = realloc(vector->buffer, new_capacity * sizeof(void *));
	}
	
	if (NULL != new_vector)
	{
		vector->buffer = new_vector;
		vector->capacity = new_capacity;
		
		if (vector->capacity < vector->size)
        {
        	vector->size = vector->capacity; 
        }
		alloc_flag = 0;
	}
	
	
	return (alloc_flag);
}

/******************************************************************************/
/***                         static functions                               ***/
/******************************************************************************/


