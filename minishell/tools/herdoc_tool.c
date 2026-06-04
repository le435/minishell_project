
#include "../parse.h"

int	is_single_qouth(char *end)
{
	int	f;

	f = 0;
	while (end[f] && end[f] != '\'' && end[f] != '\"')
		f++;
	if (end[f] == '\'' || end[f] == '\"')
		f = 1;
	else
		f = 0;
	return (f);
}

int	increment_re_string(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\''
			|| str[i] == '=' || str[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

char	*re_string(char	*str, char *new, int i)
{
	char	*first;
	char	*last;
	char	*temp;

	if (i > 0)
		i--;
	first = ft_copy_l(str, 0, i);
	if (first == NULL)
		return (free(str), free(new), NULL);
	i++;
	temp = ft_strjoin(first, new);
	free(first);
	if (temp == NULL)
		return (free(new), free(str), NULL);
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')))
		i++;
	first = ft_strdup(&str[i]);
	if (first == NULL)
		return (free(temp), free(new), free(str), NULL);
	last = ft_strjoin(temp, first);
	free(new);
	free(temp);
	free(first);
	i = 1;
	if (last == NULL)
		return (free(str), NULL);
	return (free(str), last);
}

char	*herdoc_expander(t_her her, char *str, t_env *env)
{
	int		i;
	char	*new;

	i = 0;
	if (her.f == 1)
		return (str);
	while (str && str[i])
	{
		i = skip_element(str, '$', i, 0);
		if (str[i] && str[i] == '$' && str[i + 1] != '$' && str[i + 1])
		{
			i++;
			new = expand_herdoc(str, i, env);
			if (new == NULL)
				return (free(str), NULL);
			str = re_string(str, new, i);
			if (str == NULL || str[0] == '\0')
				break ;
		}
		else if (str[i] && str[i] == '$' && str[i + 1] == '$')
			i++;
		if (str[i] != '\0')
			i++;
	}
	return (str);
}

char	*create_acess(void)
{
	char	*name;
	char	*numbr;
	int		i;

	i = 0;
	while (1)
	{
		numbr = ft_itoa(i);
		if (numbr == NULL)
			return (NULL);
		name = ft_strjoin("@my_file@", numbr);
		free(numbr);
		numbr = NULL;
		if (name == NULL)
			return (NULL);
		if (access(name, F_OK) != 0)
			break ;
		free(name);
		name = NULL;
		i++;
	}
	return (name);
}
