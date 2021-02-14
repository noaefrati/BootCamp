/******************************************************************************************************************************
*Description: Logger phase 1. A program that asks the user to enter strings. Each string ends when the user presses 'Enter'. 
*The program receives the name of a file as a parameter.
*The file opens ans closes for each operation.
*For every string entered, the program should append the string to the end of the file (on new line).
*Author: Noa Efrati
*Reviewer: Oryan Shimoni
*Date: 7/11/20
*Infinity Labs OL97
*******************************************************************************************************************************/


#include <stdio.h>/*printf, scanf, fgetc, fgets, fputc, fputs, fopen, fclose, remove*/
#include <string.h>/*strncmp*/
#include <stdio_ext.h>/*__fpurge*/
#include <stdlib.h>/*exit*/

#define MAX 100

int main()
{
	
	FILE *f_ptr = NULL; /*file pointer*/
	char file_name[10] = " ";
	char usr_input[MAX] = " ";
	
	printf("Enter a file name: ");
	scanf("%s",file_name);
	f_ptr = fopen(file_name, "a+");
	
	if (f_ptr == NULL)
	{
		printf("Error while oppening the file\n");
	}
	fclose(f_ptr); 
	
	printf("Enter text to your file up to 100 characters, if you want to exit enter -exit: \n ");
	fgets(usr_input, MAX, stdin);/*Gets the first string to the first row of the file*/
	
	while (fgets(usr_input, MAX, stdin) != NULL)/*Loop runs while usr_input is not null*/
	{	
		/*Using strncmp to check whether the user wants to finish the writing to the file*/
		if (strncmp(usr_input, "-exit", 5) == 0)
		{	

			exit(0);
		}
		
		printf("Enter text to your file up to 100 characters, if you want to exit enter -exit: \n ");	
		f_ptr = fopen(file_name, "a+");	
		
		if (f_ptr == NULL) /*Check if the file failed to open*/
		{ 
			
			exit(0); 
		} 
		
		fputs(usr_input, f_ptr);/*Put the user input into the file*/
		fclose(f_ptr); 
		__fpurge(stdin); /*Clean the buffer*/
		
	}
	
	
	return (0);
	
}

