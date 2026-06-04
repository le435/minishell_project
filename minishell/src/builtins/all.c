
#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env"));
}

int	exec_builtin(char **token, t_env **env, int i)
{
	int	stat;

	stat = 0;
	if (!ft_strcmp(token[0], "cd"))
	{
		ft_cd(token, env, &stat);
		return (stat);
	}
	else if (!ft_strcmp(token[0], "echo"))
		return (ft_echo(token));
	else if (!ft_strcmp(token[0], "pwd"))
		return (ft_pwd(*env));
	else if (!ft_strcmp(token[0], "exit"))
		return (ft_exit(token, i));
	else if (!ft_strcmp(token[0], "export"))
		return (ft_export(token, env));
	else if (!ft_strcmp(token[0], "unset"))
		return (ft_unset(env, token));
	else if (!ft_strcmp(token[0], "env"))
		return (ft_env(env));
	return (127);
}
