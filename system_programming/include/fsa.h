#ifndef __FSA_H_OL97_ILRD__
#define __FSA_H_OL97_ILRD__

/******************************************************************************/
/***                   Fixed-Size Allocator (FSA) API                       ***/
/******************************************************************************/

#include <stddef.h>   /* size_t */

typedef struct fsa_mng fsa_t;

/*

Inside implementation file:
==========================
struct fsa_mng
{
    size_t first_free; 
};

*/


/******************************************************************************/
/***                      Public functions declarations                     ***/
/******************************************************************************/

/*
 * This function returns the size (in bytes) of memory that a
 * user should allocate, in order to have enough memory
 * for num_blocks of size block_size (bytes) to be managed using the FSA.
 * Attention - user should use this function before allocating memory.
 * Time Complexity: O(1)
 */
size_t FSASuggestSize(size_t num_blocks, size_t block_size);

/*
 * This function receives a pointer that contains the address returned
 * by a memory allocation function (e.g. malloc),
 * and initializes the given memory space to make memory management
 * of this space possible, i.e. it allows the user to use
 * the functions FSAAlloc, FSAFree and FSACountFree.
 * This function returns pointer to fsa.
 * Time Complexity: O(n) (n = num of blocks)
 * WARNINGS:
 * (*) All data that was previously stored in the given allocated
 *     memory will be lost.
 * (*) After calling this function, the user must not use any pointer
 *     to this allocated memory, other than passing 'fsa' to the 
 *     relevant functions, and using the pointers received from
 *     FSAAlloc to store variables of size no more than block_size.
 * (*) If the user allocated less memory than 
 *     FSASuggest(num_blocks, block_size),
 *     the user is risking memory leaks and/or overriding
 *     other data in her program.
 */
fsa_t *FSAInit(void *pool, size_t num_blocks, size_t block_size);

/*
 * This function returns an address to a block of memory
 * that is currently available in the FSA.
 * Available blocks are ones that either were not yet returned
 * by this function, or ones that were freed by FSAFree.
 * If the FSA is full, returns NULL.
 * UB: if 'fsa' is not a valid pointer that FSAInit was used upon.
 * WARNING: the user must not use the pointers received from
 * FSAAlloc to store variables of size more than block_size.
 * Time Complexity: O(1)
 */
void *FSAAlloc(fsa_t *fsa);

/*
 * This function frees the block of memory in the given 
 * address of block, so the user will be able to get it again
 * in the future using FSAAlloc.
 * UB: - if 'fsa' is not a valid pointer that FSAInit was used upon.
 *     - if 'block' is not an address to a block in the FSA.
 *     - if 'block' is already free
 * Time Complexity: O(1)
 */
void FSAFree(fsa_t *fsa, void *block);

/*
 * This function returns the number of blocks that are still available
 * for use/allocation to the user (using FSAAlloc) in the FSA.
 * UB: if 'fsa' is not a valid pointer that FSAInit was used upon. 
 * Time Complexity: O(n) (n = num of blocks)
 */
size_t FSACountFree(const fsa_t *fsa);



#endif /* __FSA_H_OL97_ILRD__ */
