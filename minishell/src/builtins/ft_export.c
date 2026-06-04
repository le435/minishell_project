
#include "../minishell.h"

void	ft_decla(t_env *env)
{
	if (env->next)
		env = env->next;
	while (env)
	{
		printf("declare -x ");
		printf("%s", env->key);
		if (env->value && env->value != NULL)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

void	ft_swap(char **val1, char **val2)
{
	char	*tmp;

	tmp = *val1;
	*val1 = *val2;
	*val2 = tmp;
}

void	ft_only_export(t_env *env)
{
	t_env	*in;
	t_env	*next_n;

	if (!env)
		return ;
	in = env;
	while (in)
	{
		next_n = in->next;
		while (next_n)
		{
			if (ft_strcmp(in->key, next_n->key) > 0)
			{
				ft_swap(&in->key, &next_n->key);
				ft_swap(&in->value, &next_n->value);
			}
			next_n = next_n->next;
		}
		in = in->next;
	}
	ft_decla (env);
}

int	valid_format(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(char **cmd, t_env **env)
{
	char		**split;
	t_env		*new;
	int			i;
	t_expdata	data;

	(1) && (i = 1, ft_stat(0));
	if (!cmd[1])
		return (ft_only_export(*env), 0);
	while (cmd[i])
	{
		(1) && (new = NULL, split = ft_split(cmd[i], '='));
		if (!split)
			return (1);
		if (valid_format(cmd[i]))
		{
			(1) && (data.cmd = cmd, data.split = split, data.i = i);
			handl_cases(env, data, new);
		}
		else
			(1) && (printf("minishell: export: \
`%s`: not a valid identifier\n", cmd[i]), ft_stat(1));
		ft_free_split(split);
		i++;
	}
	return (0);
}
