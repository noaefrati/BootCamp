/****************************************************************************** 
 * Description: Implement VSA                                                 *
 * Author: Noa Efrati                                                         *
 * Reviewer: Snir Cohen                                                       *
 * Date: 13.12.20                                                             *
 * Infinity Labs OL97                                                         *
 ******************************************************************************/
/******************************************************************************/
#include <assert.h>                  /* assert                                */
#include "vsa.h"                     /* vsa functions                         */

#define DEADBEEF 0XDEADBEEF          /* a mark to know who is the owner       */
#define WORD_SIZE sizeof(size_t) 
#define VSA_SIZE sizeof(vsa_t)
#define HEADER_SIZE sizeof(header_t)   

/******************************************************************************/
/******************************************************************************/
typedef struct header header_t;

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
};
/******************************************************************************/
/****************************Utility Functions*********************************/

static void MergeAdjacentFreeBlock(vsa_t *vsa);
static size_t AlignmentPoolSize(size_t to_align);
static size_t AlignmentChunkSize(size_t to_align);
static size_t GetBlockSize(void *chunk);
static header_t *GetBlockAddress(void *chunk);
static size_t GetTotalPoolSize(void *vsa);
static header_t *GetNextBlock(header_t *cur_block);
static header_t *GetFirstBlock(vsa_t *vsa);
static size_t GetAddressOfEndMemory(vsa_t *vsa);
static size_t CheckSizeABS(size_t chunk_size);

/******************************************************************************/
/******************************************************************************/

vsa_t *VSAInit(void *pool, size_t pool_size)
{
	vsa_t *vsa = NULL;
	header_t *header_blk = NULL;
	
	assert(NULL != pool);
	
	pool = (void *)AlignmentChunkSize((size_t)pool);
	
	vsa = (vsa_t *)pool;
	vsa->pool_size = AlignmentPoolSize(AlignmentPoolSize(pool_size) - VSA_SIZE);
	
	header_blk = (header_t *)((char *)pool + VSA_SIZE);
	header_blk->chunk_size = vsa->pool_size - HEADER_SIZE;
	
	#ifndef NDEBUG
	header_blk->magic_number = DEADBEEF;
	#endif
	
	return vsa;
}

void *VSAAlloc(vsa_t *vsa, size_t chunk_size)
{
	header_t *block_runner= NULL; 
	size_t fit_size = 0;
	size_t end_of_memory = 0;
	
	assert(NULL != vsa);
	
	chunk_size = AlignmentChunkSize(chunk_size);
	end_of_memory = GetAddressOfEndMemory(vsa);
	
	if (VSAMaxFreeChunk(vsa) >= chunk_size)
	{	
		for (block_runner = GetFirstBlock((vsa_t *)vsa);
			 end_of_memory > (size_t)block_runner;
		 	block_runner = GetNextBlock(block_runner))
		{	
			if (chunk_size <= GetBlockSize(block_runner) && 
				0 == (GetBlockSize(block_runner) % WORD_SIZE))
			{
				fit_size = GetBlockSize(block_runner);
				
				block_runner->chunk_size = chunk_size;
		    
		   	 	/* If there is more room for another block         */  
				if (fit_size - chunk_size >= WORD_SIZE + HEADER_SIZE)
				{
					header_t *next_free = GetNextBlock(block_runner);
				
					next_free->chunk_size = (fit_size -
								(AlignmentChunkSize(chunk_size) + HEADER_SIZE));
					#ifndef NDEBUG
					next_free->magic_number = DEADBEEF;
					#endif		
				}
				else
				{		
				 /* there is no more space to add another block
				 * then add to chunk_size the difference that left over 
				 * from the continuous_size */
				
					block_runner->chunk_size += (fit_size - chunk_size);
				}
			
				/* mark block_runner->chunk_size as occupied,
				 * which leaves a remainder of 1 from modulo word_size*/
			 	
				++(block_runner->chunk_size);
			
				return  ((char *)block_runner + HEADER_SIZE);
			}
		}
	}
	
	return NULL;	
}

#include <stdio.h>

void VSAFree(void *chunk)
{
	assert(NULL != chunk);
	assert(DEADBEEF == GetBlockAddress(chunk)->magic_number);
	
	/* if size is mark as occupied (marked with residue 1)  */
	if (GetBlockSize((char *)chunk - HEADER_SIZE) % WORD_SIZE == 1)
	{
		  
		((header_t *)chunk - 1)->chunk_size -= 1; 
		/*((header_t *)((char *)chunk -  HEADER_SIZE))->chunk_size -= 1;*/
	}	
}

