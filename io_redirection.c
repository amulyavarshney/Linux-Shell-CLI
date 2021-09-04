#include "shell.h"

void redirection_execute(char** args)
{
	if(args[0])
	{
		if(!strcmp(args[0],"echo"))
		{ 
			echo(args);
		}
		else if(!strcmp(args[0],"pwd"))
		{
			pwd();
		}
		else if(!strcmp(args[0],"cd"))
		{
			cd(args);
		}
		else if(!strcmp(args[0],"ls"))
		{
			ls(args);
		}
		else if(!strcmp(args[0],"pinfo"))
		{
			pinfo(args);
		}
		else if(!strcmp(args[0],"setenv"))
		{
			execute_setenv(args);
		}
		else if(!strcmp(args[0],"unsetenv"))
		{
			execute_unsetenv(args);
		}
		else if(!strcmp(args[0],"jobs"))
		{
			jobs();
		}
		else if(!strcmp(args[0],"kjob"))
		{
			kjob(args);
		}
		else if(!strcmp(args[0],"fg"))
		{
			fg(args);
		}
		else if(!strcmp(args[0],"bg"))
		{
			bg(args);
		}
		else if(!strcmp(args[0],"overkill"))
		{
			overkill();
		}
		else if(!strcmp(args[0],"quit"))
		{
			quit();
		}
		else
			execute(args);
	}
}

void redirection(char** args)
{
	int i=0,c;
	int in=0, out=0, app=0,fd0,fd;
	char new_stdin[100];
	char new_stdout[100];

	while(args[i]!=NULL)
	{
		if(!(strcmp(args[i],"<")))
		{
			in =1;
			args[i]=NULL;
			// c = i; 
			strcpy(new_stdin, args[i+1]);
		}
		else if(!(strcmp(args[i],">")))
		{
			out = 1;
			args[i]=NULL;
			// c = i; 
			strcpy(new_stdout, args[i+1]);
		}
		else if(!(strcmp(args[i],">>")))
		{
			app = 1;
			args[i]=NULL;
			// c = i; 
			strcpy(new_stdout, args[i+1]);
		}
		i++;
	}

	if(in==0 && out==0 && app==0)
	{
		redirection_execute(args);
		return;
	}
	else if(in==1 && out==1)
	{
		if((fd0 = open(new_stdin, O_RDONLY, 0)) < 0) 
		{
    		perror("new_stdin file");
    		return;
        }

		if ((fd = open(new_stdout, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0)
		{ 
			perror("new_stdout file");
			return; 
		}

		int input_fd = dup(STDIN_FILENO);
		dup2(fd0,0);
		close(fd0);

		int output_fd = dup(STDOUT_FILENO);
		dup2(fd,1);
		close(fd);

		redirection_execute(args);
		
		dup2(input_fd, STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(input_fd);
		close(output_fd);
		return;
	}
	else if(in==1 && app==1)
	{
		if((fd0 = open(new_stdin, O_RDONLY, 0)) < 0) 
		{
    		perror("new_stdin file");
    		return;
        }
			
		if ((fd = open(new_stdout, O_CREAT|O_WRONLY|O_APPEND, 0644)) < 0)
		{ 
			perror("new_stdout file");
			return; 
		}

		int input_fd = dup(STDIN_FILENO);
		dup2(fd0,0);
		close(fd0);
		
		int output_fd = dup(STDOUT_FILENO);
		dup2(fd,1);
		close(fd);
		
		redirection_execute(args);
		
		dup2(input_fd, STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(input_fd);
		close(output_fd);
		return;
	}
	else if(in==1)
	{
		if ((fd0 = open(new_stdin, O_RDONLY, 0)) < 0) 
		{
    		perror("new_stdin file");
    		return;
        }
		int input_fd = dup(STDIN_FILENO); // assign min fd -> duplicating stdin for later
		dup2(fd0,0); 
		close(fd0);
		
		redirection_execute(args);
		
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
		return;
	}
	else if(out==1)
	{
		if ((fd = open(new_stdout, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) 
		{ 
			perror("new_stdout");
			return; 
		}
				
		int output_fd = dup(STDOUT_FILENO);
		dup2(fd,1);
		close(fd);
		
		redirection_execute(args);
		
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
		return;
	}
	else if(app==1)
	{
		if ((fd = open(new_stdout, O_CREAT|O_WRONLY|O_APPEND, 0644)) < 0) 
		{ 
			perror("new_stdout");
			return; 
		}
				
		int output_fd = dup(STDOUT_FILENO);
		dup2(fd,1);
		close(fd);

		redirection_execute(args);
		
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
		return;
	}
}