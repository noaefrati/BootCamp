#include <stdio.h>
#include <stdlib.h>

int *MaxSubArr(int *arr, size_t size)
{
	int *sum_arr = NULL, *ans_arr = NULL;
	size_t i =0, max_ind = 0;
	int len = 0;
	
	sum_arr = (int *) calloc(size, sizeof(int));
	if (sum_arr == NULL)
	{
		return NULL;
	}
	
	if (arr[0] > 0)
	{
		sum_arr[0] =arr[0];
	}
	
	for (i = 1; i < size; ++i)
	{
		if (sum_arr[i -1] == 0 && arr[i] > 0)
		{
			sum_arr[i] = arr[i];
		}
		else
		{
			if (sum_arr[i -1] != 0 && sum_arr[i-1] + arr[i] > 0)
			{
				sum_arr[i] = sum_arr[i-1] + arr[i];
				++len;
			}
		}
		
		if (sum_arr[i] > sum_arr[max_ind])
		{
			printf("sum[%lu] = %d\n", i, sum_arr[i]);
			max_ind = i;
			len = 1;
		}
	}
	ans_arr = (int *)malloc(sizeof(int) * 3);
	ans_arr[0] = sum_arr[max_ind];
	ans_arr[1] = max_ind - len;
	ans_arr[2] = max_ind;
	
	free(sum_arr);
	return ans_arr;
}
int main()
{
	int arr[9] = {-2,1,-3,4,-1,2,1,-5,4};
	int *ans = MaxSubArr(arr, 9);
	
	printf("sum : %d, from : %d, to: %d\n", ans[0], ans[1], ans[2]);
	
	free(ans);
	return 0; 
}
