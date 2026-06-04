
#include "../parse.h"

static char	*add_to_str(char *dest, char *src, t_collector *gc)
{
	char	*new;
	int		i;

	i = word(src);
	new = ft_copy_l(src, 0, i);
	if (new == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, new, gc);
	dest = ft_strjoin(dest, " ");
	if (dest == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, dest, gc);
	dest = ft_strjoin(dest, new);
	if (dest == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, dest, gc);
	return (dest);
}

char	*files_string(char *str, t_collector *gc)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			i = skip_qouth(str[i], str, i);
		if (str[i] == '>' || str[i] == '<')
		{
			i = skip_element(str, str[i], i, 1);
			i = skip_element(str, ' ', i, 1);
			new = add_to_str(new, &str[i], gc);
			i += word(&str[i]) - 1;
		}
		if (str[i])
			i++;
	}
	return (new);
}

static char	*add_redire(char *new, char *str, t_collector *gc)
{
	if (str[1] == '>')
		new = ft_strjoin(new, ">>");
	else if (str[1] == '<')
		new = ft_strjoin(new, "<<");
	else if (str[0] == '>')
		new = ft_strjoin(new, ">");
	else if (str[0] == '<')
		new = ft_strjoin(new, "<");
	if (new == NULL)
		return (NULL);
	gc->str = garbage_str(gc->str, new, gc);
	new = ft_strjoin(new, " ");
	return (new);
}

char	*redirections(char *str, t_collector *gc)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = skip_qouth(str[i], str, i);
		else if (str[i] == '>' || str[i] == '<')
		{
			new = add_redire(new, &str[i], gc);
			if (new == NULL)
				return (free_all(gc, 1), NULL);
			gc->str = garbage_str(gc->str, new, gc);
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
		}
		if (str[i])
			i++;
	}
	return (new);
}
