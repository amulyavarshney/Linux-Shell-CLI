#include "shell.h"

int isDirectory(const char *path) 
{
	struct stat statbuf;
	if (stat(path, &statbuf) == -1)
	{
		// perror("stat for directory");
		return 0;
	}
	return S_ISDIR(statbuf.st_mode);
}

// void printing_ls(int flaga, int flagc, )
// {

// }
void cd2(char* arg)
{
	if(!chdir(arg))
	{
		// if chdir returns 0 everything works fine
	}
	else if(arg[0]=='~')
	{
		char new[MAXNAMLEN];
		strcpy(new, home);
		strcat(new, arg+1);
		chdir(new);
	}
	else
	{
		fprintf(stderr, "Error: no such directory");
	}
}

void ls(char** args)
{
	DIR *dir;
	struct stat buffer;
    struct dirent  *dp;
    struct stat     statbuf;
    struct passwd  *pwd;
    struct group   *grp;
    struct tm      *tm;
    char            datestring[256];
    long int total = 0;
	int flaga=0;
	int flagl=0;
	int number_of_dir=0;
	int i=1;
	while(args[i]!=NULL)
	{
		if((!(strcmp(args[i],"-la"))) || (!(strcmp(args[i],"-al"))))
		{
			flaga=1;
			flagl=1;
		}
		else if((!(strcmp(args[i],"-l"))))
		{
			flagl=1;
		}
		else if((!(strcmp(args[i],"-a"))))
		{
			flaga=1;
		}
		else
		{
			if(isDirectory(args[i]))
			{
				number_of_dir+=1;
			}
		}
		i++;
	}

	if(number_of_dir==0)
	{
		if(flaga==1)
		{
			if(flagl==1) // both are 1 
			{
				dir = opendir(".");
			    total=0;
			    while ((dp = readdir(dir)) != NULL) {

			        if (stat(dp->d_name, &buffer) == -1)
			            continue;

			        total+=buffer.st_blocks;
			    }

			    printf("total %ld\n", total/2);
				dir = opendir(".");

			//	printf("%s:\n",args[i]); // 

				while ((dp = readdir(dir)) != NULL) 
				{
			        if (stat(dp->d_name, &statbuf) == -1)
			            continue;

			        printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
			        printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
			        printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
			        printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
			        printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
			        printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
			        printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
			        printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
			        printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
			        printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
			        printf("%4ld", statbuf.st_nlink);

			        if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
			            printf(" %-8.8s", pwd->pw_name);
			        else
			            printf(" %-8d", statbuf.st_uid);

			        if ((grp = getgrgid(statbuf.st_gid)) != NULL)
			            printf(" %-8.8s", grp->gr_name);
			        else
			            printf(" %-8d", statbuf.st_gid);

			        printf(" %9jd", (intmax_t)statbuf.st_size);

			        tm = localtime(&statbuf.st_mtime);

			        strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);

			        printf(" %s %s\n", datestring, dp->d_name);
			    }
			}
			else		// flaga is 1 
			{
				dir = opendir(".");

			//	printf("%s:\n",args[i]); // 

				while ((dp = readdir(dir)) != NULL) 
				{
			        if (stat(dp->d_name, &statbuf) == -1)
			            continue;

					printf("%s\n", dp->d_name);
				}
			}
		}
		else if(flagl==1)	// flagl is 1 
		{
			dir = opendir(".");
		    total=0;
		    while ((dp = readdir(dir)) != NULL) {

		        if (stat(dp->d_name, &buffer) == -1)
		            continue;

		        total+=buffer.st_blocks;
		    }

		    printf("total %ld\n", total/2);	

			dir = opendir(".");

		//	printf("%s:\n",args[i]); // 

			while ((dp = readdir(dir)) != NULL) 
			{
		        if(dp->d_name[0]=='.')
		        	continue;
		        if (stat(dp->d_name, &statbuf) == -1)
		            continue;

		        printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
		        printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
		        printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
		        printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
		        printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
		        printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
		        printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
		        printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
		        printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
		        printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
		        printf("%4ld", statbuf.st_nlink);

		        if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
		            printf(" %-8.8s", pwd->pw_name);
		        else
		            printf(" %-8d", statbuf.st_uid);

		        if ((grp = getgrgid(statbuf.st_gid)) != NULL)
		            printf(" %-8.8s", grp->gr_name);
		        else
		            printf(" %-8d", statbuf.st_gid);

		        printf(" %9jd", (intmax_t)statbuf.st_size);

		        tm = localtime(&statbuf.st_mtime);

		        strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);

		        printf(" %s %s\n", datestring, dp->d_name);
			}
		}
		else			// both are 0
		{		
			dir = opendir(".");
		//	printf("%s:\n",args[i]); // 
			
			while ((dp = readdir(dir)) != NULL) 
			{
		        if (stat(dp->d_name, &statbuf) == -1)
		            continue;
		        if(dp->d_name[0]=='.')
		        	continue;
				printf("%s\n", dp->d_name);
			}
		}
	}
	i=1;
	while(args[i]!=NULL)
	{
		if(isDirectory(args[i]))
		{
			if(number_of_dir>1)
			{
				if(flaga==1)
				{
					if(flagl==1) // both are 1 
					{
						cd2(args[i]);

						printf("%s:\n",args[i]); // 

						dir = opendir(".");
					    total=0;
					    while ((dp = readdir(dir)) != NULL) {

					        if (stat(dp->d_name, &buffer) == -1)
					            continue;

					        total+=buffer.st_blocks;
					    }

					    printf("total %ld\n", total/2);

						dir = opendir(".");

						while ((dp = readdir(dir)) != NULL) 
						{
					        if (stat(dp->d_name, &statbuf) == -1)
					            continue;

					        printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
					        printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
					        printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
					        printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
					        printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
					        printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
					        printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
					        printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
					        printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
					        printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
					        printf("%4ld", statbuf.st_nlink);

					        if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
					            printf(" %-8.8s", pwd->pw_name);
					        else
					            printf(" %-8d", statbuf.st_uid);

					        if ((grp = getgrgid(statbuf.st_gid)) != NULL)
					            printf(" %-8.8s", grp->gr_name);
					        else
					            printf(" %-8d", statbuf.st_gid);

					        printf(" %9jd", (intmax_t)statbuf.st_size);

					        tm = localtime(&statbuf.st_mtime);

					        strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);

					        printf(" %s %s\n", datestring, dp->d_name);
					    }
					    cd2(cwd);
					}
					else		// flaga is 1 
					{
						cd2(args[i]);

						dir = opendir(".");

						printf("%s:\n",args[i]); // 

						while ((dp = readdir(dir)) != NULL) 
						{
					        if (stat(dp->d_name, &statbuf) == -1)
					            continue;

							printf("%s\n", dp->d_name);
						}
						cd2(cwd);
					}
				}
				else if(flagl==1)	// flagl is 1 
				{
					cd2(args[i]);

					printf("%s:\n",args[i]); // 

					dir = opendir(".");
				    total=0;
				    while ((dp = readdir(dir)) != NULL) {

				        if (stat(dp->d_name, &buffer) == -1)
				            continue;

				        total+=buffer.st_blocks;
				    }

				    printf("total %ld\n", total/2);

					dir = opendir(".");

					while ((dp = readdir(dir)) != NULL) 
					{
				        if(dp->d_name[0]=='.')
				        	continue;
				        if (stat(dp->d_name, &statbuf) == -1)
				            continue;

				        printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
				        printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
				        printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
				        printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
				        printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
				        printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
				        printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
				        printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
				        printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
				        printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
				        printf("%4ld", statbuf.st_nlink);

				        if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
				            printf(" %-8.8s", pwd->pw_name);
				        else
				            printf(" %-8d", statbuf.st_uid);

				        if ((grp = getgrgid(statbuf.st_gid)) != NULL)
				            printf(" %-8.8s", grp->gr_name);
				        else
				            printf(" %-8d", statbuf.st_gid);

				        printf(" %9jd", (intmax_t)statbuf.st_size);

				        tm = localtime(&statbuf.st_mtime);

				        strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);

				        printf(" %s %s\n", datestring, dp->d_name);
					}
					cd2(cwd);
				}
				else			// both are 0
				{
					cd2(args[i]);

					dir = opendir(".");

					printf("%s:\n",args[i]); // 
					
					while ((dp = readdir(dir)) != NULL) 
					{
				        if (stat(dp->d_name, &statbuf) == -1)
				            continue;
				        if(dp->d_name[0]=='.')
				        	continue;
						printf("%s\n", dp->d_name);
					}
					cd2(cwd);
				}
			}
			else // just 1 directory
			{
				if(flaga==1)
				{
					if(flagl==1) // both are 1 
					{
						cd2(args[i]);

						dir = opendir(".");
					    total=0;
					    while ((dp = readdir(dir)) != NULL) {

					        if (stat(dp->d_name, &buffer) == -1)
					            continue;

					        total+=buffer.st_blocks;
					    }

					    printf("total %ld\n", total/2);

						dir = opendir(".");

					//	printf("%s:\n",args[i]); // 

						while ((dp = readdir(dir)) != NULL) 
						{
					        if (stat(dp->d_name, &statbuf) == -1)
					            continue;

					        printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
					        printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
					        printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
					        printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
					        printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
					        printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
					        printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
					        printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
					        printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
					        printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
					        printf("%4ld", statbuf.st_nlink);

					        if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
					            printf(" %-8.8s", pwd->pw_name);
					        else
					            printf(" %-8d", statbuf.st_uid);

					        if ((grp = getgrgid(statbuf.st_gid)) != NULL)
					            printf(" %-8.8s", grp->gr_name);
					        else
					            printf(" %-8d", statbuf.st_gid);

					        printf(" %9jd", (intmax_t)statbuf.st_size);

					        tm = localtime(&statbuf.st_mtime);

					        strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);

					        printf(" %s %s\n", datestring, dp->d_name);
					    }
					    cd2(cwd);
					}
					else		// flaga is 1 
					{
						cd2(args[i]);

						dir = opendir(".");

					//	printf("%s:\n",args[i]); // 

						while ((dp = readdir(dir)) != NULL) 
						{
					        if (stat(dp->d_name, &statbuf) == -1)
					            continue;

							printf("%s\n", dp->d_name);
						}
						cd2(cwd);
					}
				}
				else if(flagl==1)	// flagl is 1 
				{
					cd2(args[i]);

					dir = opendir(".");
				    total=0;
				    while ((dp = readdir(dir)) != NULL) {

				        if (stat(dp->d_name, &buffer) == -1)
				            continue;

				        total+=buffer.st_blocks;
				    }

				    printf("total %ld\n", total/2);

					dir = opendir(".");

				//	printf("%s:\n",args[i]); // 

					while ((dp = readdir(dir)) != NULL) 
					{
				        if(dp->d_name[0]=='.')
				        	continue;
				        if (stat(dp->d_name, &statbuf) == -1)
				            continue;

				        printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
				        printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
				        printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
				        printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
				        printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
				        printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
				        printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
				        printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
				        printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
				        printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
				        printf("%4ld", statbuf.st_nlink);

				        if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
				            printf(" %-8.8s", pwd->pw_name);
				        else
				            printf(" %-8d", statbuf.st_uid);

				        if ((grp = getgrgid(statbuf.st_gid)) != NULL)
				            printf(" %-8.8s", grp->gr_name);
				        else
				            printf(" %-8d", statbuf.st_gid);

				        printf(" %9jd", (intmax_t)statbuf.st_size);

				        tm = localtime(&statbuf.st_mtime);

				        strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);

				        printf(" %s %s\n", datestring, dp->d_name);
					}
					cd2(cwd);
				}
				else			// both are 0
				{
					cd2(args[i]);

					dir = opendir(".");
				//	printf("%s:\n",args[i]); // 
					
					while ((dp = readdir(dir)) != NULL) 
					{
				        if (stat(dp->d_name, &statbuf) == -1)
				            continue;
				        if(dp->d_name[0]=='.')
				        	continue;
						printf("%s\n", dp->d_name);
					}
					cd2(cwd);
				}
			}

		}
		i++;
	}
}