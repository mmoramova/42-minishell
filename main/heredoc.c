/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:17:03 by mmoramov          #+#    #+#             */
/*   Updated: 2023/08/23 17:29:21 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_read(t_ms *ms, char *file, int fd[2])
{
	char	*line;
	char	*filewq;

	filewq = ft_quotes_remove(file);
	while (42)
	{

		//start for tester
		if (isatty(fileno(stdin)))
		line = readline("> ");
		else
		{
			char *line2;
			line2 = get_next_line(fileno(stdin));
			line = ft_strtrim(line2, "\n");
			free(line2);
		}
		//end for tester, uncomment line below
		//line = readline("> ");
		if (!line)
		{
			rl_replace_line("", 0);
			exit(0);
		}
		if (line)
		{
			if (ft_strlen(line) == ft_strlen(filewq)
				&& ft_strncmp(line, filewq, ft_strlen(filewq)) == 0)
			{
				free(line);
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
		ft_error(ms, errno, strerror(errno), NULL, NULL);
	pid = fork();
	if (pid == -1)
		ft_error(ms, errno, strerror(errno), NULL, NULL);
	if (pid == 0)
	{
		signal(SIGINT, handle_siginth); //handle_siginth
		heredoc_read(ms, file, fd);
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	/// this is for know the exit code, if 1 i change process to 1 and cancel executions
	//if 0 we continue with heredoc and executions
	waitpid(pid, &proces_status, 0);
	if (WIFEXITED(proces_status))
	{
		if (WEXITSTATUS(proces_status) == 1)
			g_process = 1;
	}
	ms->exitstatus = g_process;
	return (fd[0]);
}

int	heredoc_fillfd(t_ms *ms, t_tok *tokens)
{
	int		fd;
	t_tok	*token;

	token = tokens;
	while (token && g_process != 1)
	{
		if (token->type == 3)
		{
			if (fd)
				close(fd);
			fd = heredoc_execute(ms, token->next->content);
			token = token->next;
			if (fd == -1)
			//no me va bien en la ejecucion del control D y control C
				ft_error(ms, errno, token->next->content, strerror(errno), NULL);
		}
		if (token)
			token = token->next;
	}
	return (fd);
}
