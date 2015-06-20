/*
	filename : fclient.c

	명령줄 인수로 연결할 서버의 이름과 포트 번호를 받아 해당 서버에 소켓 연결을 한다.
	이 클라이언트 프로그램은 이 연결을 통해 서버에 원하는 파일 이름을 보낸 후 서버로부터 해당 파일 내용을 받아 사용자에게 출력한다.
	gethostbyname(): 서버 이름에 해당하는 호스트 엔트리를 찾아 서버 소켓의 IP 주소와 포트 번호를 설정한다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DEFAULT_PROTOCOL 0
#define BUF_SIZE 100

int main(int argc, char *argv[])
{
	int sfd, port, result;
	char *host, msg_recv[BUF_SIZE], msg_send[BUF_SIZE];
	struct sockaddr_in serverAddr;
	struct hostent *hp;

	if(argc != 3) {
		fprintf(stderr, "Usage: %s <host> <port> \n", argv[0]);
		exit(0);
	}

	host = argv[1];
	port = atoi(argv[2]);

	sfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

	/* 서버의 IP 주소와 포트 번호로 채운다. */
	if((hp = gethostbyname(host)) == NULL)
		perror("gethostbyname error");		// 호스트 찾기 에러

	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	bcopy((char *) hp->h_addr_list[0], (char *) &serverAddr.sin_addr.s_addr, hp->h_length);
	serverAddr.sin_port = htons(port);

	do {	// 연결 요청
		result = connect(sfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
		if(result == -1) sleep(1);
	} while(result == -1);

	printf("다운로드할 파일 이름 입력:");
	scanf("%s", msg_recv);
	write(sfd, msg_recv, strlen(msg_recv) + 1);

	/* 소켓으로부터 파일 내용을 읽어서 프린트 */
	while(readLine(sfd, msg_send))
		printf("%s", msg_send);

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
