/******************************************************************************************************************************
*Description: A program that asks the user to enter strings. After implementing loggar phase 2 (with chain of responsibility), 
*using enum as the return type of the operation functions.
*Author: Noa Efrati
*Reviewer: Oryan Shimoni
*Date: 7/11/20
*Infinity Labs OL97
*******************************************************************************************************************************/

/*printf, scanf, fgetc, fgets, fputc, fputs, fopen, fclose, remove*/
#include <stdio.h>	

/*strncmp*/	
#include <string.h>	

/*__fpurge*/	
#include <stdio_ext.h>

/*exit()*/	
#include <stdlib.h>		

typedef enum
{	FAILURE, 
	SUCCESS
};return_status;

struct logger{	
	char *string;
	int (*is_match)(char *, char *);
	 return_status (*opt)(char *, char *);
};
typedef struct logger Logger;

/*CompareStrings compare between two inputs*/
int CompareStrings(char *usr_input, char *special_input);

/*RemoveFile removes the current file that open*/
return_status RemoveFile(char *file_name, char *input);

/*CountLines count lines, and print it*/
return_status CountLines(char *file_name, char *input);

/*AddToBginning put the user's input at the beginning of the file*/
return_status AddToBeginning(char *file_name, char *input);

/*ExitProgram finishes and exits the program*/
return_status ExitProgram(char *file_name, char *input);

/*AddToEnd adds user input to the end of the file*/
return_status AddToEnd(char *file_name, char *input);

/*max charachters in a line*/
#define MAX 100 

int main(int argc, char *argv[])
{
	FILE *f_ptr = NULL;
	char *file_name = " ";
	char usr_input[MAX] = " ";
	int index = 0;
	int is_special_input = 0;/*A flag indicating whether the selected action is special or not.*/
	int is_close = 0;
	
	/*Init logger array*/
	Logger logger[5] = {
		{"-remove\n", CompareStrings, RemoveFile},
		{"-count\n", CompareStrings, CountLines},
		{"-exit\n", CompareStrings, ExitProgram},
		{"< ", CompareStrings, AddToBeginning},
		{NULL, NULL, AddToEnd},
	        };
		
	if(argc < 2)
	{
		printf("Usage : ./a.out <filename>", argv[1]);
		return -1;
          }	
       
          file_name = argv[1];
          f_ptr = fopen(file_name, "w+");/*Opening new file*/
	
	if (f_ptr == NULL)
	{
		printf("Error while oppening the file");
		return -1;
	}
		
	is_close = fclose(f_ptr);
	if (0 != is_close)
	{
		printf("Error while closing the file");
		return -1;
	}
	__fpurge(stdin);/*Clean buffer*/
	
	printf("Choose your next operation: \n");
	printf("Enter -remove to remove your file.\nEnter -count to count lines in your file.\n"); 
	printf("Enter -exit to exit the program.\nEnter < before your input add the text to the top of your file.\n");	
	printf("***********************************************************************************************************\n");
	printf("Choose your operation: enter up to 100 characters, enter -exit to end the program.\n");
	fgets(usr_input, MAX, stdin);			
		
	while (1 != logger[2].cmp(logger[2].string, usr_input))/*The loop ran as long as the user did not type "-exit".*/
	{	
		is_special_input = 0;
				
		for (index = 0; index < 4; ++index)
		{
			if (1 == logger[index].is_match(usr_input, logger[index].string))
			{
				if(SUCCESS == logger[index].opt(file_name, usr_input))
				{
					is_special_input = 1;
					printf("Operation completed successfully\n");
					break;
				}
				else
				{
					printf("Operation failed\n");
					ExitProgram(file_name, "FAILURE");
				}
			}
		}
		
		/*If the user wants to insert input at the end of the file*/
		if (0 == is_special_input )
		{
			if (SUCCESS == logger[4].opt(file_name, usr_input))
			{
				printf("Operation completed successfully\n");					
			}
			else
			{
				printf("Operation failed\n");
				ExitProgram(file_name, "failure");
			}		
		}

		printf("Choose your next operation: enter up to 100 characters, enter -exit to end the program.\n");
		
		__fpurge(stdin);/*Clean buffer*/
		fgets(usr_input, MAX, stdin);			
	}
		
	return 0;
}

