
#include "../parse.h"

int	set_flag(char *midle)
{
	int	j;
	int	f;

	f = 1;
	j = 0;
	if (ft_strcmp(midle, "\0") == 0)
		return (f);
	while (midle[j] && midle[j] != ' ' && midle[j] > 13)
		j++;
	if ((midle[j] != ' ' && midle[j] > 13) || midle[j] == '\0')
		f = 0;
	return (f);
}

t_files	*expand_file(t_files *wlk, int i, t_env *env, t_collector *gc)
{
	char	*right;
	char	*left;
	char	*midle;

	left = ft_copy_l(wlk->name, 0, i);
	if (left == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, left, gc);
	midle = expand(wlk->name, i + 1, env, gc);
	(1) && (gc->str = garbage_str(gc->str, midle, gc), i++);
	while (wlk->name[i] && wlk->name[i] != ' ' && wlk->name[i] != '\"'
		&& wlk->name[i] != '\'' && wlk->name[i] != '$'
		&& (wlk->name[i] < '0' || wlk->name[i] > '9'))
		i++;
	if (wlk->name[i] >= '0' && wlk->name[i] <= '9')
		i++;
	right = ft_strdup(&wlk->name[i]);
	if (right == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, right, gc);
	wlk->name = join_three(left, midle, right);
	if (wlk->name == NULL)
		return (free_all(gc, 1), NULL);
	gc->str = garbage_str(gc->str, wlk->name, gc);
	return (wlk);
}

t_files	*expand_file_rule(t_files *wlk, t_env *env, t_collector *gc)
{
	int	i;

	i = 0;
	while (wlk->name[i])
	{
		if (wlk->name[i] == '\'' || wlk->name[i] == '\"')
			i = skip_qouth(wlk->name[i], wlk->name, i);
		else if (wlk->name[i] == '$' && wlk->name[i + 1] == '\0')
		{
			i++;
			continue ;
		}
		else if (wlk->name[i] == '$')
		{
			wlk = expand_file(wlk, i, env, gc);
			wlk->flag = set_flag(&wlk->name[i]);
			continue ;
		}
		i++;
	}
	wlk->name = expand_word(wlk->name, env, gc);
	return (wlk);
}

t_files	*expand_files(t_files *file, t_env *env, t_collector *gc)
{
	t_files	*wlk;

	wlk = file;
	if (file == NULL)
		return (NULL);
	while (wlk)
	{
		if (wlk->type == HEREDOC)
			wlk = wlk->next;
		else
		{
			wlk = expand_file_rule(wlk, env, gc);
			wlk = wlk->next;
		}
	}
	return (file);
}
