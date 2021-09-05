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

int	ft_cd(char **params)
{
	int res;

	res = chdir(params[0]);
	if (params[0] && params[0][0] == '-')
		printf("bash: cd: -%c: invalid option\ncd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n", params[0][1]);
	else if (params[0] && params[1])
		printf("bash: cd: too many arguments\n");
	else if (res < 0)
		printf("bash: cd: %s: No such file or directory\n", params[0]);
	return (res);
}

int	ft_echo(char **params)
{
	int i;
	int flag;

	if (!params)
		return (-1);
	if (*params == NULL)
		return (printf("\n") * 0);
	i = 0;
	flag = 0;
	while (ft_strncmp(params[i], "-n", 3) == 0)
	{
		flag = 1;
		++i;
	} 
	if (params[i])
		printf("%s", params[i]);
	while (params[++i])
		printf(" %s", params[i]);
	if (!flag)
		printf("\n");
	return (0);
}

int	ft_pwd(char **params)
{
	char	*res;

	if (params[0] && params[0][0]== '-')
	{
		printf("bash: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n",
			params[0][1]);
		return (0);
	}
	res = getcwd(NULL, 0);
	printf("%s\n", res);
	if (res == NULL)
		return (-1);
	free(res);
	return (0);
}

int	ft_exit(char **params, t_map **envp)
{
	ft_mapdelall(envp);
	//free(params);
	printf("Help me, i am empty :c -> exit %s\n", params[0]);
	return (0);
}
