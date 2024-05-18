/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:43 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/25 12:47:36 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	errors_args(char **argv, char *file)
{
	int		i;
	int		j;

	i = 0;
	while (file[i])
	{
		if ((file[i] == '/' && file[i - 1] != '.')
			|| ft_strcmp(argv[0], "sleep") == 0)
			return (1);
		i++;
	}
	i = 0;
	while (argv[i])
		i++;
	j = 0;
	while (argv[i - 1][j] && ++j)
		if (argv[i - 1][j - 1] == '/')
			return (1);
	return (0);
}

char	**make_args_file(char **argv, char *file)
{
	char	**args;
	int		i;

	if (access(file, 0) == -1)
	{
		file_error(file, 2);
		exit (-1);
	}
	if (errors_args(argv, file) == 1)
		return (argv);
	i = 0;
	while (argv[i])
		i++;
	args = malloc(((i + 1) * sizeof(char *)) + 8);
	i = 0;
	while (argv[i] && ++i)
		args[i - 1] = argv[i - 1];
	args[i] = file;
	args[i + 1] = NULL;
	return (args);
}

char	*new_mark(char *old)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(old) + 1));
	while (old[i])
	{
		if (old[i] == '\\' && old[i + 1] == '\"')
		{
			new[j] = '\"';
			i++;
		}
		else
			new[j] = old[i];
		i++;
		j++;
	}
	return (new);
}

char	*modify_mark(char *old)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] == '\"' && old[i - 1] == '\\')
			j++;
		i++;
	}
	if ((int)ft_strlen(old) == j)
		return (old);
	return (new_mark(old));
}

void	check_marks(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		argv[i] = modify_mark(argv[i]);
		i++;
	}
}
