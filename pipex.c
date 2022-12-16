/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:13:06 by jgravalo          #+#    #+#             */
/*   Updated: 2022/12/16 15:05:27 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 


//int pipex(char *comm, char **src, char **envp, char *dst)
int pipex(char *comm, char **src, char **envp, char *dst, int n)
{
	pid_t	pid;
	int		a[2];
	int		b[2];

	pipe(a);
	pipe(b);
	pid = fork();
	if (pid == 0)
	{ // hijo
		child(a, b, comm, src, envp);
	}
	else
	{ // padre
		father(a, b, dst, n);
//		father(a, b, dst);
	}
	waitpid( pid, NULL, 0 );
	return (0);
}

void	child(int a[], int b[], char *comm, char **src, char **envp)
{
	int exec;

	close(a[1]); /* cerramos el lado de escritura del padre */
	close(b[0]); /* cerramos el lado de lectura del hijo */
//	write(1, "\n\nestoy en pid==0\n", 18);// BORRAR !!!
	close(a[0]);
	dup2(b[1], 1);
//	dup2(b[1], 2);
	close(b[1]);
//	unlink(src[1]);
	exec = exec_comm(comm, src, envp);
	if (exec == -1)
		write(1, "exec=error\n", 11);
}
/*
char	free_name(char buffer[], char *file)
{
	char new[SIZE];
	int i;
	i = 0;
	while (new[i])
	{
		new[i] = buffer[i];
		i++;
	}
//	new[]
	return (new);
}
*/
void	father(int a[], int b[], char *dst, int n)
//void	father(int a[], int b[], char *dst)
{
	int		readbytes;
	int		fd;
	char	buffer[SIZE];

	if (n == -1)
	   exit(0);	
	close(a[0]); /* cerramos el lado de lectura del padre */
	close(b[1]); /* cerramos el lado de escritura del hijo */
//	write(1, "\n\nestoy en pid==1\n", 18);// BORRAR !!!
	close(a[1]);
	readbytes = read(b[0], buffer, SIZE);
	fd = open(dst, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR
		| S_IWUSR | S_IRGRP | S_IROTH);
/*	
	if (n == 1)
		unlink(dst);
*/	
	while (readbytes > 0)
	{
/*		
		if (n == 2)
			buffer = free_name(buffer);
*/
		write(1, buffer, readbytes);// BORRAR !!!
		write(fd, buffer, readbytes);
		readbytes = read(b[0], buffer, SIZE);
	}
	close(b[0]);
}

char    **makesrc(char **argv)
{
	char **src;

	src = (char **)malloc(sizeof(char *) * 3);
	src[0] = argv[0];
	src[1] = argv[1];
	src[2] = NULL;
	return (src);
}

char	**make_commands(int argc, char **argv)
{
	char    **command;
	int		i;

	command = (char **)malloc(((argc - 3) * sizeof(char)) + 8);
	i = 2;
	while (i < argc - 1)
	{
		command[i - 1] = argv[i];
		i++;
	}
	return (command);
}
