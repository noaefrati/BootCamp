/******************************************************************************************************************************
*Description: Logger phase 2. Implementing with chain of responsibility. 
*Creating an array of structs.
*The struct contain a string and two function pointer: a comprasion function and an operation function.
*For each new input from the user go through the array and activate the appropriate operation function.
*Author: Noa Efrati
*Reviewer: Oryan Shimoni
*Date: 7/11/20
*Infinity Labs OL97
*******************************************************************************************************************************/


#include <stdio.h>/*printf, scanf, fgetc, fgets, fputc, fputs, fopen, fclose, remove*/
#include <string.h>/*strncmp*/
#include <stdio_ext.h>/*__fpurge*/
#include <stdlib.h>/*exit*/

struct logger{	
	char *string;
	int (*cmp)(char *, char *);
	void (*opt)(char *, char *);
};
typedef struct logger Logger;

/*CompareStrings compare between two inputs*/
int CompareStrings(char *usr_input, char *special_input);

/*RemoveFile removes the current file that open*/
void RemoveFile(char *file_name, char *input);

/*CountLines count lines, and print it*/
void CountLines(char *file_name, char *input);

/*AddToBginning put the user's input at the beginning of the file*/
void AddToBeginning(char *file_name, char *input);

/*ExitProgram finishes and exits the program*/
void ExitProgram(char *file_name, char *input);

/*AddToEnd adds user input to the end of the file*/
void AddToEnd(char *file_name, char *input);

#define MAX 100

int main()
{
	FILE *f_ptr = NULL;
	char file_name[10] = " ";
	char usr_input[MAX] = " ";
	int index = 0;
	int special_input = 0;/*A flag indicating whether the selected action is special or not.*/
	
	/*Init logger array*/
	Logger logger[5] = {
		{"-remove\n", CompareStrings, RemoveFile},
		{"-count\n", CompareStrings, CountLines},
		{"-exit\n", CompareStrings, ExitProgram},
		{"<", CompareStrings, AddToBeginning},
		{NULL, NULL, AddToEnd},
	        };
		
	printf("Enter a file name: ");
	scanf("%s",file_name);
	f_ptr = fopen(file_name, "w+");/*Opening new file*/
	
	if (f_ptr == NULL)
	{
		printf("Error while oppening the file");
	}
	
	fclose(f_ptr);
	__fpurge(stdin);/*Clean buffer*/
	
	printf("Choose your next operation: \n");
	printf("Enter -remove to remove your file.\nEnter -count to count lines in your file.\n"); 
	printf("Enter -exit to exit the program.\nEnter < before your input add the text to the top of your file.\n");	
	printf("***********************************************************************************************************\n");
	printf("Choose your operation: enter up to 100 characters, enter -exit to end the program.\n");
	
	fgets(usr_input, MAX, stdin);			
		
	while (logger[2].cmp(logger[2].string, usr_input) != 1)/*The loop ran as long as the user did not type "-exit".*/
	{	
		special_input = 0;
				
		for (index = 0; index < 4; index++)
		{
			if (logger[index].cmp(usr_input, logger[index].string) == 1)
			{
				special_input = 1;
				logger[index].opt(file_name, usr_input);
				break;
			}
		}
		
		/*If the user wants to insert input at the end of the file*/
		if (special_input == 0)
		{
			logger[4].opt(file_name, usr_input);
		}

		printf("Choose your next operation: enter up to 100 characters, enter -exit to end the program.\n");
		
		__fpurge(stdin);/*Clean buffer*/
		fgets(usr_input, MAX, stdin);	
		
	}
		
	return 0;
}

int CompareStrings(char *usr_input, char *special_input)
{
	if (strncmp(usr_input, special_input, strlen(special_input)) == 0)
	{
		return 1;
	}
	return -1;
}

void RemoveFile(char *file_name, char *input)
{
	int removal_success = remove(file_name);
	(void)input;
	
	if( removal_success == 0)
	{
		printf("File %s removal was successful\n", file_name);
	} 
	else
	{
		printf("File %s removal was not successful\n", file_name);
	}
}

void CountLines(char *file_name, char *input)
{
	FILE *f_ptr = NULL;
	char char_storage = ' ';
	int count_lines = 0;
	(void)input;
	
	f_ptr = fopen(file_name, "r");
	
	if (f_ptr == NULL)
	{
		printf("Error while oppening the file\n");
		exit(0);
	}
	
	for (char_storage = fgetc(f_ptr); char_storage != EOF; char_storage = fgetc(f_ptr))
	{
		if (char_storage == '\n')
		{
			count_lines = count_lines + 1;
		}
	}
	fclose(f_ptr);
	
	printf("Number of lines in the file : %s is :%d\n", file_name, count_lines);
}

void AddToBeginning(char *file_name, char *input)
{
	FILE *original_file = fopen(file_name, "r");
	FILE *tmp_file= fopen("copy_file.txt", "w");
	char char_storage = ' ';
	
	
	if (original_file == NULL || tmp_file == NULL)
	{
		printf("Error while opening files");
	}
	
	/*Copies the contents of the original file into a temporary file*/	
	for (char_storage = fgetc(original_file); char_storage != EOF; char_storage = fgetc(original_file))
	{
		fputc(char_storage, tmp_file);/*Putting a char by char*/
	}
	
	fclose(original_file);
	fclose(tmp_file);
	remove(file_name);
	
	original_file = fopen(file_name, "a+");
	tmp_file= fopen("copy_file.txt", "r");
	fputs(input + 1, original_file);/*Puts the string input into the file without the char '<' .*/
	
	for (char_storage = fgetc(tmp_file); char_storage != EOF; char_storage = fgetc(tmp_file))
	{
		fputc(char_storage, original_file);/*Copies the contents of the copied file back to the original file */
	}
	
	fclose(original_file);
	fclose(tmp_file);
	remove("copy_file.txt");
}

void ExitProgram(char *file_name, char *input)
{
	(void)file_name;
	(void)input;
	printf("Exit the program.\n");
	exit(0);	
}

void AddToEnd(char *file_name, char *input)
{
	FILE *f_ptr = fopen(file_name, "a+");
	
	if (f_ptr == NULL)
	{
		printf("Error while opening the file %s.",file_name);
	}
	fputs(input, f_ptr);
	fclose(f_ptr);
}
