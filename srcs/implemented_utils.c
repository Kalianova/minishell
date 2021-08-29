#include "minishell.h"

int	is_implemented(char *cmd_name)
{
	if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (1);
	return (0);
}

int	my_exec(char *cmd, char *params)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(params);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(params);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd();
	if (ft_strncmp(cmd, "exit", 5) == 0)
		ft_exit(params);
	else
		return (-1);
	return (0);
}
