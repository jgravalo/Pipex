/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:43 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/19 14:53:43 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	errors(t_pipex *pipex, int argc, char **argv)
{
	int i;

	i = 0;
	pipex->fdin = open(argv[1], O_RDONLY);
	pipex->fdout = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 00644);
	return (i);
}

int	cmd_error(char *str)
{
	write(2, "pipex: ", 7);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
//	exit(-1);
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
//	exit(-1);
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
