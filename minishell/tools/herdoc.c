
#include "../parse.h"

char	*remove_herdoc_qouth(char *str)
{
	char	*new;
	int		len;
	int		i;

	len = count_new_len(str, 0);
	if (len <= 0)
		return (ft_strdup("\0"));
	new = malloc(len + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	len = 0;
	new = return_string(new, str, i, len);
	return (new);
}

int	red_part(t_her her, char *end, t_env *env, int out_fd)
{
	g_signal = 0;
	while (1)
	{
		her.line = readline("> ");
		if (g_signal)
		{
			(1) && (close_all_files(), free(her.line), ft_stat(1));
			g_signal = 2;
			return (4);
		}
		if (her.line == NULL)
			break ;
		if (her.line == NULL)
		{
			her.ret = -1;
			return (-1);
		}
		if (ft_strcmp(her.line, end) == 0)
			return (free(her.line), 1);
		her.line = herdoc_expander(her, her.line, env);
		ft_putstr_fd(her.line, out_fd);
		ft_putstr_fd("\n", out_fd);
		free(her.line);
	}
	return (1);
}

int	write_herdoc(int out_fd, char *end, t_env *env, int f)
{
	t_her	her;

	// if (her.saved_stdin == -1)
	// 	return (free(end), -1);
	her.f = f;
	f = red_part(her, end, env, out_fd);
	if (f == -1)
		return (-1);
	return (f);
}

char	*my_endof(char *end)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	while (end[i] && end[i] != '\'' && end[i] != '\"')
		i++;
	if (end[0] == '$' && (end[i] == '\'' || end[i] == '\"'))
	{
		temp = remove_herdoc_qouth(end);
		if (temp == NULL)
			return (NULL);
		i = dollars(temp);
		temp2 = ft_strdup(&temp[i]);
		free(temp);
		return (temp2);
	}
	temp = remove_herdoc_qouth(end);
	return (temp);
}

int	herdoc_part(char *end, t_env *env)
{
	char	*new;
	char	*name;
	int		out_fd;
	int		in_fd;
	int		f;

	(1) && (f = is_single_qouth(end), name = create_acess());
	if (name == NULL)
		return (-1);
	(1) && (signal(SIGINT, h_doc_handler), new = my_endof(end));
	if (new == NULL)
		return (free(name), -1);
	out_fd = open(name, O_CREAT | O_RDWR, 0644);
	if (out_fd == -1)
		return (free(name), free(new), -1);
	in_fd = open(name, O_RDONLY);
	if (in_fd == -1)
		return (free(name), free(new), close(out_fd), -1);
	(1) && (unlink(name), free(name), f = write_herdoc(out_fd, new, env, f));
	if (f == -1)
		return (close(out_fd), close(in_fd), free(new), -1);
	else if (f == 4)
		return (close(out_fd), close(in_fd), free(new), -2);
	return (close(out_fd), free(new), in_fd);
}
