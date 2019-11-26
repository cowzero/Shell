# Shell
1. 개요
fork와 exec계열 함수를 사용하여 2가지 이상의 명령어를 지원하는 shell을 만든다. 

2. 프로그램 구조 설명
 2.1 함수에 관한 설명

-int pwd() : 쉘에서 현재 위치한 작업 디렉터리의 경로를 출력하는 함수.

-int ls() : 쉘에서 현재 디렉터리 안의 내용을 출력하는 함수

-int ls_f() : ls의 옵션중에서 –f(파일의 형태에 따라 관련 정보를 출력한다.)기능을 제공하는 함수

-int mkdir(char* dir) : 쉘에서 현재 디렉토리에 디렉토리의 이름을 매개변수로 받아 그 이름의 디렉토리를 만드는 함수

 2.2 다이어그램
 





3. 실행 결과

-Makefile

instructions.c와 main.c를 컴파일한 후 링킹 하여 SoYoungShell이라는 실행 파일을 실행한다.
 
-실행 결과

pwd를 치니 현재 디렉터리의 경로를 볼 수 있었다.
ls를 치니 현재 디렉터리의 내용을 볼 수 있었다. 
ls –f를 치니 현재 디렉터리의 내용들을 좀 더 세부적으로 볼 수 있었다.
a라는 새로운 디렉터리를 만들기 위하여 mkdir a를 쳤고, 이를 확인하기 위해 ls를 치니 a라는 실행파일이 만들어 졌다는 사실을 알 수 있다. 
exit를 쳐서 쉘을 빠져나갈 수 있었다.

 rm –r 도 실행해 보았지만 실패하였다.







프로그램을 짜기에 앞서 실행하고자 하는 명령어의 파일 경로를 확인하였다.

4. 고찰

 리눅스에서 사용하던 명령어들을 쉘 프로그램에서 직접 명령어를 구현해 보니 감회가 새로웠다.
 execv() 함수를 구현할 때 경로가 필요한데 which라는 명령어가 경로를 알려 준다는 사실을 알았고, 많은 도움이 됐다. 인자가 하나인 명령어부터 구현해봤는데 경로만 바꿔주면 돼서 별 무리가 없었다. 그러나 인자가 2개인 경우가 조금 힘들었다. 명령어를 인식하는 원리가 띄어쓰기 단위로 인식한다는 것을 알고 argv[] 에 “ls”와 “-f”를 구분해서 입력하였더니 성공하였다. 비슷한 원리로 mkdir도 해보았는데 이 경우에는 디렉토리 명을 따로 인식해야만 했다. 그래서 strtok로 구분해서 입력을 받았다. rm –r 도 시도해 보았는데 strtok로 rm 과 –r을 따로 구분해서 입력을 받는 부분이 문제가 있었는지 실행이 되지 않았다. 다른 문자열을 구분해주는 함수를 사용해서 “rm –r”과 dir로 구분해서 받는 방법을 모색해야 겠다.
 실행을 할 때 gets() 함수의 경고가 떴는데, 이를 해결하기 위해 gets_s() 함수도 사용해 보았지만. 해결하지 못하였다. gets함수의 사용은 지양해야 겠다. 
 이론으로만 공부해오다가 프로세스를 직접 생성해보고 눈으로 확인해 볼 수 있는 계기가 되어서 좋았다. 나만의 쉘 프로그램을 만드는게 유용하다고 느꼈다.

 
5. 프로그램 소스 파일

-instructions.h
int pwd();
int ls();
int ls_f();
int mkdir(char* dir);
//int rm_r(char* dir); 실패한 함수, 현재 디렉토리에 있는 디렉토리를 지운다.

-instructions.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "instructions.h"

int pwd(){
	int pid, status;
	char* argv[] = {"pwd", 0}; //arg1 : 프로그램명
	pid = fork(); //프로세스 생성
	
	switch(pid){
	case –1: //프로세서 생성 실패 시
		printf("fork error \n");
		exit(1);
	case 0: //자식 프로세스
		execv("/bin/pwd",argv); //새로운 독립된 프로세스 생성, 경로와 인자를 넘긴다.
		printf("exec error\n"); //execv() 실패 시 문구 출력
		exit(1);
	default: //부모 프로세스
		wait(&status); //자식 프로세스가 종료하길 기다린다.
	}
	return 0;
}

