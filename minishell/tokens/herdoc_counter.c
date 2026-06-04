
#include "../parse.h"

char	*expand_safe(char *str, int i, t_env *env, t_collector *gc)
{
	char	*right;
	char	*left;
	char	*midle;

	left = ft_copy_l(str, 0, i);
	gc->str = garbage_str(gc->str, left, gc);
	(1) && (midle = expand(str, i + 1, env, gc), i++);
	gc->str = garbage_str(gc->str, midle, gc);
	midle = add_fake_qauth(midle, gc);
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')))
		i++;
	if (str[i] >= '0' && str[i] <= '9')
		i++;
	right = ft_strdup(&str[i]);
	gc->str = garbage_str(gc->str, right, gc);
	left = join_three(left, midle, right);
	gc->str = garbage_str(gc->str, left, gc);
	return (left);
}

char	*return_expand(char *str, int *i, t_env *env, t_collector *gc)
{
	char	*new;

	new = NULL;
	if (str[*i] == '$' && are_not_near(str, *i) == 1
		&& str[*i + 1] && gc->f == 0)
	{
		new = expand(str, *i + 1, env, gc);
		str = expand_safe(str, *i, env, gc);
		*i += ft_strlen(new);
	}
	else if (str[*i] == '$' && are_not_near(str, *i) == 1 && str[*i + 1])
	{
		new = expand(str, *i + 1, env, gc);
		str = expand_operation(str, *i, env, gc);
		*i += ft_strlen(new);
	}
	return (str);
}

void	herdoc_counter(t_pipe *pipes, t_collector *gc)
{
	t_pipe	*wlk;
	int		count;
	int		i;

	i = 0;
	count = 0;
	wlk = pipes;
	while (wlk)
	{
		while (wlk->str[i])
		{
			if (wlk->str[i] == '\'' || wlk->str[i] == '\"')
				i = skip_qouth(wlk->str[i], wlk->str, i);
			if (wlk->str[i] == '<' && wlk->str[i + 1] == '<')
				count++;
			i++;
		}
		i = 0;
		wlk = wlk->next;
	}
	if (count >= 16)
		return (put_error("bash: maximum here-document count exceeded",
				'\0', NULL), free_all(gc, 0));
}

int	check_nighboor(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i += skip_word(&str[i]);
		if (str[i] == ' ' || str[i] < 14)
			i = skip_element(str, str[i], i, 1);
		if (is_alphabet(str[i]) == 1)
			return (1);
		if (str[i])
			i++;
	}
	return (-1);
}
