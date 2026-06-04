
#include "../parse.h"

char	*ft_copy_l(char *str, int start, int end)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(end - start + 1);
	if (ptr == NULL)
		return (NULL);
	while (str[start] && start < end)
	{
		ptr[i] = str[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
