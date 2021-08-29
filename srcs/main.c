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
		free(*sh);
		*sh = NULL;
	}	
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_shell		*sh;
	int			err_code;

	if (argc >= 0 && argv != NULL)
		argv = NULL;
	sh = NULL;
	while (1)
	{
		line = readline("$> ");
		//signal(SIGINT, signal_handler);
		if (line == NULL)
			return (0);
		err_code = validate_line(line);
		if (err_code != 0)
			error_handler(err_code);
		else
		{
			sh = parser(line);
			execute_commads(sh, envp);
		}
		free(line);
		free_shell(&sh);
	}
	return (0);
}
