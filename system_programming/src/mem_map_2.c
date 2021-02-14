#include <stdlib.h>
#include <stdio.h>
#include "mem_map.h"

const int g2 = 1;
static int i = 0;
static const int f = 0;


int Alloc(void)
{
	const int status = 0;
	int x1 = 0;
	
	int *arrint = malloc(sizeof(int) * 4);
	char *arrchar = malloc(sizeof(char) * 4);
	float *arrfloat = calloc(sizeof(float), 4);
	 
	char *str1 = "printing global";
	 
	return status;
}

void PrintOnly3(void)
{
	static const int num = 3;
	static int upper = 10;
	int i = 0;
	
	for(; i <= upper; ++i)
	{
		if (i % num == 0)
		{
			printf("%d\n", i);
		}
	}
}

void Foo(int a, int b, int c)
{
	printf("%d %d %d", a, b, c);
}



