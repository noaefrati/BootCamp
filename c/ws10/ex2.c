/*************************************************************************************/
/*Author: Noa Efrati                                                                 */
/*Reviewer: Roi Peretz                                                               */
/*Date: 15/11/2020                                                                   */
/*Infinity Labs OL97                                                                 */  
/*                                                                                   */
/*DESCRIPTION:                                                                       */
/*    Printing the letters common to the first two strings,                          */
/*    not the third string. Implementation by the LUT table.                         */
/*    When there is a first pass over the first string, mark with a special mark     */
/*    for the characters that appear in the first string. Then go over the third     */
/*    string and also for it mark with a special mark the characters that            */
/*    appear in it.                                                                  */
/*    Final step: pass the second string If you come across a character with the     */
/*    special marking of the first string and also the same character is not         */
/*    contained in the dynamic array, then print it.                                 */
/*                                                                                   */
/*************************************************************************************/

/*printf*/
#include <stdio.h>

/*malloc*/
#include <stdlib.h>

/*strchr*/
#include <string.h>

/*Print only common letters (with norehearsals) of s1 and s2*/
int PrintLettersAppearIn2Arrays(char s1[], char s2[], char s3[]);

int main()
{
	char s1[] = "abbedor";
	char s2[] = "abbedft";
	char s3[] = "aaakopf";
	PrintLettersAppearIn2Arrays(s1, s2, s3);
	
	return (0);
}
int PrintLettersAppearIn2Arrays(char s1[], char s2[], char s3[])
{
	int lut[256] = {0};
	
	char *s1_runner = s1;
	char *s2_runner = s2;
	char *s3_runner = s3;
	char *runner_common_letters = NULL;	
	char *common_letters = (char *)malloc(0);
	
	if (NULL == common_letters)
	{
		return (-1);
	}
	
	runner_common_letters = common_letters;
	
	
	while ('\0' != *s1_runner)
	{
		
		lut[(int)*s1_runner] = 1;
		++s1_runner;
	}
	
	while ('\0' != *s3_runner)
	{
		if (lut[(int)*s3_runner] == 0 || lut[(int)*s3_runner] ==1)
		{
		lut[(int)*s3_runner] = 3;
		}
		++s3_runner;
	}
	
	printf("Common letters : ");
	
	while ('\0' != *s2_runner)
	{	
		if (1 == lut[(int)*s2_runner])
		{
			if (NULL == strchr(common_letters, *s2_runner))
			{
				char *tmp = (char *) realloc(common_letters, 1);
				
				/*Check if the realloc was successful*/
				if (NULL == tmp)
				{
					return (-1);
				}
			
				common_letters = tmp;			
				*runner_common_letters = *s2_runner;
				++runner_common_letters;
				printf("%c ",*s2_runner);
			}
		}
		
		++s2_runner;
	}
	
	free(common_letters);
	common_letters = NULL;
	printf("\n");
	return (0);	
}

