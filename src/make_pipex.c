/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:43 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/13 17:09:03 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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
	while (file[i])
	{
		if ((file[i] == '/' && file[i - 1] != '.') || ft_strcmp(argv[0],"sleep") == 0)
			return (argv);
		i++;
	}
	i = 0;
	while (argv[i])
		i++;
	int j = 0;
	while (argv[i - 1][j])
	{
		if (argv[i - 1][j] == '/')
			return (argv);
		j++;
	}
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
