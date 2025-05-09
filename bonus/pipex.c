/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:49:29 by jgravalo          #+#    #+#             */
/*   Updated: 2025/03/16 19:49:33 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		write(2, "bad arguments\n", 14);
		return (1);
	}
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	set_vars(&pipex);
	pipex.n = argc - 3 - pipex.here_doc;
	pipes(&pipex);
}

void	pipes(t_pipex *pipex)
{
	int	i;

	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * pipex->n);
	pipex->p = (int **)malloc(pipex->n * sizeof(int *));
	i = 0;
	while (i < pipex->n - 1)
	{
		pipex->p[i] = (int *)malloc(2 * sizeof(int));
		pipe(pipex->p[i]);
		i++;
	}
	child1(pipex);
	childn(pipex);
	child2(pipex);
	closes(pipex);
	waits(pipex);
	free_all(pipex);
}

void	child1(t_pipex *pipex)
{
	pipex->i = 0;
	pipex->pid[0] = fork();
	if (pipex->pid[0] == -1)
	{
		error("pipex", 10, 1);
		exit (1);
	}
	if (pipex->pid[0] == 0)
	{
		dup2(pipex->infile, 0);
		dup2(pipex->p[0][1], 1);
		exec(pipex);
	}
	pipex->i++;
}

void	childn(t_pipex *pipex)
{
	while (pipex->i + 1 < pipex->n)
	{
		pipex->pid[pipex->i] = fork();
		if (pipex->pid[pipex->i] == -1)
		{
			error("pipex", 10, 1);
			exit (1);
		}
		if (pipex->pid[pipex->i] == 0)
		{
			dup2(pipex->p[pipex->i - 1][0], 0);
			dup2(pipex->p[pipex->i][1], 1);
			exec(pipex);
		}
		pipex->i++;
	}
}

void	child2(t_pipex *pipex)
{
	pipex->pid[pipex->i] = fork();
	if (pipex->pid[pipex->i] == -1)
	{
		error("pipex", 10, 1);
		exit (1);
	}
	if (pipex->pid[pipex->i] == 0)
	{
		dup2(pipex->p[pipex->i - 1][0], 0);
		dup2(pipex->outfile, 1);
		exec(pipex);
	}
}
