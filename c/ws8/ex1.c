/******************************************************************************************************************************/
/*Description: A program that asks the user to print the value of each element,                                               */
/*add an integer to all the elements and release all the memory.                                                              */    
/*Author: Noa Efrati                                                                                                          */
/*Reviewer: Avraham Sharon                                                                                                    */
/*Date: 11/11/20                                                                                                              */
/*Infinity Labs OL97                                                                                                          */
/******************************************************************************************************************************/


/*printf*/
#include <stdio.h>

/*strcpy*/
#include <string.h>

/*malloc*/
#include <stdlib.h>

#define MAX_ELEMENTS_SIZE 6
#define MAX_STRING_SIZE 25

typedef enum status
{
	FAILURE,
	SUCCESS
}_status;

typedef struct Element
{	
	void      *data;	
	_status (*add_ptr)(void * , int);
	void (*print_ptr)(void *);
	_status (*cleanup_ptr)(void *);

	
}element;

/*Adding an int value to every member in the array. and calls the appropriate add function for the element*/
void AddVal(element arr[]);

/*Goes through all the members in the array and calls the appropriate print function for the element*/
void PrintAllElements(element arr[]);

/*Releases the memory of each element in the array*/
void CleanupElements(element arr[]);

/*Each element has a corresponding print function, which prints the current value of the element*/
void PrintIntElement(void *value);
void PrintFloatElement(void *value);
void PrintStringElement(void *value);

/*Add an integer to each of the elements with reference to the variable type.*/ 
/*each function reurn status of the operation*/
_status AddToInt(void *value, int to_add);
_status AddToFloat(void *value, int to_add);
_status AddToString(void *value, int to_add);

/*Memory release for each of the elements*/
/*each function reurn status of the operation*/
_status CleanupInt(void *element);
_status CleanupFloat(void *element);
_status CleanupString(void *element);

/*Initializes all the elements in the array and returns the address of the array*/
element *InitElementsArr(element elements_arr[]);

/*A user menu that runs on the following options: Add an integer, print and free memory.*/
void RunProgram(element arr[]);

int main(void)
{
	element *elemets_arr = malloc(MAX_ELEMENTS_SIZE * sizeof(element));/*allocate array of elements*/
	InitElementsArr(elemets_arr);
	RunProgram(elemets_arr);
	
	return 0;
}

void RunProgram(element arr[])
{
	int is_running = 1;
	
	while (is_running != 0)
	{
		int input = 0;
		
		printf("\n************To keep the program running enter 1, to exit enter 0.************** \n");
		scanf("%d", &is_running);
		
		/*If the user accidentally enters an incorrect number other than 0 or 1, the program will continue to run */
		if (1 != is_running && 0 != is_running)
		{
			 is_running = 1;
		}	
		
		printf("\nEnter 1 - to add int value to all the elements, 2 - to print the elements,\n");
		printf("3 - to cleanup all the elements.\n");
		scanf("%d", &input);
		
		switch(input)
		{
			
			case 1:
			AddVal(arr);		
			break;
		
			case 2:
			PrintAllElements(arr);	
			break;
			
			case 3:
			CleanupElements(arr);
			is_running = 0; /*to stop the runn after clean all up*/
			break;
			
			default:
			printf("Wrong number, try again\n");
		}
				
	} 
}
element *InitElementsArr(element elements_arr[])
{

	elements_arr[0].data = malloc(sizeof(int));
	*((int *)(elements_arr[0].data)) = 10;
	elements_arr[0].add_ptr = &AddToInt;
	elements_arr[0].print_ptr = &PrintIntElement;
	elements_arr[0].cleanup_ptr = &CleanupInt;
	
	elements_arr[1].data = malloc(sizeof(float));;			
	*((float *)(elements_arr[1].data)) = 35.5;
	elements_arr[1].add_ptr = &AddToFloat;
	elements_arr[1].print_ptr = &PrintFloatElement;
	elements_arr[1].cleanup_ptr = &CleanupFloat;
	
	elements_arr[2].data = malloc(sizeof(char)*MAX_STRING_SIZE);
	(elements_arr[2].data) = strcpy(elements_arr[2].data,"hello");
	elements_arr[2].add_ptr = &AddToString;
	elements_arr[2].print_ptr = &PrintStringElement;
	elements_arr[2].cleanup_ptr = &CleanupString;		
	
	elements_arr[3].data = malloc(sizeof(int));;
	*((int *)(elements_arr[3].data)) = 100;
	elements_arr[3].add_ptr = &AddToInt;
	elements_arr[3].print_ptr = &PrintIntElement;
	elements_arr[3].cleanup_ptr = &CleanupInt;
	
	elements_arr[4].data = malloc(sizeof(float));;			
	*((float *)(elements_arr[4].data)) = 50.5;
	elements_arr[4].add_ptr = &AddToFloat;
	elements_arr[4].print_ptr = &PrintFloatElement;
	elements_arr[4].cleanup_ptr = &CleanupFloat;
	
	elements_arr[5].data = malloc(sizeof(char)*MAX_STRING_SIZE);
	elements_arr[5].data = strcpy(elements_arr[5].data,"you");;
	elements_arr[5].add_ptr = &AddToString;
	elements_arr[5].print_ptr = &PrintStringElement;
	elements_arr[5].cleanup_ptr = &CleanupString;	
	
	return elements_arr;	
}

