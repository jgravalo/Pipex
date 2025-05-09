/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:57:27 by jgravalo          #+#    #+#             */
/*   Updated: 2025/03/16 19:57:36 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**paths;
	char	**args;
	char	*join;
	char	*cmd;
	pid_t	*pid;
	char	*substr;
	int		**p;
	int		here_doc;
	int		i;
	int		n;
	int		infile;
	int		outfile;
}	t_pipex;

void	ft_strerror(char *file, char *msg);

void	error(char *file, int n, int f);

void	ft_free_m(char **m);

void	set_vars(t_pipex *pipex);

void	pipes(t_pipex *pipex);

int		waits(t_pipex *pipex);

void	exec(t_pipex *pipex);

void	child1(t_pipex *pipex);

void	childn(t_pipex *pipex);

void	child2(t_pipex *pipex);

void	get_paths(t_pipex *pipex);

void	get_cmd(t_pipex *pipex);

void	closes(t_pipex *pipex);

void	here_doc(t_pipex *pipex);

void	free_all(t_pipex *pipex);

char	**ft_split(char *s, char c);

char	*ft_substr(char *s, unsigned int start, size_t len);

int		ft_strcmp(char *s1, char *s2);

size_t	ft_strlen(char *str);

char	*ft_strchr(char *str, int c);

char	*ft_strjoin(char *s1, char *s2);

#endif
