#define _XOPEN_SOURCE (600)	/* for signal.h symbols definitions:
                               must come before includes       */
#include <signal.h>		    /*             signal              */
#include <sys/types.h>	    /*          waitpid & fork         */
#include <unistd.h>		    /*            fork, pause          */
#include <stdio.h>		    /*              printf             */
/*----------------------------------------------------------------------------*/

static void UserHandler(int signal);

static int to_print = SIGUSR1;

int main()
{
	struct sigaction usr_action = {0};
	
	pid_t parent_id = getppid();
	
	usr_action.sa_handler = UserHandler;
	sigaction(SIGUSR1, &usr_action, NULL);

	while (1)
	{
		while (SIGUSR1 != to_print);
		sleep(1);
	
		kill(parent_id, SIGUSR2);
		to_print = SIGUSR2;
	
		printf("\n signal recieved from PARENT");
		
		sleep(1);
	}
	
	return 0;
}


/*sig action that prints for SIGUSR1*/
static void UserHandler(int signal)
{
	to_print = signal;
}
