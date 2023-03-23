#include "pipex.h"

int	errors(t_pipex *pipex, int argc, char **argv)
{

	pipex->fdin = open(argv[1], O_RDONLY);
	if (pipex->fdin < 0)
		file_error(argv[1]);
	pipex->fdout = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0000644);
	if (pipex->fdout < 0)
		file_error(argv[argc - 2]);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		arg_error(argv[5], 5);
	errors(&pipex, argc, argv);
	if (pipe(pipex.tube) < 0)
		arg_error("Error: ", 32);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
	{
		child1(&pipex, argv, envp);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
	{
		child2(&pipex, argv, envp);
	}
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
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
	close(pipex->tube[0]);
	pipex->args = make_args(argv[2]);
	pipex->args = make_args_file(pipex->args, argv[1]);
	pipex->cmd = file_cmd(pipex->args[0], envp);
	if (!pipex->cmd)
	{
		arg_error(pipex->args[0], 3);
		free_child(pipex);
		exit(-1);
	}
	dup2(pipex->tube[1], 1);
	dup2(pipex->fdin, 0);
	close(pipex->tube[1]);
	execve(pipex->cmd, pipex->args, envp);
}

void	child2(t_pipex *pipex, char **argv, char **envp/*, int src, int dst, int n*/)
{
	close(pipex->tube[1]);
	pipex->args = make_args(argv[3]);
	pipex->cmd = file_cmd(pipex->args[0], envp);
	if (!pipex->cmd)
	{
		arg_error(pipex->args[0], 3);
		free_child(pipex);
		exit(-1);
	}
	dup2(pipex->tube[0], 0);
//	dup2(pipex->fdout, 1);
	close(pipex->tube[0]);
	execve(pipex->cmd, pipex->args, envp);
}

/*
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
*/
