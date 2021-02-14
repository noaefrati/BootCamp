#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#include "strings.h"
int main()
{
	char srcCopy[12] = "Hello world";
	char dstCopy[12]= {0};
	char srcNCpy[] = "C programming";
	char dstNCpy[11] ={0};
	char sCsCmp1[] = "ABCD EFG";
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
