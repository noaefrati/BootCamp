#ifndef __CALCULATOR_H_OL97_ILRD__
#define __CALCULATOR_H_OL97_ILRD__

/*******************************************************************************
 * Description: Header file Containing API Definition for Calculator interface *
 *              operations and declarations.                                   *
 *                                                                             *
 * Infinity Labs - OL97                                                        *
 ******************************************************************************/

/****************************** Return Values *********************************/

typedef enum
{
    CALC_SUCCESS,
    CALC_MATH_ERROR,
    CALC_MEM_ALLOC_ERROR,
    CALC_SYNTAX_ERROR
} calc_status_t;

/****************************** Functionality *********************************/

/*
 * Description: Function parses and evaluates result of given expression.
 * Upon success function writes result into given pointer *res (out param).
 * Upon failure, value of *res remains unchanged and an ERROR value is returned.
 * Return values:
 * - CALC_SUCCESS upon successful evaluation of given expression.
 * - CALC_MATH_ERROR upon illegal operations, such as division by zero.
 * - CALC_MEM_ALLOC_ERROR if insufficient memory.
 * - CALC_SYNTAX_ERROR when encountering invalid inputs.
 *      Invalid input includes letters;
 *                             invalid repeating operators;
 *                             non-operator symbols;
 *                             mismatching brackets.
 */
calc_status_t Calculate(const char *expression, double *res);



#endif /* __CALCULATOR_H_OL97_ILRD__ */
