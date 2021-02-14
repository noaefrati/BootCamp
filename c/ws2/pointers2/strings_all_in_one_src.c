#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

char *StrCpy(char *dest, const char *src);
char *StrNCpy(char *dest, const char *src, size_t n);
int StrCaseCmp(const char *s1, const char *s2);
char *StrChr(const char *str, int c);
size_t StrLen(const char *s);
char *StrDup(const char *s);
char *StrCat(char *dest, const char *src);
char *StrNCat(char *dest, const char *src, size_t n);
char *StrStr(const char *haystack, const char *needle);
size_t StrSpn(const char *s, const char *accept);
int isPolindrom(char *s);

int main()
{
	char srcCopy[12] = "Hello world";
	char dstCopy[12];
	char srcNCpy[] = "C programming";
	char dstNCpy[11];
	char sCsCmp1[] = "ABCD  EFG";
	char sCsCmp2[] = "abcd efg";
	char *sDup =  StrDup(sCsCmp1);
	char sCat [30] = "hijk";
	char sNCat [30] = "hijk "; 
	char hystk[] = "abcddddddfgm";
	char ndl[] = "dfg";
	char poli[] = "ab";
	char poli2[] = "a";
	char poli3[] = "abcba";
	char sSpn1[] = "abcd";
	char sSpn2[] = "bca";
	
	char c = 101;
	size_t size = 10;
	int ansCase = 0;
	
	if (!sDup)
	{
		return -1;
	}
	
	printf("----------------StrCpy------------------------\n");
	assert(strcpy(dstCopy ,srcCopy) == StrCpy(dstCopy ,srcCopy)); /*Comparing the original library result to my result*/
	printf("srcCopy = %s , dstCopy = ", srcCopy);
   	puts(dstCopy);
   	
   	printf("\n----------------StrNCpy------------------------\n");
   	printf("Before StrNcpy: srcNCpy = %s, copy %lu charachters\n", srcNCpy, size);
   	assert(strncpy(dstNCpy, srcNCpy, size) == StrNCpy(dstNCpy, srcNCpy, size));
   	printf("After StrNCpy: dstNCpy = %s \n", dstNCpy);
   	
   	printf("\n----------------StrCaseCmp------------------------\n");
   	printf("Before StrCaseCmp:  sCsCmp1 = %s, sCsCmp2 = %s\n",  sCsCmp1, sCsCmp2);
   	ansCase = StrCaseCmp(sCsCmp1,sCsCmp2);
   	assert(strcasecmp(sCsCmp1,sCsCmp2) == ansCase);
   	printf("StrCaseCmp(sCsCmp1, sCsCmp2) = %d\n", ansCase);
   	
   	printf("\n----------------StrChr----------------------------\n");
   	printf("sCsCmp2 = %s, find the char = %c\n",  sCsCmp2, c);
   	assert(strchr(sCsCmp2,c) == StrChr(sCsCmp2,c));
   	printf("StrChr(sCsCmp2, c) = %s\n", StrChr(sCsCmp2,c));
   	
   	printf("\n----------------StrDup-----------------------------\n");
   	printf("sCsCmp1 = %s\n",  sCsCmp1);
   	printf("sDup = %s\n", sDup);
   	
   	printf("\n----------------StrCat----------------------------\n");
   	printf("Before StrCat: hystk = %s, sCat = %s \n", hystk, sCat);
   	assert(strcat(sCat, hystk) == StrCat(sCat, hystk));
   	printf("After StrCat: hystk = %s, sCat = %s \n", hystk, sCat);
   	
   	printf("\n----------------StrNCat---------------------------\n");
   	printf("Before StrCat: hystk = %s, sCat = %s, size to cat : %lu \n", hystk, sNCat, size);
   	assert(strncat(sNCat, hystk, size) == StrNCat(sNCat, hystk, size));
   	printf("After StrCat: hystk = %s, sCat = %s \n", hystk, sNCat);
   	
   	printf("\n----------------StrStr------------------------------\n");
   	printf("hystk = %s, ndl = %s \n", hystk, ndl);
   	assert(strstr(hystk, ndl) == StrStr(hystk, ndl));
   	printf(" StrStr(hystk, ndl) = %s\n",  StrStr(hystk, ndl));
   	
   	printf("\n----------------StrSpn------------------------------\n");
   	assert(strspn(sSpn1, sSpn2)==StrSpn(sSpn1, sSpn2));
   	printf("StrSpn(%s, %s) = %lu \n",sSpn1, sSpn2, StrSpn(sSpn1, sSpn2));
   	printf("StrSpn(abc, bc) = %lu \n", StrSpn("abc", "bc"));
   	
   	printf("\n----------------isPolindrom------------------------------\n");
   	printf("1 - is a polindrom, 0 -  non polindrom\n");
   	printf("isPolindrom(%s) =  %d, isPolindrom(%s) = %d, isPolindrom(%s) = %d\n", poli, isPolindrom(poli), poli2, isPolindrom(poli2), poli3, isPolindrom(poli3));
   	
   	
 	
   	free(sDup);
   	return 0;
   		
}

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
