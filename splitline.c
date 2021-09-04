#include "shell.h"

#define token_buffersize 64
#define delimiters " \n\t"

// each delimiter separated entity is separated or tokenized
char** split_line(char* input)
{
	int i=0,ch;

	int buffer_size = token_buffersize;
	
	char** buffer = (char**)malloc(buffer_size * sizeof(char*));
	
	if(!buffer)
	{
		fprintf(stderr, "Error: could not allocate memory\n");
		exit(0);
	}
	
	char* token = strtok(input, delimiters);
	
	while(token)
	{
		buffer[i] = token;
		i++;

		if(i >= buffer_size)
		{
			buffer_size += token_buffersize;
			buffer = realloc(buffer,buffer_size * sizeof(char*));
			if(!buffer)
			{
				fprintf(stderr, "Error: could not allocate memory\n");
				exit(0);
			}	
		}
		token = strtok(NULL,delimiters);	
	}
	
	buffer[i] = NULL;
	return buffer;
}