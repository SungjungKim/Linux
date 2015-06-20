#include <stdio.h>

/* print the process number */
int main()
{
	int pid;
	printf("My process number: [%d] \n", getpid());
	printf("My parent process number: [%d] \n", getppid());
}
