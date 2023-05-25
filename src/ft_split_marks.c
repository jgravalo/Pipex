/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_marks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:29:05 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/25 13:36:09 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

int	words(const char *s, char c)
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

char	*mark_str(char const *s, char c, int *n)
{
	char	*new;
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
	while (*s && !(*s == c && *(s - 1) != '\\') && ++i)
		s++;
	new = ft_substr(s - i, 0, i);
	*n = i;
	return (new);
}

//int	ft_split_marks(char const *s, char c, int *j, char **res)
const char	*ft_split_marks(char const *s, char c, int *j, char **res)
{
	int		i;
	int		tmp;

	tmp = 0;
	i = 0;
	if (*s != c)
	{
		if (*s == '\"' && *(s - 1) != '\\' && ++s && ++tmp)
		{
			res[*j++] = mark_str(s, '\"', &i);
			s += i + 1;
		}
		else if (*s == '\'' && *(s - 1) != '\\' && ++s && ++tmp)
		{
			res[*j++] = mark_str(s, '\'', &i);
			s += i + 1;
		}
		else
			while (*s && *s != c && ++i)
				s++;
		if (tmp == 0)
		{
			res[*j++] = ft_substr(s - i, 0, i);
//			return (i);
		}
	}
//	return (i + 1);
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		j;
	int		i;
	int		tmp;

	j = 0;
	res = (char **) malloc((words(s, c) * (sizeof(char *))) + 8);
	if (!res || !s)
		return (0);
	while (*s)
	{
//		s = ft_split_marks(s, c, &j, res) + 1;
		//
		if (*s != c)
		{
			tmp = 0;
			i = 0;
			if (*s == '\"' && *(s - 1) != '\\' && ++s && ++tmp)
			{
				res[j++] = mark_str(s, '\"', &i);
				s += i + 1;
			}
			else if (*s == '\'' && *(s - 1) != '\\' && ++s && ++tmp)
			{
				res[j++] = mark_str(s, '\'', &i);
				s += i + 1;
			}
			while (*s && *s != c && ++i)
				s++;
			if (tmp == 0)
				res[j++] = ft_substr(s - i, 0, i);
		}
		//
		else
			++s;
	}
	res[j] = NULL;
	return (res);
}
