/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:24:26 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/05 18:25:29 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**handle_pipes(t_ms *ms)
{
	int		**pipes;
	int		l;

	l = 0;
	pipes = malloc(sizeof(int *) * ms->cntcmds);
	if (!pipes)
		return ((int **)0);
	while (l < ms->cntcmds - 1)
	{
		pipes[l++] = malloc(sizeof(int) * 2);
		if (!pipes)
		{
			free_doubleint(pipes);
			return ((int **)0);
		}
	}
	pipes[l] = NULL;
	l = 0;
	while (l < ms->cntcmds - 1)
	{
		if (pipe(pipes[l]) == -1)
			ft_error(ms, errno, strerror(errno), NULL);
		l++;
	}
	return (pipes);
}

void	close_pipes(int **pipes)
{
	int	i;

	i = -1;
	while (pipes[++i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);
}

void	handle_waitpid(t_ms *ms, int is_parent)
{
	int		i;
	int		status;
	int		*pids;

	i = 0;
	pids = ms->pids;
	while (pids[i] && pids[i + 1])
		waitpid(pids[i++], NULL, 0);
	waitpid(pids[i], &status, 0);
	if (is_parent == 0 && WIFEXITED(status))
		ms->exitstatus = WEXITSTATUS(status);
	else if (is_parent == 0 && WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ms->exitstatus = 130;
			printf("^C\n");
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ms->exitstatus = 131;
			printf("^\\Quit 3\n");
		}
	}
}

void	handle_redirections(t_ms *ms, int fd[2], int lvl)
{
	if (ms->pipes && lvl > 0)
		dup2(ms->pipes[lvl - 1][0], STDIN_FILENO);
	if (ms->pipes && lvl < ms->cntcmds - 1)
		dup2(ms->pipes[lvl][1], STDOUT_FILENO);
	if (ft_fd_isopen(fd[0]))
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (ft_fd_isopen(fd[1]))
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

void	handle_child(t_ms *ms, t_ex *com, int i)
{
	signal(SIGINT, handle_sigintp);
	signal(SIGQUIT, handle_sigintp);
	handle_redirections(ms, com->fd, i);
	close_pipes(ms->pipes);
	if (com->fd[0] == -1 || com->fd[1] == -1)
		free_ex_exit(ms, 1);
	if (is_builtin(com->command[0]) && com->parent == 0)
		free_ex_exit(ms,
			execute_builtin(ms, com->command, com->parent));
	else if (is_builtin(com->command[0]) && com->parent == 1)
		free_ex_exit(ms, 0);
	else if (com->command)
		execve_prepare(ms, com->command);
	free_ex_exit(ms, 0);
}
