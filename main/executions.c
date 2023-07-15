/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:33:19 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/15 21:54:20 by mmoramov         ###   ########.fr       */
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
	printf("Executing builtin\n");
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

int ft_cmds_count(t_ex *lst)
{
	int	len;

	len = 1;
	while (lst && lst -> next)
	{
		len++;
		lst = lst -> next;
	}
	printf("We have %d commands\n", len);
	return (len);
}

/*void ft_close_pipes(int *pipes, int level)
{
	int	i;

	//int pipes[k-1][2];  //i dont know how to send this from input because is dynamic

	i = 0;
	while (i < level-1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}*/

int	ft_generalcommand(t_ms *ms,char **env)
{
	int	i;
	int	l;
	int k;
	t_ex	*com;

	com = ms->exe;
	i = ft_cmds_count(ms->exe); //count the commands

	int pipes[i-1][2];
	int pids[i];

	l = 0;
	while (l < i - 1)
	{
		printf("Opening pipe [%d]\n", l);
		if (pipe(pipes[l]) == -1)
			ft_exit(errno, strerror(errno), NULL);
		l++;
	}

	l = 0;
	while (l < i)
	{
		pids[l] = fork();
		if (pids[l] == -1)
			ft_exit(errno, strerror(errno), NULL);
		if (pids[l] == 0) //child l
		{
			printf("I am in pid[%d] (child %d)\n", l, l+1);  //child 1 is pid[0]
			printf("-------------------Command %s %s\n",com->command[0], com->command[1]);

			if (i > 1 && l > 0)
			{
				printf("------------------------------i = %d, l=%d , dup2 stdin pipe[%d][0]\n", i, l, l-1);
				dup2(pipes[l-1][0], STDIN_FILENO);
			}

			if (i > 1 && l < i-1)
			{
				printf("-------------------------------i = %d, l=%d , dup2 stdout pipe[%d][1]\n", i, l, l);
				dup2(pipes[l][1], STDOUT_FILENO);
			}

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

			k = 0;
			while (k < i-1)
			{
				close(pipes[k][0]);
				close(pipes[k][1]);
				k++;
			}

			//if (ft_isbuiltin(com->command[0])) //TODO
			//	ft_exe_buitin(ms->env, com->command);
			//else
				ft_execve_prepare(ms, env, com->command);
			return (0);
		}

		if (com->next)
			com = com->next;
		l++;
	}


	//parent
	k = 0;
	while (k < i-1)
	{
		printf("Closing pipes[%d]\n", k);
		close(pipes[k][0]);
		close(pipes[k][1]);
			k++;
	}

	k = 0;
	while (k < i)
	{
		printf("waiting for pids[%d]\n", k);
		waitpid(pids[k], NULL, 0);
		k++;
	}
	return (0);
}

void	ft_execute(t_ms	*ms, char **env)
{
	printf("Isbultin %s: %d \n", ms->exe->command[0], ft_isbuiltin(ms->exe->command[0]));
	ft_generalcommand(ms, env);
}
