
#include "../minishell.h"

char	*my_getenv(char **env, char *key)
{
	int		i;
	size_t	klen;

	klen = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, klen) == 0 && env[i][klen] == '=')
		{
			return (ft_strdup(env[i] + klen + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}

int	process_env_var(char *env_var, char **key, char **value)
{
	int	j;

	j = 0;
	while (env_var[j] && env_var[j] != '=')
		j++;
	*key = ft_substr(env_var, 0, j);
	if (!*key)
		return (0);
	*value = ft_strchr(env_var, '=');
	if (*value)
		*value = *value + 1;
	else
		*value = "";
	return (1);
}

t_env	*handl_env(char **envp, t_env *head, t_env *new, t_env *tmp)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!process_env_var(envp[i], &key, &value))
			return (free_env(head), NULL);
		new = creat_env(key, value);
		if (!new)
			return (free_env(head), NULL);
		if (!head)
			head = new;
		else
			tmp->next = new;
		tmp = new;
		i++;
	}
	return (head);
}

int	ft_env(t_env **env)
{
	t_env	*cur;

	if (!env || !*env)
		return (1);
	
	ft_stat(0);
	cur = *env;

	while (cur)
	{
		if (cur->value && *cur->value != '\0')
			printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	return (0);
}
