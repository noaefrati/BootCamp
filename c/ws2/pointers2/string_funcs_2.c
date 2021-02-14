#include <stdlib.h> /*malloc*/
#include "strings.h"
char *StrChr(const char *str, int c)
{	
	int i = 0 ;
		
	while (*(str+i) != '\0')
	{
		if (*(str + i) == c)
		{
			
		return (char *)(str + i);
		}
		i++;
	}
	return NULL;
}

size_t StrLen(const char *s)
{
	size_t size = 0;
	
	while (s[size] != '\0')
	{
		
		++size;
	}
	return size;
}
char *StrDup(const char *s)
{
	char *dup = (char *)malloc((StrLen(s)+1) * sizeof(char));
	if (NULL  == dup)
	{
		return NULL;
	}
	return StrCpy(dup, s);
}

char *StrCat(char *dest, const char *src)
{
	size_t size = StrLen(dest);
	char *startDest = dest;
	dest = dest + size;
	StrCpy(dest, src);	
		
	return startDest;
}
char *StrNCat(char *dest, const char *src, size_t n)
{	
	
	char *startDest = dest;
	size_t size = StrLen(dest);
	dest = dest + size;
	StrNCpy(dest, src, n);

	return startDest;
}

  char *StrStr(const char *haystack, const char *needle)
 {
 	
 	size_t i = 0;
 	size_t size = StrLen(needle);
 	char *hystkBfr;
 		
 	while (*haystack != '\0')
 	{
 		if (*haystack  == *needle)
 		{	
 			i = 1;
 			hystkBfr = (char *) haystack;
 			haystack++;
 			
 			 while (*haystack  == *(needle + i) && i < size)
 			 {
 			 	 haystack++;
 			 	 i++ ;
 			 }
 			 
 			 if (i == size)
 			 {
 			 	return hystkBfr;
 			 }
 			
 			 haystack = hystkBfr ;			
 		}
 		 haystack++;
 	}
 	
 	return NULL;
 }
  
 size_t StrSpn(const char *s, const char *accept)
 {
 	const char *start1 = s;
 	const char *start2 = accept;
 	size_t counter = 0;
 	
 	
 	while (StrChr((char *)start2, (int) *start1) != NULL)
 	{
 		counter ++;
 		start1++;
 		
 	}
 	return counter;
 }

 int isPolindrom(char *s)
 {	
 	size_t i = 0;
 	int isPoli = 1;
 	size_t size = StrLen(s)/2;
 	char *start = s;
 	char *end = s + (size -1);
 	
 	
 	while (i < size && isPoli)
 	{	
 		if(*start != *end)
 		{
 			isPoli = 0;
 		}
 		end--;
 		start++;
 		i++;
 	}
 	
 	return isPoli;
 	
 }
