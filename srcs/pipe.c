#include "minishell.h"

int	child_process(t_cmd cmd, int fd_in, int fd_out, t_map **envp)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (1);
	close(fd_in);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (1);
	close(fd_out);
	if (my_exec(cmd.path,  cmd.arr_params, envp) == 127)
		if (execve(cmd.path, cmd.params, NULL) == -1)
			return (1);
	return (0);
}

pid_t	execute_cmd(t_cmd cmd, int fd_in, int fd_out, t_map **envp)
{
	pid_t	pid;
	int		fd_old_out;

	pid = fork();
	if (pid == -1)
		write(1, "Error: Fork failed!\n", 21);
	if (pid == 0)
	{
		fd_old_out = dup(STDOUT_FILENO);
		if (child_process(cmd, fd_in, fd_out, envp))
		{
			dup2(fd_old_out, STDOUT_FILENO);
			close(fd_old_out);
			write(1, "Error: No such command or dup2 failed!\n", 39);
			exit(1);
		}
		// exit(0);
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
	cmd.arr_params = sh->commands->arr_params;
	if (*cmd.params[1] == '\0')
	{
		free(cmd.params[1]);
		cmd.params[1] = NULL;
	}
	return (cmd);
}

char	*get_access_path(char *cmd_name, char *path, char **paths)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	result = ft_strjoin(temp, cmd_name);
	free(temp);
	if (access(result, X_OK) == 0)
	{
		free_strings(paths);
		return (result);
	}
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
				result = get_access_path(cmd_name, paths[i], paths);
				if (result != NULL)
					return (result);
				++i;
			}
		}
		++envp;
	}
	return (NULL);
}
