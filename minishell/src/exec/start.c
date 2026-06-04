
#include "../minishell.h"

int	ft_stat(int status)
{
	static int	exit_status;

	if (status < 0)
		return (exit_status);
	else
		exit_status = status;
	return (status);
}

int	check_bui(t_list_p *tmp, t_gc **gc_list, t_exec_env xenv)
{
	char	**av;

	av = get_cmd_args(tmp->words, gc_list);
	if (!av)
		return (-1);
	if (is_builtin(tmp->words->cmd) && tmp->next == NULL)
	{
		ft_bltin_no_frk(tmp, av, &xenv);
		return (0);
	}
	return (-1);
}

long long	run_childrens(t_list_p *list,
	t_exec_env xenv, t_gc **gc_list)
{
	t_list_p	*tmp;
	t_pipe_g	p;
	long long	i;

	(1) && (i = 0, tmp = list);
	if (!tmp || !tmp->words)
		return (open_pre(list), 0);
	if (check_bui(tmp, gc_list, xenv) == 0)
		return (0);
	if (pipe(p.current_pipe) < 0)
		ft_perror("pipe");
	ft_first_child(p, list, &xenv, gc_list);
	close(p.current_pipe[1]);
	(1) && (p.input_fd = p.current_pipe[0], tmp = tmp->next);
	while (tmp && tmp->next)
	{
		if (pipe(p.previous_pipe) < 0)
			ft_perror("pipe");
		(1) && (mid_child(p, tmp, &xenv, gc_list), close(p.input_fd));
		(1) && (p.input_fd = p.previous_pipe[0], close(p.previous_pipe[1]));
		tmp = tmp->next;
	}
	if (tmp)
		i = ft_last_child(p, tmp, &xenv, gc_list);
	return (close(p.input_fd), i);
}

int	pre_process_heredocs(t_list_p *list, t_env **env)
{
	t_files	*file;

	tcgetattr(0, list->term);
	while (list)
	{
		file = list->file;
		while (file)
		{
			if (file->type == HEREDOC)
			{
				file->heredoc_fd = herdoc_part(file->name, *env);
				tcsetattr(STDIN_FILENO, TCSANOW, list->term);
				if (file->heredoc_fd == -1 || file->heredoc_fd == -2)
					return (-1);
			}
			file = file->next;
		}
		list = list->next;
	}
	return (0);
}

void	execution(t_list_p *list, t_env **tenv, t_gc **gc)
{
	t_execution_data	data;
	long long			k;

	(1) && (data.xenv.tenv = tenv, data.i = 0);
	if (!list)
		return ;
	1 && (data.fds.fd_in = dup(STDIN_FILENO),
		data.fds.fd_out = dup(STDOUT_FILENO));
	if (pre_process_heredocs(list, tenv) < 0)
		return (close(data.fds.fd_in),
			close(data.fds.fd_out), ft_stat(-1), (void)0);
	ft_sign();
	(1) && (k = run_childrens(list, data.xenv, gc),
		waitpid(k, &data.status, 0));
	while (wait(NULL) != -1)
		;
	data.exit_code = ft_status_signals(data.status, list);
	if (k == 0)
		data.exit_code = ft_stat(-1);
	if (k == -1)
		data.exit_code = ft_stat(1);
	ft_stat(data.exit_code);
	(dup2(data.fds.fd_in, 0), dup2(data.fds.fd_out, 1),
		close(data.fds.fd_in), close(data.fds.fd_out));
}
