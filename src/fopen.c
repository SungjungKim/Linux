#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;

	if((fd = open(argv[1], O_RDWR)) == -1)
		perror(argv[1]);

	printf("파일 %s 열기 성공\n", argv[1]);
	close(fd);
	exit(0);
}
