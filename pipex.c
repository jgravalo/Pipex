/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:13:06 by jgravalo          #+#    #+#             */
/*   Updated: 2022/11/25 15:20:19 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

int main(int argc, char **argv, char **envp)
{
	char	**command;
	char	**src;
//	char	*file1;
	char	*dst;
	int		*fd;
	int		i;
	
	if (argc < 2 || !argv)
		return (0);
	command = (char **)malloc(((argc - 3) * sizeof(char)) + 8);
	i = 2;
	while (i < argc - 1)
	{
		command[i - 1] = argv[i];
//		printf("command[%d] = %s\n", i - 1, command[i - 1]);// BORRAR !!!
		i++;
	}
	src = (char **)malloc(sizeof(char *) * 3);
	fd = (int *)malloc(sizeof(int) * 3);
	src[1] = argv[1];
	dst = argv[argc - 1];
	src[2] = NULL;
//	printf("file1 = %s\nfile2 = %s\n", file[1], file2);// BORRAR !!!
	fd[1] = open(src[1], O_RDWR);
	fd[2] = open(dst, O_RDWR);
	i = 0;
	pipex(command[1], src, envp);
	/*
	while (command[i])
	{
		pipex(command[i], src, envp);
		i++;
	}
	*/
}

int pipex(char *comm, char **file, char **envp)
{
	pid_t	pid;
	int		p[2], readbytes;
	char	buffer[SIZE];

	pipe(p);

	pid = fork();
	if (pid == 0)
	{ // hijo
		close(p[1]); /* cerramos el lado de escritura del pipe */
//	
//		write(1, "estoy en pid==0\n", 16);// BORRAR !!!
		readbytes = read(p[0], buffer, SIZE);
		while(readbytes > 0)
		{
			write( 1, buffer, readbytes );
			readbytes = read(p[0], buffer, SIZE);
		}
//
		close(p[0]);
	}
	else
	{ // padre
		close(p[0]); /* cerramos el lado de lectura del pipe */
//		
//		write(1, "estoy en pid==1\n", 16);// BORRAR !!!
		strcpy( buffer, "Esto llega a traves de la tuberia\n" );
//		buffer = 
		write(p[1], buffer, strlen(buffer));
//		printf("comm = %s file = %s\n", comm, file[1]);// BORRAR !!!
		exec_comm(comm, file, envp);
//		
		close(p[1]);
	}
	waitpid( pid/* fork()*/, NULL, 0 );
	exit( 0 );
}
