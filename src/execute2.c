
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("parent process start \n");
	if(fork() == 0) {
		execl("/bin/echo", "echo", "hello", NULL);
		fprintf(stderr, "first failed.");
		exit(1);
	}

	if(fork() == 0) {
		execl("/bin/date", "date", NULL);
		fprintf(stderr, "second failed.");
		exit(2);
	}

	if(fork() == 0) {
		execl("/bin/ls", "ls", "-l",  NULL);
		fprintf(stderr, "third failed.");
		exit(3);
	}

	printf("parenet process end\n");

}
