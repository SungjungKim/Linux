/*
	filename: fserver.c

	파일 이름을 받아 해당 파일을 찾아 그 내용을 보내주는 서버 프로그램
	서버는 명령줄 인수로 포트 번호를 받아 해당 포트를 사용하는 소켓을 만든다. 이 소켓을 통해 클라이언트로부터 파일 이름을 받아
	해당 파일을 찾아 열고 그 파일 내용을 다시 이 소켓을 통해 클라이언트에게 보낸다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DEFAULT_PROTOCOL 0
#define BUF_SIZE 100

int main(int argc, char *argv[])
{
	int sfd, cfd, port, clientLen;
	FILE *fp;
	char msg_recv[BUF_SIZE], msg_send[BUF_SIZE];
	struct sockaddr_in serveraddr, clientaddr;
	struct hostent *hp;
	char *haddrp;

	signal(SIGCHLD, SIG_IGN);

	if(argc != 2) {
		fprintf(stderr, "Usage: %s <port> \n", argv[0]);
		exit(0);
	}

	port = atoi(argv[1]);
	sfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)port);

	bind(sfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(sfd, 5);

	while(1) {
		clientLen = sizeof(clientaddr);
		cfd = accept(sfd, (struct sockaddr *)&clientaddr, &clientLen);
		haddrp = inet_ntoa(clientaddr.sin_addr);
		printf("Server: %s(%d) connected.\n", haddrp, clientaddr.sin_port);

		if(fork() == 0) {
			readLine(cfd, msg_recv);	// 소켓에서 파일 이름을 읽는다.
			fp = fopen(msg_recv, "r");
			if(fp == NULL) {
				write(cfd, "File is not here.", 20);
			} 
			else {	// 파일에서 한 줄씩 읽어 소켓을 통해 보낸다.
				while(fgets(msg_send, BUF_SIZE, fp) != NULL)
					write(cfd, msg_send, strlen(msg_send) + 1);
			}
			close(cfd);
			exit(0);
		}
		else close(cfd);
	}
}

readLine(int fd, char *str)
{
	int n;
	do {
		n = read(fd, str, 1);
	} while(n > 0 && *str++ != NULL);

	return (n > 0);
}
