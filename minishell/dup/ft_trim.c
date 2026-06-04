
#include "../parse.h"

static int	calc_t(char *s, char c)
{
	int	start;
	int	last;

	last = ft_strlen(s) - 1;
	start = 0;
	while (s[start] && s[start] == c)
		start++;
	while (last != 0 && s[last] == c)
		last--;
	last = last - start + 1;
	return (last);
}

char	*ft_trim(char *s, char c)
{
	char	*ptr;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = calc_t(s, c);
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (j < len)
	{
		ptr[j] = s[j + i];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
