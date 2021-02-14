#include <stdio.h>
#include <stdlib.h>

int Josephus(int a[], int n);
int *InitializeArr(int n);

/*This method solves the Josephoff problem by a free list method*/

int main()
{
	
	int soldiers = 100;
	int *a = NULL;
	a =  InitializeArr(soldiers);
	
	printf("Number of soliders: %d \n", soldiers);
	printf("The man in the place %d is the last man left .\n", Josephus(a, soldiers));
	printf("Enter number of soliders: ");
	scanf("%d", &soldiers);
	a =  InitializeArr(soldiers);
	printf("The man in the place %d is the last man left .\n", Josephus(a, soldiers));
	free(a);
	
	return 0;
}

int Josephus(int a[], int n)
{		
	int current = 0;
	int next;
	
	if ( n == 0)
	{
		return 0;
	}
	
	while (a[current] != current)
	{
		next = a[current];
		a[current] = a[next];
		current = next;	
	}
	
	return current + 1; 
}

int *InitializeArr(int n)
{
	int *a = (int *)malloc(n * sizeof(int));
	int i;
	
	for (i = 0; i < n ; i++)
	{
		a[i] = i + 1;
	}
	
	a[i - 1] = 0;
	
	return a;
}