size_t VSAMaxFreeChunk(const vsa_t *vsa)
{
	size_t biggest_chunk = 0;
	size_t end_of_memory = 0;
	size_t cur_free_size = 0;

	header_t *block_runner = NULL;
	
	assert(NULL != vsa);
	
	MergeAdjacentFreeBlock((vsa_t *)vsa);
	end_of_memory = GetAddressOfEndMemory((vsa_t *)vsa);
	
	for (block_runner = GetFirstBlock((vsa_t *)vsa);
		 end_of_memory > (size_t)block_runner;
		 block_runner = GetNextBlock(block_runner))
	{	
		cur_free_size = GetBlockSize((void *)block_runner);
		
		if (0 == cur_free_size % WORD_SIZE)
		{
			if (biggest_chunk < cur_free_size)
			{
				biggest_chunk = cur_free_size;
			}		   
		}	
	}	
	
	return biggest_chunk;	
}

static void MergeAdjacentFreeBlock(vsa_t *vsa)
{
	size_t end_of_memory = 0;
	size_t continuous_free_memory = 0;
	header_t *runner = NULL;
	header_t *runner_is_empty = NULL;
	
	assert(NULL != vsa);
	
	end_of_memory = GetAddressOfEndMemory(vsa);
			
	for(runner = GetFirstBlock(vsa);
		(size_t)runner < end_of_memory;
		runner = GetNextBlock(runner)) 
	{
		/* free space size is divisible without a word_size remainder */
		if (0 == GetBlockSize((void *)runner) % WORD_SIZE)
		{
			/* When find a first place that is free,
			* then save its address and start running from the next block 
			* when the available places are summed up
			* intended for running inside the next FOR loop.*/
			runner_is_empty = runner;
			continuous_free_memory = CheckSizeABS(GetBlockSize((void *)runner));
			
	
			for(runner = GetNextBlock(runner);
			   (size_t )runner < end_of_memory &&
				0 == (GetBlockSize((void *)runner) % WORD_SIZE);
				runner = GetNextBlock(runner)) 
			{
				continuous_free_memory += 
					   CheckSizeABS(GetBlockSize((void *)runner)) + HEADER_SIZE;			
			}
					
			runner_is_empty->chunk_size = continuous_free_memory ;
			continuous_free_memory = 0;
			
			if ((size_t)runner >= end_of_memory)
			{
				return;
			}
		}
	}	
}
static size_t AlignmentPoolSize(size_t to_align)
{
	size_t remainder = 0;
	
	assert(0 < to_align);
	
	remainder = to_align % WORD_SIZE;
	
	/* check if the size of block is align */
	if (0 != remainder)
	{
		to_align -= remainder;
	}
	
	return (to_align);
}
static size_t AlignmentChunkSize(size_t to_align)
{
	size_t remainder = 0;
	
	assert(0 < to_align);
	
	remainder = to_align % WORD_SIZE;
	
	/* check if the size of block is align */
	if (0 != remainder)
	{
		to_align += (WORD_SIZE - remainder);
	}
	
	return (to_align);
}
static size_t GetBlockSize(void *chunk)
{
	return ((header_t *)chunk)->chunk_size;
}
static header_t *GetBlockAddress(void *chunk)
{
	return ((header_t *)((char *)chunk - HEADER_SIZE));
}
static size_t GetTotalPoolSize(void *vsa)
{
	return (((vsa_t *)vsa)->pool_size);
}
static header_t *GetNextBlock(header_t *cur_block)
{
	return (header_t *)((char *)cur_block +
			CheckSizeABS(GetBlockSize((void *) cur_block)) + HEADER_SIZE);
}
static header_t *GetFirstBlock(vsa_t *vsa)
{
	return (header_t *)((char *)vsa + VSA_SIZE);
}
static size_t GetAddressOfEndMemory(vsa_t *vsa)
{
	return (size_t)vsa + GetTotalPoolSize((vsa_t *)vsa) + VSA_SIZE;
}
static size_t CheckSizeABS(size_t chunk_size)
{
	if (0 != chunk_size % WORD_SIZE)
	{
		chunk_size -= 1;
	}
	return chunk_size;
}