void PrintAllElements(element arr[])
{
	int i = 0;
	for (; MAX_ELEMENTS_SIZE > i; ++i)
	{
		arr[i].print_ptr(arr[i].data);
				
	}
	printf("\n");
}
void PrintIntElement(void *value)
{
	printf(" %d ", *(int *)value);

}

void PrintFloatElement(void *value)
{
	printf(" %f ", *(float *)value);

}

void PrintStringElement(void *value)
{
	printf(" %s ", (char *)value);

}
void AddVal(element arr[])
{
	int i = 0;
	int to_add = 0;
	
	printf("enter a value to add to all elements.\n");
	scanf("%d", &to_add);
	
	for (i = 0; MAX_ELEMENTS_SIZE > i; ++i)
	{
		
		if (SUCCESS == arr[i].add_ptr(arr[i].data, to_add))
		{
			printf("add to value completed successfully!\n");
		}
		else
		{
			printf("add to value failed.\n");
		}
	}
}
_status AddToInt(void *value, int to_add)
{
	*(int *)value += (int) to_add;
	
	if (value == NULL)
	{
		return FAILURE;
	}
	return SUCCESS;
}
_status AddToFloat(void *value, int to_add)
{
	*(float *)value += (float) to_add;
	
	if (value == NULL)
	{
		return FAILURE;
	}
	return SUCCESS;
}
_status AddToString(void *value, int to_add)
{
	char buffer[MAX_STRING_SIZE] = "";
	
	sprintf(buffer, "%d", to_add); /*store to_add in buffer*/
	strncat(value, buffer, strlen(buffer));
	
	if (value == NULL)
	{
		return FAILURE;
	}
	return SUCCESS;
}
void CleanupElements(element arr[])
{
	int i = 0;
	for (; MAX_ELEMENTS_SIZE > i; ++i)
	{
		if (SUCCESS == arr[i].cleanup_ptr(arr[i].data))
		{
			printf("cleanup value completed successfully!\n");
		}
		else
		{
			printf("cleanup value failed!\n");
		}
	}
	free(arr);
	arr = NULL;
}

_status CleanupInt(void *element)
{
	int *original = (int *) element;
	
	if (original == element)
	{
		free(element);
		element = NULL;
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
	
	
}
_status CleanupFloat(void *element)
{
	float *original =(float *) element;
	
	if (original == element)
	{
		free(element);
		element = NULL;
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
	
}
_status CleanupString(void *element)
{
	char *original =(char *) element;
	
	if (original == element)
	{
		free(element);
		element = NULL;
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
	
}
	





