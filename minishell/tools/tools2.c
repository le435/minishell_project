
#include "../parse.h"

void	put_error(char *s1, char s2, char *s3)
{
	if (s1 != NULL)
		ft_putstr_fd(s1, 2);
	if (s2 != '\0')
		write(2, &s2, 1);
	if (s3 != NULL)
		ft_putstr_fd(s3, 2);
}

t_word	*null_termenate_word(t_word *word, t_collector *gc)
{
	word->cmd = ft_strdup("\0");
	if (word->cmd == NULL)
		return (NULL);
	gc->str = garbage_str(gc->str, word->cmd, gc);
	return (word);
}
