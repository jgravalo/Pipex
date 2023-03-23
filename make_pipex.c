/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:43 by jgravalo          #+#    #+#             */
/*   Updated: 2023/03/23 15:14:56 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**make_args(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	return (args);
}

char	**make_args_file(char **argv, char *file)
{
	char	**args;
	int		i;

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

int	cmd_error(char *str)
{
	write(2, "zsh: command not found: ", 24);
	write(2, str, ft_strlen(str));

//    exit(0);
	return (0);
}

int	arg_error(char *s, int n)
{
	char	*str;

	str = ft_strjoin(s,": ");
	str = ft_strjoin(str, strerror(n));
	write(2, str, ft_strlen(str));
//	exit(0);
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
