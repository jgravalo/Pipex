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
	printf("argv 1 = %s\n", argv[1]);
	if (/* ft_ */!strcmp(argv[1], " here\\_doc"))
		printf("en here_doc\n");
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
	t_pipex	pipex;

	if (argc < 5)
	{
		write(2, "Pipex: too few arguments\n", 25);
		return (1);
	}
	parse_argv(&pipex, argc, argv);
	(void)envp;
	return (0);
}