int CompareStrings(char *usr_input, char *special_input)
{
	if (0 == strncmp(usr_input, special_input, strlen(special_input)))
	{
		return 1;
	}
	return -1;
}

return_status RemoveFile(char *file_name, char *input)
{
	int removal_success = remove(file_name);
	(void)input;
	
	if (0 == removal_success)
	{
		printf("File %s removal was successful\n", file_name);
		return (SUCCESS);
	} 
	
	printf("File %s removal was not successful\n", file_name);
	return (FAILURE);
}

return_status CountLines(char *file_name, char *input)
{
	FILE *f_ptr = NULL;
	char char_storage = ' ';
	int count_lines = -1;
	int is_close = 0;
	(void)input;
	
	f_ptr = fopen(file_name, "r");
	
	if (NULL == f_ptr)
	{
		printf("Error while oppening the file\n");
		return (FAILURE);
	}

	
	for (char_storage = fgetc(f_ptr); EOF != char_storage; char_storage = fgetc(f_ptr))
	{
		if (char_storage == '\n')
		{
			count_lines = count_lines + 1;
		}
	}
	
	is_close = fclose(f_ptr);
	
	if (0 != is_close)
	{
		printf("Error while closing the file");
		return (FAILURE);
	}	
	printf("Number of lines in the file : %s. is :%d\n", file_name, count_lines);
	return (SUCCESS);
}

return_status AddToBeginning(char *file_name, char *input)
{
	FILE *original_file = fopen(file_name, "r");
	FILE *tmp_file= fopen("copy_file.txt", "w");
	char char_storage = ' ';
	int is_close1 = 0, is_close2 = 0;
	
	if (NULL == original_file || NULL == tmp_file)
	{
		printf("Error while opening files\n");
		return (FAILURE);
	}
	
	/*Copies the contents of the original file into a temporary file*/	
	for (char_storage = fgetc(original_file); EOF != char_storage; char_storage = fgetc(original_file))
	{
		fputc(char_storage, tmp_file);/*Putting a char by char*/
	}
	
	is_close1 = fclose(original_file);
	is_close2 = fclose(tmp_file);
	
	if (0 != is_close1 || 0 != is_close2)
	{
		printf("Error while closing the file");
		return (FAILURE);
	}
	remove(file_name);
	
	original_file = fopen(file_name, "a+");
	tmp_file= fopen("copy_file.txt", "r");
	fputs(input + 2, original_file);/*Puts the string input into the file without the char '<' .*/
	
	for (char_storage = fgetc(tmp_file); EOF != char_storage; char_storage = fgetc(tmp_file))
	{
		fputc(char_storage, original_file);/*Copies the contents of the copied file back to the original file */
	}
	
	is_close1 = fclose(original_file);
	is_close2 = fclose(tmp_file);
	
	if (0 != is_close1 || 0 != is_close2)
	{
		printf("Error while closing the file");
		return (FAILURE);
	}
	remove("copy_file.txt");
	return (SUCCESS);
}

return_status ExitProgram(char *file_name, char *input)
{
	printf("Exit the program.\n");
	(void)file_name;
	(void)input;
	return (SUCCESS);
		
}

return_status AddToEnd(char *file_name, char *input)
{
	FILE *f_ptr = fopen(file_name, "a+");
	int is_close = 0;
	if (f_ptr == NULL)
	{
		printf("Error while opening the file %s", file_name);
		return (FAILURE);
	}
	fputs(input, f_ptr);
	is_close = fclose(f_ptr);
	
	if (0 != is_close)
	{
		printf("Error while closing the file");
		return (FAILURE);
	}
	return (SUCCESS);
}
