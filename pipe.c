#include "shell.h"

void piping(char* input)
{
	int i=0;
	int pid;
	int fildes[2];

	int no_of_pipes = 0;
	char* inp;
	
//	printf("%s\n", input);
	
	char* same_input;
	stpcpy(same_input, input);

	while((inp = strsep(&input,"|")) != NULL)
	{
//		printf("%s\n", inp);
		no_of_pipes++;
	}
	no_of_pipes--;
//	printf("%d\n", no_of_pipes);

//	printf("%s\n", same_input);

	int in_fd;
	int out_fd;
	int status, prev, nxt;

	while((inp = strsep(&same_input,"|")) != NULL)
	{	
//		printf("%s\n", inp);
		if (i == 0)
		{
			prev = 0;
			nxt = 1;
		}
		else if (i == no_of_pipes)
		{
			prev = 1;
			nxt = 0;
		}
		else nxt = prev = 1;
		if (prev)
		{
//			printf("%d %d %d\n",prev,nxt,i);
			close(fildes[1]);
			in_fd = dup(0);
	
			if (dup2(fildes[0], 0) == -1)
				fprintf(stderr, "Error: dup2 failed\n");
	
			close(fildes[0]);
		}
		if (nxt)
		{
			pipe(fildes);
			out_fd = dup(1);
			
//			printf("%d %d %d\n",prev,nxt,i);
			if (dup2(fildes[1], 1) == -1)
				fprintf(stderr, "Error: dup2 failed\n");
	
		}
		pid = fork();
		if(pid < 0)
		{
			fprintf(stderr, "Error: cannot create process\n");
		}
		// fprintf(stderr,"%d\n", pid);
		if (pid == 0)
		{
			// fprintf(stderr, "%s\n", inp);
			char** args = split_line(inp);
			redirection_piping(args);
			exit(0);
		}
		else 
		{
			waitpid(pid, &status, WUNTRACED);
			dup2(in_fd,0);
			dup2(out_fd,1);
			close(in_fd);
			close(out_fd);
		}

		i++;
	}
}