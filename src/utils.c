/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:29:05 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/13 17:02:42 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

size_t	ft_strlen(const char *str)
{
	unsigned long	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	while (s1[i])
	{	
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{	
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s2;
	unsigned long	j;

	if (!s)
		return (0);
	j = 0;
	if (start > ft_strlen(s))
	{
		s2 = malloc(sizeof(char));
		s2[0] = '\0';
		return (s2);
	}
	if (ft_strlen(s) - start < len)
		s2 = malloc(sizeof(char) * ft_strlen(s) - start + 1);
	else
		s2 = malloc(len + 1);
	if (!s2)
		return (0);
	while (j < len && s[start + j] != '\0')
	{
		s2[j] = s[start + j];
		j++;
	}
	s2[j] = '\0';
	return (s2);
}

int		words(const char *s, char c)
{
	int	j;

	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
			{
				s++;
			}
			j++;
		}
		else
			++s;
	}
	return (j);
}
/*char    **make_args_marks(char **args){
	int     i;
	int     j;
	while (args[i])
	{
		j = 0;
		if (argv[i][0] == "\'" || argv[i][0] == "\"")
			while (argv[i][0] == "\'" || argv[i][0] == "\"")
			{
				i++;
			}
	}
	return (0);}*/
#include<stdlib.h>
/*
char	*make_str(char c)
{
	int i;

	i = 0;
	while (*s && *s != c && ++i)
		s++;
	res[j++] = ft_substr(s - i, 0, i);
}
*/

char *mark_str(char const *s, char c, int *n)
{
	char *new;
	int i;
	int tmp;

	i = 0;
	tmp = 0;
/*
	if (*s == '\'')// && ++s)
		s++;
	{
		new = mark_str(s, '\'', n);
		n++;
//		s += n + 1;
//		tmp++;
		return (new);
	}
	if (*s == '\"')// && ++s)
		s++;
	{
		new = mark_str(s, '\"', n);
		n++;
//		s += n + 1;
//		tmp++;
		return (new);
	}
*/	
	while (*s &&/* *s != c*/ !(*s == c && *(s - 1) != '\\') && ++i)
		s++;
	new = ft_substr(s - i, 0, i);
	*n = i;
//	printf("new_quotes: |%s|\n", new);
	return (new);
}

char	**ft_split(char const *s, char c)
{
	int		tmp;
	int		i;
	int		j;
	char	**res;

	tmp = 0;
	i = 0;
	j = 0;
	res = (char **) malloc((words(s, c) * (sizeof(char *))) + 8);
	if (!res || !s)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			if (*s == '\"' && *(s - 1) != '\\' && ++s)
			{
				res[j++] = mark_str(s, '\"', &i);
				s += i + 1;
				tmp++;
			}
			else if (*s == '\'' && *(s - 1) != '\\' && ++s)
			{
				res[j++] = mark_str(s, '\'', &i);
				s += i + 1;
				tmp++;
			}
			i = 0;
			while (*s && *s != c && ++i)
				s++;
			if (tmp == 0)
				res[j++] = ft_substr(s - i, 0, i);
		}
		else
			++s;
	}
	res[j] = NULL;
//	res[0] = "pipex\0";
/*	for (i = 0; res[i]; i++)
	{
		write(10 , "res = |", 7);
		write(10 , res[i], ft_strlen(res[i]));
		write(10 , "|\n", 2);
	}
	for (i = 0; res[i]; i++) printf("res[%d] = |%s|\n", i, res[i]);
*/	return (res);
}
