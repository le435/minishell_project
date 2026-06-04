
#include "../minishell.h"

int	redirect(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		close(oldfd);
		ft_stat(1);
		return (-1);
	}
	close(oldfd);
	return (0);
}

int	redir_in_out(int flag, int fd, t_files *file)
{
	if (flag == 1)
	{
		fd = open(file->name, O_RDONLY);
		if (fd == -1)
			return (perror(file->name), -1);
		if (redirect(fd, STDIN_FILENO) == -1)
			return (-1);
	}
	else if (flag == 2)
	{
		fd = open(file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(file->name), -1);
		if (redirect(fd, STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (flag == 3)
	{
		fd = open(file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (perror(file->name), -1);
		if (redirect(fd, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	red_to(t_files *file, int fd)
{
	int	i;

	i = 0;
	if (file->type == REDIR_IN)
		i = redir_in_out(1, fd, file);
	else if (file->type == REDIR_OUT)
		i = redir_in_out(2, fd, file);
	else if (file->type == REDIR_APPEND)
		i = redir_in_out(3, fd, file);
	return (i);
}

int	hand_red(t_files *file)
{
	int	fd;
	int	i;

	(1) && (i = 0, fd = 0);
	if (!file)
		return (0);
	while (file && i == 0)
	{
		if (file->type == HEREDOC)
		{
			if (redirect(file->heredoc_fd, STDIN_FILENO) == -1)
				return (-1);
		}
		else if (file->flag == 0)
		{
			i = red_to(file, fd);
		}
		else
			return (write(2, " : ambiguous redirect\n", 23), ft_stat(1), -2);
		file = file->next;
	}
	return (i);
}

void	open_pre(t_list_p *p)
{
	t_list_p	*c;
	t_files		*wlk;
	int			fd;

	if (p == NULL || p->file == NULL)
		return ;
	c = p;
	while (c)
	{
		wlk = c->file;
		while (wlk)
		{
			if (wlk->flag == 0 && wlk->type != HEREDOC)
				fd = red_to(wlk, fd);
			else if (wlk->flag == 1 && wlk->type != HEREDOC)
			{
				write(2, " : ambiguous redirect\n", 23);
				return ;
			}
			if (wlk)
				wlk = wlk->next;
		}
		c = c->next;
	}
}
