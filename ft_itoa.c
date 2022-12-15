#include"pipex.h"

int		count_cifras(int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		i = 1;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char *c;
	int i;
	int len;

	len = count_cifras(n);
	printf("len = %d\n", len);
	c = (char *)malloc(sizeof(char) * (len + 1)); 
	i = 0;
	if (n < 0)
	{
		i = 1;
		c[0] = '-';
		n *= -1;
	}
	while (i <= len - 1)
	{
		c[len - 1] = n % 10 + 48;
		n /= 10;
		len--;
//		printf("%c = %d\n", c[len - 1]);
	}
	return (c);
}
/*
int main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	printf("n = %d\n", n);
	printf("c = %s\n", ft_itoa(n));
	return 0;
}*/
