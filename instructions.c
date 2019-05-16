#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "instructions.h"

int pwd(){
	int pid, status;
	char* argv[] = {"pwd", 0};
	pid = fork();

	switch(pid){
	case -1:
		printf("fork error \n");
		exit(1);

	case 0:
		execv("/bin/pwd",argv);
		printf("exec error\n");
		exit(1);

	default:
		wait(&status);
	}
	
	return 0;
}

int ls(){
	int pid, status;
	char* argv[] = {"ls", 0};
	pid = fork();

	switch(pid){
	case -1:
		printf("fork error \n");
		exit(1);

	case 0:
		execv("/bin/ls",argv);
		printf("exec error\n");
		exit(1);

	default:
		wait(&status);
	}
	
	return 0;

}

int ls_f(){
	
	int pid, status;
	char* argv[] = {"ls", "-f"};
	pid = fork();

	switch(pid){
	case -1:
		printf("fork error \n");
		exit(1);

	case 0:
		execv("/bin/ls",argv);
		printf("exec error\n");
		exit(1);

	default:
		wait(&status);
	}
	
	return 0;
}

int mkdir(char* dir){
	
	int pid, status;
	char* argv[] = {"mkdir", dir};
	pid = fork();

	switch(pid){
	case -1:
		printf("fork error \n");
		exit(1);

	case 0:
		execv("/bin/mkdir",argv);
		printf("exec error\n");
		exit(1);

	default:
		wait(&status);
	}
	
	return 0;
}

/*
int rm_r(char* dir){
	
	int pid, status;
	char* argv[] = {"rm", "-r", dir};
	pid = fork();

	switch(pid){
	case -1:
		printf("fork error \n");
		exit(1);

	case 0:
		execv("/bin/rm",argv);
	
		printf("exec error\n");
		exit(1);

	default:
		wait(&status);
	}
	
	return 0;
}
*/


