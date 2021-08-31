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
	res = ft_substr(s, start, end - start);
	while (s[start] != '\0')
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
	while (ft_strncmp(delim, line, ft_strlen(delim)) != 0)
	{
		write(pipefd[1], line, ft_strlen(line));
		line = readline("> ");
	}
	write(pipefd[1], "\n", 1);
	res = dup(pipefd[0]);
	close(pipefd[0]);
	close(pipefd[1]);
	return (res);
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
			file_name = get_file_name(params + i + 2);
			if (params[i] == '<' && params[i + 1] == '<')
				fd = heredoc(file_name);
			else if (params[i] == '<')
				fd = open(file_name, O_RDONLY, S_IRWXU);
			if (params[i] == '>' && params[i + 1] == '>')
				fd = open(file_name, O_WRONLY | O_APPEND);
			else if (params[i] == '>')
				fd = open(file_name, O_WRONLY | O_CREAT, S_IRWXU);
			params[i] = ' ';
			params[i + 1] = ' ';
			if (fd == -1)
			{
				write(1, "Error: Can't open file ", 24);
				write(1, file_name, ft_strlen(file_name));
				return (-1);
			}
		}
		++i;
	}
	return (fd);
}
