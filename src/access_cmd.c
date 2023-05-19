/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:09:57 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/19 15:29:07 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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
			j++;
		if (!path[j])
			return (i);
		i++;
	}
	free(path);
	return (-1);
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
int		is_local(char *cmd)
{
	int	i;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/' && cmd[i - 1] != '.')
			return (-1);
		i++;
	}
	return (0);
}

char	*access_cmd(char *cmd, char**docs)//, int env)
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
	if (is_local(cmd) == 0 && !(cmd[0] == '.' && cmd[1] == '/'))
	{
		cmd_error(cmd);
		exit(-1);
	}
	if (access(cmd, 0) != -1 && access(cmd, X_OK) != -1)
		return (cmd);
	cmd_error(cmd);
	exit(-2);
//	return (0);
}

char	*file_cmd(char *cmd, char **envp)
{
	int		env;
	char	*file;
	char	**docs;
	
	env = 0;
	if (!(cmd[0] == '.' && cmd[1] == '/'))
		env = search_path(envp);
/*
	write(2, "envp[0] = |", 10);
	write(2, envp[0], ft_strlen(envp[0]));
	write(2, "|\n", 2);
*/
//	if (env == -1)
//		return (cmd);
//	if (env > 0)
//	{
	docs = split_docs(envp[env]);
	file = access_cmd(cmd, docs);//, env);
//	}
	free(docs);
	return (file);
}
