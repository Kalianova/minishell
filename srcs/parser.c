#include "minishell.h"

int	count_commands(const char *line)
{
	int	i;
	int	res;

	res = 1;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|')
		{
			if (line[i + 1] == '|')
				++i;
			++res;
		}
		++i;
	}
	return (res);
}

char	**get_cmds(const char *line, t_shell *sh)
{
	char	**cmds;
	int		i;
	char	*tmp;

	i = 0;
	cmds = ft_split(line, '|');
	while (cmds[i] != NULL)
	{
		tmp = ft_strtrim(cmds[i], " ");
		free(cmds[i]);
		cmds[i] = tmp;
		++i;
	}
	sh->count_commands = i;
	return (cmds);
}

void	parser(const char *line, t_map *envp, t_shell *sh)
{
	int		i;
	char	**cmds;
	char	*tmp;
	char	*s;

	cmds = get_cmds(line, sh);
	i = 0;
	sh->commands = (t_ftpair *)malloc(sizeof(t_ftpair)
			* sh->count_commands); // if NULL ?
	while (cmds[i] != NULL)
	{
		sh->commands[i].name = ft_isubstr(cmds[i], 0, len_cmd(cmds[i]), '"');
		tmp = ft_substr(cmds[i], len_cmd(cmds[i]),
				ft_strlen(cmds[i]) - len_cmd(cmds[i]));
		s = ft_strtrim(tmp, " ");
		sh->commands[i].params = parser_params(s ,
				envp, sh->last_result);
		free(s);
		free(tmp);
		sh->commands[i].arr_params = parser_params_arr(sh->commands[i].params);
		++i;
	}
	i = 0;
	while (cmds[i] != NULL)
		free(cmds[++i - 1]);
	free(cmds);
}
