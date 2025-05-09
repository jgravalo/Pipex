/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:38:44 by jgravalo          #+#    #+#             */
/*   Updated: 2025/03/16 19:38:50 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	ft_free_m(char **m)
{
	int	i;

	i = 0;
	while (m[i])
	{
		free(m[i]);
		i++;
	}
}

void	closes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n - 1)
	{
		close(pipex->p[i][0]);
		close(pipex->p[i][1]);
		i++;
	}
}

int	waits(t_pipex *pipex)
{
	int	i;
	int	exit;

	i = 0;
	exit = 0;
	while (i < pipex->n)
	{
		waitpid(pipex->pid[i], &exit, 0);
		i++;
	}
	if (WIFEXITED(exit))
		return (WEXITSTATUS(exit));
	return (1);
}

void	free_all(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n)
	{
		free(pipex->p[i]);
		i++;
	}
	free(pipex->p);
	free(pipex->pid);
}

/* 
void	ft_print_m(char **m) // BORRAR FUNCION
{
    for (int i = 0; m[i]; i++)
        dprintf(2, "m[%d] = <%s> ", i, m[i]);
    dprintf(2, "\n");
} */
