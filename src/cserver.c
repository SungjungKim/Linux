/*
	filename : cserver.c

	[Server] 입력받은 문자열 중 소문자를 대문자로 변환하는 프로그램
	서버는 소켓을 통해 클라이언트로부터 받은 문자열 중 소문자를 대문자로 변환하여 소켓을 통해 클라이언트에 다시 보내는 서비스를 한다.
	클라이언트는 사용자로부터 표준입력을 통해 문자열을 입력받아 이를 소켓을 통해 서버에 보낸 후에 소켓을 통해 대문자로 변환된 문자열을 다시 받아 표준출력에 출력한다.
	이를 위해서 "convert"라는 UNIX 소켓을 생성하고 이를 바인딩한다.
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
	int sfd, cfd, clientLen;
	char msg_send[BUF_SIZE], msg_recv[BUF_SIZE];
	struct sockaddr_un serverAddr, clientAddr;

	signal(SIGCHLD, SIG_IGN);
	clientLen = sizeof(clientAddr);

	sfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
	serverAddr.sun_family = AF_UNIX;
	strcpy(serverAddr.sun_path, "convert");
	unlink("convert");

	bind(sfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	listen(sfd, 5);

	// 소켓 연결 요청 수락
	while(1) {
		cfd = accept(sfd, (struct sockaddr *)&clientAddr, &clientLen);
		if(fork() == 0) {
			// 소켓으로부터 한 줄을 읽어 대문자로 변환하여 보냄
			readLine(cfd, msg_recv);
			toUpper(msg_recv, msg_send);
			write(cfd, msg_send, strlen(msg_send) + 1);
			close(cfd);
			exit(0);
		}
		else close(cfd);
	}
}


/* convert lower to upper */
toUpper(char *recv, char *send)
{
	int i;
	for(i = 0; i < strlen(recv); i++) {
		if(islower(recv[i])) send[i] = toupper(recv[i]);
		else send[i] = recv[i];
	}

	send[i] = NULL;
}


/* read one line */
readLine(int fd, char *str)
{
	int n;
	do {
		n = read(fd, str, 1);
	} while(n > 0 && *str++ != NULL);

	return (n > 0);
}
