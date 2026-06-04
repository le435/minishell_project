
#include "../parse.h"

int	skip_word(char *s)
{
	char	c;
	int		i;

	c = '\0';
	i = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"' || s[i] == TRICK) && c == s[i])
			c = '\0';
		else if ((s[i] == '\'' || s[i] == '\"' || s[i] == TRICK) && c == '\0')
			c = s[i];
		else if ((s[i] == ' ' || s[i] < 14 || (s[i] == '>'
					|| s[i] == '<')) && c == '\0')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_copy_s(char *new, char *str, t_collector *gc)
{
	char	*ptr;
	int		i;

	ptr = NULL;
	i = skip_word(str);
	ptr = ft_copy_l(str, 0, i);
	if (ptr == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, ptr, gc);
	new = ft_strjoin(new, ptr);
	if (new == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, new, gc);
	new = c_join(new, ' ');
	if (new == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, new, gc);
	return (new);
}

char	*all_words_allocation(char *str, t_collector *gc)
{
	char	*new;
	int		i;
	char	c;

	new = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			c = str[i];
			i = index_counter(str, i, c);
		}
		if (str[i] != ' ' && str[i] > 13)
		{
			new = ft_copy_s(new, &str[i], gc);
			i += skip_word(&str[i]);
		}
		else if (str[i])
			i++;
	}
	return (new);
}

int	count_helper(char *str, int i)
{
	int		j;
	char	c;

	j = 0;
	while (str[i] && str[i] != ' ' && (str[i] > 13 || str[i] == TRICK))
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == TRICK)
		{
			c = str[i];
			i++;
			j = i;
			while (str[i] && str[i] != c)
				i++;
			if (str[i])
				i++;
			else
				return (j);
		}
		while (str[i] && str[i] != ' ' && str[i] > 13 && str[i] != '\''
			&& str[i] != '\"' && str[i] != TRICK)
			i++;
	}
	return (i);
}

int	count_words_for_struct(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] < 14) && str[i] != TRICK)
			i++;
		if (!str[i])
			break ;
		count++;
		i = count_helper(str, i);
	}
	return (count);
}
