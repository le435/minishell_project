
#include "../parse.h"

t_word	*allocate_all_words(int len, t_collector *gc)
{
	t_word	*new;
	t_word	*wlk;

	new = malloc(sizeof (t_word));
	if (new == NULL)
		return (free_all(gc, 1), NULL);
	wlk = new;
	while (len > 0)
	{
		wlk->next = malloc(sizeof(t_word));
		if (wlk->next == NULL)
			return (free_words(new), free_all(gc, 1), NULL);
		wlk->cmd = NULL;
		wlk = wlk->next;
		len--;
	}
	wlk->next = NULL;
	return (new);
}

char	*copy_word(int i, char *str)
{
	int		l;
	char	*ptr;

	l = count_helper(str, i);
	ptr = ft_copy_l(str, i, l);
	return (ptr);
}

t_word	*store_all_words(t_word *new, char *str, t_collector *gc)
{
	t_word	*word;
	int		i;
	int		word_len;

	(1) && (word = new, i = 0);
	str = basic_trim(str, gc);
	if (str[0] == '\0')
		return (null_termenate_word(word, gc));
	while (word)
	{
		while (str[i] && (str[i] == ' ' || str[i] < 14))
			i++;
		if (str[i] && str[i] != ' ' && str[i] > 14)
		{
			word->cmd = copy_word(i, str);
			if (word->cmd == NULL)
				return (free_all(gc, 1), NULL);
			gc->str = garbage_str(gc->str, word->cmd, gc);
			word_len = ft_strlen(word->cmd);
			i += word_len;
		}
		word = word->next;
	}
	return (new);
}

t_word	*all_words_struct(char *str, t_collector *gc)
{
	t_word	*words;
	int		l;

	l = count_words_for_struct(str);
	if (str[0] == '\0')
		l++;
	words = allocate_all_words(l - 1, gc);
	gc->col = garbage_list_c(gc->col, words, NULL, gc);
	words = store_all_words(words, str, gc);
	return (words);
}

t_word	*all_words(char *str, t_env *env, t_collector *gc)
{
	t_word	*word_list;
	char	*words;

	words = all_words_allocation(str, gc);
	if (words == NULL)
		return (NULL);
	words = expand_word(words, env, gc);
	word_list = all_words_struct(words, gc);
	return (word_list);
}
