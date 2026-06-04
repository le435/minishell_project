
#include "../parse.h"

static int	counter_redir(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			c = str[i];
			count++;
			i = skip_element(str, c, i, 1) - 1;
		}
		i++;
	}
	return (count);
}

t_files	*alloc_files(char *str, t_collector *gc)
{
	int		i;
	t_files	*new;
	t_files	*wlk;

	i = counter_redir(str) - 1;
	if (i < 0)
		return (NULL);
	new = malloc(sizeof(t_files));
	if (new == NULL)
		return (free_all(gc, 1), NULL);
	wlk = new;
	wlk->name = NULL;
	while (i > 0)
	{
		wlk->next = malloc(sizeof(t_files));
		if (wlk->next == NULL)
			return (free_file(new), free_all(gc, 1), NULL);
		wlk = wlk->next;
		wlk->name = NULL;
		i--;
	}
	wlk->next = NULL;
	return (new);
}
