
#include "../parse.h"

char	*c_join(char *str, char c)
{
	char	*ptr;
	int		i;

	i = 0;
	if (str == NULL)
	{
		ptr = malloc(2);
		if (!ptr)
			return (NULL);
		ptr[0] = c;
		ptr[1] = '\0';
		return (ptr);
	}
	ptr = malloc(ft_strlen(str) + 2);
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i++] = c;
	ptr[i] = '\0';
	return (ptr);
}

char	*join_three(char *left, char *midle, char *right)
{
	char	*temp;

	left = ft_strjoin(left, midle);
	if (left == NULL)
		return (NULL);
	temp = left;
	left = ft_strjoin(left, right);
	free(temp);
	return (left);
}
