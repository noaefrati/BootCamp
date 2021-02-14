/******************************************************************************* 
 * Description: Implemention of Knights Tour Algorithm                         *
 * Author: Noa Efrati                                                          *
 * Reviewer: Amir Tamir                                                        *
 * Date: 13.01.2021                                                            *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/

#include <stdio.h>         /* printf                                          */
#include <assert.h>        /* assert                                          */
#include "knights_tour.h"  /* knights_tour API                                */
#include "bit_array.h"     /* bit_Array API                                   */

#define INVALID_MOVE -1
#define BOARD_LIMIT (BOARD_SIZE * BOARD_SIZE)

typedef enum {SUCCESS = 0, FAILURE} status_t;

/******************************************************************************/
/***                   Private Functions Declerations                       ***/
/******************************************************************************/

static int CountValidMoves(int position,
						   size_t visited_bit_arr,
						   int moves_lut[][BOARD_SIZE]);

static status_t KnightsTourImp(int step,
							   int *board,
							   int position,
							   bit_array_t visited_bit_arr,
							   int moves_lut[][BOARD_SIZE]);

static int GetPositionWithMinMoves(int position,
								   bit_array_t visited_bit_arr, 
								   bit_array_t options_to_visit,
								   int moves_lut[][BOARD_SIZE]);                        

static int GetIndex(int row, int col);
static void InitLut(int moves_lut[][BOARD_SIZE]);
static int IsValidMove(int position, size_t visited_bit_arr);
/******************************************************************************/
/******************************************************************************/
/***                       API Functions Declerations                       ***/
/******************************************************************************/
void KnightsTour(int row, int col, int board[BOARD_SIZE * BOARD_SIZE])
{
	static int moves_lut[BOARD_LIMIT][BOARD_SIZE] = {0};
	bit_array_t visited_bit_arr = 0UL;
	int position = GetIndex(row, col);
	status_t status = SUCCESS;
	
	assert(board);
	
	InitLut(moves_lut);
	
	visited_bit_arr = BitArraySetOn(visited_bit_arr, position);
	status = KnightsTourImp(0, board, position, visited_bit_arr, moves_lut);
	
	if (SUCCESS != status)
	{
	 	printf("FAILED! ! !\n");
	}	
}

/******************************************************************************/
/******************************************************************************/
/***                     Private Functions Defenitions                      ***/
/******************************************************************************/
static status_t KnightsTourImp(int step,
							   int *board,
							   int position,
							   bit_array_t visited_bit_arr,
							   int moves_lut[][BOARD_SIZE])

{
	int i = 0;
	bit_array_t options_to_visit = 0UL;
	
	assert(board);
	assert(moves_lut);
	
	if (BOARD_LIMIT - 1 == step)
	{
		board[position] = step;
		
		return SUCCESS;
	}
	
	for (i = 0; BOARD_SIZE > i; ++i) 
    {
    	int next_position = GetPositionWithMinMoves(position,
    	                                            visited_bit_arr,
    	                                            options_to_visit,
    	                                            moves_lut);
    	if (INVALID_MOVE != next_position)
    	{
    		board[position] = step;
    		
    		options_to_visit = BitArraySetOn(options_to_visit, next_position);
    		
    	   if (SUCCESS  ==  KnightsTourImp(step + 1, board, next_position,
						         BitArraySetOn(visited_bit_arr, next_position), 
							     moves_lut))
    		{
    			return SUCCESS;
    		}
    	}
    }
	
	return FAILURE;
}
/******************************************************************************/
static void InitLut(int moves_lut[][BOARD_SIZE])
{
	int i = 0;
	int surfix_row[BOARD_SIZE] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int surfix_col[BOARD_SIZE] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	
	assert(moves_lut);
	
	for(; BOARD_LIMIT > i ; ++i)
    {
        int j = 0;
        
        for(; BOARD_SIZE > j; ++j)
        {
            int row = i / BOARD_SIZE;
			int col = i % BOARD_SIZE;
            int index = GetIndex(row + surfix_row[j] ,col + surfix_col[j]);
            
            moves_lut[i][j] = index;
        }
    }
}
/******************************************************************************/

int GetIndex(int row, int col)
{
    if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE )
    {
        return INVALID_MOVE;
    } 
    
    return (row * BOARD_SIZE + col);
}
/******************************************************************************/

int IsValidMove(int position, size_t visited_bit_arr)
{
	return (INVALID_MOVE != position) && 
	       (BIT_OFF == BitArrayGetVal(visited_bit_arr, position));
}
/******************************************************************************/

int CountValidMoves(int position,
					size_t visited_bit_arr,
				    int moves_lut[][BOARD_SIZE])
{
	int num_move = 0;
	int count_valid_moves = 0;
	
	assert(moves_lut);
	
	for (; BOARD_SIZE > num_move; ++num_move)
	{
		if (IsValidMove(moves_lut[position][num_move], visited_bit_arr))
	    {
			++count_valid_moves;
		}
	}
	
	return count_valid_moves;
}
/******************************************************************************/

int GetPositionWithMinMoves(int position,
						    bit_array_t visited_bit_arr, 
						    bit_array_t options_to_visit,
						    int moves_lut[][BOARD_SIZE])
{
 	int min_moves = BOARD_SIZE + 1;
 	int min_position = -1;
 	int i = 0;
 	
 	assert(moves_lut);
 	
 	for (; BOARD_SIZE > i; ++i)
 	{
 		int next_position = moves_lut[position][i];
 		
 		if (IsValidMove(next_position, visited_bit_arr))
 		{
 			int num_of_valid_moves = CountValidMoves(next_position, 
 											 	     visited_bit_arr,
 											         moves_lut);
	 		if (num_of_valid_moves < min_moves && 
	 		    BIT_OFF == BitArrayGetVal(options_to_visit, next_position))
	 		{
	 			min_moves = num_of_valid_moves;
	 			min_position = next_position;	
	 		}
 		}
 	}
 	
 	return min_position; 	
}
