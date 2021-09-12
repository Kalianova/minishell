#include "minishell.h"

int	count_len(char *param, int len)
{
	char	c;

	if (param[len] == '\'' || param[len] == '\"')
	{
		c = param[len];
		len++;
		while (param[len] && param[len] != c)
			++len;
	}
	if (param[len])
		++len;
	return (len);
}

void	del_quotes_add(char **param, int flag, int j)
{
	char	*tmp;

	if (flag)
	{
		free(*param);
		*param = NULL;
		return ;
	}
	tmp = ft_substr(*param, 0, j);
	free(*param);
	*param = tmp;
}

char	**copy_arr(char **params, char *name)
{
	int		i;
	char	**result;

	i = 0;
	while (params[i] != NULL)
		++i;
	result = (char **)malloc(sizeof(char *) * (i + 2));
	while (i >= 0)
	{
		if (params[i] == NULL)
			result[i + 1] = NULL;
		else
			result[i + 1] = ft_strdup(params[i]);
		--i;
	}
	result[0] = ft_strdup(name);
	return (result);
}
