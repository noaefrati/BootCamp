/*************************************************************************************/
/*Author: Noa Efrati                                                                 */
/*Reviewer: Roi Peretz                                                               */
/*Date: 15/11/2020                                                                   */
/*Infinity Labs OL97                                                                 */  
/*                                                                                   */
/*DESCRIPTION: implementation of little and big endian.                              */
/*************************************************************************************/

/*printf*/
#include <stdio.h>

/*macro if system is big endian*/
#define IS_BIG_ENDIAN (*(int *)"\0\0\01" == 0x31)

int IsLittleEndian(int * ptr);
int main()
{
	
	int a = 1;
	int is_little = IsLittleEndian(&a);
	int variable = (*(int *) "\0\0\01");
	if (1 == is_little)
	{
		printf("The system is little endian\n");
	}
	else
	{
		printf("The system is big endian\n");
	}
	
	printf("variable = %d\n",variable);
	
	if (1 == IS_BIG_ENDIAN)
	{
		printf("macro: the system is big endian.\n");
	}
	else
	{
		printf("the system is little endian.\n");
	}
	return (0);
}
int IsLittleEndian(int * ptr)
{
	char *char_ptr= (char *)ptr;
	return (*char_ptr== 1);
	
}
