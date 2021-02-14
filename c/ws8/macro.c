/**************************************************************************************************************************************/
/* Atuor : Noa Efrati                                                                                                                 */
/* Reviewer: Avraham Sharon                                                                                                           */
/* Date: 10.11.20                                                                                                                     */  
/* Description: Learning macros.                                                                                                      */
/*                                                                                                                                    */     
/**************************************************************************************************************************************/
         /*printf*/
#include <stdio.h>

/*q2. macro of max between 2 elements, and max between 3 elements*/
#define MAX2(a, b) ((a > b) ? a : b)
#define MAX3(a, b, c) (MAX2(MAX2(a, b), c))

/*q3. macro of sizeof var*/
#define SIZEOF_VAR(var) ((size_t)(&(var)+1)-(size_t)(&(var))) 

/*q4. sizeof type*/
#define SIZEOF_TYPE(type) (long int)(((type *)(0)) + 1)                      

typedef struct
{
     int a;
     int b;
     char c;
} foo;

int main(void)
{
	
	int a;
	int b;
	int c;
	int max2;
	int max3;
	double d;
	size_t size_of_var ;
	foo foo3;
	printf("Enter first num: ");
	scanf("%d", &a);
	printf("Enter second num: ");
	scanf("%d", &b);
	printf("Enter third num: ");
	scanf("%d", &c);
	
	max2 = MAX2(a,b);
	max3 = MAX3(a, b, c);
	printf("Max2 is : %d\n", max2);
	printf("Max3 is : %d\n", max3);
	
	
	size_of_var = SIZEOF_VAR(d);
	
	printf("size of var double = %lu\n", size_of_var);
	printf("size of var foo3 = %lu\n",  SIZEOF_VAR(foo3));
	printf("size of int = %lu\n", SIZEOF_TYPE(int) );
	printf("size of struct foo = %lu\n", SIZEOF_TYPE(foo) );

	
	
	return 0;
}

