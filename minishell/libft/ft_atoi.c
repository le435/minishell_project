
#include "libft.h"

static int	flag(int sign)
{
	if (sign < 0)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	i;
	long	res;
	long	sh;	

	sign = 1;
	i = 0;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sh = res;
		res = res * 10 + (str[i] - '0');
		if (res / 10 != sh)
			return (flag(sign));
		i++;
	}
	return (res * sign);
}
