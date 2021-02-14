/****************************************************************************** 
 * Description: Implement FSA - Fixed Size Allocator                          *
 * Author: Noa Efrati                                                         *
 * Reviewer: Yifat Baruch                                                     *
 * Date: 10.12.20                                                             *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/
/******************************************************************************/
#include <assert.h>                  /* assert                                */
#include "fsa.h"                     /* fsa functions                         */

#define WORD_SIZE sizeof(size_t)     

/******************************************************************************/
/******************************************************************************/
struct fsa_mng
{
    size_t first_free;  /*offset to first available block*/
} ;

/******************************************************************************/
/****************************Utility Functions*********************************/

 
/* Check whether the resulting number is aligned to WORD_SIZE.
 * returns the aligned value, otherwise returns the value obtained.           */         
static size_t AlignedBlockSize(size_t block_size);

/******************************************************************************/
/******************************************************************************/

size_t FSASuggestSize(size_t num_blocks, size_t block_size)
{
	size_t suggest_size = 0;
	
	assert(0 < num_blocks);
	assert(0 < block_size);
	
	block_size = AlignedBlockSize(block_size);	
	suggest_size = block_size * num_blocks + sizeof(fsa_t);
	
	return (suggest_size);
}

fsa_t *FSAInit(void *pool, size_t num_blocks, size_t block_size)
{	
	fsa_t *fsa = NULL;	
	char *blk_runner = NULL;
	size_t offset = 0;
	size_t count_blk = 1;
	
	assert(NULL != pool);
	
	pool = (void *)AlignedBlockSize((size_t) pool);
	block_size = AlignedBlockSize(block_size);
	offset = sizeof(fsa_t);
	
	fsa = (fsa_t *)pool;      	
	fsa->first_free = offset;	
	

	for (blk_runner = (char *)fsa + fsa->first_free;
	     num_blocks != count_blk;
	     blk_runner += block_size, ++count_blk)
	{
		 /* saves the offset of the next block in current one    */
		 *(size_t *)blk_runner =  (block_size * count_blk) + offset;	
	}
	
	*(size_t *)blk_runner = 0;
	
	return (fsa);		
}

void *FSAAlloc(fsa_t *fsa)
{
	char *ret_alloc = NULL;
	
	assert(NULL != fsa);
	
	if (0 != fsa->first_free)
	{
		/* Save the first block that is free */
		ret_alloc = (char *)fsa + fsa->first_free;
		
		/* update first_free for the next alloc request*/
		fsa->first_free = *(size_t *)ret_alloc;
	}
	
	return ((void *)ret_alloc);
}

void FSAFree(fsa_t *fsa, void *block)
{
	assert(NULL != fsa);
	assert(NULL != block);
	
	/* mark the free block */
	*(size_t *)block = fsa->first_free;
	
	/* get address of block to free */
	fsa->first_free = (size_t)((char *)block - (char *)fsa);
}

size_t FSACountFree(const fsa_t *fsa)
{	
	char *runner = NULL;
	size_t free_blocks = 0;
	
	assert(NULL != fsa);
	
	for (runner = (char *)fsa + fsa->first_free;
		 fsa != (fsa_t *)runner;
		 runner = ((char *)fsa + *(size_t *)(runner)), ++free_blocks)
	{
		/* empty */
	}
	
	return (free_blocks);
}

/******************************************************************************/
static size_t AlignedBlockSize(size_t block_size)
{
	size_t remainder = 0;
	
	assert(0 < block_size);
	
	remainder = block_size % WORD_SIZE;
	
	/* check if the size of block is align */
	if (0 != remainder)
	{
		block_size = block_size + WORD_SIZE - remainder;
	}
	
	return (block_size);
}
