/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:43 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/19 15:09:49 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	**make_args(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	check_marks(args);
	return (args);
}

char	**make_args_file(char **argv, char *file)
{
	char	**args;
	int		i;

	i = 0;
	if (access(file, 0) == -1)
	{
		file_error(file, 2);
		exit (-1);
	}
	while (file[i])
	{
		if ((file[i] == '/' && file[i - 1] != '.')
			|| ft_strcmp(argv[0],"sleep") == 0)
			return (argv);
		i++;
	}
	i = 0;
	while (argv[i])
		i++;
	int j = 0;
	while (argv[i - 1][j] && ++j)
		if (argv[i - 1][j - 1] == '/')
			return (argv);
	args = malloc(((i + 1) * sizeof(char *)) + 8);
	i = 0;
	while (argv[i] && ++i)
		args[i - 1] = argv[i - 1];
	args[i] = file;
	args[i + 1] = NULL;
	return (args);
}

char	*modify_mark(char *old)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (old[i])
	{
	//	printf("aqui\n");
		if (old[i] == '\"' && old[i - 1] == '\\')
			j++;
		i++;
	}
	if ((int)ft_strlen(old) == j)
		return (old);
	new = (char *)malloc(sizeof(char) * (ft_strlen(old) + 1));
	i = 0;
	j = 0;
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
//	free(old);
	return (new);
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
