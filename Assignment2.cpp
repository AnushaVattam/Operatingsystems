//CS-4328
//Operating Systems
//Anusha Vattam

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>


 main()

{
	char *pathin, *pathout, *argv[20], buf[80], n, *p, history[30][80];
	int m, status, inword, continu, i, x, y, no_of_pipes, r, Begin[10];
	int inf, outf, bg_oper;
	int history_count = 0;

	while (1) {

		inword = 0;
		p = buf;
		m = 0;
		r = 0;
		continu = 0;
		no_of_pipes = 0;
		pathin = NULL;
		pathout = NULL;
		inf = 0;
		outf = 0;
		bg_oper = 0;


		printf("\nshhh> ");
		x = 0;
		while ((n = getchar()) != '\n' || continu){
			history[history_count][x] = n;
			x++;
			if (n == ' ') {
				if (inword) {
				inword = 0;
				*p++ = 0;
				}
			}
			else if (n == '\n') continu = 0;
			else if (n == '\\' && !inword) continu = 1;
			else {
				if (!inword) {
					inword = 1;
					argv[m++] = p;
					*p++ = n;
				}
				else
					*p++ = n;
			}
		}

		*p++ = 0;
		argv[m] = 0;
		history[history_count][x] = 0;
		history_count++;
      if (argv[0] == 0) {
      }
		else if (strcmp(argv[0], "quit") == 0) exit(0);			// exits if the first argument is equal to "quit"

		else if (strcmp(argv[0], "history") == 0) {    	// prints the history array if first argument is equal to "history"
			for (x = 0; x+1 < history_count; x++){
				printf("%s \n", history[x]);
			}
		}
      else if (strcmp(argv[0], "cd") == 0) {
         chdir(argv[1]);
      }

		else{ 																				 // child processes execute
		  Begin[r] = 0;
		  r++;
		  for (x = 0; x < m; x++) {
				if (*argv[x] == '<') {
					pathin = argv[x + 1];
					argv[x] = 0;
				}
				else if (*argv[x] == '>') {
					pathout = argv[x + 1];
					argv[x] = 0;
				}
				else if (*argv[x] == '|') {
					no_of_pipes++;
					argv[x] = (char *)0;
					Begin[r] = (x + 1);
					r++;
				}
				else if (*argv[x] == '&') {
					bg_oper = 1;
					argv[x] = (char *)0;
				}
		  }

		  int oldp[2];
		  int newp[2];
		  pid_t pid;

		  if (pathin != NULL){
				inf = open(pathin, O_RDONLY);
		  }
		  if (pathout != NULL){
				outf = open(pathout, O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		  }

		  for (i = 0; i <= no_of_pipes; i++){
				if ((i + 1) <= no_of_pipes){
					pipe(newp);
				}
				pid = fork();

				if (pid == 0) {

						if (i > 0) {
							close(0);
							dup(oldp[0]);
							close(oldp[0]);
							close(oldp[1]);
						}
						if ((i + 1) <= no_of_pipes) {
							close(newp[0]);
							close(1);
							dup(newp[1]);
							close(newp[1]);
						}
						if ((pathin != NULL && (i == 0))){
							close(0);
							dup(inf);
							close(inf);
						}
						if ((i == no_of_pipes) && (pathout != NULL)){
            dup2(outf, STDOUT_FILENO);
            close(outf);
          }
					execvp(argv[Begin[i]], &argv[Begin[i]]);
					// if execl returns, the call has failed, so ...
					perror("execl failed to execute command");
				}
				else if (pid > 0) { 	// parent process
					if (i > 0) {
						close(oldp[0]);  			//this disconnects the previous pipe from the parent
						close(oldp[1]);	 			//this disconnects the previous pipe from the parent
					}
					oldp[0] = newp[0];
					oldp[1] = newp[1];


				}
		  }

			if (no_of_pipes){
				close(newp[0]);
				close(newp[1]);
			}
 if(bg_oper == 0){
             wait(&status);
          }

		}

	}
}



