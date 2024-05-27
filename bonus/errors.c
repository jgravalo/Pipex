/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:43 by jgravalo          #+#    #+#             */
/*   Updated: 2024/05/27 21:55:03 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	errors(t_pipex *pipex1, t_pipex *pipex2, int argc, char **argv)
{
	int	i;

	i = 0;
	if (access(argv[argc - 1], F_OK) != -1
		&& access(argv[argc - 1], W_OK) == -1)
		exit(1);
	pipex2->fdout = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (pipex2->fdout == -1)
		exit(127);
	pipex1->fdin = open(argv[1], O_RDONLY);
	return (i);
}

int	cmd_error(char *str)
{
	write(2, "pipex: ", 7);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
	return (-1);
}

int	file_error(char *s, int n)
{
	char	*str;

	str = ft_strjoin(s, ": ");
	str = ft_strjoin(str, strerror(n));
	write(2, "pipex: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (0);
}

void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->args[i])
	{
		free(pipex->args[i]);
		i++;
	}
	free(pipex->args);
	free(pipex->cmd);
}
