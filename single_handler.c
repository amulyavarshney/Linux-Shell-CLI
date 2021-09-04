#include "shell.h"

//for Ctrl + C
void sig_c_handler(int signum)
{
    pid_foreground_process = -1;
    return;
}

//for Ctrl + Z
void sig_z_handler(int signum)
{
    
    if (pid_foreground_process == -1)
    {
        return;
    }

    s[k_number_of_bg].pid = pid_foreground_process;
    strcpy(s[k_number_of_bg].name, foreground_process_name);
    s[k_number_of_bg].running = 1;
    k_number_of_bg++;

    kill(pid_foreground_process, SIGTSTP);

    pid_foreground_process = -1;

    return;
}