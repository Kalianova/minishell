#include "minishell.h"

int	child_process(t_cmd cmd, int fd_in, int fd_out, t_map **envp)
{
	int	result;

	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (1);
	close(fd_in);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (1);
	close(fd_out);
	result = my_exec(cmd.path, cmd.arr_params, envp);
	if (result == 127)
		result = execve(cmd.path, cmd.params, 0);
	return (result);
}

void	child(int fd_in, int fd_out, t_cmd *cmd, t_map **envp)
{
	int		fd_old_out;
	int		fd_old_in;

	fd_old_out = dup(STDOUT_FILENO);
	fd_old_in = dup(STDIN_FILENO);
	if (child_process(*cmd, fd_in, fd_out, envp) == -1)
	{
		dup2(fd_old_out, STDOUT_FILENO);
		close(fd_old_out);
	}
	else
	{
		dup2(fd_old_out, STDOUT_FILENO);
		dup2(fd_old_in, STDIN_FILENO);
		close(fd_old_out);
		close(fd_old_in);
	}
	if (!is_implemented(cmd->name) || cmd->count_commands > 1)
		exit(0);
}
