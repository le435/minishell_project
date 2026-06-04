
#include "../minishell.h"

void	close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_child_mid(t_pipe_g p, t_list_p *node)
{
	close(p.previous_pipe[0]);
	if (dup2(p.input_fd, 0) < 0)
	{
		close(p.input_fd);
		ft_perror("dup2 error");
		exit(ft_stat(1));
	}
	if (dup2(p.previous_pipe[1], 1) < 0)
	{
		close(p.previous_pipe[1]);
		ft_perror("dup2 error");
		exit(ft_stat(1));
	}
	close(p.input_fd);
	close(p.previous_pipe[1]);
	if (hand_red(node->file) < 0)
	{
		close(p.input_fd);
		close(p.previous_pipe[1]);
		exit(ft_stat(1));
	}
}

pid_t	mid_child(t_pipe_g p, t_list_p *node,
		t_exec_env *xenv, t_gc **gc_list)
{
	char	**argv;
	pid_t	pid;

	argv = get_cmd_args(node->words, gc_list);
	if (!argv[0])
		return (-1);
	pid = fork();
	if (pid < 0)
		return (ft_perror("fork"), (-1));
	if (pid == 0)
	{
		setup_exec_signals();
		if (hand_red(node->file) == -2)
			return (-1);
		ft_child_mid(p, node);
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
