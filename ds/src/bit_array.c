/************************************************************************** 
 * Description: Implement bit array functions.
 * Author: Noa Efrati
 * Reviewer: David Horovitz
 * Date: 18.11.20
 * Infinity Labs OL97
 ***************************************************************************/


#include <limits.h>                   /*CHAR_BIT*/
#include <assert.h>                  /*assert*/
#include "../include/bit_array.h" /* bit_array functions */

enum {BIT_ARRAY_SIZE = (sizeof(unsigned long)) * CHAR_BIT};


bit_array_t BitArraySetAll(bit_array_t bit_array)
{
	bit_array_t bit_array_set_all = 0xFFFFFFFFFFFFFFFF;
	(void)(bit_array);
	
	return (bit_array_set_all);
}

bit_array_t BitArrayResetAll(bit_array_t bit_array)
{
	bit_array_t bit_array_reset_all = 0x0000000000000000;
	(void)(bit_array);
	
	return (bit_array_reset_all);
}

bit_array_t BitArraySetOn(bit_array_t bit_array, size_t bit_pos)
{
	bit_array_t tmp_bit_array = 0;
	
	assert(BIT_ARRAY_SIZE > bit_pos);
	
	tmp_bit_array = bit_array | (1UL << bit_pos);
	
	return (tmp_bit_array);
}

bit_array_t BitArraySetOff(bit_array_t bit_array, size_t bit_pos)
{
	bit_array_t bitArray_set_off = 0;
	assert(BIT_ARRAY_SIZE > bit_pos);
	bitArray_set_off = bit_array & (~(1UL << bit_pos));
	
	return (bitArray_set_off);
}

bit_array_t BitArraySetBit(bit_array_t bit_array, size_t bit_pos,
                                                        bit_status_t set_val)  
{
	assert(BIT_ARRAY_SIZE > bit_pos);
	
	return (set_val ? (BitArraySetOn(bit_array,bit_pos)) : 
	                                  (BitArraySetOff(bit_array,bit_pos)));
}

bit_status_t BitArrayGetVal(bit_array_t bit_array, size_t bit_pos)
{
	bit_array_t bitArray_get_val = 0;
	assert(BIT_ARRAY_SIZE > bit_pos);
	bitArray_get_val = (bit_array >> bit_pos) & 1UL;
	
	return (bitArray_get_val);
}

bit_array_t BitArrayFlip(bit_array_t bit_array, size_t bit_pos)
{
	bit_array_t bitArray_flip = 0;
	assert(BIT_ARRAY_SIZE > bit_pos);
	bitArray_flip = bit_array ^ (1UL << bit_pos);
	
	return (bitArray_flip);
}

char *BitArrayToString(bit_array_t bit_array, char *buffer)
{
	int index = 0;
	assert(NULL != buffer);
	index = BIT_ARRAY_SIZE;
	
	buffer[index] = '\0';
	--index;
		
	for (; 0 <= index; --index)
	{
		buffer[index] = (bit_array & 1UL) ? '1' : '0' ;
		bit_array >>= 1UL;	
	}
	
	return (buffer);	
}


bit_array_t BitArrayMirror(bit_array_t bit_array)
{
	bit_array_t bitArray_mirror = 0;
	unsigned long count = BIT_ARRAY_SIZE; 
	
	for (; 0 < count; --count)
	{
		bitArray_mirror = bitArray_mirror << 1;
		
		if ( (bit_array & 1) == 1)/*if the current bit is on (=1)*/
		{
			bitArray_mirror = bitArray_mirror ^ 1UL;
		}
		bit_array = bit_array >> 1UL;
	}
	return (bitArray_mirror);
}

size_t BitArrayCountOn(bit_array_t bit_array)
{
	size_t count_on = 0;
	
	while (0 < bit_array)
	{
		/*if (bit_array & 1) is 0, count is not change*/
		count_on += (bit_array & 1); 
		bit_array >>= 1;
		
	}
	return (count_on);
	
}

size_t BitArrayCountOff(bit_array_t bit_array)
{
	return (BIT_ARRAY_SIZE - BitArrayCountOn(bit_array));
}

bit_array_t BitArrayRotateLeft(bit_array_t bit_array, size_t num_rotations)
{

	return ((bit_array << num_rotations)|
	                     (bit_array >> (BIT_ARRAY_SIZE - num_rotations)));
}

bit_array_t BitArrayRotateRight(bit_array_t bit_array, size_t num_rotations)
{
	return ((bit_array >> num_rotations)|
	                     (bit_array << (BIT_ARRAY_SIZE - num_rotations)));
}
