/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executionsv2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:25:11 by mmoramov          #+#    #+#             */
/*   Updated: 2023/07/20 21:21:14 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*in progress, now works with one pipe*/
void	execute_secondoption(t_ms	*ms, char **env)
{
	int	pid;
	int	fd[2];
	t_ex	*com;
	int		status;
	com = ms->exe;

	if (pipe(fd) == -1)
		ft_exit(errno, strerror(errno), NULL, NULL);
	pid = fork();
	if (pid == -1)
		ft_exit(errno, strerror(errno), NULL, NULL);
	if (pid == 0)
		//heredoc_read(ms, file, fd);
	{
		printf("I am in child v1\n");
		dup2(fd[1], STDOUT_FILENO);
		if (com->fd[0])
		{
			dup2(com->fd[0] ,STDIN_FILENO);
			close(com->fd[0]);
		}
		if (com->fd[1])
		{
			dup2(com->fd[1] ,STDOUT_FILENO);
			close(com->fd[1]);
		}
		close(fd[0]);
		close(fd[1]);
		if (com->command)
			execve_prepare(ms, env, com->command);
	}

	com = com->next;
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exitstatus = WEXITSTATUS(status);
		printf("Exit status for children v2 is %d\n", g_exitstatus);
	}

	pid = fork();
	if (pid == -1)
		ft_exit(errno, strerror(errno), NULL, NULL);
	if (pid == 0)
		//heredoc_read(ms, file, fd[0]);
	{
		printf("I am in child v2\n");
		dup2(fd[0], STDIN_FILENO);
		if (com->fd[0])
		{
			dup2(com->fd[0] ,STDIN_FILENO);
			close(com->fd[0]);
		}

		if (com->fd[1])
		{
			dup2(com->fd[1] ,STDOUT_FILENO);
			close(com->fd[1]);
		}

		close(fd[0]);
		close(fd[1]);
		if (com->command)
			execve_prepare(ms, env, com->command);
	}

	close(fd[1]);
	close(fd[0]);
	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
	{
		g_exitstatus = WEXITSTATUS(status);
		printf("Exit status for children v2 is %d\n", g_exitstatus);
	}
}
