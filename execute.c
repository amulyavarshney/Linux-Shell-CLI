#include "shell.h"

int k_number_of_bg=0;

int pid_foreground_process = -1;

char foreground_process_name[30];

void handler(int signum)
{
	pid_t pid1;
	int status1;
	// pid = wait(NULL); //process id of the exited child process
	pid1 = waitpid(-1, &status1, WNOHANG);

	if(pid1>0)
	{
		for(int j=0; j<k_number_of_bg; j++)
		{
			if(s[j].pid == pid1 && s[j].running == 1)
			{
				fprintf(stdout,"%s process with pid %d exited normally\n", s[j].name, pid1);
				s[j].running = 0;
				break;
			}
		}
	}
}

void execute(char** args)
{
	pid_t pid,wait_pid;
	int status, flag=0, i=0; 
	int status1, wait_pid1;

	// flag=1 -> background process
	// flag=0 -> foreground process

	while(args[i])
	{
		if(!strcmp(args[i],"&")) // if background process
		{
			flag=1;
			args[i] = NULL;
			break;
		}
		i++;
	}

	if(flag==1)
	{
		
		pid = fork(); 
		if(pid < 0)
		{
			fprintf(stderr, "Error: cannot create process\n");
		}
		else if(pid == 0) // running for the child
		{
			setpgid(0, 0); // here first argument is 0 as pid for child is 0
			if(execvp(args[0],args)<0)
			{
				fprintf(stderr, "Error: cannot execute process\n");
				exit(EXIT_FAILURE); // kill child if can't execute command otherwise 2 shells formed
			}
		}
		else 	// running for parent
		{
			setpgid(pid, 0);
			tcsetpgrp(STDIN_FILENO, getpgrp()); 
			printf("%d\n",pid); // prints pid of child 
								// = return value of fork for parent
			s[k_number_of_bg].pid = pid;
			strcpy(s[k_number_of_bg].name,args[0]);
			s[k_number_of_bg].running = 1;
			k_number_of_bg++;
			
			// while ((wait_pid1 = waitpid(-1, &status1, WNOHANG)) > 0){
   //  			printf("Exit status of %d was %d \n", wait_pid1, status1);
			// }
			// wait_pid1 = waitpid(pid,&status1,WNOHANG);
			// if(wait_pid1>0)
			// 	fprintf(stdout,"process with pid %d exited normally\n", pid);
			
			// sets stdin to only foreground
		}	// tcsetpgrp — set the foreground process group ID
	}
	else
	{
		pid = fork(); 
		if(pid < 0)
		{
			fprintf(stderr, "Error: cannot create process\n");
		}
		else if(pid == 0) // running for the child
		{
			setpgid(0, 0);
			if(execvp(args[0],args)<0)
			{
				fprintf(stderr, "Error: cannot execute process\n");
				exit(EXIT_FAILURE); // kill child if can't execute command otherwise 2 shells formed
			}
		}
		else 	// running for parent
		{		// wait for child to exit
				int savePid = pid;

				pid_foreground_process = pid;
				strcpy(foreground_process_name,args[0]);
				
	            // int shellPid = getpid();
	            signal(SIGTTOU, SIG_IGN);
	            signal(SIGTTIN, SIG_IGN);
	            
	            setpgid(pid, 0);

	            tcsetpgrp(0, pid);
	            // tcsetpgrp(1, pid);

	            do
            	{
                	waitpid(savePid, &status, WUNTRACED);
            	} while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));
	            
	            // tcsetpgrp(0, getpgid(shellPid));
	            tcsetpgrp(0, getpgrp());
	            // tcsetpgrp(1, getpgid(shellPid));
	            
	            signal(SIGTTOU, SIG_DFL);
	            signal(SIGTTIN, SIG_DFL);

	            if(WIFSTOPPED(status))
	            {
	                if (pid_foreground_process != -1)
        			{
			            s[k_number_of_bg].pid = pid_foreground_process;
			            strcpy(s[k_number_of_bg].name,foreground_process_name);
			            s[k_number_of_bg].running = 1;
			            k_number_of_bg++;
			        }
			        pid_foreground_process = -1;
				}
		}
	}
	return;
}