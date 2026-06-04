
#include "../parse.h"

int	is_empty_prompt(char *res)
{
	int	i;

	i = 0;
	if (res[0] == '\0')
		return (1);
	while (res[i] != '\0')
	{
		if (res[i] != ' ' && res[i] > 13)
			return (-1);
		i++;
	}
	return (1);
}

t_pipe	*pipe_handler(t_pipe *pipes, char *res, t_env *env, t_collector *gc)
{
	int	f;

	f = 0;
	if (res == NULL)
		return (NULL);
	pipes = ft_split_node(res, gc);
	gc->pipes = garbage_pipe(gc->pipes, pipes);
	pipes = trim_all(pipes, gc);
	if (check(pipes) == -1)
	{
		free_pipe(gc->pipes);
		gc->pipes = NULL;
		return (NULL);
	}
	f = fake_herdoc(pipes);
	if (f == -1)
	{
		free_pipe(gc->pipes);
		gc->pipes = NULL;
		return (NULL);
	}
	herdoc_counter(pipes, gc);
	pipes = primary_expand(pipes, env, gc);
	return (pipes);
}

char	*lexer_handle(char *res, t_collector *gc)
{
	res = ft_trim(res, ' ');
	gc->str = garbage_str(gc->str, res, gc);
	gc = gc->next;
	if (is_qoute_error(res) == -1 || is_pipe_error(res) == -1)
		return (NULL);
	return (res);
}

t_list_p	*lexer(t_env *env, t_collector *gc)
{
	t_list_p	*list;
	t_pipe		*pipes;
	char		*res;

	setup_prompt_signals();
	(1) && (pipes = NULL, res = readline("minishell> "));
	if (g_signal)
		ft_stat(1);
	if (!res)
		return (printf("exit\n"), free_all(gc, ft_stat(-1)), NULL);
	if (is_empty_prompt(res) == 1)
		return (free(res), NULL);
	add_history(res);
	if (ft_stat(-1) == -1)
		free_all(gc, ft_stat(0));
	gc->str = garbage_str(gc->str, res, gc);
	res = lexer_handle(res, gc);
	pipes = pipe_handler(pipes, res, env, gc);
	if (pipes == NULL)
		return (NULL);
	list = store_value(pipes, env, gc);
	if (g_signal == 2)
		close_all_files();
	return (list);
}
