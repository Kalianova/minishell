#include "minishell.h"

int	is_implemented(char *cmd_name)
{
	if (ft_strncmp(cmd_name, "cd", 2) == 0)
		return (1);
	return (0);
}

int	my_exec(char *cmd, char *params)
{
	if (ft_strncmp(cmd, "cd", 2) == 0)
		cd(params);
	else
		return (-1);
	return (0);
}
