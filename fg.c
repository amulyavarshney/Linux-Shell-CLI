#include "shell.h"

void fg(char **args)
{
    int job_index = get_job_index_fg_and_running_to_0(atoi(args[1]));
    
    if(job_index < 0)
    {
        printf("Job %s doesn't exist\n", args[1]);
        return;
    }

    pid_t pid = s[job_index].pid;
    int status;
    // printf("%d\n",pid);
    
    setpgid(pid, getpgid(0));

    strcpy(foreground_process_name, s[job_index].name);

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, pid);

    kill(pid, SIGCONT);

    pid_foreground_process = pid;

    waitpid(pid, &status, WUNTRACED);

    if (WIFSTOPPED(status))
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

    tcsetpgrp(STDIN_FILENO, getpgrp());

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}