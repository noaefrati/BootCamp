/************************************************************************** 
 * Description: Testing the bit array function implementations
 * Author: Oriel Nofekh
 * Reviewer: NONE
 *
 * Infinity Labs OL97
 ***************************************************************************/


#include <stdio.h>    /* printf, size_t */
#include <string.h>   /* strcmp */
#include <limits.h>   /* ULONG_MAX */
#include "../include/bit_array.h" /* bit_array functions */

/******************** Functions Declarations ********************/

void TestBitArraySetAll(void);
void TestBitArrayResetAll(void);
void TestBitArrayToString(void);
void TestBitArraySetOn(void);
void TestBitArraySetOff(void);
void TestBitArraySetBit(void);
void TestBitArrayFlip(void);
void TestBitArrayGetVal(void);
void TestBitArrayMirror(void);
void TestBitArrayRotateRight(void);
void TestBitArrayRotateLeft(void);
void TestBitArrayCountOn(void);
void TestBitArrayCountOff(void);
static void PrintSuccesOrFailure(int is_success, char *function_name);

/******************** main function ********************/

int main(void)
{

	
	if (1)
	{
	TestBitArraySetAll();
	TestBitArrayResetAll();
	TestBitArrayToString();
	TestBitArraySetOn();
	TestBitArraySetOff();
	TestBitArraySetBit();
	TestBitArrayFlip();
	TestBitArrayGetVal();
	TestBitArrayMirror();
	TestBitArrayRotateRight();
	TestBitArrayRotateLeft();
	TestBitArrayCountOn();
	TestBitArrayCountOff();
	}
	return 0;
}

/******************** Functions Implementations ********************/

void TestBitArraySetAll(void)
{
	static char function_name[] = "BitArraySetAll";
	bit_array_t bit_array = 0;
	
	bit_array = BitArraySetAll(bit_array);
	
	PrintSuccesOrFailure((ULONG_MAX == (unsigned long) bit_array), function_name);
}

void TestBitArrayResetAll(void)
{
	static char function_name[] = "BitArrayResetAll";
	bit_array_t bit_array = 0;
	
	bit_array = BitArrayResetAll(bit_array);
	
	PrintSuccesOrFailure((0L == bit_array), function_name);
}

void TestBitArrayToString(void)
{
	static char function_name[] = "BitArrayToString";
	bit_array_t bit_array;
	int is_the_same;
	char buffer[65] = {0};
	
	bit_array = 1UL;
	BitArrayToString(bit_array, buffer);
	is_the_same = strcmp(buffer, 
	              "00000000" "00000000" "00000000" "00000000" 
	              "00000000" "00000000" "00000000" "00000001");
	PrintSuccesOrFailure(!is_the_same, function_name);
	
	bit_array = 0x8000000000000010UL;
	BitArrayToString(bit_array, buffer);
	is_the_same = strcmp(buffer, 
	              "10000000" "00000000" "00000000" "00000000" 
	              "00000000" "00000000" "00000000" "00010000");
	PrintSuccesOrFailure(!is_the_same, function_name);
	
	bit_array = 0x4000000000000020UL;
	BitArrayToString(bit_array, buffer);
	is_the_same = strcmp(buffer, 
	              "01000000" "00000000" "00000000" "00000000" 
	              "00000000" "00000000" "00000000" "00100000");
	PrintSuccesOrFailure(!is_the_same, function_name);
	
}

void TestBitArraySetOn(void)
{
	static char function_name[] = "BitArraySetOn";
	bit_array_t bit_array;
	bit_array_t bit_array_expected;
	size_t bit_pos;
	
	bit_array =          0x0000000000000000UL;
	bit_pos = 4*0;
	bit_array_expected = 0x0000000000000001UL;
	bit_array = BitArraySetOn(bit_array, bit_pos);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array =          0x1111000000000000UL;
	bit_pos = 4*1;
	bit_array_expected = 0x1111000000000010UL;
	bit_array = BitArraySetOn(bit_array, bit_pos);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array =          0x0000110000000011UL;
	bit_pos = 63;
	bit_array_expected = 0x8000110000000011UL;
	bit_array = BitArraySetOn(bit_array, bit_pos);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array =  0xFFFFFFFFFFFFFFFF;
	bit_pos = 63;
	bit_array_expected =  0xFFFFFFFFFFFFFFFF;
	bit_array = BitArraySetOn(bit_array, bit_pos);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array =  0xFFFFFFFFFFFFFFFF;
	bit_pos = 0;
	bit_array_expected =  0xFFFFFFFFFFFFFFFF;
	bit_array = BitArraySetOn(bit_array, bit_pos);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
}

void TestBitArraySetOff(void)
{
	static char function_name[] = "BitArraySetOff";
	bit_array_t bit_array;
	bit_array_t bit_array_expected;
	size_t bit_pos;
	
	bit_array =          0x0000000000110000UL;
	bit_pos = 5*4;
	bit_array_expected = 0x0000000000010000UL;
	bit_array = BitArraySetOff(bit_array, bit_pos);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array =          0x1111000000000110UL;
	bit_pos = 1*4;
	bit_array_expected = 0x1111000000000100UL;
	bit_array = BitArraySetOff(bit_array, bit_pos);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array =          0x8100110000000011UL;
	bit_pos = 63;
	bit_array_expected = 0x0100110000000011UL;
	bit_array = BitArraySetOff(bit_array, bit_pos);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
}

