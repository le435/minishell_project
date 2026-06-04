
#ifndef PARSE_H
# define PARSE_H
# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include <readline/readline.h>
# include "src/minishell.h"
# include "stdbool.h"
# include "libft/libft.h"
# include "termios.h"

# define TRICK 1
# define PIPE 1
# define PICE 2
# define ENV 3

char		*remove_herdoc_qouth(char *str);
char		*return_expand(char *str, int *i, t_env *env, t_collector *gc);
char		*expand_operation(char *str, int i, t_env *env, t_collector *gc);
int			is_single_qouth(char *end);
int			are_not_near(char *s, int i);
char		*create_acess(void);
char		*empty_string(t_collector *gc);
int			increment_re_string(char *str, int i);
char		*re_string(char	*str, char *new, int i);
char		*herdoc_expander(t_her her, char *str, t_env *env);
void		herdoc_counter(t_pipe *pipes, t_collector *gc);
int			fake_herdoc(t_pipe *pipes);
char		*return_string(char *new, char *str, int i, int len);
int			count_new_len(char *str, int i);
void		free_env_list(t_env *env);
void		free_rest(t_collector *gc);
void		ft_sign(void);
int			ft_stat(int status);
void		init_signals(void);
char		*ft_trim(char *s, char c);
char		*ft_copy_l(char *str, int start, int end);
char		*c_join(char *str, char c);
char		*ft_copy_s(char *new, char *str, t_collector *gc);
char		*expand(char *str, int i, t_env *env, t_collector *gc);
char		*join_three(char *left, char *midle, char *right);
char		*files_string(char *str, t_collector *gc);
char		*expand_word(char *str, t_env *env, t_collector *gc);
char		*redirections(char *str, t_collector *gc);
t_word		*null_termenate_word(t_word *word, t_collector *gc);
void		free_all(t_collector *gc, int ex);
t_pipe		*garbage_pipe(t_pipe *ptr, t_pipe *val);
t_files		*garbage_files(t_files *ptr, t_files *val);
t_word		*garbage_word(t_word *ptr, t_word *val);
t_str		*garbage_str(t_str	*str, char *val, t_collector *gc);
t_list_p	*garbage_list_p(t_list_p *list, t_list_p *val);
void		free_list_p(t_list_p *list);
void		free_env(t_env	*ptr);
void		free_pipe(t_pipe *ptr);
void		free_file(t_files *ptr);
int			check_nighboor(char *str);
int			dollars(char *str);
void		free_words(t_word *ptr);
void		free_str(t_str	*ptr);
int			not_allowed(char c);
void		free_list_p(t_list_p *list);
t_word		*garbage_word(t_word *ptr, t_word *val);
t_files		*garbage_files(t_files *ptr, t_files *val);
t_pipe		*ft_split_node(char *res, t_collector *gc);
t_pipe		*trim_all(t_pipe *pipes, t_collector *gc);
t_word		*all_words(char *str, t_env *env, t_collector *gc);
char		*all_words_allocation(char *str, t_collector *gc);
t_list_p	*store_value(t_pipe *pipes, t_env *env, t_collector *gc);
t_files		*alloc_files(char *str, t_collector *gc);
t_files		*all_files(char *str, int j, t_collector *gc);
t_list_p	*lexer(t_env *env, t_collector *gc);
t_pipe		*primary_expand(t_pipe *pipes, t_env *env, t_collector *gc);
t_files		*expand_files(t_files *file, t_env *env, t_collector *gc);
t_files		*remove_qouth_from_file(t_files *file, t_collector *gc);
t_word		*remove_qouth_from_cmd(t_word *words, t_collector *gc);
t_list_c	*garbage_list_c(t_list_c *dest, t_word *word,
				t_files *files, t_collector *gc);
char		*expand_herdoc(char *str, int i, t_env *env);
int			skip_element(char *res, char c, int i, int f);
char		*empty_toke(void);
int			word(char *s);
char		is_inside_qouth(char c1, char c2);
int			count_helper(char *str, int i);
int			count_words_for_struct(char *str);
int			check(t_pipe *pipes);
int			search(char *str, int i, int f);
int			is_alphabet(char c);
int			skip_qouth(char c, char *str, int i);
int			is_alnum(char c);
int			index_counter(char *str, int i, char c);
int			skip_word(char *s);
int			herdoc_part(char *end, t_env *env);
void		put_error(char *s1, char s2, char *s3);
int			is_pipe_error(char *res);
int			dollars(char *str);
int			is_qoute_error(char *res);
char		*add_fake_qauth(char *src, t_collector *gc);
char		*create_new_qauth(char *str, char c, char q, t_collector *gc);
char		*replace_index_with_new(char *new,
				char *old, int i, t_collector *gc);
char		*basic_trim(char *str, t_collector *gc);
#endif