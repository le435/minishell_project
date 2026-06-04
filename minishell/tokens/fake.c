
#include "../parse.h"

void	he(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 4;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		ft_stat(1);
	}
	if (signum == SIGQUIT)
	{
		g_signal = 4;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		ft_stat(0);
	}
}

int	open_fake(char *str)
{
	char	*last;
	char	*res;

	g_signal = 0;
	last = remove_herdoc_qouth(str);
	if (last == NULL)
		return (free(str), -1);
	while (1)
	{
		if (g_signal == 4)
		{
			free(last);
			free(str);
			ft_stat(-1);
			return (1);
		}
		res = readline("> ");
		if (res == NULL)
			return (free(last), free(str), ft_stat(0), -1);
		if (ft_strcmp(res, last) == 0)
			break ;
		free(res);
	}
	return (free(last), free(str), free(res), 1);
}

int	open_fake_herdoc(char *str)
{
	char	*temp;
	char	*new;
	int		i;
	int		l;
	int		len;

	(1) && (l = skip_word(str), i = 0);
	if (str[i] == '$' && (str[l - 1] == '\"' || str[l - 1] == '\''))
		i = dollars(str);
	new = ft_copy_l(str, i, l);
	if (new == NULL)
		return (-1);
	(1) && (len = count_new_len(new, i), signal(SIGINT, he));
	if (len == (int) ft_strlen(new))
		return (open_fake(new));
	if (len == 0)
		len ++;
	temp = malloc(len + 1);
	if (temp == NULL)
		return (free(new), -1);
	temp = return_string(temp, new, i, 0);
	free(new);
	if (open_fake(temp) == -1)
		return (-1);
	return (-1);
}

int	find_and_open_fake_herdoc(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '<' || str[1] != '<')
		return (1);
	while (str[i])
	{
		if (str[i] != '<')
			break ;
		i = skip_element(str, '<', i, 1);
		i = skip_element(str, ' ', i, 1);
		if (check_nighboor(&str[i]) == 1)
			return (1);
		if (str[i] != ' ')
			open_fake_herdoc(&str[i]);
		i += skip_word(&str[i]);
		i = skip_element(str, ' ', i, 1);
	}
	return (-2);
}

int	fake_herdoc(t_pipe *pipes)
{
	t_pipe	*wlk;
	int		res;

	wlk = pipes;
	while (wlk)
	{
		res = find_and_open_fake_herdoc(wlk->str);
		if (res == -2)
			return (-1);
		if (res == 1)
			return (1);
		wlk = wlk->next;
	}
	return (1);
}
