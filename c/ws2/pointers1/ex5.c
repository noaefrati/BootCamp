#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


size_t StrLen(const char *s);


int StrCmp(const char *s1, const char *s2);

int main()
{	
	
	char s1[5];
	char s2[5];
	size_t size = 5;
	
	printf("Enter first string s1, till 4 characters: \n");/*Four characters because the last character should be '\0'.*/
	scanf("%s", s1);
	printf("Enter second string s2, till 4 characters: \n");
	scanf("%s",s2);
	
	assert(StrLen(s1) <= size && s1 != NULL);/*Stops program when the user has entereded in more than 4 characters.*/
	assert(StrLen(s2) <= size &&  s2 != NULL);
	
	printf("size of s1 = %lu\n",StrLen(s1));
	printf("size of s1 = %lu\n",StrLen(s2));
	printf("strcmp(s1,s2) = %d\n",StrCmp(s1, s2));
	
	
	return 0;
}

size_t StrLen(const char *s)
{
	size_t size = 0;
	
	while (*s != '\0')
	{
		s++;
		size++;
	}
	return size;
}

int StrCmp(const char *s1, const char *s2)
{
	
	while (*s1 == *s2 && (*s1 != '\0' || *s2 !='\0'))
	{	
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

