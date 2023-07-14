/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:33:19 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/14 20:06:07 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isbuiltin(char *com)
{
	if ((!ft_strncmp(com, "echo", 4) && ft_strlen(com) == 4)
	  || (!ft_strncmp(com, "cd", 2) && ft_strlen(com) == 2)
	  || (!ft_strncmp(com, "pwd", 3) && ft_strlen(com) == 3)
	  || (!ft_strncmp(com, "export", 6) && ft_strlen(com) == 6)
	  || (!ft_strncmp(com, "unset", 5) && ft_strlen(com) == 5)
	  || (!ft_strncmp(com, "env", 3) && ft_strlen(com) == 3)
	  || (!ft_strncmp(com, "exit", 4) && ft_strlen(com) == 4)
	  )
		return (1);
	return(0);
}

void ft_exe_buitin(t_env *env,char **com)
{
	if (!ft_strncmp(com[0], "echo", 4))
		b_echo(com);
	if (!ft_strncmp(com[0], "cd", 2))
		cd(env, com);
	if (!ft_strncmp(com[0], "pwd", 3))  //GREAT !!!
		pwd(env);
	if (!ft_strncmp(com[0], "export", 6))
		export(env, com);
	if (!ft_strncmp(com[0], "unset", 5))
		;
	if (!ft_strncmp(com[0], "env", 3))  // OLDPWD= ? , its the order ok?
		print_env(env);
	if (!ft_strncmp(com[0], "exit", 4))
		;
	//return (1);
}

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
	printf("Isbultin %s: %d \n", ms->exe->command[0], ft_isbuiltin(ms->exe->command[0]));
	if(ms->exe->next == NULL && ft_isbuiltin(ms->exe->command[0]))
	{
		ft_exe_buitin(ms->env, ms->exe->command);
		//if (ms->exe->fd[0])
		//	close(ms->exe->fd[0]);
		//if (ms->exe->fd[1] )
		//	close(ms->exe->fd[1]);
	}
	else
		ft_singlecommand(ms, env);
		//pipe
}
