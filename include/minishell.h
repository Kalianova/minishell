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
	char		**arr_params;
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
	char		**arr_params;
}				t_cmd;

typedef struct s_map
{
	struct s_map	*next;
	struct s_map	*prev;
	char			*key;
	char			*value;
}				t_map;

int				validate_line(const char *line);

void			parser(const char *line, t_map *envp, t_shell *sh);

int				execute_commads(t_shell *sh, char **envp, t_map **map);

/* pipe.c */

pid_t			execute_cmd(t_cmd *cmd, int fd_in, int fd_out, t_map **envp);

t_cmd			parser_cmd(t_shell *sh, int i, char **envp);

void			free_cmd(t_cmd cmd);

char			*get_path(char *cmd_name, char **envp);

/* pipex_utils.c */

int				len_cmd(const char *command);

void			free_strings(char **strs);

void			free_cmd(t_cmd cmd);

/* redirections.c */

int				redirected(char *params, int io);

/* implemented_utils.c */

int				is_implemented(char *cmd_name);

int				my_exec(char *cmd, char **params, t_map **map);

/* implemented.c */

int				ft_cd(char **params);

int				ft_echo(char **params);

int				ft_pwd(char **params);

int				ft_exit(char **params, t_map **map);

/* implemented_2.c */

int				ft_export(char **params, t_map **envp);

int				ft_unset(char **params, t_map **envp);

int				ft_env(char **params, t_map **envp);

/* parser_dollar.c */

void			parser_dollar(char **param, t_map *envp, int code);

char			*join_strings(char ***strs);

/* parser_params.c */

char			*parser_params(char *param, t_map *envp, int code);

char			**parser_params_arr(char *param);

/* map.c */

void			ft_mapadd(t_map **map, char *key, char *value);

void			ft_mapdel(t_map **map, char *key);

int				ft_mapreplace(t_map **map, char *key, char *value);

t_map			*ft_mapfind(t_map **map, char *key);

void			ft_mapdelall(t_map **map);


void show_map(t_map *map); ///////tmp

#endif