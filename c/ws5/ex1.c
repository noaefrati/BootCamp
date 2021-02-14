/******************************************************************************************************************************
*Description: Creating a new struct type "print_me" that holds an int pointer to a function "void Print(int)".
*Creating an array of 10 "struct print_me" and initialization each one to hold a different int value.
*For each "struct print_me", operate the appropriate Print function.
*Author: Noa Efrati
*Reviewer: Oryan Shimoni
*Date: 7/11/20
*Infinity Labs OL97
*******************************************************************************************************************************/
#include <stdio.h>/*printf*/

struct print_me{
	
	int value;
	void (*print_ptr)(int);
};

/*Print the value in specific index*/
void Print(int index);
#define SIZE 10
int main()
{
	struct print_me print_arr[SIZE];
	int index = 0;
	
	for(; index < 10; ++index) /*init print_arr*/
	{
		print_arr[index].value = index;
		print_arr[index].print_ptr = Print;		
	}
	
	index = 0;
	
	for(; index < 10; ++index)
	{
		print_arr->print_ptr(print_arr[index].value);
		
	}
	
	return 0;
}


void Print(int index)
{
	printf("%d\n",index);
}
