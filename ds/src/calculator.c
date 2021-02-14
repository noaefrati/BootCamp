/******************************************************************************* 
 * Description: Implemention of Calculator                                     *
 * Author: Noa Efrati                                                          *
 * Reviewer: Galit Vaknin                                                      *
 * Date: 28.12.20                                                              *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/

#include <math.h>        /* pow                                               */
#include <ctype.h>	     /* isdigit, isspace                                  */	
#include <string.h>      /* strlen                                            */
#include <stdlib.h>      /* malloc, free, strtod                              */
#include <assert.h>      /* assert                                            */
#include "calculator.h"  /* calculator api                                    */
#include "stack.h"       /* stack api                                         */

/******************************************************************************/
/***                             unions                                     ***/
/******************************************************************************/

typedef union
{
	char operator;
	double num;
}content_t;
/******************************************************************************/
/***                             Enumerations                               ***/
/******************************************************************************/

typedef enum { NUM = 0, OPERATOR, OPEN_PAR, CLOSE_PAR, ALPHA_SIGN } input_t;
typedef enum { WAIT_FOR_NUM = 0, WAIT_FOR_OPERATOR, ERROR } state_t;

/******************************************************************************/
/***                               Structs                                  ***/
/******************************************************************************/


typedef struct
{
	input_t input_type;
	content_t content;
}token_t;

typedef calc_status_t (*handler_t)(token_t *token);
typedef struct
{
	state_t next_state;
	handler_t handler;
}event_t;

typedef calc_status_t (*operator_t)(double rhs, double lhs, double *ans);
typedef struct
{
    operator_t operator;
    int precedence;
}operation_t;

/******************************************************************************/
/***                     Defines & typedefs                                 ***/
/******************************************************************************/

#define NUM_STATES 2
#define NUM_CONDITIONS 5
#define ASCII 256
#define FREE(x) free(x); x = NULL;

/******************************************************************************/
/***                               Globals                                  ***/
/******************************************************************************/
event_t states_lut[NUM_STATES][NUM_CONDITIONS];
operation_t operation_lut[ASCII];
stack_t *num_stack_g = NULL;
stack_t *operator_stack_g = NULL;   /* _g for global */

/******************************************************************************/
/***                     Private function declarations                      ***/
/******************************************************************************/

/* help function in GetToken() & IsParBalanced */
static int IsDigit(char input);
static int IsOpenPar(char input);
static int IsOperator(char input);
static int IsClosePar(char input);
static void AdvanceSpace(char **input);
static int IsMatchingPar(char open, char close);

/* Handler Function */
static calc_status_t ErrorHandler(token_t *token);
static calc_status_t NumberHandler(token_t *token);
static calc_status_t OpenParHandler(token_t *token);
static calc_status_t CloseParHandler(token_t *token);
static calc_status_t OperatorHandler(token_t *token);

/* Operation Functions*/
static calc_status_t Add(double lhs, double rhs, double *ans);
static calc_status_t Power(double lhs, double rhs, double *ans);
static calc_status_t Divide(double lhs, double rhs, double *ans);
static calc_status_t Multiply(double lhs, double rhs, double *ans);
static calc_status_t Substract(double lhs, double rhs, double *ans);

/* Init Luts Tables in ParseExpression */
static void InitStatesLut(void);
static void InitOperatorsLUT(void);

static token_t GetToken(char **expression);

/* Makes an intermediate calculation */
static calc_status_t MakeCalculation(void);

/* Makes the final calculation */
static calc_status_t CalcExpression(double *res);

/* Allocate 2 stacks: for operators and for numbers */
static calc_status_t AllocationStacks(size_t size);

static calc_status_t ParseExpression(char *expression);

/* Balanced Parentheses */
static calc_status_t IsParBalanced(char *expression, size_t len);

/******************************************************************************/
/***                      Private function definitions                      ***/
/******************************************************************************/

