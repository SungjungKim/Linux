/*
 부모 프로세스가 자식 프로세스를 생성하여 자식 프로세스로 하여금 echo 명령어를 실행하게 하는 프로그램

 execl() 시스템 호출을 사용하여 명령줄 인수로 "hello" 스트링을 주고 NULL은 인수 끝을 나타낸다.
 자식 프로세스는 echo 명령어를 실행하여 명령줄 인수로 받은 "hello" 스트링을 그대로 프린트한다.
 자식 프로세스가 echo 명령어를 정상적으로 실행하면 19, 20번 줄은 실행되지 않는다는 점을 주의하자.
 부모 프로세스는 번 줄을 실행하여 "parent process end" 메시지를 출력한다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("parent process start \n");
	if(fork() == 0) {
		execl("/bin/echo", "echo", "hello", NULL);
		fprintf(stderr, "first faile.");
		exit(1);
	}

	printf("parent process end\n");
}
