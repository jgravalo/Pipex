#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	char	*s = "prueba1c.txt";
	int		fd = open(s, O_RDONLY);
	char	*buff = (char *)malloc(4);
	int		readbytes = read(fd, buff, 5);

	if (readbytes == -1)
	{
		printf("no hay archivo");
		return 0;
	}
	if (readbytes == 0)
	{
		printf("fallo");
		return 0;
	}
	printf("buff = %s", buff);
	return 0;
}
