#include <stdio.h>

//const int j = 3;
int main()
{
   
   const int i = 3;
    int *ip = (int *)&i;
    *ip = 8;
	int x ;
	scanf("%d", &x);
    int arr[x];
    printf("%d %d\n", i, *ip);
	printf("%d\n", arr[i]);

    return 0;
}