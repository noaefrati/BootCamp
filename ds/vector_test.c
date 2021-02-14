/*************************************************************************** 
 * Description: Test the implementation of Dynamic Vector's functions.     *
 * Author: Noa Efrati                                                      *
 * Reviewer: None                                                          *
 * Date: 19.11.20                                                          *
 * Infinity Labs OL97                                                      *
 ***************************************************************************/

#include <stdio.h>             /*printf*/
#include "../include/vector.h" /* stack functions */

/******************** Functions Declarations ********************/

void TestVectorCreateVectorDestroy(void);
void TestVectorSize(void);
void TestVectorGetAccessToElementAt(void);
void TestVectorPushBack(void);
void TestVectorPopBack(void);
void TestVectorReserve(void);

/*
static void PrintSuccesOrFailure(int is_success, char *function_name);
*/

/******************** main function ********************/

int main(void)
{
	
	TestVectorCreateVectorDestroy();
	TestVectorSize();
	TestVectorGetAccessToElementAt();
	TestVectorPushBack();
	TestVectorPopBack();
	TestVectorReserve();
	
	return 0;
}
void TestVectorCreateVectorDestroy(void)
{
	size_t element_size = sizeof(int);
	size_t initial_capacity = 100;
	vector_t *vector = VectorCreate(element_size, initial_capacity);
	
	printf("Vector was created without crashing!\n");
	
	VectorDestroy(vector);
	
	printf("Vector was destroyed without crashing!\n");
	
	printf("\n");
}
void TestVectorSize(void)
{

	size_t element_size = 8;
	size_t initial_capacity = 10;
	long num = 30;
	int i = 0;
	int success = 1;
	int size_expected[] = {4, 3, 2, 1};
	int size_vector[4] = {0};
	vector_t *vector = VectorCreate(element_size, initial_capacity);
	
	VectorPushBack(vector, &num);
	VectorPushBack(vector, &num);
	VectorPushBack(vector, &num);
	VectorPushBack(vector, &num);
	
	printf("size expected :4, 3, 2, 1\n");
	
	for (; 4 > i; ++i)
	{
		 size_vector[i] = VectorSize(vector);
		 VectorPopBack(vector);
		if(size_expected[i] != size_vector[i])
		{
			success = 0;
		}
		
	}
	if (1 == success)
	{
		printf("VectorSize was a SUCCESS!\n");
	}
	else
	{
		printf("VectorSize was a FAILURE!\n");
	}
	VectorDestroy(vector);

}

void TestVectorGetAccessToElementAt(void)
{
	size_t element_size = sizeof(long);
	size_t initial_capacity = 10;
	size_t i = 0;
	int success = 1;
	long num = 70;
	long elem_vector[4] = {0};
	vector_t *vector = VectorCreate(element_size, initial_capacity);
	
	VectorPushBack(vector, &num);
	VectorPushBack(vector, &num);
	VectorPushBack(vector, &num);
	VectorPushBack(vector, &num);
	
	printf("elements expected :%ld , %ld, %ld, %ld\n",num, num, num, num);
	
	for (; 4 > i; ++i)
	{
		 elem_vector[i] = *(long *)(VectorGetAccessToElementAt(vector, i));
		
		
		if(num != elem_vector[i])
		{
			success = 0;
		}
		
	}
	if (1 == success)
	{
		printf("VectorGetAcessToElementAt was a SUCCESS!\n");
	}
	else
	{
		printf("VectorGetAcessToElementAt was a FAILURE!\n");
	}
	VectorDestroy(vector);
}
void TestVectorPushBack(void)
{
	size_t element_size = sizeof(long int);
	size_t initial_capacity = 10;
	size_t i = 0;
	int success = 1;
	long elements_expected[] = {4, 3, 2, 1};
	long elem_vector[4] = {0};
	vector_t *vector = VectorCreate(element_size, initial_capacity);
	
	
	printf("elements expected :%ld , %ld, %ld, %ld\n",
	                          elements_expected[0], elements_expected[1],
	                          elements_expected[2], elements_expected[3]);
	
	for (; 4 > i; ++i)
	{
		 
		VectorPushBack(vector, &elements_expected[i]);
		elem_vector[i] = *(long *)( VectorGetAccessToElementAt(vector, i));
		if(elements_expected[i] != elem_vector[i])
		{
			success = 0;
		}
		
	}
	
	if (1 == success)
	{
		printf("VectorPushBack was a SUCCESS!\n");
	}
	else
	{
		printf("VectorPushBack was a FAILURE!\n");
	}
	VectorDestroy(vector);
}
void TestVectorPopBack(void)
{
	size_t element_size = 8;
	size_t initial_capacity = 10;
	long num = 30;
	int i = 0;
	int success = 1;
	int size_expected[] = {4, 3, 2, 1};
	int size_vector[4] = {0};
	vector_t *vector = VectorCreate(element_size, initial_capacity);
	
	VectorPushBack(vector, &num);
	VectorPushBack(vector, &num);
	VectorPushBack(vector, &num);
	VectorPushBack(vector, &num);
	
	printf("size expected :4, 3, 2, 1\n");
	
	for (; 4 > i; ++i)
	{
		 
		size_vector[i] = VectorSize(vector);
		VectorPopBack(vector);
		
		if(size_expected[i] != size_vector[i])
		{
			success = 0;
		}
		
	}
	if (1 == success)
	{
		printf("VectorPopBack was a SUCCESS!\n");
	}
	else
	{
		printf("VectorPopBack was a FAILURE!\n");
	}
	VectorDestroy(vector);

}
void TestVectorReserve(void)
{
	size_t element_size = sizeof(long int);
	size_t initial_capacity = 4;
	long num = 30;
	int i = 0;
	int success = 1;
	int size_expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int size_vector[8] = {0};
	vector_t *vector = VectorCreate(element_size, initial_capacity);
	
	printf("size expected : 1, 2, 3, 4\n");
	
	for (; 4 > i; ++i)
	{
		VectorPushBack(vector, &num);
		size_vector[i] = VectorSize(vector);
		
		if(size_expected[i] != size_vector[i])
		{
			success = 0;
		}	
	}
	
	VectorReserve(vector, 8);
	
	printf("size expected :5, 6, 7, 8\n");
	
	for (i = 4; 8 > i; ++i)
	{
		VectorPushBack(vector,&num);
		size_vector[i] = VectorSize(vector);
		
		if(size_expected[i] != size_vector[i])
		{
			success = 0;
		}
		
	}
	
	if (1 == success)
	{
		printf("VectorReserve was a SUCCESS!\n");
	}
	else
	{
		printf("VectorReserve was a FAILURE!\n");
	}
	VectorDestroy(vector);
}

