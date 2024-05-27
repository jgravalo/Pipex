/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:09:57 by jgravalo          #+#    #+#             */
/*   Updated: 2024/05/27 21:55:27 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

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
	return (-1);
}

char	**split_docs(char *path)
{
	char	**docs;
	char	*dirs;

	dirs = ft_substr(path, 5, ft_strlen(path) - 5);
	docs = ft_split(dirs, ':');
	free(dirs);
	return (docs);
}

int	is_local(char *cmd)
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

char	*access_cmd(char *cmd, char**docs, int env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (docs[i])
	{
		tmp = ft_strjoin(docs[i], "/");
		docs[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if ((access(docs[i], F_OK)) != -1)
			return (docs[i]);
		i++;
	}
	if (env == -1 && access(cmd, F_OK) == 0)
		return (cmd);
	if (is_local(cmd) == 0 && !(cmd[0] == '.' && cmd[1] == '/'))
	{
		cmd_error(cmd);
		exit(127);
	}
	if (access(cmd, F_OK) != -1 && access(cmd, X_OK) != -1)
		return (cmd);
	cmd_error(cmd);
	exit(126);
}

char	*file_cmd(char *cmd, char **envp)
{
	int		env;
	char	*file;
	char	**docs;

	env = 0;
	if (!(cmd[0] == '.' && cmd[1] == '/'))
		env = search_path(envp);
	if (env != -1)
		docs = split_docs(envp[env]);
	else
		docs = split_docs(DEF_PATH);
	file = access_cmd(cmd, docs, env);
	free(docs);
	return (file);
}
