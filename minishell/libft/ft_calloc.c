
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*array;

	if (count == 0 || size == 0)
		return (malloc(0));
	if ((count * size) / size != count)
		return (NULL);
	array = malloc(count * size);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, count * size);
	return (array);
}
