/************************************************************************************************************************************
*Author: Noa Efrati
*Reviewer: Carolina Kats
*Date: 8/11/20
*Description: Bitwise learning.
            		
*************************************************************************************************************************************/
/*printf*/
#include <stdio.h>

/*return the result of x*(2^y)*/
long Pow2 (unsigned int x, unsigned int y);

/*Checks if the receive number is a power of 2, using a loop*/
int IsPowerOf2Loop(unsigned int x);

/*Checks if the receive number is a power of 2, without a loop*/
int IsPowerOf2(unsigned int x);

/*add 1 to a given number, and return the result*/
unsigned int Add1(unsigned int x);

/*prints only number with 3 bits*/
void OnlyPrint3(unsigned int *arr, int size);

/*revese a given number using a loop*/
unsigned int ByteMirrorLoop(unsigned int x);

/*revese a given number without using a loop (using LUT)*/
unsigned int ByteMirrorNoLoop(unsigned int x);

/*check if the bits 6 and 2 is on if it is return true, else return false*/
unsigned char CheckBitsSixAndTwo(unsigned int x);

/*check if the bits 6 or 2 is on if it is return true, else return false*/
unsigned char CheckBitsSixOrTwo(unsigned int x);

/*swap between bit 3 and bit 5, and return the new number*/
unsigned int SwapBit3AndBit5(unsigned int x);

/*receives n ansigned int and returns the closest number that is divisible by 16 without a reminder*/
unsigned int Get16(unsigned int x);

/*swaps 2 variables without using a third variable*/
void Swap(unsigned int x, unsigned int y);

/*counts the number of set bits in an integer- using a loop*/
int CountSetBitsLoop(int x);

/*counts the number of set bits in an integer- without using a loop*/
int CountSetBitsNoLoop(int x);

/*a program that receives a flot from the user and prints its bits*/
void FloatAnalysis(float *x);

/*print true when the fun gets 1 or false when gets 0 */
void PrintTrueOrFalse(unsigned char a);

int main()
{
	unsigned int x = 53; 
	unsigned int y = 66; 
	unsigned int z = 16; 
	unsigned char ans_check_bits1 = CheckBitsSixAndTwo(x);
	unsigned char ans_check_bits2 =CheckBitsSixAndTwo(y);
	unsigned int arr[] = {8, 9, 10, 5, 11, 13, 4} ;
	int size = 7;
	float n = 3.5;
	 
	
	printf("\n-------------------------- Pow2---------------------------\n");
	printf("\n 3 *(2^4) = %lu",Pow2 (3, 4));
	
	printf("\n-------------------------- IsPowerOf2Loop---------------------------\n");
	printf("%u is power of 2 ?  %d\n", z, IsPowerOf2Loop(z));
	
	printf("\n-------------------------- IsPowerOf2---------------------------\n");
	printf("%u is power of 2 without a loop. ans:  %d\n", z, IsPowerOf2(z));
	
	printf("\n-------------------------- Add1----------------------------\n");
	printf("add1 to %u + 1 = %u", x,Add1(x));
	printf("\n--------------------------- OnlyPrint3----------------------\n");
	OnlyPrint3(arr, size);
	
	printf("---------------------------ByteMirrorLoop----------------------\n");
	printf("before : %u, after reverse : %u\n", z, ByteMirrorLoop(z));
	
	printf("---------------------------ByteMirrorNoLoop----------------------\n");
	printf("before : %u, after reverse : %u\n", z, ByteMirrorNoLoop(z));
	
	printf("----------------------- CheckBitsSixAndTwo--------------------\n");
	printf("check bits 2 and 6 in %u, is = ", x);
	PrintTrueOrFalse(ans_check_bits1);
	printf("\ncheck bits 2 and 6 in %u, is = ", y);	
	PrintTrueOrFalse(ans_check_bits2);	
	
	printf("\n----------------------- CheckBitsSixOrTwo-------------------\n");
	ans_check_bits1 = CheckBitsSixOrTwo(x);
	ans_check_bits2 =CheckBitsSixOrTwo(y);
	printf("check bits 2 or 6 in %u, is = ", x);
	PrintTrueOrFalse(ans_check_bits1);
	printf("\ncheck bits 2 or 6 in %u, is = ", y);
	PrintTrueOrFalse(ans_check_bits2);
	
	printf("\n--------------------- SwapBit3AndBit5------------------------\n");	
	printf("swap between bits 3 and 5, before: %u, after : %u", x, SwapBit3AndBit5(x));
	printf("\ncheck bits 3 and 5, before: %u, after : %u", y,  SwapBit3AndBit5(y));	
	
	printf("\n---------------------------Get16---------------------------------\n");	
	printf("The closest number to %d is divisible by 16 without a reminder : %u\n", 33, Get16(33));
	printf("The closest number to %d is divisible by 16 without a reminder : %u\n", 17, Get16(17));
	printf("The closest number to %d is divisible by 16 without a reminder : %u\n", 22, Get16(22));	
	
	printf("\n-----------------------------Swap-----------------------------\n");
	printf("swaps two variable without using third variable: before : x = %u, y = %u \n", x, y);
	Swap(x, y);	
	
	printf("\n-----------------------------CountSetBitsLoop-----------------------------\n");	
	printf("counts the number of set bits in an integer : in %d, number of set bits: %d \n", -6, CountSetBitsLoop(-6));
	
	printf("\n-----------------------------CountSetBitsNoLoop-----------------------------\n");	
	printf("counts the number of set bits in an integer : in %d, number of set bits: %d \n", -6, CountSetBitsNoLoop(-6));
	
	
	printf("\n-----------------------------FloatAnalysis-----------------------------\n");	
	printf("Representation of %f in bits is :", n);
	FloatAnalysis(&n);
	return (0);
}
unsigned long Pow2 (unsigned int x, unsigned int y)
{
	unsigned long res = 1;
	res = res << y;
	return x * res;
}
int IsPowerOf2Loop(unsigned int x)
{
	unsigned int pow_2 = 1;
	int is_power_of_2 = 0;
	
	while (x > (pow_2 = pow_2 << 1))
	{
		/*empty*/
	}
	
	if (pow_2 == x)
	{
		is_power_of_2 = 1;
			
	}
	
	return (is_power_of_2);
}
int IsPowerOf2(unsigned int x)
{
	return (x && (!(x & (x - 1))));
}

