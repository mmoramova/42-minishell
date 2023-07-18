/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:33:19 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/18 17:33:03 by josorteg         ###   ########.fr       */
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

int	execute_builtin(t_env *env,char **cmd, int	parent)
{
	printf("Executing builtin\n");
	if (!ft_strncmp(cmd[0], "echo", 4))
		return(b_echo(cmd));
	if (!ft_strncmp(cmd[0], "cd", 2))
		return(cd(env, cmd));
	if (!ft_strncmp(cmd[0], "pwd", 3))  //GREAT !!!
		return(pwd(env));
	if (!ft_strncmp(cmd[0], "export", 6))
		return(export(env, cmd, parent));
	// if (!ft_strncmp(cmd[0], "unset", 5))
	// 	return(unset(env, cmd));
	if (!ft_strncmp(cmd[0], "env", 3))  // OLDPWD= ? , its the order ok?
		return(enviroment(env));
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
		//printf("Opening pipe [%d]\n", l);
		if (pipe(pipes[l]) == -1)
			ft_exit(errno, strerror(errno), NULL);
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
		//printf("Closing pipe [%d]\n", i);
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

void	handle_waitpid(int *pids)
{
	int	i;

	i = 0;
	while (pids[i])
	{
		//printf("waiting for pid[%d]\n", i);
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

void	handle_redirections(t_ms *ms, int fd[2], int lvl)
{
	if (ms->pipes && lvl > 0)
	{
		//printf("------------------------------i = %d, l=%d , dup2 stdin pipe[%d][0]\n", ms->cntcmds, lvl, lvl-1);
		dup2(ms->pipes[lvl-1][0], STDIN_FILENO);
	}
	if (ms->pipes && lvl < ms->cntcmds-1)
	{
		//printf("-------------------------------i = %d, l=%d , dup2 stdout pipe[%d][1]\n", ms->cntcmds, lvl, lvl);
		dup2(ms->pipes[lvl][1], STDOUT_FILENO);
	}
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

void handle_forks(t_ms	*ms, char **env)
{
	int		i;
	t_ex	*com;

	i = 0;
	com = ms->exe;
	while (i < ms->cntcmds)
	{
		ms->pids[i] = fork();
		if (ms->pids[i] == -1)
			ft_exit(errno, strerror(errno), NULL);
		if (ms->pids[i] == 0) //child i
		{
			// printf("I am in pid[%d] (child %d)\n", i, i+1);  //child 1 is pid[0]
			// printf("-------------------Command %s %s\n",com->command[0], com->command[1]);

			handle_redirections(ms, com->fd, i);
			close_pipes(ms->pipes);

			if (is_builtin(com->command[0]) &&
			com->parent == 0) //TODO BUILTIN EXE
				exit(execute_builtin(ms->env, com->command, com->parent));
			else if(is_builtin(com->command[0]) && com->parent == 1)
				exit(0);
			else
				execve_prepare(ms, env, com->command);
		}
		if (is_builtin(com->command[0]) && com->parent == 1)
			execute_builtin(ms->env,com->command, com->parent);


	com = com->next;
	i++;
	}
}

void execute_secondoption(t_ms	*ms, char **env)
{
	int		i;
	t_ex	*com;
	int		onepipe[2];
	int		inredir;
	int		pid;

	i = 0;
	inredir = 0;
	com = ms->exe;
	while (i < ms->cntcmds)
	{
		if (i < ms->cntcmds - 1)
		{
			if (pipe(onepipe) == -1)
				ft_exit(errno, strerror(errno), NULL);
		}

		pid = fork();
		if (pid == -1)
			ft_exit(errno, strerror(errno), NULL);
		if (pid == 0) //child i
		{

			if (inredir)
			{
				dup2(inredir, STDIN_FILENO);
				close(inredir);
			}

			if (onepipe[1] && i < ms->cntcmds-2) //??
			{
				dup2(onepipe[1], STDOUT_FILENO);
				close(onepipe[1]);
			}

			//if (is_builtin(com->command[0])) //TODO BUILTIN EXE
			//	execute_builtin(ms->env, com->command);
			//else
			execve_prepare(ms, env, com->command);
		}
	close(onepipe[1]);
	inredir = onepipe[0];
	com = com->next;
	i++;
	}
}

void	execute_cmds(t_ms	*ms, char **env)
{
	//printf("Isbultin %s: %d \n", ms->exe->command[0], is_builtin(ms->exe->command[0]));

	int version;

	version = 1;
	// first version
	if (version == 1)
	{
		ms->pipes = handle_pipes(ms);
		ms->pids =  malloc(sizeof(int) * (ms->cntcmds));
		//children
		handle_forks(ms, env);
		//parent
		close_pipes(ms->pipes);
		handle_waitpid(ms->pids);
	}
	else //second with one pipe
		execute_secondoption(ms, env);
}
