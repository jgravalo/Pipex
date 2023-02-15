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


typedef struct s_pipex{
	int		fdin;
	int		fdout;
	int		tube[2];
	char	*cmd;
} t_pipex;

size_t	ft_strlen(const char *str);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	**ft_split(char const *s, char c);

char	*ft_strjoin(char *s1, char *s2);

char    *ft_itoa(int n);

int		search_path(char **envp);

char	**split_docs(char *path);

char	*access_cmd(char *comm, char **docs);

char    *file_cmd(char *cmd, char **envp);
/*
char    **modify_file(char *comm, char **file, int size, int n);

int		exec_comm(char *comm, char **file, char **envp, int n);

char    **makesrc(char **argv);

char    **make_commands(int argc, char **argv);

void	fzero(int fd);

void    child(int a[], char *comm, char **src, char **envp, int n);

void    child2(int a[], int b[], char *comm, char **src, char **envp, int n);

void    father(int a[], int b[], char *dst, int n);

int		pipex(char **comm, char **file, char **envp, char *dst, int n);
*/
#endif
