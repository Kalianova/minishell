#include "libft.h"
#include "minishell.h"
#include <termios.h>
void	error_handler(int code)
{
	printf("minishell: ");
	if (code == 2)
		printf("syntax error near unexpected token\n");
}

void	free_shell(t_shell *sh)
{
	int	i;

	i = 0;
	if (sh != NULL)
	{
		while (i < sh->count_commands)
		{
			ft_free_words(sh->commands[i].arr_params);
			free(sh->commands[i].name);
			free(sh->commands[i].params);
			++i;
		}
		if (sh->commands)
			free(sh->commands);
	}	
}

t_map	*make_map(char **envp)
{
	t_map	*map;
	int		pos;
	int		len;
	int		i;

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
			ft_substr(envp[i], pos + 1, len - pos - 1));
	}
	return (map);
}

void	main_loop(t_shell sh, t_map *map, int err_code)
{
	char	*line;

	while (1)
	{
		my_signals(0);
		line = readline("$> ");
		if (line == NULL)
		{
			exit(0);
			continue ;
		}
		add_history(line);
		rl_on_new_line();
		err_code = validate_line(line);
		if (err_code != 0)
			error_handler(err_code);
		else
		{
			parser(line, map, &sh);
			my_signals(1);
			execute_commads(&sh, &map);
			free_shell(&sh);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell			sh;
	int				err_code;
	t_map			*map;
	struct termios	termios_p;

	err_code = 0;
	if (argc >= 0 && argv != NULL)
		argv = NULL;
	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_p);
	sh.last_result = 0;
	map = make_map(envp);
	main_loop(sh, map, err_code);
	return (0);
}
