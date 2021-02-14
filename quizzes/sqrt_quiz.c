/******************************************************************************

                  Implementation of the function sqrt

*******************************************************************************/

#include <stdio.h>      /* printf*/

double Sqrt(double num)
{
    int start = 0, end = num, i = 0;
    double ans = 0;
    double fractional_part = 0.1;
    
    while (start <= end)
    {
        double middle = (end + start)/2;
        if (middle * middle == num)
        {
            ans = middle;
            break;
        }
        if (middle * middle > num)
        {
            end = middle - 1;
        }
        else
        {
            start = middle + 1;
            ans = middle;
        }
    }
    
   for (i = 0; 6 > i; ++i)
    {
        while (ans * ans <= num)
        {
            ans += fractional_part;
        }
        
        /* when ans^2 is greater then num, than decrease ans*/
        ans -= fractional_part;
        
        /*resize fractional_part to get a closer relative accuracy of
                                                            the floating point*/
        fractional_part /= 10;
    }
    
    return ans;
}

int main()
{
    printf("sqrt(64) =  %f\n", Sqrt(64));
    printf("sqrt(9.5) = %f\n", Sqrt(9.5));
	printf("sqrt(122) = %f\n", Sqrt(122));
	printf("sqrt(-25) = %f\n", Sqrt(-25));
    return 0;
}

