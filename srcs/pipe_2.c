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
