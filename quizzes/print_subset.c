#include <stdio.h>
/*
    i < 2 ^ len = > i < 8, means last iteration of i is i = 7
    
   iter 1 :i = 000 = 0
   iter 2: i = 001 = 1
   iter 3: i = 010 = 2
   iter 4: i = 011 = 3
   iter 5: i = 100 = 4
   iter 6: i = 101 = 5
   iter 7: i = 110 = 6
   iter 8: i = 111 = 7
   
   in every iteration ask : if i & 2^j is positive
            
            001
   if 000 & 2^0 > 0 ? no
   if 000 & 2^1 > 0 ? no
   if 000 & 2^2 > 0 ? no
            
            001
   if 001 & 2^0 > 0  yes print arr[j = 0] = 1
   if 001 & 010 > 0  no
   if 001 & 100 > 0  no
   
   if 010 & 001 > 0 no
   if 010 & 010 > 0 yes print arr[j = 1] 2
   if 010 & 100 > 0 no
   
   if 011 & 001 > 0 yes print arr[j = 0] = 1
   if 011 & 010 > 0 yes print arr[j = 1] = 2
   if 011 & 100 > 0 no
   
   if 100 & 001 > 0 no
   if 100 & 010 > 0 no
   if 100 & 100 > 0 yes print arr[j = 2] = 3
   
   if 101 & 001 > 0 yes print arr[j = 0] = 1
   if 101 & 010 > 0 no
   if 101 & 100 > 0 yes print arr[j = 2] = 3
   
   if 110 & 001 > 0 no
   if 110 & 010 > 0 yes print arr[j = 1] = 2
   if 110 & 100 > 0 yes print arr[j = 2] = 3
   
   if 111 & 001 > 0 yes print arr[j = 0] = 1
   if 111 & 010 > 0 yes print arr[j = 1] = 2
   if 111 & 100 > 0 yes print arr[j = 2] = 3
   
*/
void PrintSubSet(int arr[], int len)
{
   int i=0, j = 0;
   
    for (i = 0; i < (1 << len); ++i)
    {
        for (j = 0; j < len; ++j)
        {
            if (i & (1 << j))
            {
                printf("%d", arr[j]);
            }
        }
        printf ("\n");
    }
}
int main()
{
    int arr[3] = {1, 2, 3};
    int arr2[2] = {1, 2};
    
    PrintSubSet(arr, 3);
    PrintSubSet(arr2, 2);
    
    return 0;
}

