
#include "../parse.h"

int	dollars(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i++] == '$')
		count++;
	if (count == 1)
		return (1);
	return (count % 2);
}

char	*empty_string(t_collector *gc)
{
	char	*new;

	new = ft_strdup("\0");
	gc->str = garbage_str(gc->str, new, gc);
	return (new);
}

static t_list_p	*store_data(t_list_p *list, char *str,
							t_env *env, t_collector *gc)
{
	char	*temp;

	list->words = all_words(str, env, gc);
	list->file = all_files(str, 0, gc);
	list->file = expand_files(list->file, env, gc);
	list->file = remove_qouth_from_file(list->file, gc);
	if (list->words == NULL)
		return (list);
	if (ft_strcmp(list->words->cmd, "\0") == 0)
	{
		temp = empty_toke();
		if (temp == NULL)
			free_all(gc, 1);
		gc->str = garbage_str(gc->str, temp, gc);
		list->words->cmd = temp;
	}
	else
		list->words = remove_qouth_from_cmd(list->words, gc);
	return (list);
}

t_list_p	*alloc_list(t_pipe *pipes, t_env *env, t_collector *gc)
{
	t_list_p	*list;
	t_list_p	*wlk;

	list = malloc(sizeof (t_list_p));
	if (list == NULL)
		return (NULL);
	wlk = list;
	wlk->next = NULL;
	wlk = store_data(wlk, pipes->str, env, gc);
	pipes = pipes->next;
	while (pipes)
	{
		wlk->next = malloc(sizeof (t_list_p));
		if (wlk->next == NULL)
			return (free_list_p(list), NULL);
		wlk = wlk->next;
		wlk = store_data(wlk, pipes->str, env, gc);
		pipes = pipes->next;
	}
	wlk->next = NULL;
	return (list);
}

t_list_p	*store_value(t_pipe *pipes, t_env *env, t_collector *gc)
{
	t_list_p	*list;

	list = alloc_list(pipes, env, gc);
	if (list == NULL)
		free_all(gc, 1);
	gc->list = garbage_list_p(gc->list, list);
	return (list);
}
