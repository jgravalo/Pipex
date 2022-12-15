#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
 
int main(int argc, char *argv[])
{ 
  /* Variables */
  int fd1,fd2;
  char buffer[1024];
  int numbytes;
 
  /* Comprobamos que se pasan dos argumentos */
  if (argc != 3){
    printf("Uso: %s origen destino\n", argv[0]);
    exit(1);
  }
 
  /* Abrimos los dos archivos */
  fd1 = open(argv[1], O_RDONLY);
  fd2 = open(argv[2], O_WRONLY|O_CREAT/*|O_TRUNC, 0700*/);
 
  /* Bucle de lectura/escritura */
  while ((numbytes = read(fd1, &buffer, sizeof(char))) > 0){
    write(fd2, &buffer, numbytes);
  }
 
  /* Cierre de archivos */
  close(fd1);
  close(fd2);
}
