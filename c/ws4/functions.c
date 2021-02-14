/******************************************************************************************************************************
*Description: When the 'A' or 'T' keys are pressed, respectively "A pressed" or "T pressed" should be printed in the terminal.
* When 'Esc' is pressed, the program should, the program  should exit.
*Author: Noa Efrati
*Reviewer: Galit Vaknin
*Date:4/11/20
*Infinity Labs OL97
*******************************************************************************************************************************/

#include <stdio.h>/*getchar*/
#include <string.h>/*puts*/
#include <stdlib.h>/*system*/
/*Implement the solution with if-else*/
void IfElse();

/*Implement the solution with switch & case*/
void SwitchCase();

/*Implement the solution with Lut*/
void Lut();

/*Print A to the terminal*/
void PrintA();

/*Print T to the terminal*/
void PrintT();

/*Print Esc and exit the terminal*/
void PrintEsc();

/*Using this function in Lut() function, if the index where it does not match A or T or ESC */
void DoNothing();

int main()
{
	printf("----------------------------Running IfElse() function:----------------------- \n");
	IfElse();
	
	printf("----------------------------Running SwitchCase() function:----------------------- \n");
	SwitchCase();
	
	printf("----------------------------Running Lut() function:----------------------- \n");
	Lut();
	
	return (0);
	
}
void IfElse()
{
	char input = '\0';
	system("stty -icanon -echo");
	
	while (input != 27)
	{
		input = getchar();
		if (input == 'a' || input == 'A')
		{
			PrintA();
			
		}
		else if (input == 'T' || input == 't')
		{
			PrintT();
			
		}
		else if (input == 27)
		{
			PrintEsc();
			
		}				
	}
	
}

void SwitchCase()
{
	char input = '\0';
	system("stty -icanon -echo");
	
	while (input != 27)
	{
		
		input = getchar();
		switch(input)
		{
			case 'a':
			PrintA();
			break;
		
			case 'A':
			PrintA();
			break;
		
			case 'T':
			PrintT();
			break;
		
			case 't':
			PrintT();
			break;
		
			case 27:
			PrintEsc();
			break;
		}		
	}
}
void PrintA()
{
	puts("A pressed");
}
void PrintT()
{
	puts("T pressed");
}
void PrintEsc()
{
	puts("Press Esc");
	system("stty icanon echo"); /*bring back the echo in the terminal*/

}
void DoNothing()
{
	/*empty*/
}
void Lut()
{	
	void (*func_ptr[256])();
          char input = '\0';
	int i = 0;
		
	for (; i < 256; ++i)
	{
		if (i == 97 || i == 65)
		{
			func_ptr[i] = PrintA;
			
		}
		else if (i == 84 || i == 116)
		{
			func_ptr[i] = PrintT;
			
		}
		else if (i == 27)
		{
			func_ptr[i] = PrintEsc;
			
		}
		else
		{
			func_ptr[i] = DoNothing;	
		}	
	}
	
	system("stty -icanon -echo");
          input = getchar();
	
	while (input != 27)
         {
            (func_ptr[(int)input])();
            input = getchar();
         }
          (func_ptr[(int)input])(); /*if the input was esc ,so exit*/
	
	
}

