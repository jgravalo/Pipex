#include"pipex.h"

int main()
{
	char buffer[SIZE];
	int fd = open("hello.txt", O_RDWR);
	int readbytes = read(fd, buffer, SIZE);
	printf("readbytes = %d\n", readbytes);
	printf("buffer = %s\n", buffer);
	return (0);
}
