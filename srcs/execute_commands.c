#include "minishell.h"

int	get_fd(t_shell *sh, int **fd_pipes, int i, int io)
{
	int	fd;

	fd = redirected(sh->commands[i].params, io);
	if (fd == -1)
		return (-1);
	if (fd)
		return (fd);
	if (i == 0 && io == 0)
		return (dup(0));
	if (i == sh->count_commands - 1 && io == 1)
		return (dup(1));
	if (i == 0 || io == 1)
		return (fd_pipes[i][io]);
	return (fd_pipes[i - 1][io]);
}

int	**get_pipes(int count)
{
	int		i;
	int		**fd_pipes;

	i = 0;
	fd_pipes = (int **)malloc(sizeof(int *) * count);
	if (fd_pipes == NULL)
		return (NULL);
	while (i < count)
	{
		fd_pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (fd_pipes[i] == NULL)
		{
			return (NULL);
		}
		if (pipe(fd_pipes[i]) == -1)
		{
			return (NULL);
		}
		++i;
	}
	return (fd_pipes);
}

void	free_pipes(int	**fd_pipes, int len)
{
	int	i;

	i = 0;
	if (fd_pipes == NULL)
		return ;
	while (i < len)
	{
		free(fd_pipes[i]);
		++i;
	}
	free(fd_pipes);
}

void	execute_commads_add(t_shell *sh, t_map **map,
	 pid_t *pids, int **fd_pipes)
{
	int		fd_in;
	int		fd_out;
	int		i;
	t_cmd	cmd;

	i = -1;
	while (++i < sh->count_commands)
	{
		fd_in = get_fd(sh, fd_pipes, i, 0);
		fd_out = get_fd(sh, fd_pipes, i, 1);
		cmd = parser_cmd(sh, i, map);
		if (cmd.path && cmd.name && fd_in != -1 && fd_out != -1)
			pids[i] = execute_cmd(&cmd, fd_in, fd_out, map);
		else
		{
			if (ft_mapfind(map, "PATH") == NULL && cmd.name != NULL)
				printf("minishell: %s: no such file or directory\n", cmd.name);
			else if (fd_in != -1 && fd_out != -1)
				printf("minishell: command not found\n");
			pids[i] = -1;
			sh->last_result = 127;
		}
		if (fd_in != -1)
			close(fd_in);
		if (fd_out != -1)
			close(fd_out);
		free_cmd(cmd);
	}
}

int	execute_commads(t_shell *sh, t_map **map)
{
	int		i;
	pid_t	*pids;
	int		**fd_pipes;

	if (sh->count_commands < 1)
		return (0);
	pids = (pid_t *)malloc(sizeof(pid_t) * sh->count_commands);
	if (pids == NULL)
		return (0);
	fd_pipes = get_pipes(sh->count_commands - 1);
	if (fd_pipes == NULL)
	{
		free(pids);
		return (0);
	}
	execute_commads_add(sh, map, pids, fd_pipes);
	i = 0;
	while (i < sh->count_commands)
		waitpid(pids[++i - 1], &sh->last_result, 0);
	free(pids);
	free_pipes(fd_pipes, sh->count_commands - 1);
	return (0);
}
