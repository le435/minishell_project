
#include "../minishell.h"

void	*gc_malloc(size_t size, t_gc **gc_list)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	gc_add(ptr, gc_list);
	return (ptr);
}

void	gc_add(void *ptr, t_gc **gc_list)
{
	t_gc	*new;

	if (!ptr || !gc_list)
	{
		return ;
	}
	new = malloc(sizeof(t_gc));
	if (!new)
		return ;
	new->ptr = ptr;
	new->next = *gc_list;
	*gc_list = new;
}

void	gc_free_all(t_gc **gc_list)
{
	t_gc	*tmp;

	while (*gc_list)
	{
		free((*gc_list)->ptr);
		tmp = *gc_list;
		*gc_list = (*gc_list)->next;
		free(tmp);
	}
	g_signal = 0;
	close_all_files();
}

int	ft_close_descriptors(t_list_p *gc)
{
	int	i;

	i = 0;
	if (gc && gc->fds)
	{
		while (gc->fds[i])
		{
			if (gc->fds[i] == -2)
				return (0);
			close(gc->fds[i]);
			i++;
		}
	}
	return (0);
}

void	cleanup_and_exit(t_pipe_g p, int status)
{
	if (p.current_pipe[0] != -1)
		close(p.current_pipe[0]);
	if (p.current_pipe[1] != -1)
		close(p.current_pipe[1]);
	if (p.previous_pipe[0] != -1)
		close(p.previous_pipe[0]);
	if (p.previous_pipe[1] != -1)
		close(p.previous_pipe[1]);
	if (p.input_fd != -1)
		close(p.input_fd);
	exit(status);
}
