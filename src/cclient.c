/*
	filename : cclient.c

	유닉스 소켓 생성(socket) -> 연결할 서버 소켓 이름 "convert"를 지정하고 클라이언트 소켓과 서버 소켓 사이의 연결을 요청(connect)
	-> 연결이 정삭적으로 이루어졌는지 확인하고 그렇지 않으면 1초 후에 다시 시도한다.
	-> 소켓 연결이 정삭적으로 이루어지면 표준입력으로부터 한 줄을 읽고 이를 연결된 소켓을 통해 서버에 전송(write)
	-> 연결된 소켓을 통해 서버로부터 대문자로 변환된 문자열을 받는다.(readLine)
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define DEFAULT_PROTOCOL 0
#define BUF_SIZE 100

int main()
{
	int sfd, cfd, result;
	char msg_recv[BUF_SIZE], msg_send[BUF_SIZE];
	struct sockaddr_un serverAddr;

	sfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
	serverAddr.sun_family = AF_UNIX;
	strcpy(serverAddr.sun_path, "convert");

	do {
		result = connect(sfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
		if(result == -1) sleep(1);
	} while(result == -1);

	printf("변환할 문자열 입력:\n");
	fgets(msg_recv, BUF_SIZE, stdin);
	write(sfd, msg_recv, strlen(msg_recv) + 1);	// 변환할 문자열 전송

	// 소켓으로부터 변환된 문자열을 한 줄 읽어서 프린트
	readLine(sfd, msg_send);
	printf("%s ---> \n%s", msg_recv, msg_send);
	close(sfd);
	exit(0);
}

readLine(int fd, char *str)
{
	int n;
	do {
		n = read(fd, str, 1);
	} while(n > 0 && *str++ != NULL);

	return (n > 0);
}
