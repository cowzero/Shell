#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "instructions.h"
#define size 10

int main()
{
	char str[size]; 

	printf("-------------------SO YOUNG'S SHELL-------------------\n");
	printf("pwd, ls, mkdir, exit\n");

	while (true)
	{
		printf("-> ");
		gets(str);

        if(!strcmp("pwd", str))
			pwd();

	if(!strcmp("ls", str))
			ls();

	if(!strcmp("ls -f", str))
			ls_f();

	char* tok = strtok(str," ");

	if(!strcmp("mkdir", tok)){
		tok = strtok(NULL, " ");
		mkdir(tok);
	}


/*
	if(!strcmp("rm", tok)){
		tok = strtok(NULL, " ");

		if(!strcmp("-r",tok)){
			tok = strtok(NULL, " ");	
			rm_r(tok);
		}
	}
*/

	if (!strcmp("exit", str))
			break;
	}

	return 0;
}