unsigned int Add1(unsigned int x)
{
	unsigned m = 0;
	
	/*runs while x & m is not 0*/
	while (m & (x = x ^ m))
	{		
		m = m << 1;
	}
	
	return (x);
}

void OnlyPrint3(unsigned int *arr, int size)
{
	
	int i = 0;
	for (; size > i; ++i)
	{
		int counter = 0;
		unsigned int value = arr[i];
		while (value)
		{
			counter += value & 1;
			value = value >> 1;
			
		}
		if (counter == 3)
		{
			printf("%d, ",arr[i]);
		}
				
	}
	printf("\n");
}

unsigned int ByteMirrorLoop(unsigned int x)
{
	unsigned int reverse_num = 0;
	unsigned int count = 32; 
	
	while (count > 0)
	{
		reverse_num = reverse_num << 1;/*reverse_num = reverse_num * 2^1*/
		
		if ( (x & 1) == 1)/*if the current bit is on (=1)*/
		{
			reverse_num = reverse_num ^ 1;
		}
		x = x >> 1; /* x = x/2 */
		--count;
	}
	return reverse_num;	
}

unsigned int  ByteMirrorNoLoop(unsigned int x)
{
	  
	/**************************************************
	*Phase 1: swap 4 left bits with 4 right bits.     *
	***************************************************
	*0xf0 - refer to the left side of the byte,       *
	*and move it 4 bits right                         *
	*0x0f - refer to the right side of the byte,      *
	*and move it 4 bits left.                         *
	*Finally, make a union of both side               *
	***************************************************/
	
	 x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
	
	/**************************************************
	*Phase 2: swap 2 pairs of bits.                   *
	***************************************************
	*0xcc - refer to the two left-hand bits of the    *
	*right-hand part in BYTE,                         *
	*0x33 - refer to the two left-hand bits of the    *
	*right-hand part in BYTE.                         *
	*Finally, make a union of both side               *
	***************************************************/
	
	  x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2); 
     
	
	/**************************************************
	*Phase 3: swap odd bit with even bit              *
	***************************************************
	*0x55- refer to all the even bits,                *
	* shift it 1 bit left.                            *
	*0xaa - refer to all the odd bits,                *
	*shift it 1 bit right                             *
	*Finally, make a union of both side               *
	***************************************************/
	
	x = ((x & 0xaaaaaaaa) >> 1) |  ((x & 0x55555555) << 1);
	   
	x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
	
	x = (x >> 16) | (x << 16);
	
	return x;
}

unsigned char CheckBitsSixAndTwo(unsigned int x)
{

	return (x & 64) && (x & 4);
}

unsigned char CheckBitsSixOrTwo(unsigned int x)
{
	return (x & 64) || (x & 4);
}
unsigned int SwapBit3AndBit5(unsigned int x)
{
	if ((x & 4) != (x & 16))/*Replace the 5 and 3 when it is different*/
	{
		x ^= (1 << 2);
		x ^= (1 << 4);
	}
	
	return x;

}
unsigned int Get16(unsigned int x)
{
	unsigned int shift_right = x >> 4;
	shift_right = shift_right << 4;
	return shift_right;
}
void Swap(unsigned int x, unsigned int y)
{
	if (x != y)
	{
		x = x ^ y;
		y = x ^ y;
		x = x ^ y;
		printf("swaps two variable without using third variable: after: x = %u, y = %u \n", x, y);
	}
}

int CountSetBitsLoop(int x)
{
	int counter = 0;
	if (x < 0)
	{
		x = x * (-1); 
	}
	
	while (0 != x)
	{
		if ((x & 1) == 1)
		{
			++counter;
		}
		x = x >> 1;
	}
	return counter;
}
int CountSetBitsNoLoop(int x)
{
	
	/*By using a formula x - (x/2) - (x/4) - (x/8) 
	  each line checks wich bits are on.         */                                          
 	x = x - ((x >> 1) & 0x55555555); /*0x5 is 0101*/
  	x = (x & 0x33333333) + ((x >> 2) & 0x33333333); /*0x3 is 0011*/
  	x = (x + (x >> 4)) & 0x0F0F0F0F; /*0x0f is 0000 1111*/
  	x = x + (x >> 8);
  	x = x + (x >> 16);
  	
  	return x & 0x0000003F;	
}
void FloatAnalysis(float *x)
{
	int i = 31; /*total bits in number as an index*/
	int *ptr_to_float = (int *) x;
	
	for(; 0 <= i; i--)
	{
		int bit = *ptr_to_float & 1 << i;
		if (0 == bit)
		{
			printf("0");
		}
		else
		{
			printf("1");
		}
	}
	printf("\n");
}
void PrintTrueOrFalse(unsigned char a)
{
	if (1 == a)
	{
		printf("true");
	}
	else
	{
		printf("false");
	}
}
