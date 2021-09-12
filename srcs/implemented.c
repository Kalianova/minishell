#include "minishell.h"

int	ft_cd(char **params)
{
	int	res;

	if (params[0] == NULL)
		return (0);
	res = chdir(params[0]);
	if (params[0] && params[0][0] == '-' && params[0][1])
	{
		printf("minishell: cd: -%c: invalid option\n", params[0][1]);
		printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
	}
	else if (params[0] && params[1])
		printf("minishell: cd: too many arguments\n");
	else if (res < 0)
		printf("minishell: cd: %s: No such file or directory\n", params[0]);
	return (res);
}

int	ft_echo(char **params)
{
	int	i;
	int	flag;

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
	{
		printf("%s", params[i]);
		while (params[++i])
			printf(" %s", params[i]);
	}
	if (!flag)
		printf("\n");
	return (0);
}

int	ft_pwd(char **params)
{
	char	*res;

	if (params[0] && params[0][0] == '-' && params[0][1])
	{
		printf("minishell: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n",
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
	int	res;
	int	i;

	i = -1;
	res = 0;
	printf("exit\n");
	if (params)
	{
		if (params[0])
			res = ft_atoi(params[0]);
		while (params[0] && params[0][++i])
		{
			if (!ft_isdigit(params[0][i]))
			{
				printf("minishell: exit: %s: numeric argument required\n",
					params[0]);
				res = 2;
				break ;
			}
		}
		free_strings(params);
	}
	ft_mapdelall(envp);
	return (res);
}
