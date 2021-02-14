/******************************************************************************
Description: vector (by refernce) functions implementation
Author: Roi Peretz
Reviewer: 
				
Infinity Labs OL97
*******************************************************************************/

/******************************************************************************/
/***                      Includes and Defines                              ***/
/******************************************************************************/

#include <assert.h>	   /* assert */
#include <stdlib.h>    /* malloc, free */
#include <stdio.h>    
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

void VectorDestroy(vector_t *vector)
{
	assert(vector);
	
	free(vector->buffer); vector->buffer = NULL;
	free(vector); vector = NULL;	
}

size_t VectorSize(const vector_t *vector)
{
	assert(vector);
	
	return (vector->size);
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(vector);
	
	return (vector->capacity);
}

void *VectorGetAccessToElementAt(const vector_t *vector , size_t index)
{
	void *ret_ptr = NULL;
	
	assert(vector);
	
	if (index < vector->size)
	{
		ret_ptr = *(vector->buffer + index);
	}
	
	return(ret_ptr);
}

int VectorPushBack(vector_t *vector , const void *element) 
{
    int ret_val = 0;
    
    assert(vector);
    assert(element);
    
    if (vector->capacity == vector->size) 
    {
        ret_val = VectorReserve(vector, vector->capacity * GROWTH_FACTOR);    
    }
    
    if (!ret_val)
    {
        vector->buffer[vector->size] = (void *)element;
        ++(vector->size);
    }
        
    return ret_val;
}

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
        if (vector->size <= (vector->capacity * DECREASE_FACTOR))
        {    
            ret_val = VectorReserve(vector, 
                                    vector->capacity / GROWTH_FACTOR);
        }
    }    
    
    return ret_val;
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	if (new_capacity > 0)
	{
		vector->buffer = (void **)realloc(vector->buffer, sizeof (void *) * new_capacity );
		if (NULL == vector->buffer)
		{
			return (1);
		}
		vector->capacity = new_capacity;
		if (vector->capacity < vector->size)
		{
			vector->size = vector->capacity;
		}
	}
	return (0);
}

void VectorSetElementAt(vector_t *vector, size_t index, void *element)
{
	assert(vector);
	
	if (index < vector->capacity)
	{
		vector->buffer[index] = element;
	}
}


