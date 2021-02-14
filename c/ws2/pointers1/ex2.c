#include<stdio.h>


void CopyArr(int *arr, int size, int *copied);
void PrintArr(int *arr, int size);

int main()
{	
	int original[20];
	int copied[20];
	int size;
	int i;
	
	 printf("Enter number of elements in array\n");
         scanf("%d", &size);
 
        printf("Enter %d elements\n", size);
 
	for( i = 0; i < size ;i++)
	{	printf("Enter %d vriable : ",i);
		scanf("%d",&original[i]);
	}
	
	CopyArr(original, size, copied);
	printf("original arr: ");
	PrintArr(original, size);
	printf("copied arr: ");
	PrintArr(copied, size);
	
	return 0;
}

void CopyArr(int *arr, int size, int *copied)
{
	int i;
	for(i = 0; i < size; i++)
		copied[i] = *(arr+i);
	
}

void PrintArr(int *arr, int size)
{
	int i;
	
	printf("[ ");
	for(i = 0; i <size; i++)
		printf("%d ", *(arr+i));
	printf("]\n");
}
