#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	int i = 7;
	int j = 12;
	int k = 15;
	int *p = &j;
	
	FILE *fp;
	
	if (0 == (fp = fopen("stoopid", "w")))
	{
		printf("well, that didn\'t work!\n");
		return - 1;
	}
	printf("%p\n", (void *)p);
	fprintf(fp, "%p", p);
	
	if (EOF == fclose(fp))
	{
		printf("oh well.\n");
		return - 1;
	}
	
	sleep(30);
	return 0;
}