int ls(){
	int pid, status;
	char* argv[] = {"ls", 0}; //arg1 : 프로그램명
	pid = fork(); //프로세스 생성

	switch(pid){
	case –1: //프로세서 생성 실패 시
		printf("fork error \n");
		exit(1);
	case 0: //자식 프로세스
		execv("/bin/ls",argv); //새로운 독립된 프로세스 생성, 경로와 인자를 넘긴다.
		printf("exec error\n"); //execv() 실패 시 문구 출력
		exit(1);
	default: //부모 프로세스
		wait(&status); //자식 프로세스가 종료하길 기다린다.
	}
	return 0;
}

int ls_f(){
	int pid, status;
	char* argv[] = {"ls", "-f"}; //arg1 : 프로그램명, arg2 : 옵션
	pid = fork(); //프로세스 생성
	
	switch(pid){
	case –1: //프로세서 생성 실패 시
		printf("fork error \n");
		exit(1);
	case 0: //자식 프로세스
		execv("/bin/ls",argv); //새로운 독립된 프로세스 생성, 경로와 인자를 넘긴다.
		printf("exec error\n"); //execv() 실패 시 문구 출력
		exit(1);
	default: //부모 프로세스
		wait(&status); //자식 프로세스가 종료하길 기다린다.
	}
	return 0;
}

int mkdir(char* dir){
	int pid, status;
	char* argv[] = {"mkdir", dir}; //arg1 : 프로그램명, arg2 : 디렉토리 이름
	pid = fork(); //프로세스 생성
	
	switch(pid){
	case –1: //프로세서 생성 실패 시
		printf("fork error \n");
		exit(1);
	case 0: //자식 프로세스
		execv("/bin/mkdir",argv); //새로운 독립된 프로세스 생성, 경로와 인자를 넘긴다.
		printf("exec error\n"); //execv() 실패 시 문구 출력
		exit(1);
	default: //부모 프로세스
		wait(&status); //자식 프로세스가 종료하길 기다린다.
	}
	return 0;
}

/*
int rm_r(char* dir){ 
	int pid, status;
	char* argv[] = {"rm", "-r", dir}; //arg1 : 프로그램명, arg2 : 옵션, arg3 : 디렉토리 이름
	pid = fork(); //프로세스 생성
	
	switch(pid){
	case –1: //프로세서 생성 실패 시
		printf("fork error \n");
		exit(1);
	case 0: //자식 프로세스
		execv("/bin/rm",argv); //새로운 독립된 프로세스 생성, 경로와 인자를 넘긴다.
		printf("exec error\n"); //execv() 실패 시 문구 출력
		exit(1);
	default: //부모 프로세스
		wait(&status); //자식 프로세스가 종료하길 기다린다.
	}
	return 0;
}
*/

-main.c
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
		gets(str); //명령어를 입력받는다.

        if(!strcmp("pwd", str)) //명령어가 pwd인 경우
			pwd();

	if(!strcmp("ls", str)) //명령어가 ls인 경우
			ls();

	if(!strcmp("ls -f", str)) //명령어가 ls -al인 경우
			ls_f();

	char* tok = strtok(str," "); //명령어가 mkdir인 경우 명령어와 디렉토리명을 구분해야 하므로 strtok함수 사용

	if(!strcmp("mkdir", tok)){//입력한 문자열을 “ ”단위로 한번 구분해서 mkdir인지 확인
		tok = strtok(NULL, " "); //한번 더 구분해서 디렉토리명을 받는다. 
		mkdir(tok); //디렉토리명을 mkdir함수에 넘긴다.
	}

/*
	if(!strcmp("rm", tok)){//명령어를 “ ”단위로 한번 구분해서 rm인지 확인
		tok = strtok(NULL, " ");

		if(!strcmp("-r",tok)){//한번 더 구분해서 옵션(-r)인지 확인
			tok = strtok(NULL, " ");	//한번 더 구분해서 디렉토리 명을 받는다.
			rm_r(tok); //디렉토리명을 rm_r 함수에 넘긴다.
		}
	}
*/
	if (!strcmp("exit", str))
		break;
	}
	
	return 0;
}
	
6. 자료 출처
조교님 실행 예제, https://m.blog.naver.com/jhnyang/221503009710,
