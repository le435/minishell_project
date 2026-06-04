
#include "../parse.h"

t_str	*garbage_str(t_str *str, char *val, t_collector *gc)
{
	t_str	*wlk;
	t_str	*new_node;

	wlk = str;
	while (wlk)
	{
		if (wlk->val == val)
			return (str);
		wlk = wlk->next;
	}
	new_node = malloc(sizeof(t_str));
	if (!new_node)
		free_all(gc, 1);
	new_node->val = val;
	new_node->next = str;
	return (new_node);
}

t_pipe	*garbage_pipe(t_pipe *ptr, t_pipe *val)
{
	t_pipe	*wlk;

	if (ptr == NULL)
		return (val);
	if (ptr == val)
		return (ptr);
	wlk = ptr;
	while (wlk && wlk->next)
	{
		if (ptr == val)
			return (ptr);
		wlk = wlk->next;
	}
	wlk->next = val;
	return (ptr);
}

t_list_c	*garbage_list_c(t_list_c *dest, t_word *word,
							t_files *files, t_collector *gc)
{
	t_list_c	*wlk;

	if (!dest)
	{
		dest = malloc(sizeof(t_list_c));
		if (!dest)
			free_all(gc, 1);
		dest->words = word;
		dest->file = files;
		dest->next = NULL;
		return (dest);
	}
	wlk = dest;
	while (dest->next)
		dest = dest->next;
	dest->next = malloc(sizeof(t_list_c));
	if (!dest->next)
		free_all(gc, 1);
	dest->next->words = word;
	dest->next->file = files;
	dest->next->next = NULL;
	return (wlk);
}

t_list_p	*garbage_list_p(t_list_p *list, t_list_p *val)
{
	t_list_p	*wlk;

	if (!list)
		return (val);
	if (list == val)
		return (list);
	wlk = list;
	while (wlk->next)
		wlk = wlk->next;
	wlk->next = val;
	return (list);
}
