#include "shell.h"

void cd(char** args)
{
	if(args[1])
	{
		if(!chdir(args[1]))
		{
			// if chdir returns 0 everything works fine
		}
		else if(args[1][0]=='~')
		{
			char new[MAXNAMLEN];
			strcpy(new, home);
			strcat(new, args[1]+1);
			chdir(new);
		}
		else
		{
			fprintf(stderr, "Error: cd: %s: No such file or directory\n",args[1]);
		}
	}
	else // no argument is passed
	{
		// chdir(getenv("HOME"));
		chdir(home);
	}
	return;
}