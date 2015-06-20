/*
 부모 프로세스가 wait() 시스템 호출을 이용하여 자식 프로세스가 종료하기를 기다리는 프로그램

 부모 프로세스는 18번 줄에서 자식 프로세스를 생성하고 24번 줄에서 자식 프로세스가 종료하기를 기다리며
 종료한 후에는 26, 27번 줄에서 자식 프로세스 종료 메시지와 자식 프로세스로부터 받은 종료코드 값을 프린트한다.
 자식 프로세스로부터 받은 종료코드 값은 status 변수의 4바이트 중에 3번째 바이트에 저장되므로 우로 8비트 이동해서 프린트한다.
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pid, child, status;

	printf("[%d] parent process start \n", getpid());
	pid = fork();
	if(!pid) {
		printf("[%d] child process start \n", getpid());
		exit(1);
	}

	child = wait(&status);		// wait until end child process
	printf("[%d] child process %d quit \n", getpid(), child);
	printf("\t종료코드 %d\n", status>>8);
}
