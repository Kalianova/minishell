#include "minishell.h"

int	get_fd(t_shell *sh, int **fd_pipes, int i, int io)
{
	int	fd;

	fd = redirected(sh->commands->params, io);
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
	fd_pipes = (int **)malloc(sizeof(int) * count);
	if (fd_pipes == NULL)
		return (NULL);
	while (i < count)
	{
		fd_pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (fd_pipes[i] == NULL)
		{
			//free pipes
			return (NULL);
		}
		if (pipe(fd_pipes[i]) == -1)
		{
			//free pipes
			return (NULL);
		}
		++i;
	}
	return (fd_pipes);
}

int	execute_commads(t_shell *sh, char **envp)
{
	int		i;
	pid_t	*pids;
	int		**fd_pipes;
	int		fd_in;
	int		fd_out;
	t_cmd	cmd;

	pids = (pid_t *)malloc(sizeof(pid_t) * sh->count_commands);
	fd_pipes = get_pipes(sh->count_commands - 1);
	if (pids == NULL || fd_pipes == NULL)
		write(1, "ERROR!\n", 7); // fix me or broke :
	i = 0;
	// printf("COUNT OF commands = %i\n", sh->count_commands);
	while (i < sh->count_commands)
	{
		fd_in = get_fd(sh, fd_pipes, i, 0);
		fd_out = get_fd(sh, fd_pipes, i, 1);
		cmd = parser_cmd(sh, i, envp);
		pids[i] = execute_cmd(cmd, fd_in, fd_out);
		close(fd_in);
		close(fd_out);
		free_cmd(cmd);
		++i;
	}
	i = 0;
	while (i < sh->count_commands)
	{
		waitpid(pids[i], NULL, 0);
		++i;
	}
	free(pids);
	// fd_pipe_[0] free;
	return (0);
}