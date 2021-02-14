#include "g.h"
#include <stdio.h>

void Foo(void);

int main(void)
{
	int g_s = 3;
	printf("%d\n", g_s);
	Foo();
	printf("%d\n", g_s);
	return 0;
}
