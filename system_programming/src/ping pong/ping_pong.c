#define _XOPEN_SOURCE (500)	/* for signal.h symbols definitions:
                               must come before includes       */
#include <signal.h>		    /*             signal              */
#include <stdlib.h>		    /*              exit               */
#include <sys/types.h>	    /*          waitpid & fork         */
#include <unistd.h>		    /*            fork, pause          */
#include <stdio.h>		    /*              printf             */
/*----------------------------------------------------------------------------*/

static int recieved_sig = SIGUSR2;

int parent_pid = 0;

static void UserHandler(int signal);
static int PingPonfWithFork(void);
static int PingPongForkAndExec(void);
static void handler(int sig, siginfo_t* info, void *vp);

int main()
{
	return  PingPongUnrealetedProc();
}

int PingPongUnrealetedProc(void)
{
	struct sigaction usr_action = {0};
	
	usr_action.sa_sigaction = handler;
    sigemptyset(&usr_action.sa_mask);
    usr_action.sa_flags = SA_SIGINFO; 
	
	if (0 > sigaction(SIGUSR1, &usr_action, NULL))
	{
		printf("Error in sigaction\n");
		return 1;
	}
	
	printf("pid: %d\n", getpid());
	while(1)
	{
		
		while (recieved_sig!= SIGUSR1);
		sleep(2);
		printf("Pong\n");
		kill(parent_pid, SIGUSR2);
		recieved_sig = SIGUSR2;
		sleep(2);
	}
	

	return 0;
}

int PingPongForkAndExec(void)
{
	pid_t child_pid = 0;
	struct sigaction user_act = {0};
	
	user_act.sa_handler = &UserHandler;
	sigaction(SIGUSR2, &user_act, NULL);
	
	child_pid = fork();
	
	/* case : fork failed */
	if (0 > child_pid) 
	{
		return 1;
	}
	
	while (1)
	{
		/*parent case: he recieved his child pid*/
		if (0 < child_pid)
		{
			while (SIGUSR2 != recieved_sig);
			sleep(1);
			
			/* the parent will send SIGUSR1 to his child */
			kill(child_pid, SIGUSR1);
			
			recieved_sig = SIGUSR1;
			printf("\n signal recieved from CHILD");
			
			sleep(1);
		}
		else if (0 == child_pid)
		{
			execv("./ex2_ping_pong.out", NULL);
		}
	}
	
	return 0;
}
int PingPonfWithFork(void)
{
	pid_t child_pid = 0;	
	
	struct sigaction user_act = {0};
	
	user_act.sa_handler = &UserHandler;
	
	sigaction(SIGUSR1, &user_act, NULL);
	sigaction(SIGUSR2, &user_act, NULL);
	
	child_pid = fork();
	
	if (0 > child_pid) /* case : fork failed */
	{
		return 1;
	}
	
	while(1)
	{
		if (0 < child_pid) /* parent process */
		{
			while (SIGUSR2 != recieved_sig);
			sleep(1);
			/* the parent will send SIGUSR1 to his child */
			kill(child_pid, SIGUSR1);
				
		  	recieved_sig = SIGUSR1;
			printf("\n signal recieved from CHILD");
				
			sleep(1);
		}
		else /* in the child process */
		{
			while (SIGUSR1 != recieved_sig);
			sleep(1);
			kill(getppid(),SIGUSR2); /* send to parent */
			
			recieved_sig = SIGUSR2;
			printf("\n\t\t\t\tsignal recieved from PARENT");
			
			sleep(1);
		}
		
	}
	
	return (0);
}
void UserHandler(int signal)
{
	recieved_sig = signal;
}
void handler(int sig, siginfo_t* info, void *vp)
{ 
	(void)vp;
	parent_pid = info->si_pid;
	recieved_sig = sig;
}

