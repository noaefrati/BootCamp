#include <stdio.h>


int FindAppearsOnceInArrOfPairs(int arr[], size_t len)
{
    size_t i = 0 ;
    int appears_once = 0;
    
    for (; len > i; ++i)
    {
       appears_once ^= arr[i]; 
    }
    return appears_once;
}
int main()
{
    int a[3] = {1, 5, 1};
    int b[9] = {5, 7, 8, 9, 3, 8, 3, 5, 9};
    int c[9] = {1, 3, 4, 2, 2, 4, 4, 3, 1};
	int d[4] = {-1, 3, -1, 3};
	
	printf("FindAppearsOnceInArrOfPairs {1, 5, 1} : %d\n",
	                                         FindAppearsOnceInArrOfPairs(a, 3));
	
	printf("\nFindAppearsOnceInArrOfPairs {5, 7, 8, 9, 3, 8, 3, 5, 9} : %d\n",
	                                         FindAppearsOnceInArrOfPairs(b, 9));
	
	printf("\nFindAppearsOnceInArrOfPairs {1, 3, 4, 2, 2, 4, 4, 3, 1} : %d\n",
	                                         FindAppearsOnceInArrOfPairs(c, 9));
	
	printf("\nFindAppearsOnceInArrOfPairs {-1, 3, -1, 3} : %d\n",
	                                         FindAppearsOnceInArrOfPairs(d, 4));
	return 0;
}
