/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:14:07 by jgravalo          #+#    #+#             */
/*   Updated: 2022/11/25 14:06:06 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int search_path(char **envp)
{
	char	*path = "PATH";
	int		i;
	int		j;

	i = 0;
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
	return (-1);
}

char **split_docs(char *path)
{
	char **docs;
	char *dirs;

	dirs = ft_substr(path, 5, ft_strlen(path) - 5);
	docs = ft_split(dirs, ':');
	free(dirs);
	return (docs);
}

char *access_comm(char *comm, char**docs)
{
	char *tmp;
	int i;

	i = 0;
	while (docs[i])
	{
		tmp = ft_strjoin(docs[i], "/");
		docs[i] = ft_strjoin(tmp, comm);
		free(tmp);
		if ((access(docs[i], 0)) != -1)
			return (docs[i]);
		i++;
	}
	return (0);
}

int exec_comm(char *comm, char **file, char **envp)
{
	int env;
	char **docs;

//	printf("comm = %s file = %s\n", comm, file[1]);// BORRAR !!!
	env = search_path(envp);
	docs = split_docs(envp[env]);
//	char **file = &argv[2];
	char *cmd = access_comm(comm, docs);
	free(docs);
	execve(cmd, file, envp);
	return (0);
}
/*
int main(int argc, char **argv, char **envp)
{
	if (argc < 2 || !argv || !envp)
		return (0);
//	int i;
//	for (i = 1; argv[i]; i++)
//		printf("argv[%d] = %s, ", i, argv[i]);
	exec_comm(argc, argv, envp);
	return (0);
}*/
/*
int main(int argc, char **argv, char **envp)
{
	if (argc < 2 || !argv || !envp)
		return (0);
	char *cmd = "/bin/echo";
	execve(cmd, argv, envp);
	return 0;
}*/