void TestBitArraySetBit(void)
{
	static char function_name[] = "BitArraySetBit";
	bit_array_t bit_array;
	bit_array_t bit_array_expected;
	size_t bit_pos;
	bit_status_t set_val;
	
	bit_array = 0x0000000000000000UL;
	bit_pos = 5*4;
	set_val = BIT_ON;
	bit_array_expected = 0x0000000000100000UL;
	bit_array = BitArraySetBit(bit_array, bit_pos, set_val);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array = 0x1111000000000111UL;
	bit_pos = 1*4;
	set_val = BIT_OFF;
	bit_array_expected = 0x1111000000000101UL;
	bit_array = BitArraySetBit(bit_array, bit_pos, set_val);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
}

void TestBitArrayFlip(void)
{
	static char function_name[] = "BitArrayFlip";
	bit_array_t bit_array;
	bit_array_t bit_array_expected;
	size_t bit_pos;
	
	bit_array = 0x0000000000110000UL;
	bit_pos = 5*4;
	bit_array_expected = 0x0000000000010000UL;
	bit_array = BitArrayFlip(bit_array, bit_pos);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array = 0x1111000000000110UL;
	bit_pos = 60 - 4*4;
	bit_array_expected = 0x1111100000000110UL;
	bit_array = BitArrayFlip(bit_array, bit_pos);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array = 0x8100110000000011UL;
	bit_pos = 63;
	bit_array_expected = 0x0100110000000011UL;
	bit_array = BitArrayFlip(bit_array, bit_pos);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
}

void TestBitArrayGetVal(void)
{
	static char function_name[] = "BitArrayGetVal";
	bit_array_t bit_array;
	size_t bit_pos;
	bit_status_t status;
	bit_status_t status_expected;
	
	bit_array = 0x0000000000110001UL;
	bit_pos = 0;
	status_expected = BIT_ON;
	status = BitArrayGetVal(bit_array, bit_pos);
	PrintSuccesOrFailure((status == status_expected), function_name);
	
	bit_array = 0x0000001111111011UL;
	bit_pos = 8;
	status_expected = BIT_OFF;
	status = BitArrayGetVal(bit_array, bit_pos);
	PrintSuccesOrFailure((status == status_expected), function_name);
	
	bit_array = 0xFFFFFFFFFFFFFFFF;
	bit_pos = 18;
	status_expected = BIT_ON;
	status = BitArrayGetVal(bit_array, bit_pos);
	PrintSuccesOrFailure((status == status_expected), function_name);
}

void TestBitArrayMirror(void)
{
	static char function_name[] = "BitArrayMirror";
	bit_array_t bit_array;
	bit_array_t bit_array_expected;
	
	bit_array = 0x0000000000000211UL;
	bit_array_expected = 0x8840000000000000UL;
	bit_array = BitArrayMirror(bit_array);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array = 0x0000000000080101UL;
	bit_array_expected = 0x8080100000000000UL;
	bit_array = BitArrayMirror(bit_array);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
}

void TestBitArrayRotateRight(void)
{
	static char function_name[] = "BitArrayRotateRight";
	size_t num_rotations;
	bit_array_t bit_array;
	bit_array_t bit_array_expected;
	
	bit_array = 0x0000000000110000UL;
	num_rotations = 2*4;
	bit_array_expected = 0x0000000000001100UL;
	bit_array = BitArrayRotateRight(bit_array, num_rotations);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array = 0x0000000000110000UL;
	num_rotations = 7*4;
	bit_array_expected = 0x0110000000000000UL;
	bit_array = BitArrayRotateRight(bit_array, num_rotations);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
}

void TestBitArrayRotateLeft(void)
{
	static char function_name[] = "BitArrayRotateLeft";
	size_t num_rotations;
	bit_array_t bit_array;
	bit_array_t bit_array_expected;
	
	bit_array = 0x0000000000110000UL;
	num_rotations = 2*4;
	bit_array_expected = 0x0000000011000000UL;
	bit_array = BitArrayRotateLeft(bit_array, num_rotations);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
	
	bit_array = 0x1011000000000000UL;
	num_rotations = 7*4;
	bit_array_expected = 0x0000000001011000UL;
	bit_array = BitArrayRotateLeft(bit_array, num_rotations);
	PrintSuccesOrFailure((bit_array == bit_array_expected), function_name);
}

void TestBitArrayCountOn(void)
{
	static char function_name[] = "BitArrayCountOn";
	bit_array_t bit_array;
	size_t count;
	size_t count_expected;
	
	bit_array = 0x0000000000110000UL;
	count_expected = 2;
	count = BitArrayCountOn(bit_array);
	PrintSuccesOrFailure((count == count_expected), function_name);
	
	bit_array = 0x0000004040110000UL;
	count_expected = 4;
	count = BitArrayCountOn(bit_array);
	PrintSuccesOrFailure((count == count_expected), function_name);
	
	bit_array = 0x0068004040110000UL;
	count_expected = 7;
	count = BitArrayCountOn(bit_array);
	PrintSuccesOrFailure((count == count_expected), function_name);
}

void TestBitArrayCountOff(void)
{
	static char function_name[] = "BitArrayCountOff";
	bit_array_t bit_array;
	size_t count;
	size_t count_expected;
	
	bit_array = 0x0000000000110000UL;
	count_expected = 64 - 2;
	count = BitArrayCountOff(bit_array);
	PrintSuccesOrFailure((count == count_expected), function_name);
	
	bit_array = 0x0000004040110000UL;
	count_expected = 64 - 4;
	count = BitArrayCountOff(bit_array);
	PrintSuccesOrFailure((count == count_expected), function_name);
	
	bit_array = 0x0068004040110000UL;
	count_expected = 64 - 7;
	count = BitArrayCountOff(bit_array);
	PrintSuccesOrFailure((count == count_expected), function_name);
}

static void PrintSuccesOrFailure(int is_success, char *function_name)
{
	if (is_success)
	{
		printf("%s test was a SUCCESS\n", function_name);
	}
	else
	{
		printf("%s test was a FAILURE   !!!   !!!   !!!\n", function_name);
	}
}







