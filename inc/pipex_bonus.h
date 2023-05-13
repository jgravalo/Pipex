/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:25:44 by jgravalo          #+#    #+#             */
/*   Updated: 2023/02/21 17:27:37 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "pipex.h"

# define SIZE 512

typedef struct s_pipex{
	int		fdin;
	int		fdout;
	int		tube[2];
	char	*cmd;
	char	**args;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

size_t	ft_strlen(const char *str);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	**ft_split(char const *s, char c);

char	*ft_strjoin(char *s1, char *s2);

int		search_path(char **envp);

char	**split_docs(char *path);

char	*access_cmd(char *comm, char **docs);

char	*file_cmd(char *cmd, char **envp);

void	childn(t_pipex *pipex, char **argv, char **envp, int i);

void	child1(t_pipex *pipex, char **argv, char **envp);

void	child2(t_pipex *pipex, int argc, char **argv, char **envp, int n);

char	**make_args(char *cmd);

char	**make_args_file(char **argv, char *file);

int		file_error(char *str);

int		arg_error(char *s, int n);

void	free_child(t_pipex *pipex);
#endif
