
#include "../parse.h"

int	skip_element(char *res, char c, int i, int f)
{
	if (f == 1)
	{
		while (res[i] && res[i] == c)
			i++;
	}
	else
	{
		while (res[i] && res[i] != c)
			i++;
	}
	return (i);
}

int	word(char *s)
{
	char	c;
	int		i;

	i = 0;
	c = '\0';
	while (s[i])
	{
		if (s[i] == '\"' && c != s[i])
			c = s[i];
		else if (s[i] == '\'' && c != s[i])
			c = s[i];
		else if (s[i] == c)
			c = '\0';
		if ((s[i] == ' ' || s[i] == '>' || s[i] == '<')
			&& (c != '\'' && c != '\"'))
			return (i);
		i++;
	}
	return (i);
}

char	is_inside_qouth(char c1, char c2)
{
	if ((c1 == '\'' || c1 == '\"') && c1 != c2)
		return (c1);
	else if ((c1 == '\"' || c1 == '\'' ) && c1 == c2)
		return ('\0');
	return (c2);
}

int	is_alnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int	is_alphabet(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (-1);
}
