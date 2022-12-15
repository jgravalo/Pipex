#include"pipex.h"

void	printf_fd(int fd)
{
	char	buffer[SIZE];
	int		readbytes;
	int		i;

	printf("%d\n", fd);
	readbytes = read(fd, buffer, SIZE);
	for (i = 0; buffer[i]; i++)
		printf("%s\n", buffer);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	int fd = open(argv[1], O_WRONLY); 
	printf_fd(fd);
	return (0);
}
