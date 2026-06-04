
#include "../parse.h"

void	free_words(t_word *ptr)
{
	t_word	*temp;

	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp);
		temp = NULL;
	}
}

void	free_file(t_files *ptr)
{
	t_files	*temp;

	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp);
		temp = NULL;
	}
}

void	free_pipe(t_pipe *ptr)
{
	t_pipe	*temp;

	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp);
		temp = NULL;
	}
}

void	free_env(t_env	*ptr)
{
	t_env	*temp;

	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp->key);
		free(temp->value);
		free(temp->pwd);
		free(temp);
		temp = NULL;
	}
}

void	free_str(t_str	*ptr)
{
	t_str	*temp;

	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp->val);
		free(temp);
		temp = NULL;
	}
}
