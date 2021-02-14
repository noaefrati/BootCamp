#define _XOPEN_SOURCE (600)	/* for signal.h symbols definitions:
                               must come before includes       */
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

/*#include <sys/siginfo.h>*/


/*char *arg_list[] = {"child.out", NULL};*/
static int recieved_sig = SIGUSR2;

void Handler(int sig)
{
	recieved_sig = sig;
}

int main(int argc, char *argv[])
{
	pid_t child_pid =  atoi(argv[1]);
	
	struct sigaction usr_action = {0};
	usr_action.sa_handler = &Handler;
	sigemptyset(&usr_action.sa_mask);
	usr_action.sa_flags = SA_SIGINFO;
	(void)argc;
	
	
	if (0 > sigaction(SIGUSR2, &usr_action, NULL))
	{
		
		printf("Error in sigaction\n");
		return 1;
	}

	while(1)
	{			
		while (recieved_sig != SIGUSR2);
		
		sleep(2);
		printf("Ping\n");
		kill(child_pid, SIGUSR1);
		recieved_sig = SIGUSR1;
		sleep(2);
	}

	return 0;
}
