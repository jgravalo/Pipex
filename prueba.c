#include"pipex.h"

int main(int argc, char **argv, char **envp)
{
    if (argc < 2 || !argv || !envp)
        return (0);
//    char *cmd = "/usr/bin/wc";
    char *cmd = "/bin/ls";
    int i;
    for (i = 0; argv[i]; i++)
        printf("argv[%d] = %s\n", i, argv[i]);
    execve(cmd, argv, envp);
    return 0;
}
