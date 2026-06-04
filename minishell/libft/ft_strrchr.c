
#include "libft.h"

char	*ft_strrchr(const char *d, int c)
{
	int	i;

	i = ft_strlen(d);
	while (i >= 0)
	{
		if (d[i] == (char)c)
			return ((char *)&d[i]);
		i--;
	}
	return (NULL);
}
