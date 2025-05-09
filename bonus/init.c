/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:46:28 by jgravalo          #+#    #+#             */
/*   Updated: 2025/03/16 19:46:31 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	ft_strerror(char *file, char *msg)
{
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	error(char *file, int n, int f)
{
	if (f)
		ft_strerror(file, strerror(n));
	if (access(file, F_OK))
		ft_strerror(file, strerror(2));
	else if (access(file, X_OK))
		ft_strerror(file, strerror(13));
	else
		ft_strerror(file, strerror(n));
}

void	set_vars(t_pipex *pipex)
{
	pipex->here_doc = 0;
	if (!ft_strcmp(pipex->argv[1], "here_doc"))
		pipex->here_doc = 1;
	if (pipex->here_doc)
		here_doc(pipex);
	else
		pipex->infile = open(pipex->argv[1 + pipex->here_doc], O_RDONLY);
	if (pipex->infile == -1)
	{
		error(pipex->argv[1 + pipex->here_doc], 9, 0);
		exit(1);
	}
	if (pipex->here_doc)
		pipex->outfile = open(pipex->argv[pipex->argc - 1],
				O_RDWR | O_APPEND | O_CREAT, 00644);
	else
		pipex->outfile = open(pipex->argv[pipex->argc - 1],
				O_RDWR | O_TRUNC | O_CREAT, 00644);
	if (pipex->outfile == -1)
	{
		error(pipex->argv[pipex->argc - 1], 9, 0);
		exit(1);
	}
	pipex->i = 0;
}

char	*get_line(void)
{
	char	*buffer;
	char	*text;
	int		num;

	buffer = malloc(2);
	text = NULL;
	if (!buffer)
		return (NULL);
	num = 1;
	while (!ft_strchr(text, '\n') && num != 0)
	{
		num = read(0, buffer, 1);
		if (num == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[num] = '\0';
		text = ft_strjoin(text, buffer);
	}
	free(buffer);
	return (text);
}

void	here_doc(t_pipex *pipex)
{
	char	*line;
	char	*key;
	int		p[2];

	pipe(p);
	while (42)
	{
		line = get_line();
		key = ft_strjoin(pipex->argv[2], "\n");
		if (!ft_strcmp(line, key))
			break ;
		write(p[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	pipex->infile = dup(p[0]);
	close(p[1]);
}
