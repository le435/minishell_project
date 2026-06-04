

#include "../minishell.h"

t_env	*find_key(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void    ft_del_env_node(t_env *node)
{
    if (!node)
        return ;
    if (node->key)
        free(node->key);
    if (node->value)
        free(node->value);
    if (node->pwd)
        free(node->pwd);
    free(node);
}
int	ft_valid_unset(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		i++;
		while (str[i])
		{
			if (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	delete_node(t_env **env, char *to_delet)
{
	t_env	*prev;
	t_env	*cur;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, to_delet) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			ft_del_env_node(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	ft_unset(t_env **env, char **cmd)
{
	int	i;
	int	stat;

	stat = 0;
	i = 1;
	ft_stat(0);
	if (!env || !*env || !cmd || !cmd[i])
		return (0);
	while (cmd[i])
	{
		if (ft_valid_unset(cmd[i]))
		{
			delete_node(env, cmd[i]);
		}
		else
		{
			stat = 1;
			ft_stat(1);
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
	return (stat);
}
