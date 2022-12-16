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

char    *ft_itoa(int n);

int		search_path(char **envp);

char	**split_docs(char *path);

char	*access_comm(char *comm, char **docs);

char    **modify_file(char *comm, char **file, int size);

char    *modify_comm(char *comm, int size);

int		exec_comm(char *comm, char **file, char **envp);

char    **makesrc(char **argv);

char    **make_commands(int argc, char **argv);

void	fzero(int fd);

void    child(int a[], int b[], char *comm, char **src, char **envp);

void    father(int a[], int b[], char *dst, int n);
//void    father(int a[], int b[], char *dst);

int		pipex(char *comm, char **file, char **envp, char *dst, int n);
//int		pipex(char *comm, char **file, char **envp, char *dst);

#endif
