
#include "../minishell.h"

void	ft_update(char *str, t_env *env, t_env *new, char **s)
{
	if (ft_strchr(str, '='))
	{
		new = compare_var(s[0], env);
		free(new->value);
		new->value = ft_strdup(ft_strchr(str, '=') + 1);
	}
}

int	check_export(char **s, char *str, t_env *new, t_env **env)
{
	int	i;

	i = 0;
	while (s[0] && s[0][i])
	{
		if (s[0][i] == '+' && !s[0][i + 1] && ft_strchr(str, '='))
		{
			value_join(s, str, new, env);
			return (1);
		}
		if (!ft_isalnum(s[0][i]) && s[0][i] != '_')
		{
			printf("minishell: export: `%s`: not a valid identifier\n", s[0]);
			return (1);
		}
		if (i == 0 && ft_isdigit(s[0][0]))
		{
			printf("minishell: export: `%s`: not a valid identifier\n", s[0]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	add_new_back(t_env **env, t_env *new, t_expdata data)
{
	char	*value;
	char	*key;
	char	*equal_sign;

	key = ft_strdup(data.split[0]);
	equal_sign = ft_strchr(data.cmd[data.i], '=');
	if (equal_sign)
		value = ft_strdup(equal_sign + 1);
	else
		value = NULL;
	new = lstnew_env(key, value);
	add_back_env(env, new);
	free(value);
}

void	handl_cases(t_env **env, t_expdata data, t_env *new)
{
	if (valid_format(data.cmd[data.i]))
	{
		if (!check_export(data.split, data.cmd[data.i], new, env))
		{
			if (compare_var(data.split[0], *env))
				ft_update(data.cmd[data.i], *env, new, data.split);
			else
				add_new_back(env, new, data);
		}
	}
}
