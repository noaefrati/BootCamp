#include <stdio.h>

void foo();
void foo(unsigned char c);
void foo(char c);
void foo(int a, int b);

int main()
{
	int a = 1;
	char c = 'a';
	unsigned char ch = 'w';
	
	//foo(NULL);
	foo(ch);
	foo(c);
	foo(a, a);
	return 0;
}
void foo(unsigned char c)
{
	printf("11c = %c\n", c);
}
void foo(char c)
{
	printf("c = %c\n", c);
}

void foo(int a, int b)
{
	printf("a = %d\n",a);
}

void foo()
{
	printf("!!\n");
}
