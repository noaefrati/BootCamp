#include <stdio.h>
#include <assert.h>

long *IntsToLongsArr(int *arr, size_t size)
{
	long *longs = NULL;
	size_t i = 0, j = 0;
	
	assert(arr);
	
	longs = (long *)arr;
	
	for (i = 0, j = 1; i < size/2 && j < size; ++i, j += 2)
	{
		longs[i] = (long)arr[j] + (long)arr[j - 1];
	}
	
	return longs;
}
int main()
{
	int arr[6] = {1, 6, 456, -3, 8, 12};
	long *ans = NULL;
	size_t i = 0;
	
	ans = IntsToLongsArr(arr, 6);
	
	
	for (i = 0; i < 3; ++i)
	{
		printf("%ld, ", ans[i]);
	}
	printf("\n");
	return 0;
}
