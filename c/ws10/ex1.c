/*************************************************************************************/
/*Author: Noa Efrati                                                                 */
/*Reviewer: Roi Peretz                                                               */
/*Date: 15/11/2020                                                                   */
/*Infinity Labs OL97                                                                 */  
/*DESCRIPTION: implementation atoi() and itoa()                                      */
/*                                                                                   */
/*************************************************************************************/

#include <string.h> /*strchr*/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*atoi*/
#include <ctype.h> /*isspace*/


#define BASE 10
#define STRING_SIZE 50

char symbols10[] = "0123456789";
char symbols36[]="0123456789abcdefghijklmnopqrstuvwxyz";

/*convert a string to an integer (base 10)*/
int Atoi10(const char *s);

/*convert a string to integer up to base 36*/
int Atoi36(const char *s, int base);

/*convert an integer in base 10 to a string */
char *Itoa10(int value, char *s);

/*convert an integer up to base 36 to a string*/
char *Itoa36(int value, char *s, int base); 

/*test atoi functions*/
void TestAtoi();

int main()
{
	int n = -543;
	char s1[] = "-124";
	char s2[STRING_SIZE];
	char s3[] ="100";
	

	printf("Itoa36(-123, s2, 36): s= %s\n", Itoa36(123,s2, 36));
	printf("Itoa10(-543, s2) s2= %s\n", Itoa10(n,s2));
	
	 TestAtoi();
	
	
	return 0;
}
int Atoi10(const char *s)
{
	int result = 0;
	char *s_runner = (char *)s;
	int is_negative = 0;
	int to_add = 0;
	
	if ('-' == *s_runner)
	{
		is_negative = 1;
		++s_runner;
		
	}
	
	/*if the string has a white space in the begining, skip it*/
	if (0 != isspace(*s_runner))
	{
		++s_runner;
	}
	
	while (('\0' != *s_runner) && (0 == isspace(*s_runner)))
	{		
		to_add = strchr(symbols10, *s_runner) -symbols10;
		result = to_add + (result * BASE);
		++s_runner;
	}
	
	if (1 == is_negative)
	{
		result *= -1;
	}
	
	return result;
}
char *Itoa10(int value, char *s)
{
	
	char *s_runner = (char *)s;
	int num_of_digit = 0;
	int val = value;
	int res = 0;
	
	if (NULL == s)
	{
		return NULL; 
	}
	
	if (0 > value)
	{
		value *= -1;
		val = value;
		*s_runner = '-';
		++s_runner;
	}
	
	while (0 < val)
	{
		val/=BASE;
		++num_of_digit;
	}
	
	*(s_runner + num_of_digit) = '\0';
	s_runner = s_runner + num_of_digit - 1;
	
	for (res = value % BASE; num_of_digit > 0; --num_of_digit, --s_runner, res = value % BASE)
	{	
		
		*s_runner = symbols10[res];
		value = value / BASE;
	}
	
	return s;
}
int Atoi36(const char *s, int base)
{
	int result = 0;
	char *s_runner = (char *)s;
	int is_negative = 0;
	int to_add = 0;
	
	if ('-' == *s_runner)
	{
		is_negative = 1;
		++s_runner;
		
	}
	
	/*if the string has a white space in the begining, skip it*/
	if (0 != isspace(*s_runner))
	{
		++s_runner;
	}
	
	while (('\0' != *s_runner) && (0 == isspace(*s_runner)))
	{		
		to_add = strchr(symbols36, *s_runner) -symbols36;
		result = to_add + (result * base);
		++s_runner;
	}
	
	if (1 == is_negative)
	{
		result *= -1;
	}
	
	return result;
}
char *Itoa36(int value, char *s, int base)
{
	
	char *s_runner = (char *)s;
	int num_of_digit = 0;
	int val = value;
	int res = 0;
	
	if (NULL == s)
	{
		return NULL; 
	}
	
	if (0 > value)
	{
		value *= -1;
		val = value;
		*s_runner = '-';
		++s_runner;
	}
	
	while (0 < val)
	{
		val/=base;
		++num_of_digit;
	}
	
	*(s_runner + num_of_digit) = '\0';
	s_runner = s_runner + num_of_digit - 1;
	
	for (res = value % base; num_of_digit > 0; --num_of_digit, --s_runner, res = value % base)
	{	
		
		*s_runner = symbols36[res];
		value = value / base;
	}
	
	return s;
}
void TestAtoi()
{
	
	printf("atoi(-124) =%d\n", atoi("-124"));
	printf("Atoi10(s1 = -124) = %d\n", Atoi10("-124"));
	printf("atoi(1245) =%d\n", atoi("1245"));
	printf("Atoi10(1245) = %d\n", Atoi10("1245"));
	printf("Atoi36(123df,36) : %d\n", Atoi36("123df", 36));
	printf("Atoi36(100,36) : %d\n", Atoi36("100", 36));
		
	
}
