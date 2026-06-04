
#include "../parse.h"

int	count_len_word(char *str, int i, char c)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	count_len_end(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (i);
		i++;
	}
	return (i);
}

int	skip_qouth(char c, char *str, int i)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	search(char *str, int i, int f)
{
	if (str[i] == '_')
		i++;
	while (f == 1 && str[i])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
		{
			i = skip_qouth(str[i], str, i);
			return (i);
		}
		else if (str[i] == ' ' || str[i] < 14)
		{
			if (str[i] < 14)
				return (i + 1);
			else
				return (i);
		}
		else if (str[i] && str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

int	index_counter(char *str, int i, char c)
{
	i = skip_element(str, c, i, 1);
	i = skip_element(str, ' ', i, 1);
	i += skip_word(&str[i]);
	return (i);
}
