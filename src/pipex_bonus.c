#include "pipex_bonus.h"

int	errors(t_pipex *pipex, int argc, char **argv)
{

	if (argc < 5)
		arg_error(argv[5], 5);
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

	t_pipex	pipex[argc - 4], *ptr;
	int		i;


	ptr = pipex[argc - 4];
	errors(ptr[0], argc, argv);
	i = 0;
	while (ptr[i])
	{
		if (pipe(ptr[i].tube) < 0)
			arg_error("Error: ", 32);
		ptr[i].pid1 = fork();
		i++;
	}
	if (ptr[0].pid1 == 0)
	{
		child1(ptr[0], argv, envp);
		i++;
	}
	i = 1;
	while (ptr[i])
	{
		if (ptr[i].pid1 == 0)
		{
			childn(ptr, argv, envp, i);
		}
		i++;
	}
	ptr[0].pid2 = fork();
	if (ptr[0].pid2 == 0)
	{
		child2(ptr, argc, argv, envp, i);
	}

	i = 0;
	while (ptr[i])
	{
		close(ptr[i].tube[0]);
		close(ptr[i].tube[1]);
		waitpid(ptr[i].pid1, NULL, 0);
		i++;
	}
	waitpid(ptr[0].pid2, NULL, 0);


/*
	t_pipex	pipex[argc - 4];
	int		i;

	errors(&pipex[0], argc, argv);
	i = 0;
	while (pipex[i])
	{
		if (pipe(pipex[i].tube) < 0)
			arg_error("Error: ", 32);
		pipex[i].pid1 = fork();
		i++;
	}
	if (pipex[0].pid1 == 0)
	{
		child1(&pipex[0], argv, envp);
		i++;
	}
	i = 1;
	while (pipex[i])
	{
		if (pipex[i].pid1 == 0)
		{
			childn(&pipex, argv, envp, i);
		}
		i++;
	}
	pipex[0].pid2 = fork();
	if (pipex[0].pid2 == 0)
	{
		child2(&pipex, argc, argv, envp, i);
	}

	i = 0;
	while (pipex[i])
	{
		close(pipex[i].tube[0]);
		close(pipex[i].tube[1]);
		waitpid(pipex[i].pid1, NULL, 0);
		i++;
	}
	waitpid(pipex[0].pid2, NULL, 0);
	return (0);
*/
}
		
void	child1(t_pipex *pipex, char **argv, char **envp)
{
	close(pipex[0].tube[0]);
	close(pipex[1].tube[1]);
	
	pipex[0].args = make_args(argv[2]);
	pipex[0].args = make_args_file(pipex[0].args, argv[1]);
	pipex[0].cmd = file_cmd(pipex[0].args[0], envp);
	if (!pipex[0].cmd)
	{
		arg_error(pipex[0].args[0], 3);
		free_child(&pipex[0]);
		exit(-1);
	}
	dup2(pipex[0].fdin, 1);
	dup2(pipex[1].tube[0], 0);
	
	close(pipex[0].tube[1]);
	close(pipex[1].tube[0]);
	execve(pipex[0].cmd, pipex[0].args, envp);
}

void	childn(t_pipex *pipex, char **argv, char **envp, int i)
{
	close(pipex[i].tube[0]);
	close(pipex[i + 1].tube[1]);

	pipex[i].args = make_args(argv[2 + i]);
	pipex[i].cmd = file_cmd(pipex[i].args[0], envp);
	if (!pipex[i]->cmd)
	{
		arg_error(pipex[i].args[0], 3);
		free_child(&pipex[i]);
		exit(-1);
	}
	dup2(pipex[i].tube[1], 1);
	dup2(pipex[i + 1].tube[0], 0);

	close(pipex[i].tube[1]);
	close(pipex[i + 1]->tube[0]);
	execve(pipex[i].cmd, pipex[i].args, envp);
}

void	child2(t_pipex *pipex, int argc, char **argv, char **envp, int n)
{
	close(pipex[0].tube[1]);
	
	pipex[0].args = make_args(argv[argc - 2]);
	pipex[0].cmd = file_cmd(pipex[0].args[0], envp);
	if (!pipex[0]->cmd)
	{
		arg_error(pipex[0].args[0], 3);
		free_child(&pipex[0]);
		exit(-1);
	}
	dup2(pipex[n].tube[0], 0);
//	dup2(pipex[0].fdout, 1);
	
	close(pipex.tube[0]);
	execve(pipex.cmd, pipex.args, envp);
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
