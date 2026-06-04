
#include "../parse.h"

char	*empty_toke(void)
{
	char	*s;

	s = malloc(2);
	if (s == NULL)
		return (NULL);
	s[0] = 16;
	s[1] = '\0';
	return (s);
}

int	are_not_near(char *s, int i)
{
	if (i == 0)
		return (1);
	if (((s[i - 1] == '\'' || s[i - 1] == '\"')
			&& (s[i + 1] == '\"' || s[i + 1] == '\''))
		|| (s[i + 1] == ' ' || s[i + 1] == '\t'
			|| s[i + 1] == '\n' || s[i + 1] == '\0'))
		return (0);
	return (1);
}

int	not_allowed(char c)
{
	if (c != '\'' && c != '\"' && c != '=' && c > 13 && c != '`')
		return (1);
	return (-1);
}

char	*expand(char *str, int i, t_env *env, t_collector *gc)
{
	char	*new;
	char	*temp;
	int		end;

	end = i;
	while (str[end] && ((str[end] >= 'a' && str[end] <= 'z')
			|| (str[end] >= 'A' && str[end] <= 'Z')))
		end++;
	if (i == end)
		return (ft_strdup("\0"));
	if (str[end] <= '9' && str[end] >= '0')
		return (ft_strdup("\0"));
	temp = ft_copy_l(str, i, end);
	gc->str = garbage_str(gc->str, temp, gc);
	while (env && env->key != NULL
		&& ft_strcmp(temp, env->key) != 0)
		env = env->next;
	if (!env)
		return (ft_strdup("\0"));
	new = ft_strdup(env->value);
	gc->str = garbage_str(gc->str, new, gc);
	if (new == NULL)
		return (free_all(gc, 1), NULL);
	return (new);
}

char	*expand_herdoc(char *str, int i, t_env *env)
{
	char	*new;
	char	*temp;
	int		end;

	end = i;
	while (str[end] && ((str[end] >= 'a' && str[end] <= 'z')
			|| (str[end] >= 'A' && str[end] <= 'Z')))
		end++;
	if (i == end)
		return (ft_strdup("\0"));
	temp = ft_copy_l(str, i, end);
	if (temp == NULL)
		return (NULL);
	while (env && env->key != NULL
		&& ft_strcmp(temp, env->key) != 0)
		env = env->next;
	free(temp);
	if (!env || env->value[0] == '\0')
		return (ft_strdup("\0"));
	new = ft_strdup(env->value);
	if (new == NULL)
		return (NULL);
	return (new);
}
