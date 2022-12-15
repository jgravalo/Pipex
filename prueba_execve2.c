#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	int i;
	if (!argc)
		return (0);
//	char *cmd = "/usr/bin/wc";
	char *cmd = "/bin/ls";
	for (i = 0; argv[i]; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
	execve(cmd, argv, envp);
	return (0);
}
