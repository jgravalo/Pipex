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

int	file_error(char *str)
{
	perror(str);
	exit(0);
}

int	arg_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (0);
}

int	errors(t_pipex *pipex, int argc, char **argv)
{

	if (argc < 5)
		arg_error("ERR_INFILE");
	pipex->fdin = open(argv[1], O_RDONLY);
	if (pipex->fdin < 0)
		file_error("ERR_INFILE");
	pipex->fdout = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0000644);
	if (pipex->fdout < 0)
		file_error("ERR_OUTFILE");
	if (pipe(pipex->tube) < 0)
		arg_error("ERR_PIPE");
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex) + 1);
	errors(pipex, argc, argv);
	pid1 = fork();
	if (pid1 == 0)
	{ // hijo1
//		child(argv, envp, pipex->fdin, pipex->tube[1], 1);
		child1(pipex, argv, envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{ // hijo2
//		child(argv, envp, pipex->tube[0], pipex->fdout, 2);
		child2(pipex, argv, envp);
	}
	close(pipex->tube[0]);
	close(pipex->tube[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
		
/*
	i = 1;
	while (i < argc - 3)
	{
		if (pid[i] == 0)
		{
			
		}
	}
*/
void	child1(t_pipex *pipex, char **argv, char **envp/*, int src, int dst, int n*/)
{
	close(pipex->tube[0]); /* cerramos el lado de lectura del pipe */
	pipex->args = make_args(argv[2]);
	pipex->args = make_args_file(pipex->args, argv[1]);
	pipex->cmd = file_cmd(pipex->args[0], envp);
	dup2(pipex->tube[1], 1);
	dup2(pipex->fdin, 0);
	close(pipex->tube[1]); /* cerramos el lado de escritura del pipe */
	execve(pipex->cmd, pipex->args, envp);
}

void	child2(t_pipex *pipex, char **argv, char **envp/*, int src, int dst, int n*/)
{
	close(pipex->tube[1]); /* cerramos el lado de escritura del pipe */
	pipex->args = make_args(argv[3]);
	pipex->cmd = file_cmd(pipex->args[0], envp);
	dup2(pipex->tube[0], 0);
//	dup2(pipex->fdout, 1);
	close(pipex->tube[0]); /* cerramos el lado de lectura del pipe */
	execve(pipex->cmd, pipex->args, envp);
}

void	child(t_pipex *pipex, char **argv, char **envp, int src, int dst, int n)
{
//	pid = fork();
//	if (pid == 0)
//	{
		pipex->args = make_args(argv[n + 1]);
		if (n == 1)
			pipex->args = make_args_file(pipex->args, argv[1]);
		print_array("args", pipex->args);
		pipex->cmd = file_cmd(pipex->args[0], envp);
//		printf("cmd = %s\n", pipex->cmd);
//		print_array("args", pipex->args);
		dup2(src, 0);
		dup2(dst, 1);
		execve(pipex->cmd, pipex->args, envp);
//	}
}

