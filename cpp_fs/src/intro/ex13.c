#include <stdio.h>

  const int i = 3;
int main()
{
   
 
     /*int arr[i];*/
    int *ip = (int *)&i;
    *ip = 5;
   
    printf("%d %d\n", i, *ip);
	/*printf("%d\n", arr[i]);*/

    return 0;
}