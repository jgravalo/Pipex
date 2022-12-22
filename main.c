/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:13:06 by jgravalo          #+#    #+#             */
/*   Updated: 2022/12/16 16:57:08 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

int	search_comm(char *comm, char *arg)
{
	int i;

	i = 0;
	while (comm[i] && comm[i] == arg[i])
		i++;
	if (!arg[i])
//	if (comm[i] || arg[i])
		return(1);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char	**command;
	char	**src;
	char	*dst;
	int		i;
	if (argc < 5 || !argv)
		return (0);
	src = makesrc(argv);
	command = make_commands(argc, argv);
	dst = argv[argc - 1];
	i = 1;

	for (i = 1; i < 3; i++)
	{
		printf("\nPROCESO \"%d\" \n", i);
		pipex(command[i], src, envp, dst, i);
//		pipex(command[i], src, envp, dst);
		src[1] = dst; 
	}

	/*
	//int fd = 
//	open(NULL, O_CREAT | O_RDWR, S_IRUSR
//			| S_IWUSR | S_IRGRP | S_IROTH);
	i = 2;
	while (i < 3)
	{
		pipex(command[i], src, envp, NULL, i);
		i++;
		if (search_comm("wc", command[i]) == 1 || search_comm("cat", command[i]) == 1)
			src[1] = dst;
		else
			src[1] = NULL; 
		pipex(command[i], src, envp, dst, i);
		i++;
	}*/
}
