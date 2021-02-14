#include <stdio.h>
#include <stdlib.h>

int *foo(void)
{
	int *a = malloc(sizeof(int) * 2);
	if (NULL == a)
	{
		return NULL;
	}
	a[0] = 1;
	a[1] = 2;
	
	return a;
}
int main()
{
	int x = 10;
	
	printf(" x : %p\n", &x); /* l-value, type of int, value of 10 */
	
	/* non l-value, type: char literal, value: value of 'x' in ascii table */
	printf(" 'x' : %p\n", &'x'); 
	
	/* non l-value type of int, value: 11 */
	printf(" x + 1 : %p\n", &(x + 1)); 
	
	/* non l-value, type of int, post increanent, value of 11*/
	printf(" x++ : %p\n", &(x++));
	
	/* non l-value, type of int, pre increament, value of 11 */
	printf(" ++x : %p\n", &(++x));
	
	/* l-value */
	printf(" *foo(): %p\n", *foo());
	
	/* non l-value*/
	printf(" &foo() : %p\n", &foo());
	
	/* l-value */
	printf(" foo() : %p\n", foo());
	
	/* l-value */
	printf(" foo : %p\n", foo);
	
	/* lvalue */
	printf(" &foo : %p\n", &foo);
	
	return 0;
}
