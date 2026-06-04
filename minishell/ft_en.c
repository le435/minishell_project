
#include "parse.h"

t_env	*add_shlvl(t_env *tmp)
{
	t_env	*shlvl;
	char	*dushlvl;

	dushlvl = ft_strdup("1");
	shlvl = creat_env(ft_strdup("SHLVL"), dushlvl);
	if (tmp)
		tmp->next = shlvl;
	free(dushlvl);
	return (shlvl);
}

t_env	*add_path(t_env *tmp)
{
	t_env	*path;
	char	*dupath;

	dupath = ft_strdup("/usr/bin:/bin:/usr/sbin:/sbin");
	path = creat_env(ft_strdup("PATH"), dupath);
	if (tmp)
		tmp->next = path;
	free(dupath);
	return (path);
}

t_env	*init_default_env(void)
{
	t_env	*env;
	t_env	*tmp;
	char	cwd[1024];
	char	*dupcwd;

	env = NULL;
	tmp = NULL;
	dupcwd = NULL;
	if (getcwd(cwd, sizeof(cwd)))
	{
		dupcwd = ft_strdup(cwd);
		env = creat_env(ft_strdup("PWD"), dupcwd);
		tmp = env;
		tmp = add_shlvl(tmp);
		tmp = add_path(tmp);
		free(dupcwd);
	}
	else
		printf("i should not handl this case\n");
	return (env);
}

t_env	*creat_env(char *key, char *value)
{
	t_env	*env;

	if (key == NULL)
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = ft_strdup("");
	if (!env->value)
	{
		free(key);
		free(env);
		return (NULL);
	}
	if (key && ft_strcmp(key, "PWD") == 0)
		env->pwd = ft_strdup(env->value);
	else
		env->pwd = NULL;
	if (key && ft_strcmp(key, "PWD") == 0 && !env->pwd)
	{
		free(key);
		free(env->value);
		free(env);
		return (NULL);
	}
	env->next = NULL;
	return (env);
}
t_env	*init_env(char **envp)
{

	t_env	*head;
	t_env	*tmp;
	t_env	*new;
	t_env	*pwd_node;

	head = NULL;
	tmp = NULL;
	new = NULL;

	if (!envp || !*envp)
	{
		return (init_default_env());
	}
	head = handl_env(envp, head, new, tmp);
	
	if (!head)
		return (NULL);
	pwd_node = ft_check_var("PWD", head);
	if (pwd_node)
	{
		if (pwd_node->pwd)
			free(pwd_node->pwd);
		pwd_node->pwd = ft_strdup(pwd_node->value);
		if (!pwd_node->pwd) {
            return (NULL);
        }
	}
	else
	{
		char *cwd = getcwd(NULL, 0);
		if (cwd)
		{
			new = creat_env(ft_strdup("PWD"), cwd);
			if (new)
			{
				add_back_env(&head, new);
			}
			free(cwd);
		}
	}
	return (head);
}