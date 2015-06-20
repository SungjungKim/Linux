#include <stdio.h>
#include <pwd.h>
#include <grp.h>


/* print user id */
int main()
{
	int pid;

	printf("My real user id: %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
	printf("My effective user id: %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
	printf("My real group id: %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
	printf("My effective group id: %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);

}
