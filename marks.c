#include<stdio.h>
#include<stdlib.h>

char    **ft_split(char const *s, char c);

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	char **tmp = ft_split(argv[1], '\"');
	int i;
	for (i = 0; tmp[i]; i++)
		printf("tmp[%d] = <%s>\n", i, tmp[i]);
	return (0);
}
