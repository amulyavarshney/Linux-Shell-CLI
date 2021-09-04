#include "shell.h"

void kjob(char** args)
{
    int job_index = get_job_index(atoi(args[1]));

    if(job_index < 0)
    {
        printf("Job %s doesn't exist\n", args[1]);
        return;
    }

    pid_t pid = s[job_index].pid;
    
    kill(pid, atoi(args[2]));
    
}