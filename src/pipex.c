/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:03:32 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/15 14:51:14 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int i;

	//
//	int i; for (i = 0; argv[i]; i++) printf("argv[%d] = |%s|\n", i, argv[i]);
	//
	i = 0;
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
	wait(NULL);
	return (i);
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
	return (execve(pipex->cmd, pipex->args, envp));

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
	return (execve(pipex->cmd, pipex->args, envp));
}
