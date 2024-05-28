/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:03:32 by jgravalo          #+#    #+#             */
/*   Updated: 2024/05/29 00:16:50 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex1;
	t_pipex	pipex2;
	int		i;
	int		j;
	int		exit;

	i = 0;
	j = 0;
	exit = 0;
	if (argc < 5)
		return (1);
	i = errors(&pipex1, &pipex2, argc, argv);
	if (pipe(pipex2.tube) < 0)
		file_error("Error: ", 32);
	pipex1.pid = fork();
	if (pipex1.pid == 0)
		if (child1(&pipex1, &pipex2, argv, envp) == -1)
			i = 127;
	close(pipex1.tube[0]);
	close(pipex1.tube[1]);
 	
	pid_t	pid_aux[argc - 5];
	while (j < argc - 5)
	{
		printf("aqui\n");
		//pipex1.tube = pipex2.tube;
		dup2(pipex2.tube[0], pipex1.tube[0]);
		dup2(pipex2.tube[1], pipex1.tube[1]);
		dup2(pipex2.fdout, pipex1.fdout);
		if (pipe(pipex2.tube) < 0)
			file_error("Error: ", 32);
		pid_aux[j] = fork();// pipex1.pid 
		if (pid_aux[j] == 0)// pipex1.pid 
			if (childn(&pipex1, &pipex2, argv, envp) == -1)
				i = 127;
		close(pipex1.tube[0]);
		close(pipex1.tube[1]);
	}

	
	pipex2.pid = fork();
	if (pipex2.pid == 0)
		if (child2(&pipex1, &pipex2, argv, envp) == -1)
			i = 127;	
	close(pipex2.tube[0]);
	close(pipex2.tube[1]);
	waitpid(pipex1.pid, NULL, 0);
/* 	
	j = -1;
	while (++j && j < argc - 5)
		waitpid(pid_aux[j], NULL, 0);
	 */
	waitpid(pipex2.pid, &exit, 0);
	exit = WEXITSTATUS(exit);
	return (exit);
}

int	child1(t_pipex *pipex1, t_pipex *pipex2, char **argv, char **envp)
{
	close(pipex2->tube[0]);
	close(pipex1->tube[1]);
	pipex1->args = make_args(argv[2]);
	pipex1->args = make_args_file(pipex1->args, argv[1]);
	pipex1->cmd = file_cmd(pipex1->args[0], envp);
	if (!pipex1->cmd)
	{
		file_error(pipex1->args[0], 3);
		free_child(pipex1);
		exit(-1);
	}
	dup2(1, 10);
	dup2(pipex2->tube[1], 1);
	dup2(pipex1->fdin, 0);
	/* 
	char buffer[10];
	read(0, buffer, 10);
	write(pipex2->tube[1], buffer, 10);
	char buffer2[10];
	read(pipex2->tube[0], buffer2, 10);
	write(2, buffer2, 10);
	 */
	close(pipex2->tube[1]);
	close(pipex1->tube[0]);
	execve(pipex1->cmd, pipex1->args, envp);
	write(2, "aqui\n", 5);
	exit(1);
}

int	childn(t_pipex *pipex1, t_pipex *pipex2, char **argv, char **envp)
{
	close(pipex1->tube[1]);
	close(pipex2->tube[0]);
	pipex1->args = make_args(argv[3]);
	pipex1->cmd = file_cmd(pipex1->args[0], envp);
	if (!pipex1->cmd)
	{
		file_error(pipex1->args[0], 3);
		free_child(pipex1);
		exit(-1);
	}
	dup2(1, 10);
	dup2(pipex1->tube[0], 0);
	dup2(pipex2->tube[1], 1);
	close(pipex1->tube[0]);
	close(pipex2->tube[1]);
	execve(pipex1->cmd, pipex1->args, envp);
	exit(1);
}

int	child2(t_pipex *pipex1, t_pipex *pipex2, char **argv, char **envp)
{
	close(pipex1->tube[1]);
	close(pipex1->tube[0]);
	close(pipex2->tube[1]);
	pipex1->args = make_args(argv[3]);
	pipex1->cmd = file_cmd(pipex1->args[0], envp);
	if (!pipex1->cmd)
	{
		file_error(pipex1->args[0], 3);
		free_child(pipex1);
		exit(-1);
	}
	dup2(1, 10);
	dup2(pipex2->tube[0], 0);
	/* 
	char buffer2[12];
	read(0, buffer2, 12);
	write(pipex2->fdout, buffer2, 12);
	 */
	dup2(pipex2->fdout, 1);
	close(pipex2->tube[0]);
	execve(pipex1->cmd, pipex1->args, envp);
	exit(1);
}

char	**make_args(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	check_marks(args);
	return (args);
}
