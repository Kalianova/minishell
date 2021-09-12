#include "minishell.h"

pid_t	execute_cmd(t_cmd *cmd, int fd_in, int fd_out, t_map **envp)
{
	pid_t	pid;

	if (!is_implemented(cmd->name) || cmd->count_commands > 1)
		pid = fork();
	else
		pid = 0;
	if (pid == -1)
		write(1, "Error: Fork failed!\n", 21);
	if (pid == 0)
	{
		child(fd_in, fd_out, cmd, envp);
	}
	return (pid);
}

t_cmd	parser_cmd(t_shell *sh, int i, t_map **map)
{
	t_cmd	cmd;

	cmd.name = ft_substr(sh->commands[i].name,
			0, len_cmd(sh->commands[i].name));
	cmd.path = get_path(cmd.name, map);
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

char	*get_path(char *cmd_name, t_map **map)
{
	char	**paths;
	int		i;
	char	*result;
	t_map	*tmp;

	i = 0;
	if (is_implemented(cmd_name) || access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	tmp = ft_mapfind(map, "PATH");
	if (tmp)
	{
		paths = ft_split(tmp->value, ':');
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
	return (NULL);
}
