/*
 WEXITSTATUS() 
 : <sys/wait.h>에 정의된 매크로 함수, 내부적으로 표현된 종료코드 값을 찾아서 반환한다.
   주어진 명령어가 정상적으로 실행되면 0을 반환하고, 해당 명령어가 없으면 127을 반환하고, 별도의 종료코드가 주어지면 그 값을 반환한다.
 
*/

#include <sys/wait.h>
#include <stdio.h>

int main()
{
	int status;
	if((status = system("date")) < 0)
		perror("system() error");
	printf("종료코드 %d\n", WEXITSTATUS(status));

	if((status = system("hello")) <0)
		perror("system() error");
	printf("종료코드 %d\n", WEXITSTATUS(status));

	if((status = system("who; exit 44")) < 0)
		perror("system() error");
	printf("종료코드 %d\n", WEXITSTATUS(status));
}
