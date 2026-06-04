
#include "../parse.h"

char	*basic_trim(char *str, t_collector *gc)
{
	while (str[0] == ' ' || str[0] == '\t' || str[0] == '\n')
	{
		str = ft_trim(str, str[0]);
		gc->str = garbage_str(gc->str, str, gc);
	}
	return (str);
}

int	c_find(char *s, int i, char c)
{
	char	a;

	a = '\0';
	while (s[i])
	{
		if (a == '\0' && s[i] == c)
			return (i);
		else if ((s[i] == '\'' || s[i] == '\"') && s[i] == a)
			a = '\0';
		else if ((s[i] == '\'' || s[i] == '\"') && a == '\0')
			a = s[i];
		i++;
	}
	return (i);
}

t_pipe	*ft_alloc_node(char *res, t_pipe *nodes, t_collector *gc)
{
	t_pipe	*new;

	new = NULL;
	if (res[0] != '\0')
	{
		new = malloc(sizeof(t_pipe));
		if (new == NULL)
			return (free_pipe(nodes), free_all(gc, 1), NULL);
	}
	return (new);
}

t_pipe	*ft_split_node(char *res, t_collector *gc)
{
	int		i;
	t_pipe	*head;
	t_pipe	*wlk;

	i = 0;
	head = malloc(sizeof(t_pipe));
	if (head == NULL)
		return (free_all(gc, 1), NULL);
	wlk = head;
	while (res[i])
	{
		wlk->str = ft_copy_l(res, i, c_find(res, i, '|'));
		if (wlk->str == NULL)
			return (free_pipe(head), free_all(gc, 1), NULL);
		gc->str = garbage_str(gc->str, wlk->str, gc);
		i = c_find(res, i, '|');
		if (res[i++] == '\0')
			break ;
		wlk->next = ft_alloc_node(&res[i], head, gc);
		wlk = wlk->next;
		if (wlk == NULL)
			return (free_pipe(head), free_all(gc, 1), NULL);
	}
	wlk->next = NULL;
	return (head);
}
