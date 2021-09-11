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
