/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:14:07 by jgravalo          #+#    #+#             */
/*   Updated: 2022/12/16 15:47:40 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// BUSCO EL PUNTERO DEL PATH EN EL ENTORNO
int search_path(char **envp)
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
	exit(-1);
}

// CREO UN ARRAY DE STRINGS CON LAS DIRECCIONES DENTRO DEL PATH
char **split_docs(char *path)
{
	char **docs;
	char *dirs;

	dirs = ft_substr(path, 5, ft_strlen(path) - 5);
	docs = ft_split(dirs, ':');
	free(dirs);
	return (docs);
}

// VERIFICO LA EXISTENCIA DEL COMANDO
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

// ARREGLAMOS EL ARRAY DE ARGUMENTOS SI HAY FLAGS
char	**modify_file(char *comm, char **file, int size)
{
	char **src;
	
	src = (char **)malloc(sizeof(char *) * 4);
	src[0] = modify_comm(comm, size);
	src[1] = ft_substr(comm, size + 1, ft_strlen(comm) - size);
	src[2] = file[1];
	src[3] = NULL;
	free(file);
	return (src);
}

// ARREGLAMOS LA STRING DEL COMANDO SI HAY FLAGS
char	*modify_comm(char *comm, int size)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * size + 1);
	i = 0;
	while (i < size)
	{
		new[i] = comm[i];
		i++;
	}
	new[i] = '\0';
//	printf("new comm = %s\n", new);// BORRAR !!!
	return (new);
}

char	*make_comm(char *comm, char **envp)
{
    int env;
    char **docs;
	char *cmd;

	env = search_path(envp);
	docs = split_docs(envp[env]);
	cmd = access_comm(comm, docs);
	free(docs);
	return (cmd);
}

int exec_comm(char *comm, char **file, char **envp)
{
	int i = 0;
	char *cmd;

	while (comm[i] && (!(comm[i] == ' ' && comm[i + 1] == '-')))
		i++;
	if (comm[i] == ' ' && comm[i + 1] == '-')
	{
		file = modify_file(comm, file, i);
		comm = modify_comm(comm, i);
	}
	cmd = make_comm(comm, envp);
	printf("cmd = %s, file0 = \"%s\", file1 = \"%s\", file2 = \"%s\"\n", cmd, file[0], file[1], file[2]);
	return (execve(cmd, file, envp));
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
}
*/
