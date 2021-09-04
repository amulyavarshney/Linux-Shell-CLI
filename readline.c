#include "shell.h"

#define line_size_initial 256

// using dynamic memory allocation to avoid complications
char* read_line()
{

	int i=0,ch;
	
	int size = line_size_initial;
	
	char* buffer = (char*)malloc(size * sizeof(char));
	
	if(!buffer)
	{
		fprintf(stderr, "Error: could not allocate memory\n");
		exit(0);
	}
	
	while(1){
		
		ch = getchar();
		if(ch =='\n')
		{
			buffer[i] = '\0';
			return buffer;
		}
		else if(ch == EOF)
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			buffer[i] = ch;
		}
		i = i + 1;


		if(i < size)
			continue;
		else // reallocate more memory i.e increase by 256
		{
			size += line_size_initial;
			buffer = realloc(buffer,size);
			if(!buffer)
			{
				fprintf(stderr, "Error: could not allocate memory\n");
				exit(0);
			}	
		}
	}

}