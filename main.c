/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:13:06 by jgravalo          #+#    #+#             */
/*   Updated: 2022/12/16 15:31:22 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

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
	/*
	for (i = 1; i < 3; i++)
	{
		printf("\nPROCESO \"%d\" \n", i);
		pipex(command[i], src, envp, dst, i);
//		pipex(command[i], src, envp, dst);
		src[1] = dst; 
	}
	*/
	//int fd = 
	open(NULL, O_CREAT | O_RDWR, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
	pipex(command[i], src, envp, NULL, i);
	src[1] = NULL; 
	pipex(command[i + 1], src, envp, dst, i);
}
