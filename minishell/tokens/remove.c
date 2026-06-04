
#include "../parse.h"

char	*return_string(char *new, char *str, int i, int len)
{
	char	c;

	c = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"' || str[i] == TRICK) && c == '\0')
		{
			c = str[i++];
			continue ;
		}
		if (str[i] == c && c != '\0')
		{
			c = '\0';
			i++;
			continue ;
		}
		new[len++] = str[i++];
	}
	new[len] = '\0';
	return (new);
}

int	count_new_len(char *str, int i)
{
	int		count;
	char	c;

	count = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'' || str[i] == TRICK)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == c)
			{
				count++;
				count++;
				i++;
			}
			else
				break ;
		}
		else
			i++;
	}
	return (ft_strlen(str) - count);
}

char	*remove_all_qouth(char *str, t_collector *gc)
{
	char	*new;
	int		len;
	int		i;

	if (str[0] == '\0')
		return (str);
	len = count_new_len(str, 0);
	if ((str[0] == '\'' || str[0] == '\"') && str[1] == '\0')
		return (str);
	if (len == 0)
		return (empty_string(gc));
	new = malloc(len + 1);
	if (new == NULL)
		return (free_all(gc, 1), NULL);
	i = 0;
	len = 0;
	new = return_string(new, str, i, len);
	return (new);
}

t_files	*remove_qouth_from_file(t_files *file, t_collector *gc)
{
	t_files	*wlk;

	wlk = file;
	if (file == NULL)
		return (NULL);
	while (wlk)
	{
		if (wlk->type == HEREDOC)
			wlk = wlk->next;
		if (!wlk)
			break ;
		wlk->name = remove_all_qouth(wlk->name, gc);
		gc->str = garbage_str(gc->str, wlk->name, gc);
		wlk = wlk->next;
	}
	return (file);
}

t_word	*remove_qouth_from_cmd(t_word *words, t_collector *gc)
{
	t_word	*wlk;

	wlk = words;
	while (wlk)
	{
		wlk->cmd = remove_all_qouth(wlk->cmd, gc);
		gc->str = garbage_str(gc->str, wlk->cmd, gc);
		wlk = wlk->next;
	}
	return (words);
}
