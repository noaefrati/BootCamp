
#include <stdio.h>
#include <stdlib.h>



int main()
{
	int *ptr = (int*)malloc(1000 *sizeof(int));
	delete ptr;
	
	int *ptr2 = new int[1000];

	free(ptr2);
	printf ("*-*!\n");
	//float *f = new float(12.6);
	//delete f;
	
	//f = new float[15];
	//delete[] f;
	
	//int *a = new int(0);
	//delete a; a = 0;
	//delete a; 
	
	//printf ("0 go!\n");
	return 0;
}


