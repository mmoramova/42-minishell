/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:17:03 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/05 19:05:49 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_checkline(t_ms *ms, char *file, int fd[2], char *line)
{
	char	*filewq;
	char	*aux;

	filewq = ft_q_r(file);
	if (ft_strlen(line) == ft_strlen(filewq)
		&& ft_strncmp(line, filewq, ft_strlen(filewq)) == 0)
	{
		free(filewq);
		free(line);
		free_tok(ms->start);
		(0 || close(fd[0]) || close(fd[1]));
		exit(0);
	}
	if (ft_strlen(file) == ft_strlen(filewq)
		&& ft_strchrn(line, '$') != -1)
	{
		aux = ft_expand(ms, line);
		ft_putstr_fd(aux, fd[1]);
		free(aux);
	}
	else
		ft_putstr_fd(line, fd[1]);
	ft_putchar_fd('\n', fd[1]);
	free(filewq);
	free(line);
}

void	heredoc_read(t_ms *ms, char *file, int fd[2])
{
	char	*line;

	signal(SIGINT, handle_siginth);
	while (42)
	{
		line = readline("> ");
		if (!line)
		{
			rl_replace_line("", 0);
			free_tok(ms->start);
			exit(0);
		}
		if (line)
			heredoc_checkline(ms, file, fd, line);
	}
	free_tok(ms->start);
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

int	heredoc_execute(t_ms *ms, char *file)
{
	int	pid;
	int	fd[2];
	int	proces_status;

	if (pipe(fd) == -1)
	{
		ft_error(ms, errno, strerror(errno), NULL);
		return (-2);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_error(ms, errno, strerror(errno), NULL);
		return (-2);
	}
	if (pid == 0)
		heredoc_read(ms, file, fd);
	waitpid(pid, &proces_status, 0);
	if (WIFEXITED(proces_status) && WEXITSTATUS(proces_status) == 1)
		g_process = 1;
	ms->exitstatus = g_process;
	close(fd[1]);
	return (fd[0]);
}

int	heredoc_fillfd(t_ms *ms, t_tok *tokens)
{
	int		fd;
	t_tok	*token;

	token = tokens;
	fd = -2;
	while (token && g_process != 1)
	{
		if (token->type == 3)
		{
			if (fd && fd != -2)
				close(fd);
			fd = heredoc_execute(ms, token->next->content);
			token = token->next;
		}
		if (token)
			token = token->next;
	}
	return (fd);
}
