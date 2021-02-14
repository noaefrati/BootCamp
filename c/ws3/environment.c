#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

int NumberLinesEnvp(char **envp);/*This function counts the number of lines in envp*/
char *LowerStr(char *s);/*This function converts all the letters in the given string to lowercase*/

int main(int argc, char **argv, char **envp)
{
	char **env = envp;
	int maxLines = NumberLinesEnvp(envp);
	char **buff = (char **)malloc(maxLines * sizeof(char *)); 
	
	if (!buff)
	{
		return -1;		
	}
	
	int i = 0;
	
 	 for (; i < maxLines; i++)
  	{
		buff[i] = (char *) malloc((strlen(env[i]) + 1)*sizeof(char));	
    		
    		strcpy(buff[i], env[i]);
    		
    		buff[i] = LowerStr(buff[i]);
    		
    		printf("%s\n", buff[i]);    
  	}
  	
  	
  	 for (i = 0; i < maxLines; i++)
  	{
		free(buff[i]);
  	}
  	
  	free(buff);
  	buff = NULL;
 	
 	return 0;
}

int NumberLinesEnvp(char **envp)
{
 	int numLines = 0;
	
	 while ( *envp != 0 )
	 {
	 	envp++;
	 	numLines++;
	 }
	 
	 return numLines;
}

char *LowerStr(char *s)
{	
	int i = 0;
	
	while (*(s + i) != '\0')
	{
		*(s + i) = tolower(*(s + i));
		i++;
	}
	
	return s;
}
