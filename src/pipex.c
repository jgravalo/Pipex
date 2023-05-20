/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:03:32 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/20 16:47:29 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		exit;

	i = 0;
	exit = 0;
	if (argc < 5)
		return (1);
	i = errors(&pipex, argc, argv);
	if (pipe(pipex.tube) < 0)
		file_error("Error: ", 32);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		if (child1(&pipex, argv, envp) == -1)
			i = 127;
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		if (child2(&pipex, argv, envp) == -1)
			i = 127;
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &exit, 0);
	exit = WEXITSTATUS(exit);
	return (exit);
}

int	child1(t_pipex *pipex, char **argv, char **envp)
{
	close(pipex->tube[0]);
	pipex->args = make_args(argv[2]);
	pipex->args = make_args_file(pipex->args, argv[1]);
	pipex->cmd = file_cmd(pipex->args[0], envp);
	if (!pipex->cmd)
	{
		file_error(pipex->args[0], 3);
		free_child(pipex);
		exit(-1);
	}
	dup2(1, 10);
	dup2(pipex->tube[1], 1);
	dup2(pipex->fdin, 0);
	close(pipex->tube[1]);
	execve(pipex->cmd, pipex->args, envp);
	exit(1);
}

int	child2(t_pipex *pipex, char **argv, char **envp)
{
	close(pipex->tube[1]);
	pipex->args = make_args(argv[3]);
	pipex->cmd = file_cmd(pipex->args[0], envp);
	if (!pipex->cmd)
	{
		file_error(pipex->args[0], 3);
		free_child(pipex);
		exit(-1);
	}
	dup2(1, 10);
	dup2(pipex->tube[0], 0);
	dup2(pipex->fdout, 1);
	close(pipex->tube[0]);
	execve(pipex->cmd, pipex->args, envp);
	exit(1);
}

char	**make_args(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	check_marks(args);
	return (args);
}
