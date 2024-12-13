#include"pipex.h"
#include<string.h>

void	ft_strerror(char *file, int i)
{
	write(2, file, /* ft_ */strlen(file));
	write(2, ": ", 2);
	write(2, strerror(i), /* ft_ */strlen(strerror(i)));
	write(2, "\n", 1);
}

void	error(t_pipex *pipex, char *file, int i)
{
	close(pipex->fdout);
	write(2, "Pipex: ", 7);
	if (i == 1)
		perror(file);
	else if (i == 2)
		//printf("%s: %s\n", strerror(13), file); // BORRAR
		ft_strerror(file, 13);
	else if (i == 3)
		write(2, "too few arguments\n", 18);
	exit(1);
}

void	parse_argv(t_pipex	*pipex, int argc, char **argv)
{
	char	*c;

	c = malloc(1);
	printf("argv 1 = %s\n", argv[1]);
	pipex->here_doc = 0;
	if (/* ft_ */!strcmp(argv[1], "here_doc"))
	{
		pipex->here_doc = 1;
		if (argc < 6)
			error(pipex, argv[argc - 1], 3);
		/* {
			write(2, "Pipex: too few arguments\n", 25);
			return ;
		} */
		if (!access(argv[argc - 1], F_OK) && access(argv[argc - 1], W_OK))
			error(pipex, argv[argc - 1], 2);
		pipex->fdout = open(argv[argc - 1], O_RDONLY | O_CREAT | O_APPEND);
		//printf("en here_doc\n");
		pipex->fdin = open("/tmp/here_doc", O_RDWR | O_CREAT);
		//printf("argv 2 = <%s>\n", argv[2]);
		//printf("c = <%s>\n", c);
		while (/* ft_ */ strcmp(argv[2], c)) // CONTINUAR !!!!
		{
			printf("aqui\n");
			write(1, c, /* ft_ */strlen(c));
			write(pipex->fdin, c, /* ft_ */strlen(c));
			free(c);
			c = get_next_line(0);
			c[/* ft_ */strlen(c) - 1] = '\0';
			//printf("c = <%s>\n", c);
		}
	}
	else
	{
		if (!access(argv[argc - 1], F_OK) && access(argv[argc - 1], W_OK))
			error(pipex, argv[argc - 1], 2);
		pipex->fdout = open(argv[argc - 1], O_RDONLY | O_CREAT | O_TRUNC);
		if (access(argv[1], F_OK))
			error(pipex, argv[1], 1);
		else if (access(argv[1], R_OK))
			error(pipex, argv[1], 2);
		pipex->fdin = open(argv[1], O_RDONLY);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;//[argc - 3];

	if (argc < 5)
			error(&pipex, argv[argc - 1], 3);
/*	{
		write(2, "Pipex: too few arguments\n", 25);
		return (1);
	} */
	parse_argv(&pipex, argc, argv);
	
	(void)envp;
	return (0);
}