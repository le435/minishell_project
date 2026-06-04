
#include "../minishell.h"

void	msg_er(char *argv, char *msg)
{
	write(2, argv, ft_strlen(argv));
	write(2, msg, ft_strlen(msg));
}

char	**updated_env(t_env **envp)
{
	char	**env;
	int		i;
	t_env	*curr;

	i = 0;
	curr = *envp;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (curr)
	{
		env[i] = ft_strjoin(ft_strdup(curr->key), ft_strdup(curr->key));
		i++;
		curr = curr->next;
	}
	env[i] = NULL;
	return (env);
}

void	ft_check_dup_red(t_pipe_g p, t_list_p *node)
{
	if (dup2(p.input_fd, 0) < 0)
	{
		close(p.input_fd);
		ft_perror("dup2 error");
	}
	close(p.input_fd);
	if (hand_red(node->file) < 0)
	{
		exit(ft_stat(1));
	}
}

pid_t	ft_last_child(t_pipe_g p, t_list_p *node,
		t_exec_env *xenv, t_gc **gc_list)
{
	char	**argv;
	pid_t	pid;

	argv = get_cmd_args(node->words, gc_list);
	if (!argv[0])
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		ft_perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		setup_exec_signals();
		ft_check_dup_red(p, node);
		if (is_builtin(argv[0]))
		{
			exit(ft_stat(exec_builtin(argv, xenv->tenv, 1)));
		}
		get_cmd_and_exec(p, argv, *xenv, gc_list);
	}
	else
		signal(SIGINT, SIG_IGN);
	return (pid);
}
