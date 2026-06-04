
#include "../minishell.h"

long	ft_atoi_1(const char *str, int *overflow)
{
	int					i;
	int					sign;
	unsigned long long	total;

	(1) && (*overflow = 0, i = 0, sign = 1, total = 0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		total = total * 10 + (str[i++] - '0');
		if (total > 9223372036854775807)
		{
			*overflow = 1;
			break ;
		}
	}
	if (*overflow)
		return (0);
	return ((long)(total * sign));
}

int	is_number(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **cmd, int interactive)
{
	long	exit_code;
	int		overflow;

	if (interactive == 0)
		printf("exit\n");
	if (!cmd[1])
		exit(ft_stat(-1));
	if (!is_number(cmd[1]) || cmd[1][0] == '\0')
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		exit(255);
	}
	if (cmd[2])
		return (printf("minishell: exit: too many arguments\n"),
			ft_stat(1), 1);
	exit_code = ft_atoi_1(cmd[1], &overflow);
	if (overflow)
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		exit(255);
	}
	return (exit((unsigned char)exit_code), 0);
}
