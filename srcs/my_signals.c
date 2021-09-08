#include "minishell.h"
#include <termios.h>

void	sig_handler(int code)
{
	if (code == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (code == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_it(int code)
{
	if (code == SIGINT)
	{
		printf("\n");
	}
	if (code == SIGQUIT)
	{
		printf("Quit\n");
	}
}

int	my_signals(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
	}
	if (mode == 1)
	{
		signal(SIGINT, sig_handler_it);
		signal(SIGQUIT, sig_handler_it);
	}
	return (0);
}
