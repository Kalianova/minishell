#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

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

typedef struct s_cmd
{
	char		*name;
	char		*path;
	char		*params[3];
}				t_cmd;

int				validate_line(const char *line);

t_shell			*parser(const char *line);

int				execute_commads(t_shell *sh, char **envp);

/* pipe.c */

pid_t			execute_cmd(t_cmd cmd, int fd_in, int fd_out);

t_cmd			parser_cmd(t_shell *sh, int i, char **envp);

void			free_cmd(t_cmd cmd);

char			*get_path(char *cmd_name, char **envp);

/* pipex_utils.c */

int				len_cmd(const char *command);

void			free_strings(char **strs);

void			free_cmd(t_cmd cmd);

/* redirections.c */

int				redirected(char *params, int io);

#endif