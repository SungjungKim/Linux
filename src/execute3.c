/*
 명령줄 인수로 받은 임의의 명렁어를 실행시키는 프로그램

 명령줄 인수로 받은 명렁어의 실행을 위해 20번 줄에서 자식 프로세스를 생성하고 22줄에서 자식 프로세스로 하여금 그 명령어를 실행하게 한다.
 argv[1]은 첫 번째 명령줄 인수를 실행할 명령어(혹은 실행파일) 이름
 &argv[1]은 첫 번째 명령줄 인수부터 시작되는 명령줄 인수들의 배열
 부모 프로세스는 26번 줄에서 자식 프로세스가 끝날 때까지 기다리며 자식 프로세스가 종료하면 27, 28줄에서 자식 프로세스 종료 메시지와 자식 프로세스로부터 받은 종료코드를 프린트한다.
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int child, pid, status;

	pid = fork();
	if(!pid) { 	// child process
		execvp(argv[1], &argv[1]);
		fprintf(stderr, "%s:could not execute.\n", argv[1]);
	}
	else {	// parent process
		child = wait(&status);
		printf("[%d] child process %d end \n", getpid(), pid);
		printf("\t종료코드 %d \n", status>>8);
	}
}
