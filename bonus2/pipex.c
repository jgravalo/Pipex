#include"pipex.h"
#include<string.h>

void error(char *file, int i)
{
	write(2, "Pipex: ", 7);
	if (i == 1)
		perror(file);
	if (i == 2)
		printf("%s: %s\n", strerror(13), file); // BORRAR
	exit(1);
}

void parse_argv(t_pipex	*pipex, int argc, char **argv)
{
	char	*c;

	c = malloc(1);
	printf("argv 1 = %s\n", argv[1]);
	if (/* ft_ */!strcmp(argv[1], "here_doc"))
	{
		if (argc < 6)
		{
			write(2, "Pipex: too few arguments\n", 25);
			return ;
		}
		printf("en here_doc\n");
		pipex->fdin = open("/tmp/here_doc", O_RDWR | O_CREAT);
		printf("argv 2 = <%s>\n", argv[2]);
		printf("c = <%s>\n", c);
		

		while (/* ft_ */ strcmp(argv[2], c)) // CONTINUAR !!!!
		{
			printf("aqui\n");
			write(pipex->fdin, c, /* ft_ */strlen(c));
			free(c);
			c = get_next_line(0);
			c[/* ft_ */strlen(c) - 1] = '\0';
			printf("c = <%s>\n", c);
		}
		if (!access(argv[argc - 1], F_OK) && access(argv[argc - 1], W_OK))
			error(argv[argc - 1], 2);
		pipex->fdout = open(argv[argc - 1], O_RDONLY | O_CREAT | O_APPEND);
	}
	else
	{
		if (access(argv[1], F_OK))
			error(argv[1], 1);
		else if (access(argv[1], R_OK))
			error(argv[1], 2);
		pipex->fdin = open(argv[1], O_RDONLY);
		if (!access(argv[argc - 1], F_OK) && access(argv[argc - 1], W_OK))
			error(argv[argc - 1], 2);
		pipex->fdout = open(argv[argc - 1], O_RDONLY | O_CREAT | O_TRUNC);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;//[argc - 3];

	if (argc < 5)
	{
		write(2, "Pipex: too few arguments\n", 25);
		return (1);
	}
	parse_argv(&pipex, argc, argv);
	(void)envp;
	return (0);
}