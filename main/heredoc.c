/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:17:03 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/02 11:35:45 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_read(t_ms *ms, char *file, int fd[2])
{
	char	*line;
	char	*filewq;

	filewq = ft_q_r(file);
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
		{
			//printf("my line is %s\n", line);
			//printf ("%d|%d|%d|%d\n", (int)ft_strlen(line),(int)ft_strlen(filewq), ft_strncmp(line, filewq, ft_strlen(filewq)), ft_strchrn(line, '$'));
			if (ft_strlen(line) == ft_strlen(filewq)
				&& ft_strncmp(line, filewq, ft_strlen(filewq)) == 0)
			{
				free(line);
				free_tok(ms->start);
				close(fd[0]);
				close(fd[1]);
				exit(0);
			}
			if (ft_strlen(file) == ft_strlen(filewq)
				&& ft_strchrn(line, '$') != -1)
				ft_putstr_fd(ft_expand(ms, line), fd[1]);
			else
				ft_putstr_fd(line, fd[1]);
			ft_putchar_fd('\n', fd[1]);
			free(line);
		}
	}
}

int	heredoc_execute(t_ms *ms, char *file)
{
	int	pid;
	int	fd[2];
	int	proces_status;

	//**YA NO NECESITO G_PROCESS
	//g_process = 2;
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
	{
		signal(SIGINT, handle_siginth); //handle_siginth
		heredoc_read(ms, file, fd);
		free_tok(ms->start);
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	/// this is for know the exit code, if 1 i change process to 1 and cancel executions
	//if 0 we continue with heredoc and executions
	waitpid(pid, &proces_status, 0);
	if (WIFEXITED(proces_status) && WEXITSTATUS(proces_status) == 1)
			g_process = 1;
	ms->exitstatus = g_process;
	close(fd[1]);
	//printf("I finished and i am returning %d\n", fd[0]);
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
		//printf("token is %s and type is %d\n", token->content, token->type);
		if (token->type == 3)
		{
			if (fd && fd != -2)
				close(fd);
			//printf("token is %s and type is %d\n", token->next->content, token->type);
			fd = heredoc_execute(ms, token->next->content);
			token = token->next;
			//no me va bien en la ejecucion del control D y control C
		}
		if (token)
			token = token->next;
	}
	return (fd);
}
