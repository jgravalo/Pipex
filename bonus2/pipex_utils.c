#include"pipex.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
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

static int	words2(char *s, char c)
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

char	**ft_split(char *s, char c)
{
	int		size;
	int		j;
	char	**res;

	size = 0;
	j = 0;
	res = (char **) malloc((words2(s, c) * (sizeof(char *))) + 8);
	if (!res || !s)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			size = 0;
			while (*s && *s != c && ++size)
				s++;
			res[j++] = ft_substr(s - size, 0, size);
		}
		else
			++s;
	}
	res[j] = NULL;
	return (res);
}