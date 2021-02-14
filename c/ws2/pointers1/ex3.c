#include<stdio.h>
#include<stdlib.h>

int main()
{	
	static int s_i =7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *)malloc(sizeof(int));
	
	
	printf("&s_i = %p\n", (void*)&s_i);
	printf("&i = %p\n", (void*)&i);
	printf("&ptr = %p\n", (void*)&ptr);
	printf("ptr = %p\n", (void*)ptr);
	printf("&ptr2 = %p\n", (void*)&ptr2);
	printf("ptr2 = %p\n", (void*)ptr2);
	
	if(ptr2)
	{
			
		printf("&ptr2 = %p\n", (void*)&ptr2);
		printf("ptr2 = %p\n", (void*)ptr2);
	}
	
	
	free(ptr2);
	printf("&ptr2 = %p\n", (void*)&ptr2);
	printf("ptr2 = %p\n", (void*)ptr2);
	

	return 0;
}

