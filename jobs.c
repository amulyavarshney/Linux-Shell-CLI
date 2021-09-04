#include "shell.h"

void jobs() 
{
    int i, j = 1;
    char status[10009], status1[10009], status2[10009];
    for (i = 0; i < k_number_of_bg; i++) 
    {
        if(s[i].running==0)
            continue;

        char myproc[10009];

        sprintf(myproc, "%d", s[i].pid);
        
        char demo[1024];
        strcpy(demo,"/proc/");
        strcat(demo,myproc);
        strcat(demo,"/stat");
        
        FILE *mem = fopen(demo, "r");
        fscanf(mem, "%s %s %s", status1, status2, status);
        // printf("Process Status -- %s\n", status);
        if(strcmp(status,"T")==0)
        {   
            strcpy(status,"Stopped");
        }
        else
        {
            strcpy(status,"Running");
        }
        printf("[%d] %s %s [%d]\n", j, status, s[i].name, s[i].pid);
        j++;
    }
}

int get_job_index(int job_no)
{
    int i, j = 1;
    for (i = 0; i < k_number_of_bg; i++) 
    {
        if(s[i].running==0)
            continue;
        if(j==job_no)
            return i;
        j++;
    }
    return -1;
}

int get_job_index_fg_and_running_to_0(int job_no)
{
    int i, j = 1;
    for (i = 0; i < k_number_of_bg; i++) 
    {
        if(s[i].running==0)
            continue;
        if(j==job_no)
        {
            s[i].running = 0;
            return i;
        }
        j++;
    }
    return -1;
}