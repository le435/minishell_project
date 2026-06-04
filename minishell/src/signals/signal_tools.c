
#include "../minishell.h"

void	ft_sign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	h_doc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 2;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		ft_stat(1);
	}
}

int	ft_status_signals(int status, t_list_p *p)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, p->term);
		write(1, "Quit: 3\n", 8);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, p->term);
		write(1, "\n", 2);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	ft_stat(-1);
	return (1);
}
