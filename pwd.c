#include "shell.h"

void pwd()
{
	char cwd[100];
	getcwd(cwd,100);
	printf("%s\n",cwd);
	return;
}