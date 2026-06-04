
#include "../parse.h"

t_pipe	*trim_all(t_pipe *pipes, t_collector *gc)
{
	t_pipe	*wlk;

	wlk = pipes;
	while (wlk)
	{
		while (wlk->str[0] == ' ' || wlk->str[0] == '\t'
			|| wlk->str[ft_strlen(wlk->str) - 1] == ' '
			|| wlk->str[ft_strlen(wlk->str) - 1] == '\t')
		{
			if (wlk->str[0] == ' ' || wlk->str[ft_strlen(wlk->str) - 1] == ' ')
				wlk->str = ft_trim(wlk->str, ' ');
			else
				wlk->str = ft_trim(wlk->str, '\t');
			if (wlk->str == NULL)
				return (free_pipe(pipes), free_all(gc, 1), NULL);
			gc->str = garbage_str(gc->str, wlk->str, gc);
		}
		wlk = wlk->next;
	}
	return (pipes);
}
