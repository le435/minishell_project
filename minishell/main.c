
#include "parse.h"

int	g_signal;

void	init_gc(t_collector *gc)
{
	rl_catch_signals = 0;
	g_signal = 0;
	gc->env = NULL;
	gc->pipes = NULL;
	gc->str = NULL;
	gc->list = NULL;
	gc->col = NULL;
}

int	ft_wrd_sz(t_word *lst)
{
	int		count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	statement(t_collector	*gc, t_env	*tmp)
{
	struct termios	term;
	t_gc			*gc_list;
	t_list_p		*list;

	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		list = lexer(tmp, gc);
		if (list == NULL)
			continue ;
		list->term = &term;
		gc_list = NULL;
		list->term = NULL;
		execution(list, &tmp, &gc_list);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		if (gc_list)
			gc_free_all(&gc_list);
	}
}
void	f()
{
	system("leaks minishell");
}
int	main(int ac, char **av, char **envp)
{
	atexit(f);
	t_collector		*gc;
	t_env			*tmp;
	t_env			*nvm;

	(void) ac;
	(void) av;
	gc = malloc(sizeof(t_collector));
	if (gc == NULL)
		return (-1);
	init_gc(gc);
	tmp = init_env(envp);
	if (!tmp)
		return (free(gc), -1);
	nvm = malloc(sizeof(t_env));
	if (nvm == NULL)
		return (free_env(tmp), 1);
	nvm->key = empty_toke();
	nvm->value = NULL;
	nvm->pwd = my_getenv(envp, "PWD");
	nvm->next = tmp;
	tmp = nvm;
	gc->env = tmp;
	statement(gc, tmp);
	return (0);
}
