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
	if (ft_strncmp(cmd_name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (1);
	return (0);
}

int	my_exec(char *cmd, char *params, char **envp)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (ft_cd(params));
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (ft_echo(params));
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (ft_pwd(params));
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (ft_exit(params));
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (ft_env(params, envp));
	else
		return (127);
	return (0);
}
