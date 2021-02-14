#include "mem.h" /*macro - WORD*/

 /********************************************************************************/
 /*The memmove function refers to a situation where a source has to be copied    */
 /*to a destination,that they overlap in their addresses.                        */
 /*The solution - is to check which address preceded the second.                 */
 /*When it is found who precedes the second, the indexes are updated accordingly.*/
 /*If the destination address is larger than the source address,                 */
 /*then the array must be passed from end to beginning.                          */
 /*Otherwise go through it from beginning to end.                                */
 /********************************************************************************/


 void *Memmove(void *dst, const void *src, size_t n)
 {
 	signed char operation;
 	size_t runner;
 	size_t end;
 	char *dst_runner = (char *)dst;
 	char *src_runner = (char *)src;
 	
 	if (NULL == src_runner)
 	{
 		return src_runner;
 	}
 	
 	if (dst_runner != src_runner)
 	{
 		if (dst_runner < src_runner)
 		{
 			operation = 1;
 			runner = 0;
 			end = n;
 		}
 		else
 		{
 			operation = -1;
 			runner = n - 1;
 			end = -1;
 		}
 	}
 	
 	for (; runner != end; runner += operation)
 	{
 		*(dst_runner + runner) = *(src_runner + runner);
 	}
 	
 	return dst;
 }

