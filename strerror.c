#include"inc/pipex.h"

int main()
{
	char *str = "command not found";
	//perror(str);
	int i;
	for (i = 0; i < 107; i++)
		printf("hola: [%d]%s\n", i, strerror(i));
	for (i = 0; i < 107; i++)
		if (strerror(i) == str)
			printf("hola: [%d]%s\n", i, strerror(i));
	return (0);
}
