#include <stdio.h>                /*  printf                  */
#include <string.h>               /* strlen                   */
#include <stdlib.h>

#include "circular_buffer.h"             /* circular buffer functions */
#define RED     "\033[31m"       /*  Red                      */
#define GREEN   "\033[32m"       /* Green                     */
#define DEF   "\033[0m"

#define TEST(name, real, expected) (real == expected) ?\
printf(GREEN"%s, SUCCESS in line %d\n"DEF, name, __LINE__)\
: printf(RED"%s, FAIL in line %d\n"DEF, name, __LINE__)


int CBTest1(void);
int CBTest2(void);

int main()
{
	return (0);
}

int CBTest1(void)
{
	ssize_t ret_val = 0;
	const char *src = "Hello World!";
	size_t size = strlen(src);
	char *dest = malloc(sizeof(size)*sizeof(char));
	cbuffer_t *cb = CBufferCreate(size);
	

	
	ret_val = CBufferWrite(cb, src, size);

	TEST("CBufferWrite TEST",ret_val, size);
	TEST("CBufferSize TEST",CBufferSize(cb), size);
	TEST("CBufferIsFull TEST",CBufferIsFull(cb), 1);
	TEST("CBufferFreeSpace TEST",CBufferFreeSpace(cb), 0);
	
	ret_val = CBufferRead(cb, dest, size);
	
	TEST("CBufferRead TEST",ret_val, size);
	TEST("CBufferIsEmpty TEST",CBufferIsEmpty(cb), 1);
	TEST("CBufferSize TEST",CBufferSize(cb), 0);
	TEST("CBufferIsFull TEST",CBufferIsFull(cb), 0);
	TEST("CBufferFreeSpace TEST",CBufferFreeSpace(cb), size);
	
	CBufferDestroy(cb);
	if (NULL != cb)
	{
		TEST("CBufferDestroy TEST", -1,1);
		return (-1);
	}

	free(dest);
	return 0; 
}
int CBTest2(void)
{
	ssize_t ret_val = 0;
	const char *src = "Hello World Hello World!";
	size_t size = strlen(src);
	char *dest = malloc(sizeof(size)*sizeof(char));
	cbuffer_t *cb = CBufferCreate(size);
	size_t free_space = 0;
	

	free_space = CBufferFreeSpace(cb);
	
	ret_val = CBufferWrite(cb, src, size);
	
	TEST("CBufferWrite TEST",ret_val, free_space);
	TEST("CBufferSize TEST",CBufferSize(cb), size/2);
	TEST("CBufferIsFull TEST",CBufferIsFull(cb), 1);
	TEST("CBufferFreeSpace TEST",CBufferFreeSpace(cb), 0);
	
	ret_val = CBufferRead(cb, dest, size);
	
	TEST("CBufferRead TEST",ret_val, size/2);
	TEST("CBufferIsEmpty TEST",CBufferIsEmpty(cb), 1);
	TEST("CBufferSize TEST",CBufferSize(cb), 0);
	TEST("CBufferIsFull TEST",CBufferIsFull(cb), 0);
	TEST("CBufferFreeSpace TEST",CBufferFreeSpace(cb), size);
	
	CBufferDestroy(cb);
	if (NULL != cb)
	{
		TEST("CBufferDestroy TEST", -1,1);
		return (-1);
	}

	free(dest);
	return 0; 
}
