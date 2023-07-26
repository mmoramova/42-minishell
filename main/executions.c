/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:33:19 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/26 16:59:43 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd)
{
	if ((!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
	  || (!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
	  || (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
	  || (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
	  || (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
	  || (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
	  || (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
	  )
		return (1);
	return(0);
}

int	execute_builtin(t_ms *ms,char **cmd, int	parent)
{
	//printf("Executing builtin\n");
	if (!ft_strncmp(cmd[0], "echo", 4))
		return(b_echo(cmd));
	if (!ft_strncmp(cmd[0], "cd", 2))
		return(cd(ms, cmd));
	if (!ft_strncmp(cmd[0], "pwd", 3))  //GREAT !!!
		return(pwd(ms->env));
	if (!ft_strncmp(cmd[0], "export", 6))
		return(export(ms, cmd, parent));
	if (!ft_strncmp(cmd[0], "unset", 5))
		return(unset(ms, cmd));
	if (!ft_strncmp(cmd[0], "env", 3))
		return(enviroment(ms->env));
	// if (!ft_strncmp(cmd[0], "exit", 4))
	// 	return(ft_exit());
	return(0);
}

int **handle_pipes(t_ms *ms)
{
	int		**pipes;
	int		l;

	l = 0;
	pipes = malloc(sizeof(int *) * ms->cntcmds);
	while (l < ms->cntcmds - 1)
	{
		pipes[l] = malloc(sizeof(int) * 2);
		l++;
	}
	pipes[l] = NULL;

	l = 0;
	while (l < ms->cntcmds - 1)
	{
		if (pipe(pipes[l]) == -1)
			ft_exit(errno, strerror(errno), NULL, NULL);
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
	}
}

void	handle_waitpid(int *pids, int is_parent)
{
	int	i;
	int		status;

	i = 0;
	while (pids[i] && pids[i+1])
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	waitpid(pids[i], &status, 0);
	if (is_parent == 0 && WIFEXITED(status))
		g_exit.status = WEXITSTATUS(status);
}

void	handle_redirections(t_ms *ms, int fd[2], int lvl)
{
	if (ms->pipes && lvl > 0)
		dup2(ms->pipes[lvl-1][0], STDIN_FILENO);
	if (ms->pipes && lvl < ms->cntcmds-1)
		dup2(ms->pipes[lvl][1], STDOUT_FILENO);
	if (fd[0])
	{
		dup2(fd[0] ,STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1])
	{
		dup2(fd[1] ,STDOUT_FILENO);
		close(fd[1]);
	}
}

int	handle_forks(t_ms	*ms, char **env)
{
	int		i;
	t_ex	*com;
	//int		status;

	i = 0;
	com = ms->exe;
	while (i < ms->cntcmds)
	{
		signal(SIGINT,handle_sigint);
		signal(SIGQUIT,handle_sigint);
		ms->pids[i] = fork();
		if (ms->pids[i] == -1)
			ft_exit(errno, strerror(errno), NULL, NULL);
		if (ms->pids[i] == 0) //child i
		{
			// printf("I am in pid[%d] (child %d)\n", i, i+1);  //child 1 is pid[0]
			// printf("-------------------Command %s %s\n",com->command[0], com->command[1]);

			handle_redirections(ms, com->fd, i);
			close_pipes(ms->pipes);

			if (is_builtin(com->command[0]) && com->parent == 0)
				exit(execute_builtin(ms, com->command, com->parent));
			else if(is_builtin(com->command[0]) && com->parent == 1)
				exit(0);
			else if (com->command)
				execve_prepare(ms, env, com->command);

			exit(0);
		}
		//THIS WAITPID MAKE THE  CAT | LS PROBLEM
		//blocker comands (needs input) don't have to stop the execution of the rest of the pipes/commands
		if (is_builtin(com->command[0]) && com->parent == 1)
		{
			if (!com -> next) //i want exit status only from the last one
			{
				g_exit.status = execute_builtin(ms,com->command, com->parent); //here on inside lets decide
				return(1);
			}
			else
				execute_builtin(ms,com->command, com->parent);
			//printf("Exit status for builtin parent %d is %d\n", ms->pids[i], g_exit.status);
		}
		//else if (!com->next && WIFEXITED(status))
		//{
		//	g_exit.status = WEXITSTATUS(status);
		//	printf("Exit status for children %d is %d\n", ms->pids[i], g_exit.status);
		//}

	com = com->next;
	i++;
	}
	return(0);
}

void	execute_cmds(t_ms	*ms, char **env)
{
	//printf("Isbultin %s: %d \n", ms->exe->command[0], is_builtin(ms->exe->command[0]));

	int version;
	int	is_parent;

	version = 1;
	// first version
	g_exit.proces = 2;
	if (version == 1)
	{
		ms->pipes = handle_pipes(ms);
		ms->pids =  malloc(sizeof(int) * (ms->cntcmds));
		//children
		is_parent = handle_forks(ms, env);
		//parent
		close_pipes(ms->pipes);
		handle_waitpid(ms->pids, is_parent);
	}
	else //second with one pipe
		execute_secondoption(ms, env);
	g_exit.proces = 0;
}
