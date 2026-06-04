
#include "../parse.h"

t_token_type	type_redir(char *s)
{
	if (s[0] == '>' && s[1] == '>')
		return (REDIR_APPEND);
	else if (s[0] == '>' && s[1] != '>')
		return (REDIR_OUT);
	else if (s[0] == '<' && s[1] == '<')
		return (HEREDOC);
	return (REDIR_IN);
}

void	store_name(t_files *file, char *f_name, char *r_name, t_collector *gc)
{
	int	end;

	end = 0;
	end = word(f_name);
	file->type = type_redir(r_name);
	file->name = ft_copy_l(f_name, 0, end);
	file->flag = 0;
	gc->str = garbage_str(gc->str, file->name, gc);
	if (file->name == NULL)
	{
		free(r_name);
		free(f_name);
		free_all(gc, 1);
	}
}

t_files	*all_files(char *str, int j, t_collector *gc)
{
	t_files	*files;
	t_files	*wlk;
	char	*f_names;
	char	*r_names;
	int		i;

	i = 0;
	f_names = files_string(str, gc);
	if (f_names == NULL)
		return (NULL);
	r_names = redirections(str, gc);
	files = alloc_files(r_names, gc);
	if (files == NULL)
		return (NULL);
	gc->col = garbage_list_c(gc->col, NULL, files, gc);
	wlk = files;
	j = 1;
	while (wlk)
	{
		store_name(wlk, &f_names[j], &r_names[i], gc);
		i = skip_element(r_names, ' ', i, 0) + 1;
		j += word(&f_names[j]) + 1;
		wlk = wlk->next;
	}
	return (files);
}
