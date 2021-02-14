#ifndef __VSA_H_OL97_ILRD__
#define __VSA_H_OL97_ILRD__

/******************************************************************************/
/***                 Variable-Size Allocator (VSA) API                      ***/
/******************************************************************************/

#include <stddef.h>   /* size_t */

typedef struct vsa_mng vsa_t;

/*
Inside implementation file:
==========================
struct vsa_mng
{
    size_t pool_size;
};

struct header
{
	size_t chunk_size;
	#ifndef NDEBUG
	size_t magic_number; 
	#endif
}
*/

/******************************************************************************/
/***                      Public functions declarations                     ***/
/******************************************************************************/

/*
 * This function receives a pointer that contains the address of the pool.
 * The first 'pool_size' bytes of the pool must be accessible by the program.
 * The function initializes the given memory space to make memory management
 * of this space possible, i.e. it allows the user to use the functions
 * VSAAlloc, VSAFree and VSAMaxFreeChunk.
 * The function returns pointer to vsa.
 * Time Complexity: O(1)
 * WARNINGS:
 * (*) All data that was previously stored in the given allocated
 *     memory may be lost.
 * (*) After calling this function, the user must not use any pointer
 *     to this allocated memory, other than passing 'vsa' to the 
 *     relevant functions, and using the pointers received from
 *     VSAAlloc to store variables of size no more than the size
 *     that was passed to VSAAlloc as parameter.
 * (*) The actual available memory for use of the user is smaller
 *     then 'pool_size', as some of the memory is used for memory
 *     management utilities.
 */
vsa_t *VSAInit(void *pool, size_t pool_size);

/*
 * This function returns an address to a chunk of memory
 * with 'chunk_size' in bytes, that is currently available 
 * in the VSA.
 * return NULL if there is no available chunk size in the VSA.
 * UB: if 'vsa' is not a valid pointer that VSAInit was used upon.
 * WARNING: the user must not use the pointers received from
 * VSAAlloc to store variables of size more than 'chunk_size'.
 * Time Complexity: O(n), 
 *                  where n is the number of allocations
 *                  that were performed by the VSA.
 */
void *VSAAlloc(vsa_t *vsa, size_t chunk_size);

/*
 * This function frees the chunk of memory in the given 
 * address of chunk, so the user will be able to get it again
 * in the future using VSAAlloc.
 * UB: - if 'chunk' is not an address to a chunk in the VSA.
 *     - if 'chunk' is already free.
 * Time Complexity: O(1)
 */
void VSAFree(void *chunk);

/*
 * This function returns the size of the biggest available chunk
 * for use/allocation to the user (using VSAAlloc) in the VSA.
 * UB: if 'vsa' is not a valid pointer that VSAInit was used upon. 
 * Time Complexity: O(n), 
 *                  where n is the number of allocations
 *                  that were performed by the VSA.
 */
size_t VSAMaxFreeChunk(const vsa_t *vsa);



#endif /* __VSA_H_OL97_ILRD__ */
