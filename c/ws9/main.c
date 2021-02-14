#include <stdio.h>
#include "mem.h"

int main()
{
	float a[20] = {1.5, 33.3, 41.2, 35, -9, 10};
	/*float b[20];*/
    char src[20] = "How Are you ?"; 
    char dst[20] = {0}; 
   	char s[20] = "abcdefgh";
   	int c = '$';
   	size_t n =4;
   	char str3[ ] = "Hello World !!!";
    char str[100] = "Learningisfun";
    int i = 0;
   	char *first, *second;
    first = str;
    second = str;
   	
   	/*
   	printf("-------memset--------\n");
   	printf("Before : s = %s\n", s);
   	Memset(s, c, n);
   	printf("After s = %s\n", s);
   	printf("Before : float arr =");
   	for (;i<6 ; ++i)
   	{
   		printf("%f ",a[i]);
   	}
   	Memset(a, '1', n);
   	printf("\nAfter: a= "); 
   	for (;i<6 ; ++i)
   	{
   		printf("%f ", a[i]);
   	}
   	*/
   	
   	printf("\n-------memcpy--------\n");
   	printf("Before : src = %s\n", src);
   	 /*copy source buffer int dst*/
   	Memcpy(dst,src,sizeof(src));
    	printf("After dst = %s\n", dst);
   /*
   	printf("-------memmove--------\n");
  	printf("str3 = %s\n", str3);
   	Memmove(str3, &str3[6], 5);
	printf("str3 = %s\n", str3);
  	
  	printf("Original string :%s\n ", str);
     */
  	  /* when overlap happens then it just ignore it*/
    	/*Memcpy(first + 8, first, 10);
    	printf("memcpy overlap : %s\n ", str);
 */
   	 /*when overlap it start from first position*/
   /*	 Memmove(second + 8, first, 10);
   	 printf("memmove overlap : %s\n ", str);
  	*/
  	return 0;
}
