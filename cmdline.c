#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
	int status;
	pid_t pid;
	pid = fork ();
	if (pid == 0)
	{
		//child process

		if(argc != 1 && (strcmp(argv[1], "ls") == 0 || strcmp(argv[1],"ps")==0))
		{
			printf ( "\nOriginal Child PID: %d\n", getppid());
            printf ( "Grandchild PID: %d\n\n", getpid());

            char *cmd[argc];
            int i;
            for(i=0;i<argc-1;i++)
            {
               cmd[i]=argv[i+1];
            }
            cmd[argc-1]=(char *)0;
            //Execution of User entered command
            execvp(argv[1], cmd);

			status=0;
		}
		else
		{
			printf("Improper command \n");
        }

	}
	//fork failure
	else if (pid < 0)
    {
        printf("fork failure");
        status = -1;
    }
    //parent process.  Wait for child
	else if (waitpid (pid, &status, 0) != pid)
		status = -1;
		sleep(1);
		printf ( "\nOriginal Parent PID: %d\n", getppid());
		printf ( "Original Child PID: %d\n", getpid());

	return status;
}
