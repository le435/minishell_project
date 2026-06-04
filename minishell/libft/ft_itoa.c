
#include "libft.h"

static	int	count_size(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	if (n < 0)
	{
		i = 1;
		n *= -1;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int num)
{
	char		*dst;
	int			count;
	int			i;
	long		n;

	n = num;
	i = 0;
	count = count_size(n);
	dst = (char *)malloc((count + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		dst[0] = '-';
		i++;
	}
	dst[count] = '\0';
	while (count > i)
	{
		count--;
		dst[count] = (n % 10) + '0';
		n /= 10;
	}
	return (dst);
}
