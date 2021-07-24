#include <stdio.h>
#include "libft.h"

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	printf("%i\n", argc);
	while (++i < argc)
	{
		printf("%s - %li\n", argv[i], ft_strlen(argv[i]));
	}
	return (0);
}