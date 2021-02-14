#include<stdio.h>
#include<stdlib.h>


void Swap2SizeT(size_t *size1, size_t *size2);
void Swap2SizeTPointers(size_t **size1, size_t **size2);

int main()
{
	size_t size1 = 3;
	size_t size2 = 5;
	size_t *ptr1 = &size1;
	size_t *ptr2 = &size2;
	
	
	printf("----------------------------------Part a----------------------------------------\n");
	printf("Before swap size1 = %lu, size2 = %lu\n", size1, size2);
	printf("Before swap: &size1 = %p, &size2 = %p\n",(void *) &size1, (void *) &size2);
	Swap2SizeT(&size1, &size2);
	printf("After swap size1 = %lu, size2 = %lu\n", size1, size2);
	printf("After swap : &size1 = %p, &size2 = %p\n",(void *)&size1, (void *)&size2);
	
	printf("----------------------------------Part b----------------------------------------\n");
	printf("Before swap *ptr1 = %lu, *ptr2 = %lu\n", *ptr1, *ptr2);
	printf("Before swap ptr1 = %p, ptr2 = %p\n",(void *)ptr1, (void *)ptr2);
	Swap2SizeTPointers(&ptr1,&ptr2);
	printf("After swap *ptr1 = %lu, *ptr2 = %lu\n", *ptr1, *ptr2);
	printf("After swap ptr1 = %p, ptr2 = %p\n",(void *)ptr1, (void *)ptr2);
	
	printf("----------------------------------Part c----------------------------------------\n");
	printf("Before swap *ptr1 = %lu, *ptr2 = %lu\n", *ptr1, *ptr2);
	printf("Before swap ptr1 = %p, ptr2 = %p\n",(void *)ptr1, (void *)ptr2);
	Swap2SizeT((size_t *)&ptr1, (size_t *)&ptr2);
	printf("After swap *ptr1 = %lu, *ptr2 = %lu\n", *ptr1, *ptr2);
	printf("After swap ptr1 = %p, ptr2 = %p\n",(void *)ptr1, (void *)ptr2);
	
	return 0;
}

void Swap2SizeT(size_t *size1, size_t *size2)
{
	size_t temp = *size1;
	*size1 = *size2;
	*size2 = temp;
}

void Swap2SizeTPointers(size_t **size1, size_t **size2)
{
	size_t *temp = *size1;
	*size1 = *size2;
	*size2 = temp;
	
}