static calc_status_t ParseExpression(char *expression)
{
	token_t token = {0};
	calc_status_t status = CALC_SUCCESS;
	state_t curr_state = WAIT_FOR_NUM;
	state_t next_state = 0;
	
	assert(expression);
	assert(*expression);
	
	InitStatesLut();
	InitOperatorsLUT();
	
	while (('\0' != *expression) && 
	       (ERROR != curr_state) &&
	       (CALC_SUCCESS == status))
	{
		token = GetToken(&expression);
		
		if ((OPERATOR == token.input_type) &&
		    ('\0' == token.content.operator))
		{
			break;
		}
		
		next_state = states_lut[curr_state][token.input_type].next_state;
		status = states_lut[curr_state][token.input_type].handler(&token);
		
		curr_state = next_state;
	}
	
	return status;
}
/*
 * Description: Function returns current token pointed by input.
 * Return values: token_t with current token parameters.
*/
static token_t GetToken(char **expression)
{
	token_t res = { 0 };
	
	assert(expression);
	assert(*expression);
	
	AdvanceSpace(expression);
	
	/* In case there is a space at the end of the string 
	 * and after using the function AdvanceSpace we have reached to '\0'
	 */
	if ('\0' == **expression)
	{
		res.content.operator = **expression;
		res.input_type = OPERATOR;
	}
	else if (IsDigit(**expression))
	{	
		res.content.num = strtod(*expression, expression);
		res.input_type = NUM;
	}	
	else if (IsOpenPar(**expression))
	{
		res.content.operator = **expression;
		res.input_type = OPEN_PAR;
		++(*expression);
	}
	else if (IsClosePar(**expression))
	{
		res.content.operator = **expression;
		res.input_type = CLOSE_PAR;
		++(*expression);
	}
	else if (IsOperator(**expression))
	{
		res.content.operator = **expression;
		res.input_type = OPERATOR;
		++(*expression);
	}
	else /* Not one of the possibly legal stuff, So illegal */
	{
		res.input_type = ALPHA_SIGN;
	}	

	return res;
}
static calc_status_t AllocationStacks(size_t size)
{
	calc_status_t ret_status = CALC_MEM_ALLOC_ERROR;
	
	assert(0 < size);
	
	num_stack_g = StackCreate(sizeof(double), size);
	
	if (NULL != num_stack_g)
	{
		operator_stack_g = StackCreate(sizeof(char), size);
		
		if (NULL != operator_stack_g)
		{
			ret_status = CALC_SUCCESS;
		}
		else
		{
			StackDestroy(num_stack_g);
		}
	}
	
	return ret_status;
}

static int IsOpenPar(char c)
{
	return ('(' == c || '[' == c || '{' == c);
}

static int IsClosePar(char c)
{
	return (')' == c || ']' == c || '}' == c);
}

static int IsMatchingPar(char open, char close)
{
	return (('(' == open && ')' == close) ||
			('[' == open && ']' == close) ||
			('{' == open && '}' == close) );
} 
static calc_status_t IsParBalanced(char *expression, size_t len)
{
    calc_status_t status = CALC_SUCCESS;
	char *runner = NULL;
	stack_t *stack = NULL;

	assert(expression);
	
	stack = StackCreate(sizeof(char), len);
	if (NULL == stack)
	{
		return CALC_MEM_ALLOC_ERROR;
	}
	
	for (runner = (char*)expression; '\0' != *runner; ++runner)
	{
		if (IsOpenPar(*runner))
		{
			StackPush(stack, runner);			
		}
		else if (IsClosePar(*runner))
		{
			char *last_open = (char *)StackPeek(stack);
			
			if (NULL != last_open && IsMatchingPar(*last_open, *runner))
			{
				StackPop(stack);
			} 
			else
			{
				status = CALC_SYNTAX_ERROR;
				break;
			}
		}
	}

	if (!StackIsEmpty(stack))
	{
		status = CALC_SYNTAX_ERROR;
	}
	
	if (NULL != stack)
	{
		StackDestroy(stack);
	}
	
	return status;
}

/*
 * Description: Function advances pointer while it points to space.
 * Return values: none.
*/
static void AdvanceSpace(char **input)
{
	assert(input);
	assert(*input);
	
	while (isspace(**input))
	{
		++(*input);
	}
}

