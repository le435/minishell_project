
#include "libft.h"

void	*memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	size_t				i;

	str = (const unsigned char *)s;
	i = 0;
	while (i < n && str[i] != c)
		i++;
	if (str[i] == c)
	{
		return ((char *)&str[i]);
	}
	return (0);
}
