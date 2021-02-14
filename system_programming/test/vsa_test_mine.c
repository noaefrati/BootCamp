#include <stdio.h>
#include <stdlib.h>
#include "test_utills.h"
#include "vsa.h"

/******************************************************************************/
void Suggest(void);
void Complete(void);

/******************************************************************************/
int main()
{
	Complete();
	return 0;
}

/******************************************************************************/

void Complete(void)
{
	char *str1 = "hello",
	str2 = "world", str3 = "hello world!", str4 = "hello world hello world!";
	char *p1 = NULL;
	char *p2 = NULL;
	char *p3 = NULL;
	char *p4 = NULL;

	size_t pool_size = sizeof(char) * 8, res = 0;
	void *pool = NULL; 
	
	
	pool = malloc(pool_size);
	
	if (NULL != pool)
	{
		vsa_t *vsa = FSAInit(pool, pool_size);
		
		p1 = (char *)FSAAlloc(vsa, strlen(str1) + 1);
		strcpy(p1, str1);
		res = LargestChunkAvailable(vsa);
		TEST("LargestChunkAvailable", res, 0);
		res = (strcmp(p1, str1));
		TEST("Alloc", res, 0);
		
		p2 = (char *)FSAAlloc(vsa, strlen(str2) + 1);
		strcpy(p2, str2);
		res = LargestChunkAvailable(vsa);
		TEST("LargestChunkAvailable", res,0;
		res = (strcmp(p1, str1));
		TEST("Alloc", res, 0);
		res = (strcmp(p2, str2));
		TEST("Alloc", res, 0);

		p3 = (char *)FSAAlloc(vsa, strlen(str3) + 1);
		strcpy(p3, str3);
		res = LargestChunkAvailable(vsa);
		TEST("LargestChunkAvailable", res, ???);
		res = (strcmp(p1, str1));
		TEST("Alloc", res, 0);
		res = (strcmp(p2, str2));
		TEST("Alloc", res, 0);
		res = (strcmp(p3, str3));
		TEST("Alloc", res, 0);
		
		p4 = (char *)FSAAlloc(vsa, strlen(str4) + 1);
		strcpy(p4, str4);
		res = LargestChunkAvailable(vsa);
		TEST("LargestChunkAvailable", res, 0);
		res = (strcmp(p1, str1));
		TEST("Alloc", res, 0);
		res = (strcmp(p2, str2));
		TEST("Alloc", res, 0);
		res = (strcmp(p3, str3));
		TEST("Alloc", res, 0);
		res = (strcmp(p4, str4));
		TEST("Alloc", res, 0);
		
		FSAFree((void *)p4);
		res = LargestChunkAvailable(vsa);
		TEST("LargestChunkAvailable", res, strlen(str4) + 1);	
		res = (strcmp(p1, str1));
		TEST("Free", res, 0);
		res = (strcmp(p2, str2));
		TEST("Free", res, 0);
		res = (strcmp(p3, str3));
		TEST("Free", res, 0);
		
		FSAFree((void *)p2);
		res = LargestChunkAvailable(vsa);
		TEST("LargestChunkAvailable", res, strlen(str4) + 1);	
		res = (strcmp(p1, str1));
		TEST("Free", res, 0);
		res = (strcmp(p3, str3));
		TEST("Free", res, 0);
		
	
		p2 = (int *)FSAAlloc(vsa, strlen(str4) + 1);
		strcpy(p2, str4);
		res = (strcmp(p2, str4));
		TEST("Alloc", res, 0);
		TEST("LargestChunkAvailable", LargestChunkAvailable(vsa), strlen(str2) + 1);	
		res = (strcmp(p1, str1));
		TEST("Alloc", res, 0);
		res = (strcmp(p2, str4));
		TEST("Alloc", res, 0);
		res = (strcmp(p3, str3));
		TEST("Alloc", res, 0);
		
		CHECK("Complete", success_counter, 27);
		RESET();
		
		free(vsa);

	}	
}

