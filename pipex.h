#ifndef PIPEX_H
#define PIPEX_H

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pipex.h"

#define SIZE 512

size_t	ft_strlen(const char *str);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	**ft_split(char const *s, char c);

char	*ft_strjoin(char *s1, char *s2);

int		search_path(char **envp);

char	**split_docs(char *path);

char	*access_comm(char *comm, char **docs);

int		exec_comm(char *comm, char **file, char **envp);

int		pipex(char *comm, char **file, char **envp);

#endif
