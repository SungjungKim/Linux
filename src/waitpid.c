/*
 waitpid() 호출을 사용하는 프로그램

 부모 프로세스는 두 개의 자식 프로세스를 생성하고 첫 번째 자식 프로세스가 종료할 때까지 기다린다.
 부모 프로세스는 번 줄과 번 줄에서 두 개의 자식 프로세스를 생성하고 번 줄에서 waitpid() 호출을 사용하여 첫 번째 자식 프로세스가 종료하기를 기다린다.
 첫 번째 자식 프로세스가 종료한 후에는 종료 메시지와 종료코드 값을 프린트한다.
 이 프로그램에서는 첫 번째 자식 프로세스는 1초 동안 잠잔 후에 종료하고 두 번째 자식 프로세스는 2초 동안 잠잔 후에 종료하므로
 첫 번째 자식 프로세스가 먼저 종료할 것이다. 실행결과를 보면 첫 번째 자식 프로세스가 종료하자마자 부모 프로세스가 기다림을 멈추고
 첫 번째 자식 프로세스 종료 메시지를 프린트하는 것을 확인할 수 있다.
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pid1, pid2, child, status;

	printf("[%d] parent process start \n", getpid());
	pid1 = fork();
	if(!pid1) {
		printf("[%d] child process[1] start \n", getpid());
		sleep(1);
		printf("[%d] child process[1] end \n", getpid());
		exit(1);
	}

	pid2 = fork();
	if(!pid2) {
		printf("[%d] child process[2] start \n", getpid());
		sleep(2);
		printf("[%d] child process[2] end \n", getpid());
		exit(2);
	}

	// 첫 번째 자식 프로세스 종료를 기다린다.
	child = waitpid(pid1, &status, 0);
	printf("[%d] child process[1] %d end \n", getpid(), child);
	printf("\t종료코드 %d \n", status>>8);
}
