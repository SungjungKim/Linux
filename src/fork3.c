/*
 하나의 부모 프로세스가 두 개의 자식 프로세스를 생성하는 프로그램
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pid1, pid2;

	pid1 = fork();
	if(!pid1) {
		printf("[Child1] Hello, world! pid=%d \n", getpid());
		exit(0);
	}

	pid2 = fork();
	if(!pid2) {
		printf("[Child2] Hello, world! pid=%d \n", getpid());
		exit(0);
	}
}
