#include "shell.h"

char home[100],cwd[100];

int main(int argc, char const *argv[])
{
	char *input;
	char host_name[100];
	char prompt[100];
	getcwd(home, 100); 										// get the original shell directory -> home 
	gethostname(host_name, 100);	

    signal(SIGINT,sig_c_handler);

    signal(SIGTSTP,sig_z_handler);

    signal(SIGCHLD, handler);

	while(1)
	{
		getcwd(cwd,100);  // keep saving current working directory

		if(!strcmp(cwd,home))
		{  // strings are equal -> strcmp returns a 0
			strcpy(prompt,"~");
		}
		// earlier mistake -> ignored one case
		
		// else if(strstr(home, cwd) != NULL)
		// { // cwd is a substring of home
		// 	strcpy(prompt,cwd);
		// }
		else if(strstr(cwd, home) != NULL)
		{ // home is substring of cwd -> cwd is larger 
			char p[100]; 
			int len = strlen(home);
			int j=0;
			p[0]='~';
			for(j=1;j<strlen(cwd)-strlen(home)+1 ;j++)
			{
				p[j] = cwd[j+strlen(home)-1];	
			}
			p[j]='\0';
			strcpy(prompt,p);
		}
		else
		{
			strcpy(prompt,cwd);
		}
		printf("%s@%s:%s>", getlogin(),host_name,prompt);


		input = read_line();
		// printf("%s\n", input);
		char* inp;// = strsep(&input,";");
		// char* inp2;
		char my_string_inp[100];

		int i,flag, flag2;
		while((inp = strsep(&input,";")) != NULL)
		{
			stpcpy(my_string_inp, inp);
			
			char** args = split_line(inp);
			i=0;
			flag=0;
			flag2=0;
			
			while(args[i]!=NULL)
			{
				if(!(strcmp(args[i],"|")))
				{
					// printf("%s\n", my_string_inp);
					piping(my_string_inp);
					flag2=1;
					break;
				}
				i++;
			}
			i=0;

			if(flag2!=1)
			{
				while(args[i]!=NULL)
				{
					if(!(strcmp(args[i],"<")) || !(strcmp(args[i],">")) || !(strcmp(args[i],">>")))
					{
						redirection(args);
						flag=1;
						break;
					}
					i++;
				}
			}
			
			if(flag==1 || flag2==1)
				continue;

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
	}
	return 0;
}