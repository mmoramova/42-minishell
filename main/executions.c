/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:33:19 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/13 19:37:00 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_singlecommand(t_ms *ms,char **env)
{
	if (ms->exe->fd[0])
	{
		dup2(ms->exe->fd[0] ,STDIN_FILENO);
		close(ms->exe->fd[0]);
	}
	if (ms->exe->fd[1] )
	{
		dup2(ms->exe->fd[1] ,STDOUT_FILENO);
		close(ms->exe->fd[1]);
	}

	ft_execve_prepare(ms, env);
}

void	ft_execute(t_ms	*ms, char **env)
{
	if(ms->exe->next == NULL)
		ft_singlecommand(ms, env);
	else
		; //pipe
}
