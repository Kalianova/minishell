#include "minishell.h"

int ft_export(const char *params)
{
	printf("Help me, i am empty :c -> cd %s\n", params);
	return (0);
}

int ft_unset(const char *params)
{
	printf("Help me, i am empty :c -> cd %s\n", params);
	return (0);
}

int ft_env(const char *params, t_map *envp)
{
	if (envp == NULL)
		return (-1);
	if (params && params[0] == '-')
	{
		printf("env: invalid option -- '%c'\n", params[1]);
		return (0);
	}
	if (params)
	{
		printf("env: invalid arguments -- '%s'\n", params);
		return (0);
	}
	while (envp->prev)
	{
		printf("%s=%s\n", envp->key, envp->value);
		envp = envp->prev;
	}
	printf("%s=%s\n", envp->key, envp->value);
	return (0);
}