#include "mem.h"

void *Memset(void *s, int c, size_t n)
{
	size_t *s_runner = (size_t *) s;
	size_t to_add = (size_t) c;
	char *s_cpy_byte = (char *)s_runner;
	size_t rest = (size_t)s_runner % WORD;
	
	if (NULL == s_runner)
	{
		return s;
	}
		
	/************************************************************/
	/*If the address held by the pointer is aligned with "word" */
	/* then the remainder should be zero.                       */
	/* otherwise (if it is not zero) then we will copy byte by  */
	/* byte until the size of the remainder is equal to zero.   */
	/************************************************************/
	
	if(0 != rest)
	{
		to_add = (char)to_add;			
		for (; 0 < rest; --rest, --n)
		{
			*s_cpy_byte++ = to_add;
		}		
		s_runner = (size_t *)s_cpy_byte;
		to_add = (size_t)to_add;
	}
	
	while (n >= WORD)
	{
		*s_runner++ = to_add;
		n -= WORD;
	}

	/*************************************************************/
	/*If n has not yet reached zero,                             */
	/*and is already smaller than a "word" then,                 */
	/* we will run on it until it is reset and copy byte by byte */
	/*************************************************************/
	
	if (0 < n)
	{		
		to_add = (char)to_add;		
		for (; 0 < n; --n)
		{
			*s_cpy_byte++ = to_add;
		}
	}
	
	
	return s;
}
