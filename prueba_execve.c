#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char    **ft_split(char const *s, char c);

char    *ft_substr(char const *s, unsigned int start, size_t len);

size_t  ft_strlen(const char *str);

char    *ft_strjoin(char *s1, char *s2);

char **split_docs(char *path)
{
	char **docs;
	char *dirs;

	dirs = ft_substr(path, 5, ft_strlen(path) - 5);
//	printf("%s", dirs);// BORRAR !!!
	docs = ft_split(dirs, ':');
	free(dirs);
	return (docs);
}

int search_path(char **envp)
{
	char	*path = "PATH";
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (path[j] && envp[i][j] == path[j])
		{
			j++;
		}
//		printf("envp[%d] = (%s)\n", i, envp[i]);// BORRAR !!!
		if (!path[j])
		{
//			printf("path = %d\n", i);// BORRAR !!!
			return (i);
		}
		i++;
	}
	return (-1);
}

char *access_comm(char *comm, char**docs)
{
	char *tmp;
	int i;

	i = 0;
	while (docs[i])
	{
//		printf("docs[%d] = (%s)\n", i, docs[i]);// BORRAR !!!
		tmp = ft_strjoin(docs[i], "/");
		docs[i] = ft_strjoin(tmp, comm);
//		printf("docs[%d] = (%s)\n", i, docs[i]);// BORRAR !!!
		free(tmp);
//		printf("docs[%d] = (%s)\n", i, docs[i]);// BORRAR !!!
//		printf("\n");// BORRAR !!!
		if ((access(docs[i], 0)) != -1)
		{
//			printf( "cmd exists.\n" );
			if ((access(docs[i], 4)) != -1)
			{
//          	printf("File cmd has read permission.\n");// BORRAR !!!
			}
			return (docs[i]);
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
//	int i;

	if (!argc)
		return (0);
	if (!argv)
		return (0);
//	write(1, "empieza el proceso\n", 19);
	/*
	for (i = 0; argv[i]; i++)
		printf("argv[%d] = (%s)\n", i, argv[i]);// BORRAR !!!
//	printf("\n");// BORRAR !!!
	
	for (i = 0; envp[i]; i++)
		printf("envp[%d] = (%s)\n", i, envp[i]);// BORRAR !!!
	printf("\n");// BORRAR !!!
	*/
	int env = search_path(envp);
//	printf("path = %d", env);// BORRAR !!!
	char **docs = split_docs(envp[env]);
//	for (i = 0; docs[i]; i++)
//		printf("docs[%d] = (%s)\n", i, docs[i]);// BORRAR !!!
//	printf("\n");// BORRAR !!!

//	char *cmd = "/bin/echo";
	char *cmd = access_comm(argv[1], docs);
	execve(cmd, argv, envp);
}
/*
void pip()
{	
	char *cmd = "/bin/echo";

	if ((access(cmd, 0)) != -1)
    {
        printf( "cmd exists.\n" );

        // Check for write permission.
        // Assume file is read-only.
        if ((access(cmd, 4)) == -1)
            printf("File cmd does not have read permission.\n");// BORRAR !!!
		else
            printf("File cmd has read permission.\n");// BORRAR !!!
        if ((access(cmd, 2)) == -1)
            printf("File cmd does not have write permission.\n");// BORRAR !!!
		else
            printf("File cmd has write permission.\n");// BORRAR !!!
    }
	else
        printf( "File cmd does not exist.\n" );// BORRAR !!!
//	execve(cmd, argv, envp);
}*/
