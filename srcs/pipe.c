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
	// else
	// 	exit(result);
	return (result);
}

pid_t	execute_cmd(t_cmd *cmd, int fd_in, int fd_out, t_map **envp)
{
	pid_t	pid;
	int		fd_old_out;
	int		fd_old_in;

	if (!is_implemented(cmd->name) || cmd->count_commands > 1)
		pid = fork();
	else
		pid = 0;
	if (pid == -1)
		write(1, "Error: Fork failed!\n", 21);
	if (pid == 0)
	{
		fd_old_out = dup(STDOUT_FILENO);
		fd_old_in = dup(STDIN_FILENO);

		if (child_process(*cmd, fd_in, fd_out, envp) == -1)
		{
			dup2(fd_old_out, STDOUT_FILENO);
			close(fd_old_out);
			write(1, "Error: No such command or dup2 failed!\n", 39);
		}
		else
		{
			if (cmd->count_commands > 1)
				exit(0);
			dup2(fd_old_out, STDOUT_FILENO);
			dup2(fd_old_in, STDIN_FILENO);
		}
	}
	return (pid);
}

t_cmd	parser_cmd(t_shell *sh, int i, char **envp)
{
	t_cmd	cmd;

	cmd.name = ft_substr(sh->commands[i].name,
			0, len_cmd(sh->commands[i].name));
	cmd.path = get_path(cmd.name, envp);
	cmd.params[0] = ft_strdup(cmd.name);
	cmd.params[1] = ft_strtrim(sh->commands[i].params, " ");
	cmd.params[2] = NULL;
	cmd.arr_params = sh->commands[i].arr_params;
	cmd.count_commands = sh->count_commands;
	if (*cmd.params[1] == '\0')
	{
		free(cmd.params[1]);
		cmd.params[1] = NULL;
	}
	return (cmd);
}

char	*get_access_path(char *cmd_name, char *path)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	result = ft_strjoin(temp, cmd_name);
	free(temp);
	if (access(result, X_OK) == 0)
		return (result);
	free(result);
	return (NULL);
}

char	*get_path(char *cmd_name, char **envp)
{
	char	**paths;
	int		i;
	char	*result;

	i = 0;
	if (is_implemented(cmd_name))
		return (ft_strdup(cmd_name));
	if (access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			paths = ft_split(*envp + 5, ':');
			while (paths[i] != NULL)
			{
				result = get_access_path(cmd_name, paths[i]);
				if (result != NULL)
				{
					ft_free_words(paths);
					return (result);
				}
				++i;
			}
			ft_free_words(paths);
		}
		++envp;
	}
	return (NULL);
}
