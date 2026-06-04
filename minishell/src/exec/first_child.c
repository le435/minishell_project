
#include "../minishell.h"

int	ft_bltin_no_frk(t_list_p *list,
		char **argv, t_exec_env *xenv)
{
	t_save_std	sv;
	int			status;
	int			tst;

	(1) && (tst = hand_red(list->file), sv.out = dup(1), sv.in = dup(0));
	if (sv.out < 0 || sv.in < 0)
		(1) && (ft_perror("dup error"), ft_stat(1));
	if (tst == -2)
		return (-1);
	if (tst < 0)
	{
		if (sv.out != -1)
			close(sv.out);
		if (sv.in != -1)
			close(sv.in);
		return (ft_stat(1));
	}
	(1) && (status = exec_builtin(argv, xenv->tenv, 0), ft_stat(status));
	if (sv.out != -1)
		(1) && (dup2(sv.out, STDOUT_FILENO), close(sv.out));
	if (sv.in != -1)
		(1) && (dup2(sv.in, STDIN_FILENO), close(sv.in));
	if (status != 0)
		return (-1);
	return (0);
}

void	get_cmd_and_exec(t_pipe_g p, char **argv,
	t_exec_env xenv, t_gc **gc_list)
{
	char	*cmd;

	xenv.env = updated_env_exe(xenv.tenv);
	gc_add(xenv.env, gc_list);
	if (argv[0][0] == 16)
		exit(0);
	if (argv[0][0] == '\0')
		cmd = NULL;
	else
		cmd = get_cmd(argv[0], *xenv.tenv, gc_list);
	if (!cmd)
	{
		(1) && (write(2, "minishell: ", 11), write(2, argv[0],
			ft_strlen(argv[0])), write(2, " : command not found\n", 21));
		ft_stat(127);
		cleanup_and_exit(p, 127);
	}
	(1) && (gc_add(cmd, gc_list), execve(cmd, argv, xenv.env));
	if (errno == EACCES)
	{
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, ": Permission denied\n", 21);
		exit(126);
	}
	cleanup_and_exit(p, 0);
}

static pid_t	handle_builtin_fork(t_list_p *list,
		int *current_pip, char **argv, t_exec_env *xenv)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (ft_perror("fork"), ft_stat(1), -1);
	if (pid == 0)
	{
		if (list->next && dup2(current_pip[1], STDOUT_FILENO) < 0)
		{
			close_fd(current_pip);
			ft_perror("dup error");
			exit(ft_stat(1));
		}
		close_fd(current_pip);
		if (hand_red(list->file) < 0)
		{
			exit(ft_stat(1));
		}
		exit(ft_stat(exec_builtin(argv, xenv->tenv, 1)));
	}
	else
		signal(SIGINT, SIG_IGN);
	return (pid);
}

void	ft_dup_red(t_pipe_g p, t_list_p *list)
{
	if (list->next && dup2(p.current_pipe[1], STDOUT_FILENO) < 0)
	{
		close_fd(p.current_pipe);
		ft_stat(1);
	}
	close_fd(p.current_pipe);
	if (hand_red(list->file) < 0)
	{
		exit(ft_stat(1));
	}
}

pid_t	ft_first_child(t_pipe_g p, t_list_p *list,
		t_exec_env *xenv, t_gc **gc_list)
{
	char	**argv;
	pid_t	pid;

	argv = get_cmd_args(list->words, gc_list);
	if (!argv[0])
		return (-1);
	if (is_builtin(argv[0]))
		return (handle_builtin_fork(list, p.current_pipe, argv, xenv));
	else
	{
		pid = fork();
		if (pid < 0)
			return (ft_perror("fork"), -1);
		if (pid == 0)
		{
			setup_exec_signals();
			ft_dup_red(p, list);
			get_cmd_and_exec(p, argv, *xenv, gc_list);
		}
		else
			signal(SIGINT, SIG_IGN);
	}
	return (pid);
}
