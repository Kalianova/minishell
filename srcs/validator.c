#include "minishell.h"

int	validate_sequence(const char *line, char ch, int i, int flag)
{
	int	char_in_row;

	char_in_row = 0;
	if (line[0] == ch)
		return (1);
	while (line[++i] != '\0')
	{
		if (line[i] == ' ')
		{
			if (char_in_row > 0)
				flag = 1;
			continue ;
		}
		if (line[i] == ch)
			++char_in_row;
		else
		{
			char_in_row = 0;
			flag = 0;
		}
		if (char_in_row > 2 || (char_in_row > 1 && ch == '|')
			|| (char_in_row > 1 && flag == 1))
			return (1);
	}
	return (0);
}

int	validate_line(const char *line)
{
	if (validate_sequence(line, '|', -1, 0) != 0
		|| validate_sequence(line, '>', -1, 0) != 0
		|| validate_sequence(line, '<', -1, 0))
		return (2);
	return (0);
}
