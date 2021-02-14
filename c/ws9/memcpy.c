#include "mem.h"



void *Memcpy(void *dst, const void *src, size_t n)
{

	size_t rest = WORD - (size_t)src % WORD;
	
	if (NULL == src)
	{
		return NULL;
	}
	
	/************************************************************/
	/*If the address held by the pointer is aligned with "word" */
	/* then the remainder should be zero.                       */
	/* otherwise (if it is not zero) then we will copy byte by  */
	/* byte until the size of the remainder is equal to zero.   */
	/************************************************************/
		
	for (; 0 < rest; --rest, --n)
	{
		*(char *)dst = *(char *)src;
		dst = (char *)dst+ 1;
		src = (char *)src + 1;
	}

		
	/*n in each iteration decreases by "word"*/	
	while(n >= WORD)
	{
		*(size_t *)dst = *(size_t*)src;
		n -= WORD;
		dst = (size_t *)dst + 1;
		src = (size_t *)src + 1;
				
	}
	
	/*************************************************************/
	/*If n has not yet reached zero,                             */
	/*and is already smaller than a "word" then,                 */
	/* we will run on it until it is reset and copy byte by byte */
	/*************************************************************/
	
	
		for (; 0 < n ; --n)
		{
			*(char *)dst = *(char *)src;
			dst = (char *)dst+ 1;
		 	src = (char *)src + 1;
		}
	
	
		return dst;	
}
	

