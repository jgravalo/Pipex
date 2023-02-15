/*
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/
#include "pipex.h"

//#define SIZE 512

void	print_array(char *name, char **str)
{
	int i;
	for (i = 0; str[i]; i++)
		printf("%s[%d]: \"%s\"\n", name, i, str[i]);
}

char	**make_args(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	return (args);
}

char	**make_args_file(char **argv, char *file)
{
	char	**args;
	int i;

	i = 0;
	while (argv[i])
		i++;
	args = malloc(((i + 1) * sizeof(char *)) + 8);
	i = 0;
	while (argv[i])
	{
		args[i] = argv[i];
		i++;
	}
	args[i] = file;
	args[i + 1] = NULL;
	return (args);
}

int main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
//	char	buffer[SIZE];
	t_pipex	*pipex;
	char	**args;
	char	*cmd;

	if (argc < 5)
		return (0);
//	print_array("argv", argv);
	pipex = (t_pipex *)malloc(sizeof(t_pipex) + 1);
	pipex->fdin = open(argv[1], O_RDONLY);
//	printf("fdin = %d\n", pipex->fdin);
	pipex->fdout = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0000644);
//	printf("fdout = %d\n", pipex->fdout);
	if (pipe(pipex->tube) < 0)
		return 0;
//	printf("\n");

	pid1 = fork();
	if (pid1 == 0)
	{ // hijo1
//		child(pipex->fdin, pipex->tube[1], 1);
		close(pipex->tube[0]); /* cerramos el lado de lectura del pipe */
		args = make_args(argv[2]);
		args = make_args_file(args, argv[1]);
		cmd = file_cmd(args[0], envp);
//		printf("cmd = %s\n", cmd);
//		print_array("args", args);
		dup2(pipex->tube[1], 1);
		dup2(pipex->fdin, 0);
		execve(cmd, args, envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{ // hijo2
//		child(pipex->tube[0], pipex->fdout, 2);
		close(pipex->tube[1]); /* cerramos el lado de escritura del pipe */
		args = make_args(argv[3]);
		cmd = file_cmd(args[0], envp);
//		printf("cmd = %s\n", cmd);
//		print_array("args", args);
		dup2(pipex->tube[0], 0);
//		dup2(pipex->fdout, 1);
		close(pipex->tube[0]);
		execve(cmd, args, envp);
	}
/*	else
	{ // padre
	}
*/	
	close(pipex->tube[0]);
	close(pipex->tube[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
/*		
{
	i = 1;
	while (i < argc - 3)
	{

	}
}

void	child(int src, int dst, int n)
{
	char	**args;
	char	*cmd;
	pid = fork();
	if (pid == 0)
	{
		args = make_args(argv[n + 1]);
		if (n == 1)
			args = make_args_file(args, argv[1]);
		print_array("args", args);
		cmd = file_cmd(args[0], envp);
		printf("cmd = %s\n", cmd);
		dup2(src, 0);
		dup2(dst, 1);
		execve(cmd, args, envp);
	}
}
*/
