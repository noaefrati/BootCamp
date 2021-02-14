#ifndef __VECTOR_H_OL97_ILRD__
#define __VECTOR_H_OL97_ILRD__
/******************************************************************************
 *
 * Definition of vector ADT & declaration of its interface functions.
 *
 ******************************************************************************/

/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h>   /* size_t                                               */

/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/
typedef struct vector vector_t;

/******************************************************************************/
/***                      Public functions declarations                     ***/
/******************************************************************************/

/*
 * Create an empty vector with the given capacity.
 * If memory allocation fails, the function will return NULL.
 */
vector_t *VectorCreate(size_t element_size,  size_t initial_capacity);

/*
 * Free memory allocated for the vector, and change vector's pointer to NULL.
 * If vector is NULL, behaviour is undefined.
 */
void VectorDestroy(vector_t *vector);

/*
 * Returns the number of already inserted elements.
 * If vector is NULL, behaviour is undefined.
 */
size_t VectorSize(const vector_t *vector);
					
/*
 * Returns the pointer to the element at the requested index
 * If index is invalid (larger or equal to size) the array will be updated with
 * the value, but there is no guarantees about the future of the value (could
 * be changed later by push & pop).
 * If vector is NULL behaviour is undefined.
 */
void *VectorGetAccessToElementAt(const vector_t *vector , size_t index);

/*
 * Add the element to the next free position pointed to by size. 
 * if reach full capacity we enlarge using realloc to Capacity * growth factor. 
 * We agreed on growth factor = 2.
 * If memory realocation failes return 1,  else 0 (sucess).
 */						 			
int VectorPushBack(vector_t *vector , const void *element);

/*
 * Removes element from position pointed to by size. 
 * If size reaches shrink factor of capacity we shring by factor of 2.
 * We agreed on shrink factor = 0.25 of capacity. This function will return 0
 * on successful realoc and 1 otherwise.
 */	
int VectorPopBack(vector_t *vector);

/*
 * resize the vector to given new_capacity.
 */
int VectorReserve(vector_t *vector, size_t new_capacity);

#endif   /* __VECTOR_H_OL97_ILRD__ */
