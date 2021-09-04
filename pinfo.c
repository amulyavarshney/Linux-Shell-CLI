#include "shell.h"

void pinfo(char** args)
{
	char process_loc[1024];
	int memory_size;
	char status1[100], status2[100], status[100];

	if(args[1]==NULL)
	{
		char my_string[1024];
		pid_t pid;
		pid = getpid();
		
		printf("pid -- %d\n", pid);
		
		FILE *mem = fopen("/proc/self/stat", "r"); // r-> read mode
		fscanf(mem, "%s %s %s", status1, status2, status);
		printf("Process Status -- %s\n", status);
		
		mem = fopen("/proc/self/statm", "r");
		fscanf(mem, "%d", &memory_size);
		printf("Memory -- %d\n", memory_size);
		
		strcpy(my_string,"/proc/self/exe");
		int length = readlink(my_string, process_loc, sizeof(process_loc));
		process_loc[length] = '\0';
		printf("Executable Path -- %s\n",process_loc);
	}
	else
	{
		char my_string[1024];
		printf("pid -- %s\n", args[1]);
		
		strcpy(my_string, "/proc/");
		strcat(my_string, args[1]);
		strcat(my_string, "/stat");
		FILE *mem = fopen(my_string, "r");
		fscanf(mem, "%s %s %s", status1, status2, status);
		printf("Process Status -- %s\n", status);
		
		strcpy(my_string, "/proc/");
		strcat(my_string, args[1]);
		strcat(my_string, "/statm");
		mem = fopen(my_string, "r");
		fscanf(mem, "%d", &memory_size);
		printf("Memory -- %d\n", memory_size);
		
		strcpy(my_string, "/proc/");
		strcat(my_string, args[1]);
		strcat(my_string, "/exe");
		int length = readlink(my_string, process_loc, sizeof(process_loc));
		process_loc[length] = '\0';
		printf("Executable Path -- %s\n",process_loc);
	}
}