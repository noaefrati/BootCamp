/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
static int counter = 100;

int BingoImpl2(int arr[100])
{
    int i = 0, temp = 0;
    int rand_num = 0, ans = 0;
    static int init = 1;
    
    if (1 == init)
    {
    	 for (i = 0; i < 100; ++i)
        {
            arr[i] = i + 1;
        }
        init = 0;
    }
   
    if (counter == 0)
    {
        for (i = 0; i< 100; ++i)
        {
            arr[i] = i + 1;
        }
        counter = 0;
    }
    
    rand_num = rand() % (counter);
   	ans	= arr[rand_num];
    
   temp =  arr[rand_num];
   arr[rand_num] = arr[counter-1];
   arr[counter-1] = temp;
   --counter;
    
   return ans;
}

int Bingo(int smaller, int bigger)
{
    static int arr[100] = {0};
    return BingoImpl2(arr);
}
int main()
{
   int i = 0, ans = 0;
   int arr[100] = {0};
    while ( i < 100)
    {
         ans = Bingo(1, 100);
         printf("arr[%d] = %d\n",ans -1, ans);
         ++i;
    }
   
    return 0;
}