/***************************** Init LUT Tables ********************************/
static void InitStatesLut(void)
{
	states_lut[WAIT_FOR_NUM][NUM].next_state = WAIT_FOR_OPERATOR;
	states_lut[WAIT_FOR_NUM][NUM].handler = &NumberHandler;
	states_lut[WAIT_FOR_NUM][OPERATOR].next_state = ERROR;
	states_lut[WAIT_FOR_NUM][OPERATOR].handler = &ErrorHandler;
	states_lut[WAIT_FOR_NUM][OPEN_PAR].next_state = WAIT_FOR_NUM;
	states_lut[WAIT_FOR_NUM][OPEN_PAR].handler = &OpenParHandler;
	states_lut[WAIT_FOR_NUM][CLOSE_PAR].next_state = ERROR;
	states_lut[WAIT_FOR_NUM][CLOSE_PAR].handler = &ErrorHandler; 
	states_lut[WAIT_FOR_NUM][ALPHA_SIGN].next_state = ERROR;
	states_lut[WAIT_FOR_NUM][ALPHA_SIGN].handler = &ErrorHandler;
	
	states_lut[WAIT_FOR_OPERATOR][NUM].next_state = ERROR;
	states_lut[WAIT_FOR_OPERATOR][NUM].handler = &ErrorHandler;
	states_lut[WAIT_FOR_OPERATOR][OPERATOR].next_state = WAIT_FOR_NUM;
	states_lut[WAIT_FOR_OPERATOR][OPERATOR].handler = &OperatorHandler;
	states_lut[WAIT_FOR_OPERATOR][OPEN_PAR].next_state = ERROR;
	states_lut[WAIT_FOR_OPERATOR][OPEN_PAR].handler = &ErrorHandler;	
	states_lut[WAIT_FOR_OPERATOR][CLOSE_PAR].next_state = WAIT_FOR_OPERATOR;
	states_lut[WAIT_FOR_OPERATOR][CLOSE_PAR].handler = &CloseParHandler; 
	states_lut[WAIT_FOR_OPERATOR][ALPHA_SIGN].next_state = ERROR;
	states_lut[WAIT_FOR_OPERATOR][ALPHA_SIGN].handler = &ErrorHandler;
	
}	
static void InitOperatorsLUT(void)
{
		
		operation_lut['+'].precedence = 0;
		operation_lut['+'].operator = &Add;
		
		operation_lut['-'].precedence = 0;
		operation_lut['-'].operator = &Substract;
		
		operation_lut['*'].precedence = 1;
		operation_lut['*'].operator = &Multiply;
		
		operation_lut['/'].precedence = 1;
		operation_lut['/'].operator = &Divide;
		
		operation_lut['^'].precedence = 2;
		operation_lut['^'].operator = &Power;
		
		operation_lut['('].precedence = -1;
		operation_lut['['].precedence = -1;
		operation_lut['{'].precedence = -1;
		
}
 
/****************************** Operation Functions ***************************/

static calc_status_t Add(double lhs, double rhs, double *ans)
{
	assert(ans);
	
	*ans = lhs + rhs;
	
	return CALC_SUCCESS;
}

static calc_status_t Substract(double lhs, double rhs, double *ans)
{
	assert(ans);
	
	*ans = lhs - rhs;
	
	return CALC_SUCCESS;
}

static calc_status_t Multiply(double lhs, double rhs, double *ans)
{
	assert(ans);
	
	*ans = lhs * rhs;
	
	return CALC_SUCCESS;
}

static calc_status_t Divide(double lhs, double rhs, double *ans)
{
	calc_status_t status = CALC_MATH_ERROR;
	
	assert(ans);
	
	if (0.0 != rhs)
	{
		*ans = lhs / rhs;
		status = CALC_SUCCESS;
		
	}
	
	return status;
}
/*
 * Description: Function that rasies lhs to the power of rhs.
 * Return values: CALC_SUCCESS on success, CALC_MEM_ALLOC_ERROR is returned in 
 *				  case of StackPush failure and CALC_MATH_ERROR in case 
 *                math_error is returned by pow. 
 *  HUGE_VAL -- if the value of a function returning double is positive and too
 *            large in magnitude to represent
 * -HUGE_VAL -- if the value of a function returning double is negative and too
 *           large in magnitude to represent
 * __isnan() -- functions determine if x is Not-A-Number (NAN).
*/
static calc_status_t Power(double lhs, double rhs,  double *ans)
{
	calc_status_t status = CALC_SUCCESS;

	assert(ans);
	
	*ans = pow(lhs,rhs);
	
	if ((HUGE_VAL == *ans) || (-HUGE_VAL == *ans) || __isnan(*ans))
    {
       status = CALC_MATH_ERROR;        
    }
		
	
	return status;
}

static int IsDigit(char input)
{
	return (isdigit(input));
} 

static int IsOperator(char input)
{
	return (NULL != operation_lut[(int)input].operator);
}
/*********************************** Handlers *********************************/

static calc_status_t ErrorHandler(token_t *token)
{
	(void)token;
	
	return (CALC_SYNTAX_ERROR);
}

static calc_status_t NumberHandler(token_t *token)
{
	calc_status_t status = CALC_SUCCESS;
	
	assert(token);
	
	if (1 == StackPush(num_stack_g, &token->content.num))
	{
		status = CALC_MEM_ALLOC_ERROR;
	}
	
	return status;
}

