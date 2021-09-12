#include "minishell.h"

int	validate_sequence(const char *line, char ch)
{
	int	i;
	int	char_in_row;

	i = 0;
	char_in_row = 0;
	if (line[i] == ch)
		return (1);
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			++i;
			continue ;
		}
		if (line[i] == ch)
			++char_in_row;
		else
			char_in_row = 0;
		if (char_in_row > 2
			|| (char_in_row > 1 && ch == '|'))
			return (1);
		++i;
	}
	return (0);
}

int	validate_line(const char *line)
{
	if (validate_sequence(line, '|') != 0 || validate_sequence(line, '>') != 0
		|| validate_sequence(line, '<'))
		return (2);
	return (0);
}
