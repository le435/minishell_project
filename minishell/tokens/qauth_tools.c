
#include "../parse.h"

char	*create_new_qauth(char *str, char c, char q, t_collector *gc)
{
	int		i;
	int		start;
	char	*new;

	i = 1;
	start = 1;
	while (str[i] && str[i] != c)
		i++;
	new = malloc(i + 4);
	if (new == NULL)
		return (NULL);
	if (c == '\"')
		q = '\'';
	new[0] = q;
	(1) && (i = 0, new[start] = str[i], i = 1, start++);
	while (str[i] && str[i] != c)
	{
		new[start] = str[i];
		i++;
		start++;
	}
	new[start] = str[i];
	new[start + 1] = q;
	new[start + 2] = '\0';
	gc->str = garbage_str(gc->str, new, gc);
	return (new);
}

char	*replace_index_with_new(char *new, char *old, int i, t_collector *gc)
{
	char	*first;
	char	*last;

	(1) && (first = NULL, last = NULL);
	if (i != 0)
	{
		first = ft_copy_l(old, 0, i - 1);
		gc->str = garbage_str(gc->str, first, gc);
	}
	first = ft_strjoin(first, new);
	gc->str = garbage_str(gc->str, first, gc);
	i = skip_qouth(old[i], old, i) + 1;
	last = ft_strdup(&old[i]);
	gc->str = garbage_str(gc->str, last, gc);
	first = ft_strjoin(first, last);
	return (first);
}

char	*add_fake_qauth(char *src, t_collector *gc)
{
	int		i;
	int		size;
	char	*dst;

	(1) && (i = 0, size = 0);
	while (src[i])
	{
		if ((src[i] == '\'' || src[i] == '\"' ) && src[i + 1] != '\0')
		{
			dst = create_new_qauth(&src[i], src[i], '\"', gc);
			if (!dst)
				return (NULL);
			src = replace_index_with_new(dst, src, i + 1, gc);
			gc->str = garbage_str(gc->str, src, gc);
			(1) && (size = ft_strlen(src), i += ft_strlen(dst));
			if (i >= size)
				return (src);
		}
		else
			i++;
	}
	return (src);
}
