#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define SIZE 512
 
int main(/*int argc, char **argv*/)
{
	pid_t pid;
	int		p[2], readbytes;
	char	buffer[SIZE];

	pipe(p);

	pid = fork();
	if (pid/*=fork()*/ == 0)
	{ // hijo
		close(p[1]); /* cerramos el lado de escritura del pipe */
		
		write(1, "estoy en pid==0\n", 16);
		while((readbytes=read( p[0], buffer, SIZE )) > 0)
		{
//			readbytes = read(p[0], buffer, SIZE);
			write( 1, buffer, readbytes );
		}

		close(p[0]);
	}
	else
	{ // padre
		close(p[0]); /* cerramos el lado de lectura del pipe */
		
		write(1, "estoy en pid==1\n", 16);
		strcpy( buffer, "Esto llega a traves de la tuberia\n" );
		write(p[1], buffer, strlen(buffer));
		
		close(p[1]);
	}
	waitpid( /*pid*/ fork(), NULL, 0 );
	exit( 0 );
}
