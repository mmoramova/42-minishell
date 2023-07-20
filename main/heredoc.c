/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:17:03 by mmoramov          #+#    #+#             */
/*   Updated: 2023/07/18 18:11:21 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_read(t_ms *ms, char *file, int fd[2])
{
	char	*line;
	int		expand;
	char	*filewq;

	filewq = ft_quotes_remove(file);
	expand = 0;
	if (ft_strlen(file) == ft_strlen(filewq))
			expand = 1;
	while(42)
	{
		line = readline("> ");
		if (line)
		{
			if (ft_strlen(line) == ft_strlen(filewq)
				&& ft_strncmp(line, filewq, ft_strlen(filewq)) == 0)
			{
				free(line);
				exit(0);
			}
			if (expand == 1 && ft_strchrn (line,'$') != - 1)
				ft_putstr_fd(ft_expand(ms, line), fd[1]);
			else
				ft_putstr_fd(line, fd[1]);
			ft_putchar_fd('\n', fd[1]);
			free(line);
		}
	}
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

int	heredoc_execute(t_ms *ms, char *file)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit(errno, strerror(errno), NULL);
	pid = fork();
	if (pid == -1)
		ft_exit(errno, strerror(errno), NULL);
	if (pid == 0)
		heredoc_read(ms, file, fd);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return(fd[0]);
}

int	heredoc_fillfd(t_ms *ms, t_tok *tokens)
{
	int		fd;
	t_tok	*token;

	token = tokens;
	while (token)
	{
		if (token->type == 3)
		{
			if (fd)
				close(fd);
			fd = heredoc_execute(ms, token->next->content);
			token = token->next;
			if (fd == -1)
				ft_exit(errno, token->next->content, strerror(errno));
		}
		if (token)
			token = token->next;
	}
	return(fd);
}

