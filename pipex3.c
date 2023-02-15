/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:13:06 by jgravalo          #+#    #+#             */
/*   Updated: 2023/02/13 12:50:18 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

int main(int argc, char **argv, char **envp)
{
	char	**command;
	char	**src;
	char	*dst;
	int		fd;
	int		i;
	
	if (argc < 5 || !argv)
		return (0);
	command = (char **)malloc(((argc - 3) * sizeof(char)) + 8);
	i = 2;
	src = (char **)malloc(sizeof(char *) * 3);
	src[0] = argv[0];
	src[1] = argv[1];
//	src[2] = ft_strjoin(">", argv[argc - 1]);
//	src[2] = ft_strjoin(src[2], ".output");
	src[2] = NULL;
	while (i < argc - 1)
	{
		command[i - 1] = argv[i];
		i++;
	}
	dst = argv[argc - 1];
	fd = open(dst, O_RDWR);
	i = 0;
	for (i = 1; i < 3; i++)
		pipex(command[i], src, envp, fd);
//	pipex(command, src, envp, fd);

}

int pipex(char *comm, char **file, char **envp, int fd)
{
	pid_t	pid;
	int		a[2];
	int		b[2];
	int		readbytes;
	char	buffer[SIZE];
	int		exec;

	exec = 0;
	pipe(a);
	pipe(b);

	pid = fork();
	if (pid == 0)
	{ // hijo
		close(a[1]); /* cerramos el lado de escritura del pipe */
		close(b[0]); /* cerramos el lado de escritura del pipe */
//	
		write(1, "\n\nestoy en pid==0\n", 18);// BORRAR !!!
		readbytes = read(a[0], buffer, SIZE);
//		printf("readbytes = %d\n", readbytes);// BORRAR !!!
		while (readbytes > 0)
		{
			write(1, buffer, readbytes);
			strcat( buffer, "esto tambien\n");
			write(b[1], buffer, strlen(buffer));
			readbytes = read(a[0], buffer, SIZE);		
//			printf("readbytes = %d\n", readbytes);// BORRAR !!!
		}
		dup2(fd, 1);
		dup2(fd, 2);
//
		close(a[0]);
		close(b[1]);
//		
		exec = exec_comm(comm/*[2]*/, file, envp);
		printf("exec2 = %d\n", exec);// BORRAR !!!
	}
	else
	{ // padre
		close(a[0]); /* cerramos el lado de lectura del pipe */
		close(b[1]); /* cerramos el lado de lectura del pipe */
//		
		write(1, "\n\nestoy en pid==1\n", 18);// BORRAR !!!
		strcpy( buffer, "Esto llega a traves de la tuberia\n" );
		write(a[1], buffer, strlen(buffer));

		close(a[1]);
		close(b[0]);
	}
	waitpid( pid/* fork()*/, NULL, 0 );
	printf("exec = %d\n", exec);// BORRAR !!!
	exit( 0 );
}
