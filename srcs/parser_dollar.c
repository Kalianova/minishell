#include "minishell.h"

char	*join_strings(char ***strs)
{
	int		i;
	int		sum;
	char	*res;

	i = 0;
	sum = 0;
	while ((*strs)[i])
	{
		sum += ft_strlen((*strs)[i]);
		++i;
	}
	res = (char *)malloc(sizeof(char) * sum + 1);
	i = 0;
	sum = 0;
	while ((*strs)[i])
	{
		ft_strlcpy(res + sum, (*strs)[i], ft_strlen((*strs)[i]) + 1);
		sum += ft_strlen((*strs)[i]);
		free((*strs)[i]);
		++i;
	}
	free(*strs);
	res[sum] = '\0';
	return (res);
}

void	new_param(char **param, t_map *envp, int code)
{
	int		len;
	char	*part_of_param;
	t_map	*res;

	len = ft_strlen(*param);
	if (ft_strncmp(*param, "$?", 3) == 0)
	{
		free(*param);
		*param = ft_itoa(code);
		return ;
	}
	part_of_param = ft_substr(*param, 1, len - 1);
	res = ft_mapfind(&envp, part_of_param);
	if (res)
	{
		free(part_of_param);
		free(*param);
		*param = ft_strdup(res->value);
		return ;
	}
	free(part_of_param);
	free(*param);
	*param = (char *)malloc(sizeof(char) * 1);
	(*param)[0] = '\0';
}

void	count_param(char *param, int *count)
{
	int	i;

	i = 0;
	*count = 0;
	if (param[i] && (param[i] != '$'
			|| !(ft_isalnum(param[i + 1]) || param[i + 1] == '?')))
		*count = 1;
	while (param[i])
	{
		if (param[i] == '$' && (ft_isalnum(param[i + 1])
				|| param[i + 1] == '?'))
		{
			++i;
			if (param[i + 1] == '?')
				++i;
			else
				while (param[i] && ft_isalnum(param[i]))
					++i;
			if (param[i] && !(param[i] == '$' && ft_isalnum(param[i + 1])))
				(*count)++;
			(*count)++;
		}
		else
			++i;
	}
}

int	find_end_elem(char *param)
{
	int	i;

	i = 1;
	if (param[0] == '$' && param[1] == '?')
		return (2);
	if (param[0] == '$' && ft_isalnum(param[1]))
	{
		while (ft_isalnum(param[i]))
			i++;
	}
	else
	{
		while (param[i] && !(param[i] == '$'
				&& (ft_isalnum(param[i + 1]) || param[i + 1] == '?')))
			i++;
	}
	return (i);
}

void	parser_dollar(char **param, t_map *envp, int code)
{
	int		i;
	int		len;
	int		end_elem;
	char	*first_param;
	char	**res;

	i = 0;
	first_param = *param;
	count_param(*param, &len);
	res = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		end_elem = find_end_elem(*param);
		res[i] = ft_substr(*param, 0, end_elem);
		if ((*param)[0] == '$' && (ft_isalnum((*param)[1])
				|| (*param)[1] == '?'))
			new_param(&(res[i]), envp, code);
		*param += end_elem;
		++i;
	}
	res[len] = NULL;
	free(first_param);
	*param = join_strings(&res);
}
