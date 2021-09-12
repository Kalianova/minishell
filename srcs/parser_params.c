#include "minishell.h"

int	count_params(char *param)
{
	int	count;

	count = 0;
	while (*param)
	{
		if (param[0] == '\'')
		{
			++param;
			while (*param && param[0] != '\'')
				param++;
			if (*param)
				param++;
			count++;
		}
		else
		{
			while (*param && param[0] != '\'')
				param++;
			count++;
		}
	}
	return (count);
}

char	*parser_params(char *param, t_map *envp, int code)
{
	int		count;
	int		i;
	char	**res;
	int		len;

	count = count_params(param);
	res = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		len = 0;
		if (param[len] == '\'')
			len++;
		while (param[len] && param[len] != '\'')
			len++;
		if (param[len] && param[0] == '\'')
			len++;
		res[i] = ft_substr(param, 0, len);
		if (param[0] != '\'')
			parser_dollar(&res[i], envp, code);
		param += len;
		i++;
	}
	res[count] = NULL;
	return (join_strings(&res));
}

int	count_params_arr(char *param)
{
	char	c;
	int		count;

	count = 0;
	while (*param)
	{
		count++;
		while (*param && *param != ' ')
		{
			if (*param == '\'' || *param == '\"')
			{
				c = *param;
				++param;
				while (*param && *param != c)
					++param;
			}
			if (*param)
				param++;
		}
		while (*param && *param == ' ')
			++param;
	}
	return (count);
}

void	del_quotes(char **param, int flag)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*param)[i])
	{
		if ((*param)[i] == '\'' || (*param)[i] == '\"')
		{
			c = (*param)[i];
			++i;
			while ((*param)[i] && (*param)[i] != c)
				(*param)[++j - 1] = (*param)[++i - 1];
			if ((*param)[i])
				i++;
		}
		else
			(*param)[++j - 1] = (*param)[++i - 1];
	}
	del_quotes_add(param, flag, j);
}

char	**parser_params_arr(char *param)
{
	int		count;
	int		i;
	char	**res;
	int		len;
	int		flag;

	i = -1;
	flag = 0;
	count = count_params_arr(param);
	res = (char **)malloc(sizeof(char *) * (count + 1));
	while (++i < count)
	{
		len = 0;
		while (*param && *param == ' ')
			++param;
		while (param[len] && param[len] != ' ')
			len = count_len(param, len);
		res[i] = ft_substr(param, 0, len);
		if (check_redir(res, i))
			flag = 1;
		del_quotes(&res[i], flag);
		param += len;
	}
	res[count] = NULL;
	return (res);
}
