#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>

int isDirectory(const char *path);
void handler(int signum);
char* read_line();
char** split_line(char* input);
void echo(char** args);
void pwd();
void cd(char** args);
void ls(char** args);
void execute(char** args);
void pinfo(char** args);
void redirection(char** args);
void piping(char* input);
void redirection_execute(char** args);
void redirection_piping_execute(char** args);
void redirection_piping(char** args);
void execute_setenv (char** args);
void execute_unsetenv (char** args);
void jobs(); 
void kjob(char** args);
int get_job_index(int job_no);
void fg(char** args);
void bg(char** args);
void overkill();
void quit();
int get_job_index_fg_and_running_to_0(int job_no);
void sig_z_handler(int signum);
void sig_c_handler(int signum);

struct process 
{  
    int pid;  
    char name[20]; 
    int running;
}s[100];  

extern int k_number_of_bg;
extern int pid_foreground_process;
extern char foreground_process_name[30];
extern char home[100];
extern char cwd[100];