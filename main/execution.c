/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:33:19 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/05 18:25:43 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd && ((!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
			|| (!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
			|| (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
			|| (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
			|| (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
			|| (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
			|| (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)))
		return (1);
	return (0);
}

int	execute_builtin(t_ms *ms, char **cmd, int parent)
{
	if (!ft_strncmp(cmd[0], "echo", 4))
		return (b_echo(cmd));
	if (!ft_strncmp(cmd[0], "cd", 2))
		return (cd(ms, cmd));
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return (pwd(ms->env));
	if (!ft_strncmp(cmd[0], "export", 6))
		return (export(ms, cmd));
	if (!ft_strncmp(cmd[0], "unset", 5))
		return (unset(ms, cmd));
	if (!ft_strncmp(cmd[0], "env", 3) && cmd[1] == NULL)
		return (enviroment(ms->env));
	if (!ft_strncmp(cmd[0], "exit", 4))
		return (b_exit(ms, cmd, parent));
	ms->exitstatus = 1;
	return (ft_error4(1, cmd[0], cmd[1], "not a valid option"));
}

int	execute_builtin_inparent(t_ms *ms, t_ex *com)
{
	if (!com -> next)
	{
		ms->exitstatus = execute_builtin(ms, com->command, com->parent);
		return (1);
	}
	else
		execute_builtin(ms, com->command, com->parent);
	return (0);
}

int	handle_forks(t_ms *ms)
{
	int		i;
	t_ex	*com;

	i = 0;
	com = ms->exe;
	while (i < ms->cntcmds)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		ms->pids[i] = fork();
		if (ms->pids[i] == -1)
			ft_error(ms, errno, strerror(errno), NULL);
		if (ms->pids[i] == 0)
			handle_child(ms, com, i);
		if (ft_fd_isopen(com->fd[0]))
			close(com->fd[0]);
		if (ft_fd_isopen(com->fd[1]))
			close(com->fd[1]);
		if (is_builtin(com->command[0]) && com->parent == 1
			&& execute_builtin_inparent(ms, com))
			return (1);
		com = com->next;
		i++;
	}
	return (0);
}

void	execute_cmds(t_ms *ms)
{
	int	is_parent;

	if (g_process == 1)
		return ;
	ms->pipes = handle_pipes(ms);
	ms->pids = malloc(sizeof(int) * (ms->cntcmds + 1));
	if (!ms->pids)
		return ;
	ms->pids[ms->cntcmds] = '\0';
	is_parent = handle_forks(ms);
	close_pipes(ms->pipes);
	handle_waitpid(ms, is_parent);
	if (ms->pids != NULL)
		free(ms->pids);
	if (ms->exe != NULL)
		free_ex(ms->exe);
	g_process = 0;
}
