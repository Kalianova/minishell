#include "minishell.h"

char	*get_file_name(char *s)
{
	int		i;
	int		start;
	int		end;
	char	*res;

	i = 0;
	while (s[i] == ' ')
		++i;
	start = i;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\n')
		++i;
	end = i;
	res = ft_isubstr(s, start, end - start, '"');
	while (s[start] != '\0' && s[start] != '<' && s[start] != '>')
	{
		s[start] = ' ';
		++start;
	}
	return (res);
}

int	heredoc(char *delim)
{
	char	*line;
	int		pipefd[2];
	int		res;

	line = NULL;
	if (pipe(pipefd) == -1)
		printf("Pipe error\n");
	line = readline("> ");
	while (line != NULL && ft_strncmp(delim, line, ft_strlen(delim) + 1) != 0)
	{
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = readline("> ");
		write(pipefd[1], "\n", 1);
	}
	free(line);
	res = dup(pipefd[0]);
	close(pipefd[0]);
	close(pipefd[1]);
	return (res);
}

char	*parse_fd(char **params, int i, int *fd)
{
	char	*file_name;

	if (*fd != 0)
	{
		close(*fd);
		*fd = 0;
	}
	file_name = get_file_name((*params) + i + 2);
	if ((*params)[i] == '<' && (*params)[i + 1] == '<')
		*fd = heredoc(file_name);
	else if ((*params)[i] == '<')
		*fd = open(file_name, O_RDONLY, S_IRWXU);
	if ((*params)[i] == '>' && (*params)[i + 1] == '>')
		*fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	else if ((*params)[i] == '>')
		*fd = open(file_name, O_WRONLY | O_CREAT, S_IRWXU);
	(*params)[i] = ' ';
	(*params)[i + 1] = ' ';
	return (file_name);
}

int	redirected(char *params, int io)
{
	int		i;
	int		fd;
	char	*file_name;

	i = 0;
	fd = 0;
	if (params == NULL)
		return (0);
	while (params[i] != '\0')
	{
		if ((params[i] == '>' && io == 1) || (params[i] == '<' && io == 0))
		{
			file_name = parse_fd(&params, i, &fd);
			if (fd == -1)
			{
				printf("minishell: %s: No such file or directory\n", file_name);
				free(file_name);
				return (-1);
			}
			free(file_name);
		}
		++i;
	}
	return (fd);
}
