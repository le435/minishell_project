
#include "../minishell.h"

void	join_existing_value(char *str, t_env *new)
{
	char	*equal_sign;
	char	*value_part;
	char	*joined;

	equal_sign = ft_strchr(str, '=');
	value_part = ft_strdup(equal_sign + 1);
	joined = ft_strjoin(new->value, value_part);
	free(value_part);
	free(new->value);
	new->value = joined;
}

void	value_join(char **sp, char *str, t_env *new, t_env **env)
{
	char	*key;
	char	*value;

	key = ft_substr(sp[0], 0, ft_strlen(sp[0]) - 1);
	if (compare_var(key, *env))
	{
		new = compare_var(key, *env);
		free(key);
		if (!new->value)
			new->value = ft_strdup(ft_strchr(str, '='));
		else
			join_existing_value(str, new);
		return ;
	}
	value = ft_strdup(ft_strchr(str, '=') + 1);
	new = lstnew_env(ft_strdup(key), value);
	free(value);
	add_back_env(env, new);
	free(key);
}
