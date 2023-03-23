#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define SIZE 512
 
int main(/* int argc, char **argv*/ )
{
	pid_t pid;
	int a[2], b[2], readbytes;
	char buffer[SIZE];
	
	pipe( a );
	pipe( b );

 
	write(1, "estoy fuera del pid\n", 21);
	if ( (pid=fork()) == 0 )
	{ // hijo
		close( a[1] ); /* cerramos el lado de escritura del pipe */
		close( b[0] ); /* cerramos el lado de lectura del pipe */
 
		while( (readbytes=read( a[0], buffer, SIZE ) ) > 0)
			write( 1, buffer, readbytes );
		close( a[0] );

		write(1, "estoy en pid==0\n", 16);
		strcpy( buffer, "Soy tu hijo hablandote por la otra tuberia.\n" );
		write( b[1], buffer, strlen( buffer ) );
		close( b[1] );
	}
	else
	{ // padre
		close( a[0] ); /* cerramos el lado de lectura del pipe */
		close( b[1] ); /* cerramos el lado de escritura del pipe */
 
		write(1, "estoy en pid==1\n", 16);	
		strcpy( buffer, "Soy tu padre hablandote por una tuberia.\n" );
		write( a[1], buffer, strlen( buffer ) );
		close( a[1]);
 
		while( (readbytes=read( b[0], buffer, SIZE )) > 0)
			write( 1, buffer, readbytes );
		close( b[0]);
	}
	waitpid( pid, NULL, 0 );
	exit( 0 );
}
