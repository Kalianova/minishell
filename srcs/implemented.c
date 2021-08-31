#include "minishell.h"

void	ft_clean(char ***arr)
{
	int	i;

	i = 0;
	if ((*arr) == NULL)
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
}

int	ft_cd(const char *params)
{
	chdir(params);
	return (0);
}

int	ft_echo(const char *params)
{
	char	**splited;
	int		i;
	int		flag;

	if (params == NULL)
		return (printf("\n") * 0);
	splited = ft_split(params, ' ');
	i = 0;
	flag = 0;
	if (!splited)
		return (-1);
	while (ft_strncmp(splited[i], "-n", 3) == 0)
	{
		flag = 1;
		++i;
	}
	if (splited[i])
		printf("%s", splited[i]);
	while (splited[++i])
		printf(" %s", splited[i]);
	ft_clean(&splited);
	if (!flag)
		printf("\n");
	return (0);
}

int	ft_pwd(const char *params)
{
	char	*res;

	if (params && params[0] == '-')
	{
		printf("bash: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n",
			params[1]);
		return (0);
	}
	res = getcwd(NULL, 0);
	printf("%s\n", res);
	if (res == NULL)
		return (-1);
	free(res);
	return (0);
}

int	ft_exit(const char *params)
{
	printf("Help me, i am empty :c -> exit %s\n", params);
	return (0);
}
