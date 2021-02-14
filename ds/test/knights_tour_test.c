/*************************************************************************** 
 * Description: Testing of Implementation of Knight's Tour
 * Author: Oriel Nofekh
 *
 * Infinity Labs OL97
 ***************************************************************************/


#include <stdio.h>           /* printf */
#include <time.h>            /* clock_t, clock */
#include "knights_tour.h"    /* Knight's Tour API */


/******************************************************************************/
/***                        Color Defines   		                      ***/
/******************************************************************************/
#define DEF     "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

static int test_counter_g = 0;
static int success_counter_g = 0;

#define TEST(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEF, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)

#define TESTC(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %c, Expected: %c\n" DEF, name, __LINE__, (char) (real), (char) (expected)); \
    } while (0)

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)




/************************* Helper Functions *************************/

static int IsCorrectSolution(int row, int col, int board[BOARD_SIZE * BOARD_SIZE], int *fail_counter)
{
	int counter = 0;
	
	int index = row*BOARD_SIZE + col;
	if (counter != board[index])
	{
		*fail_counter = 0;
		return 0;
	}
	
	for (counter = 1; counter < BOARD_SIZE * BOARD_SIZE; ++counter)
	{
		if (row-2 >= 0)
		{
			index = (row-2)*BOARD_SIZE + (col-1);
			if (col-1 >= 0 && board[index] == counter)
			{
				row = row-2;
				col = col-1;
				continue;
			}
			
			index = (row-2)*BOARD_SIZE + (col+1);
			if (col+1 < BOARD_SIZE && board[index] == counter)
			{
				row = row-2;
				col = col+1;
				continue;
			}
		}
		
		if (row+2 < BOARD_SIZE)
		{
			index = (row+2)*BOARD_SIZE + (col-1);
			if (col-1 >= 0 && board[index] == counter)
			{
				row = row+2;
				col = col-1;
				continue;
			}
			
			index = (row+2)*BOARD_SIZE + (col+1);
			if (col+1 < BOARD_SIZE && board[index] == counter)
			{
				row = row+2;
				col = col+1;
				continue;
			}
		}
		
		if (row-1 >= 0)
		{
			index = (row-1)*BOARD_SIZE + (col-2);
			if (col-2 >= 0 && board[index] == counter)
			{
				row = row-1;
				col = col-2;
				continue;
			}
			
			index = (row-1)*BOARD_SIZE + (col+2);
			if (col+2 < BOARD_SIZE && board[index] == counter)
			{
				row = row-1;
				col = col+2;
				continue;
			}
		}
		
		if (row+1 < BOARD_SIZE)
		{
			index = (row+1)*BOARD_SIZE + (col-2);
			if (col-2 >= 0 && board[index] == counter)
			{
				row = row+1;
				col = col-2;
				continue;
			}
			
			index = (row+1)*BOARD_SIZE + (col+2);
			if (col+2 < BOARD_SIZE && board[index] == counter)
			{
				row = row+1;
				col = col+2;
				continue;
			}
		}
		
		*fail_counter = counter;
		return 0;   /* failed to find a correct continuation */
	}
	
	return 1;   /* success, correct solution */
}

static void PrintBoard(int board[BOARD_SIZE * BOARD_SIZE])
{
	int index = 0, row = 0, col = 0;
	
	for (row = 0; row < BOARD_SIZE; ++row)
	{
		for (col = 0; col < BOARD_SIZE; ++col)
		{
			index = row*BOARD_SIZE + col;
			
			if (board[index] < 10)
			{
				printf(" ");
			}
			
			printf("%d ", board[index]); 
		}
		printf("\n");
	}
}

/************************* Tests Functions *************************/

static void Test0(void)
{
	int fail_counter = 0;
	
	/* this is a board for example, that IS NOT a solution */
	/*
	static int board[BOARD_SIZE * BOARD_SIZE] =
			{ 0, 1, 2, 3, 4, 5, 6, 7,
			  8, 9,10,11,12,13,14,15,
			 16,17,18,19,20,21,22,23,
			 24,25,26,27,28,29,30,31,
			 32,33,34,35,36,37,38,39,
			 40,41,42,43,44,45,46,47,
			 48,49,50,51,52,53,54,55,
			 56,57,58,59,60,61,62,63 };
	*/
	
	/* this is a board for example, that IS a solution */
	
	static int board[BOARD_SIZE * BOARD_SIZE] =
			{ 0, 47, 30, 49, 32, 15, 62, 17,
			 29, 50, 45,  2, 61, 18, 13, 34,
			 46,  1, 48, 31, 14, 33, 16, 63,
			 51, 28,  3, 44, 19, 60, 35, 12,
			  4, 43, 24, 55,  8, 39, 20, 59,
			 27, 52,  7, 40, 23, 56, 11, 36,
			 42,  5, 54, 25, 38,  9, 58, 21,
			 53, 26, 41,  6, 57, 22, 37, 10 }; 
	
	
	int row = 0;
	int col = 0;
	int is_correct = 0;
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		printf("   fail_counter = %d\n", fail_counter);
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	printf(BOLDBLUE "Completed Test0\n" DEF);
}

