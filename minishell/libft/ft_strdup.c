
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*s ;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (i < len)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return ((char *)s);
}