/*
 * Description: Fuction that handles token with open parentheses.
 * Return values: CALC_SUCCESS on success. CALC_MEM_ALLOC_ERROR is returned in 
 *				  case of StackPush failure.	  
*/
static calc_status_t OpenParHandler(token_t *token)
{
	calc_status_t status = CALC_SUCCESS;
	
	assert(token);
	
	if (0 != StackPush(operator_stack_g, (void *)(&token->content.operator)))
	{
		status = CALC_MEM_ALLOC_ERROR;
	}
	
	return (status);
}
/*
 * Description: Fuction that handles token with closed parentheses.
 * Return values: CALC_SUCCESS on success. Other errors can be returned by
 * 				  called functions.
*/
static calc_status_t CloseParHandler(token_t *token)
{
	calc_status_t status = CALC_SUCCESS;
	
	assert(token);
	
	while (!IsOpenPar(*(char *)StackPeek(operator_stack_g))) 
	{
		status = MakeCalculation();
	}
	/* poping the open parentheses after done calculation */
	StackPop(operator_stack_g); 
	
	return status;
}

static calc_status_t OperatorHandler(token_t *token)
{
    calc_status_t status = CALC_SUCCESS;

	assert(token);
	
	while (!StackIsEmpty(operator_stack_g) && CALC_SUCCESS == status &&
    		operation_lut[(int)token->content.operator].precedence <= 
            operation_lut[(int)*(char *)StackPeek(operator_stack_g)].precedence)
    {
		status = MakeCalculation();
    }
   	
   /* 
   	* In case that the operator_stack_g is empty OR 
   	* after done "break claculate" in the while loop above - 
   	* Push to operator_stack_g the operator.
   	*/
    if (CALC_SUCCESS == status)
    {
        status = StackPush(operator_stack_g, &token->content.operator) ?
                                            CALC_MEM_ALLOC_ERROR : CALC_SUCCESS;
    }    
   
    return status;
}

static calc_status_t MakeCalculation(void)
{
    calc_status_t status = CALC_SYNTAX_ERROR;
    double lhs = 0, rhs = 0, result = 0;
    unsigned char operator = 0;
    
    if (!StackIsEmpty(operator_stack_g))
    {
        operator = *(char *) StackPeek(operator_stack_g);
        StackPop(operator_stack_g);
       
        if (!StackIsEmpty(num_stack_g))
        {
           rhs = *(double *) StackPeek(num_stack_g);
           StackPop(num_stack_g);
       
            if (!StackIsEmpty(num_stack_g))
            {
               lhs = *(double *) StackPeek(num_stack_g);
               StackPop(num_stack_g);
               status = operation_lut[operator].operator(lhs,rhs,&result);  
            }
        }
    }
    
    if (CALC_SUCCESS == status)
    {
        status = StackPush(num_stack_g, &result) ? CALC_MEM_ALLOC_ERROR :
                                                   CALC_SUCCESS;
    }
    
    return status;    
}
static calc_status_t CalcExpression(double *res)
{
	calc_status_t status = CALC_SUCCESS;
 
    while (!StackIsEmpty(operator_stack_g) && CALC_SUCCESS == status)
    {
       	status = MakeCalculation();    	     	                  
    }
    
    if (CALC_SUCCESS == status && 1 == StackSize(num_stack_g))
    {
    	*res = *(double *)StackPeek(num_stack_g);    	
    }
    
    return status;
}

/******************************************************************************/
/***                       Public function definitions                      ***/
/******************************************************************************/

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
 * UB: - if expression contains empty brackets.
 */	
calc_status_t Calculate(const char *expression, double *res)
{
	size_t len = 0;
	calc_status_t ret_status = CALC_SUCCESS;
	char *cpy_exp = NULL;
	
	assert(expression);
	
	len = strlen(expression);
	cpy_exp = (char *)malloc(sizeof(char) * (len + 1));
	
	if (!cpy_exp)
	{
		return CALC_MEM_ALLOC_ERROR;
	}
	
	memcpy(cpy_exp, expression, len + 1);
	ret_status = IsParBalanced(cpy_exp, len);
	
	if (CALC_SUCCESS == ret_status)
	{
		len = strlen(cpy_exp); 

		if (CALC_SUCCESS == (ret_status = AllocationStacks(len))) 
		{	 
		 	if (CALC_SUCCESS == (ret_status = ParseExpression(cpy_exp)))
			{
		 		/* calculate the expression and returns the status of it*/
		 		ret_status = CalcExpression(res); 
		 		
			}
			
			/* after the last calculation - destroying the stacks  */
			StackDestroy(num_stack_g);
			StackDestroy(operator_stack_g);
		}	
	}

	FREE(cpy_exp);
	
	return ret_status;	
}		