static void Test1(void)
{
	int fail_counter = 0;
	clock_t start, end;
	double total;
	
	static int board[BOARD_SIZE * BOARD_SIZE];
	
	int row = 0;
	int col = 0;
	int is_correct = 0;
	
	
	start = clock();
	
	KnightsTour(row, col, board);
	
	end = clock();
	total = (double) (end - start) / CLOCKS_PER_SEC;
	printf(MAGENTA "Total time taken by CPU: %g seconds\n" DEF, total);
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	printf(BOLDBLUE "Completed Test1\n" DEF);
}

static void Test2(void)
{
	int fail_counter = 0;
	clock_t start, end;
	double total;
	
	static int board[BOARD_SIZE * BOARD_SIZE];
	int row = 0;
	int col = 0;
	int is_correct = 0;
	
	
	start = clock();
	
	
	row = 0;
	col = 0;
	KnightsTour(row, col, board);
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		printf("   fail_counter = %d\n", fail_counter);
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	row = 0;
	col = 1;
	KnightsTour(row, col, board);
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		printf("   fail_counter = %d\n", fail_counter);
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	row = 0;
	col = 2;
	KnightsTour(row, col, board);
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		printf("   fail_counter = %d\n", fail_counter);
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	row = 0;
	col = 3;
	KnightsTour(row, col, board);
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		printf("   fail_counter = %d\n", fail_counter);
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	row = 1;
	col = 1;
	KnightsTour(row, col, board);
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		printf("   fail_counter = %d\n", fail_counter);
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	row = 1;
	col = 2;
	KnightsTour(row, col, board);
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		printf("   fail_counter = %d\n", fail_counter);
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	row = 1;
	col = 3;
	KnightsTour(row, col, board);
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		printf("   fail_counter = %d\n", fail_counter);
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	row = 2;
	col = 2;
	KnightsTour(row, col, board);
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		printf("   fail_counter = %d\n", fail_counter);
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	row = 2;
	col = 3;
	KnightsTour(row, col, board);
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		printf("   fail_counter = %d\n", fail_counter);
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	row = 3;
	col = 3;
	KnightsTour(row, col, board);
	
	is_correct = IsCorrectSolution(row, col, board, &fail_counter);
	if (!is_correct)
	{
		printf("   fail_counter = %d\n", fail_counter);
		PrintBoard(board);  /* for debugging */
	}
	TEST("IsCorrectSolution", is_correct, 1);
	
	
	end = clock();
	total = (double) (end - start) / CLOCKS_PER_SEC;
	printf(MAGENTA "Total time taken by CPU: %g seconds\n" DEF, total);
	
	
	printf(BOLDBLUE "Completed Test2\n" DEF);
}

static void Test3(void)
{
	int fail_counter = 0;
	clock_t start, end;
	double total;
	
	static int board[BOARD_SIZE * BOARD_SIZE];
	
	int row = 0;
	int col = 0;
	int is_correct = 0;
	
	start = clock();
	
	for (row = 0; row < BOARD_SIZE; ++row)
	{
		for (col = 0; col < BOARD_SIZE; ++col)
		{
			KnightsTour(row, col, board);
			
			is_correct = IsCorrectSolution(row, col, board, &fail_counter);
			if (!is_correct)
			{
				printf("   fail_counter = %d\n", fail_counter);
				PrintBoard(board);  /* for debugging */
			}
			TEST("IsCorrectSolution", is_correct, 1);
		}
	}
	
	end = clock();
	total = (double) (end - start) / CLOCKS_PER_SEC;
	printf(MAGENTA "Total time taken by CPU: %g seconds\n" DEF, total);
	
	printf(BOLDBLUE "Completed Test3\n" DEF);
}

/************************* main function *************************/

int main(void)
{
	/* this tests the is-correct-solution function */
	Test0();	
	
	/* a simple test, used for debugging */
	Test1();
	
	if (BOARD_SIZE == 8 || BOARD_SIZE == 6)
	{
		/* the real tests (use only after heuristic is implemented) */
		Test2();
		Test3();
	}
	
	PASS;
	
	return 0;
}




















