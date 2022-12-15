/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:13:06 by jgravalo          #+#    #+#             */
/*   Updated: 2022/12/15 16:50:35 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

int main(int argc, char **argv, char **envp)
{
	char	**command;
	char	**src;
	char	*dst;
	int		i;
	if (argc < 5 || !argv)
		return (0);
	command = (char **)malloc(((argc - 3) * sizeof(char)) + 8);
	i = 2;
	src = (char **)malloc(sizeof(char *) * 3);
	src[0] = argv[0];
	src[1] = argv[1];
	src[2] = NULL;
	while (i < argc - 1)
	{
		command[i - 1] = argv[i];
		i++;
	}
	dst = argv[argc - 1];
	i = 1;
	for (i = 1; i < 3; i++)
	{
		printf("\nPROCESO \"%d\" \n", i);
		pipex(command[i], src, envp, dst);
		src[1] = dst; 
		//src = makesrc(dst, src[0]);
	}
		
// cambiar src al nuevo

}

//int pipex(char *comm, char **src, char **envp, int fd)
int pipex(char *comm, char **src, char **envp, char *dst)
{
	pid_t	pid;
	int		a[2];
	int		b[2];
	int		readbytes;
	char	buffer[SIZE];
	int		exec;
	int fd;

	exec = 0;
	pipe(a);
	pipe(b);
	fd = 0;
	pid = fork();
	if (pid == 0)
	{ // hijo
		close(a[1]); /* cerramos el lado de escritura del padre */
		close(b[0]); /* cerramos el lado de lectura del hijo */

//		write(1, "\n\nestoy en pid==0\n", 18);// BORRAR !!!
		readbytes = read(a[0], buffer, SIZE);
		while (readbytes > 0)
		{
			write(1, buffer, readbytes);
			readbytes = read(a[0], buffer, SIZE);
		}
		
		close(a[0]);
		
		dup2(b[1], 1);
		dup2(b[1], 2);
		
		close(b[1]);
		
		exec = exec_comm(comm, src, envp);

		if (exec == -1)
			write(1, "exec=error\n", 11);
	}
	else
	{ // padre
		close(a[0]); /* cerramos el lado de lectura del padre */
		close(b[1]); /* cerramos el lado de escritura del hijo */
		
//		write(1, "\n\nestoy en pid==1\n", 18);// BORRAR !!!
		strcpy( buffer, "Soy tu padre hablandote por una tuberia.\n" );
		write(a[1], buffer, strlen(buffer));
		
		close(a[1]);

		readbytes = read(b[0], buffer, SIZE);
		fd = open(dst, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
		while (readbytes > 0)
		{
			write(1, buffer, readbytes);
			write(fd, buffer, readbytes);
			readbytes = read(b[0], buffer, SIZE);
		}
		
		close(b[0]);
	
	}
	waitpid( pid, NULL, 0 );
//	printf("exec = %d\n", exec);// BORRAR !!!
	return (0);
}

char    **makesrc(char *file, char *zero)
{
	char **src;

	src = (char **)malloc(sizeof(char *) * 3);
	src[0] = zero;
	src[1] = file;
	src[2] = NULL;
	return (src);
}

void fzero(int fd)
{
	char buffer;
	while (read(fd, &buffer, 1))
	{
		write(fd, "\0", 1);
	}
}
