
#include "../parse.h"

static void	free_it(char **ptr, int j)
{
	while (j > 0)
	{
		free(ptr[j]);
		j--;
	}
	free(ptr[j]);
	free(ptr);
}

static char	*c_copy(char *s, int start, char sep)
{
	char	*ptr;
	int		i;
	int		j;

	i = start;
	j = 0;
	while (s[start] && s[start] != sep)
		start++;
	ptr = malloc (start + 1);
	if (ptr == NULL)
		return (NULL);
	while (s[i] && s[i] != sep)
	{
		ptr[j] = s[i];
		j++;
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

static int	count_word(char *s, char sep)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == sep)
			i++;
		if (s[i])
			word++;
		while (s[i] && s[i] != sep)
			i++;
	}
	return (word);
}

static char	**splt(int words, char *s, char sep)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	ptr = malloc ((words + 1) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (i < words)
	{
		while (s[j] && s[j] == sep)
			j++;
		ptr[i] = c_copy(s, j, sep);
		if (ptr[i] == NULL)
			return (free_it(ptr, i), NULL);
		while (s[j] && s[j] != sep)
			j++;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_split(char *s, char sep)
{
	char	**ptr;
	int		words;

	if (s == NULL)
		return (NULL);
	words = count_word(s, sep);
	ptr = splt(words, s, sep);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}
