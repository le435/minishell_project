
#include "../parse.h"

int	is_pipe_error(char *res)
{
	int	i;

	i = 0;
	if (res[0] == '|')
		return (put_error("bash: syntax error near unexpected token `|'\n"
				, 0, NULL), ft_stat(258), -1);
	while (res[i])
	{
		i = skip_element(res, '|', i, 0);
		if (res[i] != '|')
			break ;
		i++;
		while (res[i] && not_allowed(res[i]) == 1
			&& is_alphabet(res[i]) != 1 && res[i] != '|')
			i++;
		if (res[i] == '|' || res[i] == '\0')
			return (put_error("bash: syntax error near unexpected token `|'\n"
					, 0, NULL), ft_stat(258), -1);
	}
	return (1);
}

int	is_qoute_error(char *res)
{
	char	x;
	int		i;

	i = 0;
	while (res[i])
	{
		if (res[i] == '\"' || res[i] == '\'')
		{
			x = res[i];
			i++;
			while (res[i] && res[i] != x)
				i++;
			if (res[i] == '\0')
				return (put_error("bash: syntax error near unexpected token `"
						, x, "'\n"), ft_stat(258), -1);
		}
		i++;
	}
	return (1);
}

int	syntax_error(char *res, int i, char c, int count)
{
	if (res[i] != c && (res[i] == '>' || res[i] == '<'))
	{
		if (res[i] == res[i + 1])
			return (put_error("bash: Syntax Error `", res[i], NULL),
				put_error(NULL, res[i + 1], "'\n"), ft_stat(258), -1);
		return (put_error("bash: Syntax Error `", c, "'\n"),
			ft_stat(258), -1);
	}
	if (count > 2)
		return (put_error("bash: Syntax Error `", c, "'\n"),
			ft_stat(258), -1);
	if (res[i] == '\0')
		return (put_error("bash: Syntax Error `", 0, "\\n'\n"),
			ft_stat(258), -1);
	else if (res[i] == '<' || res[i] == '>')
		return (put_error("bash: Syntax Error `", res[i], "'\n"),
			ft_stat(258), -1);
	return (i);
}

int	redir_check(char *res)
{
	char	c;
	int		i;
	int		count;

	i = 0;
	if (res[i] == '>' || res[i] == '<')
	{
		count = 0;
		c = res[i];
		if (res[i + 1] == '\0')
			return (put_error("bash: Syntax Error `newline'\n", 0, NULL)
				, ft_stat(258), -1);
		while (res[i] == c)
		{
			if (count == 1 && res[i] == res[i + 1])
				return (put_error("bash: Syntax Error `", res[i], NULL),
					put_error(NULL, res[i + 1], "'\n"), ft_stat(258), -1);
			count ++;
			i++;
		}
		i = skip_element(res, ' ', i, 1);
		return (syntax_error(res, i, c, count));
	}
	return (i);
}

int	check(t_pipe *pipes)
{
	t_pipe	*wlk;
	int		hold;
	int		i;

	wlk = pipes;
	i = 0;
	while (wlk)
	{
		while (wlk->str && wlk->str[i])
		{
			if (wlk->str[i] == '\'' || wlk->str[i] == '\"')
				i = skip_qouth(wlk->str[i], wlk->str, i);
			hold = redir_check(&wlk->str[i]);
			if (hold == -1)
				return (-1);
			i += hold;
			if (wlk->str[i] == '\0')
				break ;
			i++;
		}
		i = 0;
		wlk = wlk->next;
	}
	return (1);
}
