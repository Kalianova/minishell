#include "minishell.h"

int validation(char *param)
{
	int res;

	res = 1;
	if (!ft_isalnum(param[0]) || ft_isdigit(param[0]))
		res = 0;
	while (*param)
	{
		if (!(ft_isalnum(param[0])))
			res = 0;
		param++;
	}
	return (res);
}

int ft_export(char **params, t_map **envp)
{
	t_map *map;

	map = *envp;
	if (params[0] == NULL)
		while (map)
		{
			printf("declare -x %s=\"%s\"\n", map->key, map->value);
			map = map->prev;
		}
	else if (params[0][0] == '-' && params[0][1])
	{
		printf("export: %c: invalid option'\n", params[0][1]);
		return (0);
	}
	return (0);
}

int ft_unset(char **params, t_map **envp)
{
	if (params[0] && params[0][0] == '-' && params[0][1])
		printf("bash: unset: -%c: invalid option\nunset: usage: unset [-f] [-v] [-n] [name ...]\n", params[0][1]);
	else
	{
		while (*params)
		{
			if (!validation(*params))
				printf("bash: unset: `%s': not a valid identifier\n", *params);
			else
				ft_mapdel(envp, *params);
			++params;
		}
	}
	return (0);
}

int ft_env(char **params, t_map **map)
{
	t_map *envp;

	envp = *map;
	if (envp == NULL)
		return (-1);
	if (params[0] && params[0][0] == '-')
	{
		if (params[0][1])
			printf("env: invalid option -- '%c'\n", params[0][1]);
		return (0);
	}
	if (params[0])
	{
		printf("env: invalid arguments -- '%s'\n", params[0]);
		return (0);
	}
	while (envp->prev)
	{
		if (envp->value != NULL)
			printf("%s=%s\n", envp->key, envp->value);
		envp = envp->prev;
	}
	printf("%s=%s\n", envp->key, envp->value);
	return (0);
}
