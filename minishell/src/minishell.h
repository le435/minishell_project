
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h> 
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>
# include <sys/stat.h>
# include <limits.h>
# include <string.h>
# include "termios.h"
# include <sys/ioctl.h>
# include <errno.h>
# include "dirent.h"

extern int	g_signal;
typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;
typedef struct s_env
{
	char			*key;
	char			*value;
	char 			*pwd;
	struct s_env	*next;
}	t_env;

typedef enum e_token_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_pipe
{
	char			*str;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_str
{
	char			*val;
	struct s_str	*next;
}	t_str;

typedef struct s_word
{
	char			*cmd;
	t_token_type	*redirec;
	int				f;
	struct s_word	*next;
}	t_word;

typedef struct s_files
{
	char			*name;
	t_token_type	type;
	int				flag;
	int				f;
	struct s_files	*next;
	int				heredoc_fd;
}	t_files;

typedef struct s_list_p
{
	t_word			*words;
	t_files			*file;
	int				*fds;
	struct termios	*term;
	struct s_list_p	*next;
}	t_list_p;

typedef struct s_fd
{
	int		fd_in;
	int		fd_out;
}	t_fd;
typedef struct s_list_c
{
	t_word			*words;
	t_files			*file;
	struct s_list_c	*next;
}	t_list_c;
typedef struct s_expdata
{
	char	**cmd;
	char	**split;
	int		i;
}	t_expdata;
typedef struct s_collector
{
	t_str				*str;
	t_pipe				*pipes;
	t_env				*env;
	t_list_p			*list;
	t_list_c			*col;
	int					f;
	struct s_collector	*next;
}	t_collector;

typedef struct s_pipe_g
{
	int	input_fd;
	int	current_pipe[2];
	int	previous_pipe[2];
}	t_pipe_g;

typedef struct s_exec_data
{
	char	**env;
	t_env	**tenv;
	t_gc	**gc_list;
	char	*cmd;
}	t_exec_data;

typedef struct s_exec_env
{
	char	**env;
	t_env	**tenv;
}	t_exec_env;

typedef struct s_save_std
{
	int	in;
	int	out;
}	t_save_std;

typedef struct s_execution_data
{
	int			exit_code;
	int			i;
	int			child_count;
	int			status;
	int			*pids;
	t_exec_env	xenv;
	t_fd		fds;
}	t_execution_data;
typedef struct s_cd_str
{
	char	*new_dir;
	char	*path;
	int		flag;
	t_env	*pwd;
	int		chdir;
	char	*current_dir;
}	t_cd;

typedef struct s_her
{
	char	*line;
	int		saved_stdin;
	int		f;
	int		ret;
}	t_her;
int		ft_close_descriptors(t_list_p *gc);
t_env	*lstnew_env(char *key, char *value);
char	**updated_env_exe(t_env **envp);
void	msg_er(char *argv, char *msg);
t_env	*handl_env(char **envp, t_env *head, t_env *new, t_env *tmp);
t_env	*creat_env(char *key, char *value);
int		red_to(t_files *file, int fd);
void	update_env(t_env **env, const char *key, const char *new_value);
void	ft_sign(void);

void	handle_sigint_prompt(int sig);
int		ft_stat(int status);
int		redirect(int oldfd, int newfd);

t_env	*ft_check_var(char *str, t_env *env);
t_env	*find_key(char *key, t_env *env);
t_env	*init_env(char **envp);
void	setup_exec_signals(void);
void	execution(t_list_p *list, t_env **tenv, t_gc **g_list);
void	setup_prompt_signals(void);
int		ft_status_signals(int status, t_list_p *p);
void	cleanup_and_exit(t_pipe_g p, int status);
void	*gc_malloc(size_t size, t_gc **gc_list);
void	gc_add(void *ptr, t_gc **gc_list);
void	gc_free_all(t_gc **gc_list);
int		ft_export(char **cmd, t_env **env);
void	ft_swap(char **val1, char **val2);
int		valid_format(char *str);
void	free_env(t_env *env);
void	ft_free_split(char **str);
int		is_builtin(char *cmd);
void	value_join(char **sp, char *str, t_env *new, t_env **env);
void	ft_cd(char **cmd, t_env **env, int *stat);
void	ft_update(char *str, t_env *env, t_env *new, char **s);
void	get_cmd_and_exec(t_pipe_g p, char **argv, t_exec_env xenv,
			t_gc **gc_list);
int		ft_echo(char **args);
int		ft_env(t_env **env);
int		ft_exit(char **cmd, int i);
int		ft_export(char **cmd, t_env **env);
int		ft_pwd();
int		ft_unset(t_env **env, char **cmd);
t_env	*compare_var(char *str, t_env *env);
void	add_back_env(t_env **lst, t_env *new);
void	handl_cases(t_env **env, t_expdata data, t_env *new);
long long	run_childrens(t_list_p *list,
	t_exec_env xenv, t_gc **gc_list);
int		hand_red(t_files *file);
void	open_pre(t_list_p *p);
int		redirect(int oldfd, int newfd);
char	*get_cmd(char *cmd, t_env *env, t_gc **gc_list);
pid_t	mid_child(t_pipe_g p, t_list_p *node,
			t_exec_env *xenv, t_gc **gc_list);
pid_t	ft_last_child(t_pipe_g p, t_list_p *node,
			t_exec_env *xenv, t_gc **gc_list);
pid_t	ft_first_child(t_pipe_g p, t_list_p *list,
			t_exec_env *xenv, t_gc **gc_list);
void	ft_perror(char *str);
int		redirect(int oldfd, int newfd);
char	**get_cmd_args(t_word *words, t_gc **gc_list);
void	close_fd(int fd[2]);
int		exec_builtin(char **token, t_env **env, int i);
char	*find_path(t_env *env);
void	ft_perror(char *str);
int		herdoc_part(char *end, t_env *env);
void	ft_retreiv_or_upt(t_env **env, t_env *pwd);
void	close_all_files(void);
int		ft_bltin_no_frk(t_list_p *list, char **argv, t_exec_env *xenv);
void	h_doc_handler(int signum);
char	*my_getenv(char **env, char *key);

#endif