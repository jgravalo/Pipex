/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:13:06 by jgravalo          #+#    #+#             */
/*   Updated: 2022/12/15 17:15:52 by jgravalo         ###   ########.fr       */
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
	command = (char **)malloc(((argc - 3) * sizeof(char)) + 8);
	i = 2;
	src = (char **)malloc(sizeof(char *) * 3);
	src[0] = argv[0];
	src[1] = argv[1];
	src[2] = NULL;
	while (i < argc - 1)
	{
		command[i - 1] = argv[i];
		i++;
	}
	dst = argv[argc - 1];
	i = 1;
	for (i = 1; i < 3; i++)
	{
		printf("\nPROCESO \"%d\" \n", i);
		pipex(command[i], src, envp, dst);
		src[1] = dst; 
		//src = makesrc(dst, src[0]);
	}
}
