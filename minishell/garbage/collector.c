
#include "../parse.h"

void	close_all_files(void)
{
	int	i;

	i = 1024;
	while (i > 2)
	{
		close(i);
		i--;
	}
}

void	free_list_p(t_list_p *list)
{
	t_list_p	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void	free_col(t_list_c *col)
{
	t_list_c	*tmp;

	while (col)
	{
		tmp = col->next;
		free_words(col->words);
		free_file(col->file);
		free(col);
		col = tmp;
	}
}

void	free_all(t_collector *gc, int ex)
{
	free_col(gc->col);
	free_env(gc->env);
	free_pipe(gc->pipes);
	free_list_p(gc->list);
	free_str(gc->str);
	close_all_files();
	exit(ex);
}
