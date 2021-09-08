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