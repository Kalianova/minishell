#include "libft.h"
#include "minishell.h"

void	signal_handler(int code)
{
	printf("--%i", code);
	fflush(stdout);
}

void	error_handler(int code)
{
	printf("minishell: ");
	if (code == 2)
		printf("syntax error near unexpected token\n");
}

void	free_shell(t_shell **sh)
{
	int	i;

	i = 0;
	if (*sh != NULL)
	{
		while (i < (*sh)->count_commands)
		{
			free((*sh)->commands[i].name);
			free((*sh)->commands[i].params);
			++i;
		}
		if ((*sh)->commands)
			free((*sh)->commands);

	}	
}

/*void show_map(t_map *map)
{
	if (!map)
		return ;
	while (map)
	{
		printf("%s %s\n", map->key, map->value);
		map = map->prev;
	}
}*/

t_map *make_map(char **envp)
{
	t_map *map;
	int pos;
	int len;
	int i;

	i = 0;
	map = NULL;
	while (envp[i])
		++i;
	while (i > 0)
	{
		--i;
		len = ft_strlen(envp[i]);
		pos = ft_strchr(envp[i], '=') - envp[i];
		ft_mapadd(&map, ft_substr(envp[i], 0, pos),
		ft_substr(envp[i], pos + 1, len - pos));
	}
	//show_map(map);
	return (map);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_shell		*sh;
	int			err_code;
	t_map		*map;

	if (argc >= 0 && argv != NULL)
		argv = NULL;
	sh = (t_shell *)malloc(sizeof(t_shell));
	sh->last_result = 0;
	if (sh == NULL)
		return (0);
	while (1)
	{
		line = readline("$> ");
		//signal(SIGINT, signal_handler);
		if (line == NULL)
			return (0);
		add_history(line);
		rl_on_new_line();
		err_code = validate_line(line);
		if (err_code != 0)
		{
			error_handler(err_code);
			free(line);
		}
		else
		{
			map = make_map(envp);
			parser(line, map, sh);
			execute_commads(sh, envp, map);
		}
		free_shell(&sh);
	}
	free(sh);
	sh = NULL;
	return (0);
}
