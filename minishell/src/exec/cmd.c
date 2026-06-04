
#include "../minishell.h"

char	*search_in_paths(char *cmd, char **paths, t_gc **gc_list)
{
	char	*tmp;
	char	*command;
	int		i;

	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!command)
			return (NULL);
		if (access(command, X_OK) == 0)
		{
			gc_add(command, gc_list);
			return (command);
		}
		free(command);
	}
	return (NULL);
}

char	**get_paths(t_env *env, t_gc **gc_list)
{
	char	**paths;
	char	*path;

	path = find_path(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	gc_add(paths, gc_list);
	return (paths);
}

char	*get_path_and_res(t_gc **gc_list, char *cmd, char	**paths)
{
	char	*result;

	result = NULL;
	result = search_in_paths(cmd, paths, gc_list);
	if (result)
		return (result);
	else
		return (NULL);
}

char	*chech_files(char *cmd)
{
	struct stat		statbuf;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		printf("here\n");
		if (stat(cmd, &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
				return (msg_er(cmd, ": is a directory\n"),
					ft_stat(126), exit(126), (NULL));
			if (S_ISREG(statbuf.st_mode) && access(cmd, F_OK) == 0)
				return (ft_strdup(cmd));
		}
		return (msg_er(cmd, ": No such file or directory\n"),
			ft_stat(127), exit(127), (NULL));
	}
	return (NULL);
}

// char *check_sta(char *cmd)
// {
// 		struct stat		statbuf;

// 	if (stat(cmd, &statbuf) == 0)
// 		{
// 			if (S_ISDIR(statbuf.st_mode))
// 			{
// 				return (msg_er(cmd, ": is a directory\n"), ft_stat(126), exit(126), (NULL));
// 			}
// 			if (S_ISREG(statbuf.st_mode) && access(cmd, F_OK) == 0)
// 				return (ft_strdup(cmd));
// 		}
// 		return (NULL);
// }
char	*get_cmd(char *cmd, t_env *env, t_gc **gc_list)
{
	struct stat		statbuf;
	char			*res;
	char			**paths;

	if (!cmd || !*cmd)
		return (NULL);
	if (cmd && cmd[0] == '.' && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd + 2));
	(1) && (paths = get_paths(env, gc_list), chech_files(cmd));
	if (!paths)
	{
		if (stat(cmd, &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
			{
				return (msg_er(cmd, ": is a directory\n"), exit(ft_stat(126)), (NULL));
			}
			if (S_ISREG(statbuf.st_mode) && access(cmd, F_OK) == 0)
				return (ft_strdup(cmd));
		}
		return (NULL);
	}
	res = get_path_and_res(gc_list, cmd, paths);
	if (res)
		return (res);
	return (NULL);
}
