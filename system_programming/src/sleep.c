#include <stddef.h> /*NULL*/
#include <string.h> /* strcpy */
#include <stdio.h>
#include <unistd.h>

int Normal(void)
{
	printf("I executed this....\n");
	return 0;
}

int DivideByZero()
{
	int i = 10;
	printf("Execute failure in\n");
	for (i = 10; i >= 0; --i)
	{
		printf("%d\n", 10/i);
	}
	return 0;
}

int AccessMemoryViolation(void)
{
	char* str = "asdf";
	printf("Execute memory violation\n");
	str[0] = 45;
	return 0;
}

int main(int argc, char* argv[])
{
	/*char test[100] ;*/
	
	/*strcpy(test, argv[1]);
	
	switch(*test)
	{
		case '0':
			status = DivideByZero();
			break;
		case '1':
			status = AccessMemoryViolation();
			break;
		default:
			status = Normal();
	}
	*/
	if (2 != argc)
	{
		return 1;
	}

	sleep(*argv[1] - '0');
	printf("i am a child and my pid is %d and i have sleeped for %d seconds\n",
													getpid(), *argv[1] - '0');
	return ( *argv[1] - '0');
}
