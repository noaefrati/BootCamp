#ifndef __KNIGHTS_TOUR_H_OL97_ILRD__
#define __KNIGHTS_TOUR_H_OL97_ILRD__

/*******************************************************************************
 * Description: Header file for Knight's Tour Function                         *
 *                                                                             *
 * Infinity Labs - OL97                                                        *
 ******************************************************************************/

#define BOARD_SIZE 8

/*
 * Description: This function receives a Knight's starting position from the user,
 *              as row index and column index (each in the range 0 - BOARD_SIZE).
 *              The board parameter represents a chess board. The square at
 *              row i and column j is represented by the (i*BOARD_SIZE + j) index
 *              in the board array.
 *              The function updates the board by putting in each of its indexes 
 *              the step number of each move the Knight performs during her tour. 
 * UB: if row or col are outside the valid range. 
 * Return Value: None.
 */
void KnightsTour(int row, int col, int board[BOARD_SIZE * BOARD_SIZE]);

#endif /* __KNIGHTS_TOUR_H_OL97_ILRD__ */
