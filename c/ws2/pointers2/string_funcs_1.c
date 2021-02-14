#include <ctype.h>
#include "strings.h"
char *StrCpy(char *dest, const char *src)
{
	char *startDest = dest;
	
	while (*src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}
	
	*dest = '\0';
	
	return startDest;
}

char *StrNCpy(char *dest, const char *src, size_t n)
{
	size_t j = 0;
	const char *startSrc = src;
	
	while ( n != 0 && src != NULL)
	{
		*(dest + j) = *src;
		n--;
		j++;
		src++;		
	}
	
	if ((n != 0) && (startSrc + j != NULL))
	{
		while (n != 0 && (dest +j) != NULL)
		{
			*(dest + j) = '\0' ;
			n--;
			j++;
		}
	}
	
	return dest;
}

int StrCaseCmp(const char *s1, const char *s2)
{
	int diff= 0;
		
	while (*s1 != '\0' && *s2 != '\0')
	{
		diff = tolower(*s1) - tolower(*s2);
		
		if (diff != 0)
		{
			return diff;
		}
		s1++;
		s2++;	
	}
	
	if (s1 != NULL)
	{
		diff = tolower(*s1);
	} 
	
	else if (s2 != NULL)
	{
		diff = tolower(*s2);
	}
	
	return diff;
}
