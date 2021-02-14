#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int num = 0;
static int numnum = 1;

void *
func1(void *func1_arg)
{	
	size_t i_reg = 0;
	static int i_stat = 5;
	char *str1 = "hello world";
	char str1array[2];
	int *ptr = malloc(4 * sizeof(int));
	num = 4;

	printf("i_reg is %lu i_stat is: %d, num is: %d heap mem is: %d\n", 
	       i_reg, i_stat, num, *ptr);
	
	return NULL;
}

void *
func2(void *func2_arg)
{	
	size_t j_reg = 2;
	static int j_stat = 7;
	char *char_ptr = malloc(6 * sizeof(char));
	numnum = 8;

	printf("i_reg is %lu i_stat is: %d, num is: %d heap mem is: %d\n", 
	       j_reg, j_stat, numnum, *char_ptr);
	
	return NULL;
}

int 
main(void)
{
	pthread_t id1, id3;
	static pthread_t id2;
	
	size_t i = 2;
	static size_t j = 4;
	char *str2 = "hello";
	char str2array[2];
	int *heap_var = malloc(sizeof(int));
	
	pthread_create(&id1, NULL, func1, &i);
	pthread_create(&id2, NULL, func2, &j);
	pthread_create(&id3, NULL, func1, &j);
	
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);
	
	free(heap_var);
	
	return 0;
}



/*
Map:
---

	functions:
	---------
	1. main -  0x4012b0
	2. func1 - 0x4011b6
	3. func2 - 0x401248
	
	Main:
	----
	1. id1 -       0x7fffffffdf60
	2. id2 -       0x404078 (static)
	3. id3 -       0x7fffffffdf68
	3. i -         0x7fffffffdf70
	4. j -         0x404060  (static)
	5. str2 -      0x402050  (String literal)
	6. str2array - 0x7fffffffdf86
	7. num -       0x404070 (global uninitialized - BSS)
	8. numnum -    0x404050 (global initialized - Data)

	func1 (first time):
	------------------
	1. i_reg -     0x7ffff7d97ec8
	2. i_stat -    0x404054 (static)
	3. str1 -      
	4. ptr -       

	func1 (second time):
	-------------------
	1. i_reg -      0x7ffff6d95ec8
	2. i_stat -     0x404054 (static)
	3. str1 -       
	4. ptr -        
	
	func2:
	-----
	1. j_reg -     0x7ffff7596ee0
	2. j_stat -    0x404058 (static)
	3. char_ptr -  0x7ffff0000f90 (Heap)
*/
