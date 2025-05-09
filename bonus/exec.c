/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:43:20 by jgravalo          #+#    #+#             */
/*   Updated: 2025/03/16 19:43:22 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	exec(t_pipex *pipex)
{
	pipex->args = ft_split(pipex->argv[pipex->i + 2 + pipex->here_doc], ' ');
	get_paths(pipex);
	get_cmd(pipex);
	ft_free_m(pipex->paths);
	closes(pipex);
	if (execve(pipex->cmd, pipex->args, pipex->envp))
	{
		error(pipex->cmd, 1, 0);
		free(pipex->cmd);
		ft_free_m(pipex->args);
		exit(1);
	}
}

void	get_cmd(t_pipex *pipex)
{
	int	j;

	j = 0;
	if (pipex->args[0][0] == '/')
		pipex->cmd = ft_substr(pipex->args[0], 0, ft_strlen(pipex->args[0]));
	else
	{
		while (pipex->paths[j])
		{
			pipex->join = ft_strjoin(pipex->paths[j], "/");
			pipex->cmd = ft_strjoin(pipex->join, pipex->args[0]);
			free(pipex->join);
			if (!access(pipex->cmd, F_OK))
				break ;
			if (!pipex->paths[j + 1])
			{
				ft_strerror(pipex->args[0], "command not found");
				exit(1);
			}
			j++;
		}
	}
}

void	get_paths(t_pipex *pipex)
{
	int		i;
	char	*substr;

	i = 0;
	while (pipex->envp[i])
	{
		substr = ft_substr(pipex->envp[i], 0, 5);
		if (!ft_strcmp(substr, "PATH="))
		{
			free(substr);
			substr = ft_substr(pipex->envp[i], 5,
					ft_strlen(pipex->envp[i]) - 5);
			pipex->paths = ft_split(substr, ':');
			free(substr);
			return ;
		}
		free(substr);
		i++;
	}
}
