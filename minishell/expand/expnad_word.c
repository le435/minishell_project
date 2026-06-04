

#include "../parse.h"

char	*expand_operation(char *str, int i, t_env *env, t_collector *gc)
{
	char	*right;
	char	*left;
	char	*midle;

	left = ft_copy_l(str, 0, i);
	if (left == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, left, gc);
	midle = expand(str, i + 1, env, gc);
	gc->str = garbage_str(gc->str, midle, gc);
	i++;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')))
		i++;
	if (str[i] >= '0' && str[i] <= '9')
		i++;
	right = ft_strdup(&str[i]);
	if (right == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, right, gc);
	left = join_three(left, midle, right);
	if (left == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, left, gc);
	return (left);
}

char	*expand_exit_status(void)
{
	int	status;

	status = ft_stat(-1);
	return (ft_itoa(status));
}

char	*join_operation(char *str, int i, char *temp, t_collector *gc)
{
	char	*new;
	char	*right;

	new = ft_copy_l(str, 0, i);
	if (new == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, new, gc);
	right = ft_strdup(&str[i + 2]);
	if (right == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, right, gc);
	new = ft_strjoin(new, temp);
	if (new == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, new, gc);
	new = ft_strjoin(new, right);
	if (new == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, new, gc);
	return (new);
}

int	skip_part(char *str, int i, int f)
{
	if (str[i] == '\'' && f % 2 == 0)
		i = skip_qouth(str[i], str, i);
	if (str[i] == '\"')
		i++;
	if (f == 1)
		while (str[i] && str[i] != '$' && str[i] != '\"')
			i++;
	return (i);
}

char	*expand_word(char *str, t_env *env, t_collector *gc)
{
	char	*temp;
	int		i;

	(1) && (i = 0, gc->f = 0);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			temp = expand_exit_status();
			if (temp == NULL)
				return (free_all(gc, 1), NULL);
			gc->str = garbage_str(gc->str, temp, gc);
			str = join_operation(str, i, temp, gc);
		}
		if (str[i] == '\"')
			gc->f++;
		else if (str[i] == '\'')
			i = skip_part(str, i, gc->f);
		str = return_expand(str, &i, env, gc);
		if (str[i])
			i++;
	}
	return (str);
}
