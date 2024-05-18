/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:03:32 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/25 12:46:54 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex1;
	t_pipex	pipex2;
	int		i;
	int		j;
	int		exit;

	i = 0;
	j = 0;
	exit = 0;
	if (argc < 5)
		return (1);
	i = errors(&pipex1, &pipex2, argc, argv);
	if (pipe(pipex2.tube) < 0)
		file_error("Error: ", 32);
	pipex1.pid = fork();
	if (pipex1.pid == 0)
		if (child1(&pipex1, pipex2, argv, envp) == -1)
			i = 127;

	while (j < argc - 5)
	{
		pipex1.tube = pipex2.tube;
		//dup2(pipex2.tube[0], pipex1.tube[0]);
		//dup2(pipex2.tube[1], pipex1.tube[1]);
		if (pipe(pipex2.tube) < 0)
			file_error("Error: ", 32);
		pipex1.pid = fork();
		if (pipex1.pid == 0)
			if (childn(&pipex1, pipex2, argv, envp) == -1)
				i = 127;
		close(pipex1.tube[0]);
		close(pipex1.tube[1]);
	}
	pipex2.pid = fork();
	if (pipex2.pid == 0)
		if (child2(&pipex1, &pipex2, argv, envp) == -1)
			i = 127;
	close(pipex1.tube[0]);
	close(pipex1.tube[1]);
	waitpid(pipex1.pid, NULL, 0);
	while (j < argc - 5)
		waitpid(pipex1.pid, NULL, 0);
	waitpid(pipex2.pid, &exit, 0);
	exit = WEXITSTATUS(exit);
	return (exit);
}

int	child1(t_pipex *pipex1, t_pipex *pipex2, char **argv, char **envp)
{
	close(pipex2->tube[0]);
	pipex1->args = make_args(argv[2]);
	pipex1->args = make_args_file(pipex->args, argv[1]);
	pipex1->cmd = file_cmd(pipex->args[0], envp);
	if (!pipex1->cmd)
	{
		file_error(pipex1->args[0], 3);
		free_child(pipex1);
		exit(-1);
	}
	dup2(1, 10);
	dup2(pipex2->tube[1], 1);
	dup2(pipex1->fdin, 0);
	close(pipex2->tube[1]);
	execve(pipex1->cmd, pipex1->args, envp);
	exit(1);
}

int	childn(t_pipex *pipex1, t_pipex *pipex2, char **argv, char **envp)
{
	close(pipex1->tube[1]);
	close(pipex2->tube[0]);
	pipex1->args = make_args(argv[3]);
	pipex1->cmd = file_cmd(pipex1->args[0], envp);
	if (!pipex1->cmd)
	{
		file_error(pipex1->args[0], 3);
		free_child(pipex1);
		exit(-1);
	}
	dup2(1, 10);
	dup2(pipex1->tube[0], 0);
	dup2(pipex2->tube[1], 1);
	close(pipex1->tube[0]);
	close(pipex2->tube[1]);
	execve(pipex1->cmd, pipex1->args, envp);
	exit(1);
}

int	child2(t_pipex *pipex1, t_pipex *pipex2, char **argv, char **envp)
{
	close(pipex2->tube[1]);
	pipex1->args = make_args(argv[3]);
	pipex1->cmd = file_cmd(pipex1->args[0], envp);
	if (!pipex1->cmd)
	{
		file_error(pipex1->args[0], 3);
		free_child(pipex1);
		exit(-1);
	}
	dup2(1, 10);
	dup2(pipex2->tube[0], 0);
	dup2(pipex1->fdout, 1);
	close(pipex2->tube[0]);
	execve(pipex1->cmd, pipex1->args, envp);
	exit(1);
}

char	**make_args(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	check_marks(args);
	return (args);
}
