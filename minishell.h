#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_ftpair
{
	char		*name;
	char		*params;
}				t_ftpair;

typedef struct s_shell
{
	t_ftpair	*commands;
	int			count_commands;
	int			last_result;
}				t_shell;

int				validate_line(const char *line);

t_shell			*parser(const char *line);

#endif