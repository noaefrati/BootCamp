/******************************************************************************
 * Description: C basic quiz (bitwise, alloc 2d arrays)                       *
 * Date: 31.01.2021                                                           *
 ******************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
/* Q1 : Write the following function without using 'if' statements:
      a. Function 1 check the 2nd and 6th bits in an unsigned char, 
         if they are both set, it return "true".
      b. Function 2 the same like function 1 exept that at least one of
          them is set on.
      c. Function 3 swaps between 3rd and 5th bits of an unsigned char.    
*/


static int IsBitSetOn(unsigned char num, size_t pos)
{
	return (num >> pos) & 1;
}
/* Q1. a */
static int Is6And2IsSetOn(unsigned char num)
{
	return IsBitSetOn(num,2) & IsBitSetOn(num, 6);

}
/* Q1.b */
static int Is6Or2BitIsOn(unsigned char num)
{
	return IsBitSetOn(num, 2) | IsBitSetOn(num, 6);
}
/* Q1 .c */
static void Swap3_5(unsigned char *num)
{
	assert(num);
	
	*num ^= (1 << 3);
	*num ^= (1 << 5);
}

/* Q2 : IMplement a function that swaps values of two integers. */

void SwapValue(int *a, int *b)
{
	int tmp = 0;
	
	assert(a);
	assert(b);
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* Q3. Implement a function that swaps values of two pointers of int*/

void SwapPtrValues(int **p1, int **p2)
{
	int *tmp = NULL;
	
	assert(p1);
	assert(p2);
	
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

/* Q4 : Implement function that swaps between values of two void pointers */

void SwapVoidPtr(void *p1, void *p2)
{
	size_t *tmp = NULL;
	
	assert(p1);
	assert(p2);
	
	tmp = *(size_t **)p1;
	*(size_t **)p1 = *(size_t**)p2;
	*(size_t**)p2 = tmp;
	/*
	memcpy(&tmp, p1, sizeof(size_t));
	memcpy(p1, p2, sizeof(size_t));
	memcpy(p2, &tmp, sizeof(size_t));
	*/
}
/* Q 5: what is the difference between string literal and array of chars? */
static void Q5(void)
{
	char *p = "lalala";
	char arr[10] = "lalala";
	
	++p;
	 /* cannot modify the address of an array. arr points to the first value of the arr*/
	/*++arr;*/
	/**p = 's'; seg fault*/
	/*p[0] = 's';*/ /* seg fault. string literal is const and can be read only*/
	arr[1] = 's';
	*(arr +1) = 's';
	1[arr] = 's';
}
/* Q6: IMplement a function that creates 1D array with a given size */
static int *Create1DArr(size_t size)
{
	int *arr = (int *) malloc(sizeof(int) * size);
	
	if (NULL == arr)
	{
		return NULL;
	}
	return arr;	
}
/* Q 7: Implement a function that create 2D arr of given sizes*/
static int *Create2DArr(size_t rows, size_t cols)
{
	size_t i =0;
	int **matrix = (int **) malloc(sizeof(int *)*rows);
	if (NULL == matrix)
	{
		return NULL;
	}
	
	for (i = 0; i <rows; ++i)
	{
		matrix[i] =  (int *) malloc(sizeof(int) * cols);
		if (NULL == matrix[i])
		{
			DestroyArr(matrix, i);
			return NULL;
		}
	}	
	
	return matrix;
}
int main()
{
	size_t a = 123; /* 1111011 */
	size_t b = 127; /* 1111111 */
	size_t c = 119; /* 1110111 */
	
	printf("Is6And2IsSetOn(123 = 1111011) ? %d\n", 
	                                          Is6And2IsSetOn((unsigned char)a));
	                                          
	printf("Is6And2IsSetOn(127 = 1111111) ? %d\n", 
	                                          Is6And2IsSetOn((unsigned char)b));
	printf(" Is6Or2BitIsOn(123 = 1111011) ? %d\n", 
	                                          Is6Or2BitIsOn((unsigned char)a));
	                                        
	printf("Before Swap3_5(%ld = 1110111)\n", c);
	Swap3_5((unsigned char *)&c);
	printf("After Swap3_5: %ld\n", c); 
	                                                                                                                             
	printf("Before swap void pointers: a = %ld, b = %ld\n", a, b);
	SwapVoidPtr(&a, &b);
	printf("After swap void pointers :a = %ld, b = %ld\n", a, b);
	
	Q5();
	return 0;
}
