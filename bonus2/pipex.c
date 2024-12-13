#include"pipex.h"
#include<string.h>

void	ft_strerror(char *file, int i)
{
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, strerror(i), ft_strlen(strerror(i)));
	write(2, "\n", 1);
}

void	error(t_pipex *pipex, char *file, int i)
{
	close(pipex->fdout);
	write(2, "Pipex: ", 7);
	if (i == 1)
		perror(file);
	else if (i == 2)
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

void	child(t_pipex *pipex, int *infile, int *outfile)
{
	(void)pipex;
	dup2(*infile, 0);
	dup2(*outfile, 1);
	// if (execve(pipex->cmd, pipex->args, pipex->envp))
		exit(1);
}

void	do_pipex(t_pipex *pipex, char *arg, int *infile, int *outfile)
{
	pid_t	id;//[argc - 3 - pipex->here_doc];

	pipex->args = ft_split(arg, ' ');
	for (size_t i = 0; pipex->args[i]; i++)
	{
		printf("args[%zu] = %s\n", i, pipex->args[i]);
	}
	id = fork();
	if (id < 0)
		error(pipex, NULL, 2);
	// momento critico, a ver si se copia el fd
	else if (id == 0)
		child(pipex, infile, outfile);
	else
		;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;//[argc - 3];
	int		i;
	int		p1[2];//[argc - 4 - pipex->here_doc][2];
	
	pipe(p1);
	pipex.envp = envp;
	if (argc < 5)
		error(&pipex, argv[argc - 1], 3);
	parse_argv(&pipex, argc, argv);
	i = 0;
	do_pipex(&pipex, argv[2 + pipex.here_doc], &pipex.fdin, &p1[1]);
	i++;
	// while (i < argc - 3)
	// {
	// 	do_pipex(&pipex, argv[i + 2 + pipex.here_doc]);
	// }
	//dup2(p1[1], p2[0]);
	do_pipex(&pipex, argv[argc - 2], &p1[0], &pipex.fdout);
	//waitpid(pipex.pid, NULL, 0);
	return (0);
}