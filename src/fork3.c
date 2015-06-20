/*
 하나의 부모 프로세스가 두 개의 자식 프로세스를 생성하는 프로그램
 13번 줄에서 첫 번째 자식 프로세스가 exit()을 하고 있는데 만약 이 exit()를 하지 않으면,
 첫 번째 자식 프로세스도 if문 이후에 실행을 계속하여 16번 줄에서 fork() 호출을 하게 되고
 결과적으로 첫 번째 자식 프로세스가 또 다른 자식 프로세스를 생성하게 될 것이다.
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
