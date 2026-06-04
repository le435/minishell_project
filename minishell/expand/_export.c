
#include "../parse.h"

char	*use_trick(char *str, int i, t_env *env, t_collector *gc)
{
	char	*new;
	char	*ptr;
	int		j;

	j = 0;
	new = expand(str, i, env, gc);
	gc->str = garbage_str(gc->str, new, gc);
	ptr = malloc(ft_strlen(new) + 3);
	if (ptr == NULL)
		return (free_all(gc, 1), NULL);
	i = 0;
	ptr[j++] = TRICK;
	while (new[i])
	{
		ptr[j] = new[i];
		j++;
		i++;
	}
	ptr[j] = TRICK;
	ptr[j + 1] = '\0';
	return (ptr);
}

char	*expand_string(char *str, int i, t_env *env, t_collector *gc)
{
	char	*left;
	char	*right;
	char	*midle;

	left = ft_copy_l(str, 0, i);
	if (left == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, left, gc);
	midle = use_trick(str, i + 1, env, gc);
	if (midle == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, midle, gc);
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '\"'
		&& str[i] != '$' && str[i] != '=' && str[i] != '\'')
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

char	*expand_rule(char *str, t_env *env, int i, t_collector *gc)
{
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] < 14 && str[i] >= 9))
			i = skip_element(str, str[i], i, 1);
		if (str[i] == '\'' || str[i] == '\"')
			i = skip_qouth(str[i], str, i);
		if (str[i] == '>' || str[i] == '<' || str[i] == '\0')
			return (str);
		if (str[i] != '_' && is_alphabet(str[i]) == -1)
			i += skip_word(&str[i]);
		i = search(str, i, 0);
		if ((str[i] != '+' && str[i] != '=' && is_alphabet(str[i]) == -1))
			i += skip_word(&str[i]);
		while (((str[i] && str[i] != ' ') || str[i] == '$'))
		{
			i = search(str, i, 1);
			if (str[i] == '\0' || str[i] == ' ' || str[i] == '\''
				|| (str[i] < 14 && str[i] != TRICK) || str[i] == '\"' )
				continue ;
			str = expand_string(str, i, env, gc);
			i += skip_word(&str[i]);
		}
	}
	return (str);
}

char	*expand_export_rule(char *str, t_env *env, t_collector *gc)
{
	char	*temp;

	if (ft_strncmp(str, "export", 5) != 0 && ft_strncmp(str, "EXPORT", 5) != 0)
		return (str);
	if (str[5] == '\0')
		return (str);
	temp = expand_rule(str, env, 6, gc);
	return (temp);
}

t_pipe	*primary_expand(t_pipe *pipes, t_env *env, t_collector *gc)
{
	t_pipe	*wlk;

	wlk = pipes;
	while (wlk)
	{
		wlk->str = expand_export_rule(wlk->str, env, gc);
		wlk = wlk->next;
	}
	return (pipes);
}
