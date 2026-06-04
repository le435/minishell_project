
#include "../minishell.h"

char	*find_path(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

char	**get_cmd_args(t_word *words, t_gc **gc_list)
{
	int		count;
	t_word	*tmp;
	char	**argv;
	int		i;

	(1) && (count = 0, tmp = words);
	while (tmp)
		(1) && (count++, tmp = tmp->next);
	argv = gc_malloc(sizeof(char *) * (count + 1), gc_list);
	if (!argv)
		return (NULL);
	(1) && (tmp = words, i = 0);
	while (tmp)
	{
		argv[i] = ft_strdup(tmp->cmd);
		if (!argv[i])
		{
			while (i-- > 0)
				free(argv[i]);
			return (free(argv), NULL);
		}
		gc_add(argv[i], gc_list);
		(1) && (i++, tmp = tmp->next);
	}
	return (argv[i] = NULL, argv);
}

void	ft_perror(char *str)
{
	perror(str);
}

char	**alocat_env(t_env **envp)
{
	t_env	*curr;
	int		i;

	i = 0;
	curr = *envp;
	while (curr)
		(1) && (i++, curr = curr->next);
	return (malloc(sizeof(char *) * (i + 1)));
}

char	**updated_env_exe(t_env **envp)
{
	char	**env;
	int		i;
	t_env	*curr;
	char	*key_eq;

	env = alocat_env(envp);
	if (!env)
		return (NULL);
	i = 0;
	curr = *envp;
	while (curr)
	{
		key_eq = ft_strjoin(curr->key, "=");
		if (!key_eq)
			ft_free_split(env);
		env[i] = ft_strjoin(key_eq, curr->value);
		free(key_eq);
		if (!env[i])
			ft_free_split(env);
		i++;
		curr = curr->next;
	}
	env[i] = NULL;
	return (env);
}
