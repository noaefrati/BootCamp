#ifndef __BIT_ARRAY_H_OL97_ILRD__
#define __BIT_ARRAY_H_OL97_ILRD__

/*
 * Purpose: 
 * 
 * Language:  C.
 * Created: 16/11/2020
 */

#include <stddef.h>   /* size_t */

/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/
typedef unsigned long bit_array_t;

typedef enum 
{
BIT_OFF = 0, 
BIT_ON = 1
} bit_status_t;

/******************************************************************************/
/***                      Public functions declarations                     ***/
/******************************************************************************/

/*
 * This function receives a bit_array and sets all the bits of
 * the array to be '1' - on.
 */
bit_array_t BitArraySetAll(bit_array_t bit_array);

/*
 * This function receives a bit_array and sets all the bits of
 * the array to be '0' - off.
 */
bit_array_t BitArrayResetAll(bit_array_t bit_array);

/*
 * This function receives a bit_array of size arr_len and returns a string 
 * (char*) to the caller, caller responsibility is to free the string when he
 * finishes using it.
   buffer should be a character array of size at least 65.
 */
char *BitArrayToString(bit_array_t bit_array, char *buffer);

/*
 * This function receives a bit_array and index of the bit to set on - '1'.
 */
bit_array_t BitArraySetOn(bit_array_t bit_array, size_t bit_pos);

/*
 * This function receives a bit_array and index of the bit to set off - '0'.
 */
bit_array_t BitArraySetOff(bit_array_t bit_array, size_t bit_pos);

/*
 * This function receives a bit_array, index of the bit to set, and the value
 * to which this bit needed to be set.
 */
bit_array_t BitArraySetBit(bit_array_t bit_array, 
					  size_t bit_pos, 
					  bit_status_t set_val);

/*
 * This function receives a bit_array and index of the bit which value it is
 * supposed to return. 
 */
bit_status_t BitArrayGetVal(bit_array_t bit_array, size_t bit_pos);

/*
 * This function receives a bit_array and index of the bit which value it is
 * supposed to flip. On success, return SUCCESS.
 */
bit_array_t BitArrayFlip(bit_array_t bit_array, size_t bit_pos);

/*
 * This function receives a bit_array, the function
 * performs mirror action on the whole array.
 */
bit_array_t BitArrayMirror(bit_array_t bit_array);

/*
 * This function receives a bit_array, 
 * the function performs a count of all the turned on bits
 * and returns this number to the caller.
 */
size_t BitArrayCountOn(bit_array_t bit_array);

/*
 * This function receives a bit_array, 
 * the function performs a count of all the turned off bits
 * and returns this number to the caller.
 */
size_t BitArrayCountOff(bit_array_t bit_array);

/*
 * This function receives a bit_array and the number of rotations
 * requested by the caller as (num_rotations) the function rotates the bit 
 * array to the right by the requested amount of times, in a circular manner.
 */
bit_array_t BitArrayRotateRight(bit_array_t bit_array, size_t num_rotations);

/*
 * This function receives a bit_array and the number of rotations 
 * requested by the caller as (num_rotations) the function rotates the bit 
 * array to the left by the requested amount of times, in a circular manner.
 */
bit_array_t BitArrayRotateLeft(bit_array_t bit_array, size_t num_rotations);

#endif /* __BIT_ARRAY_H_OL97_ILRD__ */
