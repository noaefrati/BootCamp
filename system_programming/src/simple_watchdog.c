#include <stdio.h>		/* printf */
#include <sys/types.h>	/* fork   */
#include <unistd.h>		/* fork   */
#include <sys/wait.h>	/* wait   */
#include <errno.h>		/* perror */
#include <stdlib.h>
#include <string.h>     /* strcat */

/*
	The  exec() family of functions replaces the current process image with a 
	new process image. The functions described in this manual page are 
	front-ends for execve(2). 
	(See the manual page for execve(2) for further details about the replacement
	of the current process image.)
    The initial argument for these functions is the name of a file that is
    to be executed.
    The functions can be grouped based on the letters following the
    "exec" prefix.
   
     v - execv(), execvp(), execvpe()
     The char *const argv[] argument is an array of pointers to null-terminated
     strings that represent the argument list available to the new program.
     The  first  argument,  by convention, should point to the filename 
     associated with the file being executed. 
     The array of pointers must be terminated by a null pointer.
     
      p - execlp(), execvp(), execvpe()
      These functions duplicate the actions of the shell in searching for an 
      executable file if the specified filename does not contain a slash (/) 
      character. The file is sought in the colon-separated list  of directory
      pathnames specified in the PATH environment variable.  If this variable
      isn't defined, the path list defaults to a list that includes the
      directories returned by confstr(_CS_PATH) (which typically returns the
      value "/bin:/usr/bin") and possibly also the current working directory;
      see NOTES for  further details.

      If the specified filename includes a slash character, then PATH is 
      ignored, and the file at the specified pathname is executed.

      In addition, certain errors are treated specially.

      If permission is denied for a file (the attempted execve(2) failed with 
      the error EACCES), these functions will continue searching the rest of the
      search path. If no other file is found, however, they will return with
      errno set to EACCES.

      If the header of a file isn't recognized (the attempted execve(2) failed
      with the error ENOEXEC), these functions will execute the shell (/bin/sh)
      with the path of the file as its first argument.  (If this attempt fails,
      no further searching is done.)

      All  other  exec()  functions  (which do not include 'p' in the suffix)
      take as their first argument a (relative or absolute) pathname that 
      identifies the program to be executed.



*/


/* fork()  creates  a  new  process  by duplicating the calling process.
 * The new process is referred to as the child process. 
 * The calling process is referred to as the parent process.
 */
 /* On  success,  the PID of the child process is returned in the parent,
	 * and 0 is returned in the child. 
	 * On failure, -1 is returned in the parent, 
	 * no child process is created, and errno is set appropriately.
     */
int ForkImpl(int argc, char *argv[])
{
	static size_t count = 0 ;
	int status = 0;
	pid_t pid = 0;
	char *args[3] = {NULL};
	
	
	/*
	  args[0] = program name to run(sleep \ printmsg)
	  args[1] = parameters to the called program:
	  			num of seconds to sleep, msg to print.
	  args[2] = NULL
	 */
	if (3 != argc)
	{
		return 1; /* Error not enoght arguments */
	}
	
	args[0] = argv[1];
	args[1] = argv[2];
	args[2] = NULL; /* arguments from the command line should end with NULL*/
	
	while (1)
	{
		pid = fork();
		

		if (0 == pid)
		{
	   
			/* when dupicating a process by fork the status of the new child
			  process is equivilent to 0
			 */
			execv(args[0], args);
			 
			 /* if get here sfter call execv it means that the function failed*/
			perror("child teminated due to error");
		}
		else if (0 < pid)
		{
			/* after creating a new child an calling the exec function, the
			   parent process should wait till the child will be done
			*/
			printf ("this is the parent process, with id %d\n", (int)getpid());
			printf ("the child’s process ID is %d\n", (int)pid);
			
			wait(&status);
			
			if (WIFEXITED(status))
			{
				
				printf("Child ran successfully\n");
			}
			else
			{
				if(WIFSIGNALED(status))
				{
					printf("child was terminated with signal %d\n", WTERMSIG(status));
				}
			}
		
		}
		else
		{
		
			printf("Error in fork()\n");
			
			return (-1);
		
		}
		if (3 == count)
		{
			break;
		}
		++count;
	}

}
int SystemImpl(int argc, char *argv[])
{
	int status = 0;
	size_t len = strlen(argv[1]);
	size_t len2 = strlen(argv[2]);
	char *abs_path = (char *) calloc((len +len2 +4), sizeof(char));
	 
	strcat(abs_path, "./");
	strcat(abs_path + 2, argv[1]);
	
	abs_path[len + 2] =' ';
	
	strcat(abs_path + len + 3,  argv[2]);
	abs_path[ len + len2 + 1] = '\0';
	printf("abs_path : %s\n", abs_path);
	status = system(abs_path);
	printf("system returned: %d\n", WEXITSTATUS(status));
	
	while (1)
	{
		status = system(abs_path);
		
		if (0 != WEXITSTATUS(status))
		{
			break;
		}
		if (WIFSIGNALED(status))
		{
			printf("signal accured\n");
			printf("the child has terminated by signal: %d\n", 
				WTERMSIG(status));
				break;
		}		
	}
	
	free(abs_path);
	return 0;
}
int main(int argc, char* argv[])
{
	
	return SystemImpl(argc, argv);
}
