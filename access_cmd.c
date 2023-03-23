/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:09:57 by jgravalo          #+#    #+#             */
/*   Updated: 2023/03/23 16:25:03 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// BUSCO EL PUNTERO DEL PATH EN EL ENTORNO
int	search_path(char **envp)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	path = "PATH";
	while (envp[i])
	{
		j = 0;
		while (path[j] && envp[i][j] == path[j])
		{
			j++;
		}
		if (!path[j])
		{
			return (i);
		}
		i++;
	}
	free(path);
	return (0);
}

// CREO UN ARRAY DE STRINGS CON LAS DIRECCIONES DENTRO DEL PATH
char	**split_docs(char *path)
{
	char	**docs;
	char	*dirs;

	dirs = ft_substr(path, 5, ft_strlen(path) - 5);
	docs = ft_split(dirs, ':');
	free(dirs);
	return (docs);
}

// VERIFICO LA EXISTENCIA DEL COMANDO
char	*access_cmd(char *cmd, char**docs)
{
	char	*tmp;
	int		i;

	i = 0;
	while (docs[i])
	{
		tmp = ft_strjoin(docs[i], "/");
		docs[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if ((access(docs[i], 0)) != -1)
			return (docs[i]);
		i++;
	}
	cmd_error(cmd);
	exit(-1);
}

char	*file_cmd(char *cmd, char **envp)
{
	int		env;
	char	**docs;
	char	*file;

	env = search_path(envp);
	docs = split_docs(envp[env]);
	file = access_cmd(cmd, docs);
	free(docs);
	return (file);
}
