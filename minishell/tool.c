#include "../minishell.h"

char	*ft_get_env(char *key, t_env *lst)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, key))
			return (lst->value + 1);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_update_pwd(t_env *old, t_env *pwd, char *buf, t_env **env)
{
	if (old)
	{
		free(old->value);
		old->value = ft_strjoin(ft_strdup("="),ft_strdup(buf));
	}
	else if (!old && pwd)
	{
		t_env *env_o = lstnew_env(ft_strdup("OLDPWD"),ft_strjoin(ft_strdup("="), ft_strdup(buf)));
		gc_add(env_o, pwd->gc);
		add_back_env(env, env_o);
		
	}	
	getcwd(buf, 4096);
	if (pwd)
	{
		free(pwd->value);
		pwd->value = ft_strjoin(ft_strdup("="), ft_strdup(buf));
		gc_add(pwd->value, pwd->gc);
		
	}
	else
	{
		t_env *env_pp = lstnew_env(ft_strdup("PWD"),ft_strjoin(ft_strdup("="), ft_strdup(buf)));
		gc_add(env_pp, pwd->gc);
		add_back_env(env, env_pp);
		
	}
}

void	error_cmd(char *cmd, char *msg)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, msg, ft_strlen(msg));
}
t_env	*ft_check_var(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, str))
			return (env);
		env = env->next;
	}
	return (NULL);
}
void	ft_cd(char **cmd, t_env **env, int *stat)
{
	(void)stat;
	t_env	*node;
	t_env	*old;
	char	*cwd;
	char	buf[4096];
	int		test;

	1 && (node = ft_check_var("PWD", *env), old = ft_check_var("OLDPWD", *env));

	(getcwd(buf, 4096), test = chdir(cmd[1]), cwd = getcwd(NULL, 0));

	if (!access(cmd[1], F_OK) && access(cmd[1], R_OK))
		(error_cmd(cmd[1], "Permission denied\n"), ft_status(1));
	
	else if (!ft_strcmp(cmd[1], "..") && (test < 0 || !cwd))
		((error_cmd("", "getcwd : No such file or direct\n"),
				ft_status(1), ft_update_pwd(old, node, buf, env)));
				
	else if (test >= 0)
		(ft_update_pwd(old, node, buf, env), ft_status(0));
	else if (test < 0)
		(error_cmd(cmd[1], "getcwd : No such file or direct\n"),
			ft_status(1));
	free(cwd);
}

