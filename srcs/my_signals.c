#include "minishell.h"
#include <termios.h>

void	sig_handler(int code)
{

	if (code == SIGINT)
	{
		// rl_replace_line("\n$> ", 0);
		printf("\n");
		// rl_redisplay();
		rl_on_new_line();
	}
	if (code == SIGQUIT)
	{
		printf("quit\n");
		exit (0);
	}
}

void	sig_handler_it(int code)
{
	static struct termios termios_save;

	printf("it\n");
	if (code == SIGINT)
	{
		printf("\n");
		tcsetattr(0, 0, &termios_save);
	}
	if (code == SIGQUIT)
	{
		printf("quit\n");
		exit (0);
	}
	// rl_on_new_line();
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
