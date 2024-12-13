#ifndef PIPEX_H
#define PIPEX_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include"get_next_line.h"

//child(t_pipex, int *fdin, int *fdout);

typedef struct s_cmd {
	char	cmd;
	t_cmd	*next;
}	t_cmd;
typedef struct s_pipex {
	int 	fdin;// open(infile) || dup(p[0])
	int 	fdout;// open(outfile) || dup(p[1])
	int		here_doc;
	char	*cmd;
	char	**args;
	char	**envp;
}	t_pipex;

#endif