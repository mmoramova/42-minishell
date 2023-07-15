/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:33:19 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/15 21:02:39 by mmoramov         ###   ########.fr       */
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

/*void	ft_singlecommandx(t_ms *ms,char **env)
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

	ft_execve_prepare(ms, env,0);
}*/


void	ft_singlecommand(t_ms *ms,char **env)
{
	int	pid;
	printf("Hi from singlecommand\n");

	pid = fork();
	if (pid == -1)
		ft_exit(errno, strerror(errno), NULL);
	if (pid == 0) //child
	{
		if (ms->exe->fd[0])
		{
			dup2(ms->exe->fd[0] ,STDIN_FILENO);
			close(ms->exe->fd[0]);
		}
		if (ms->exe->fd[1])
		{
			dup2(ms->exe->fd[1] ,STDOUT_FILENO);
			close(ms->exe->fd[1]);
		}
		ft_execve_prepare(ms, env,0);
	}

	//parent
	waitpid(pid, NULL, 0);
}

int	ft_doublecommand(t_ms *ms,char **env)
{
	//nb of commands = 2
	int	pipes[2]; //0
	int pids[2]; //0 1

	printf("Hi from doublecommand\n");
	if (pipe(pipes) == -1)
		ft_exit(errno, strerror(errno), NULL);

	pids[0] = fork();
	if (pids[0] == -1)
		ft_exit(errno, strerror(errno), NULL);
	if (pids[0] == 0) //child 1
	{
		printf("I am in child 1\n");
		dup2(pipes[1], STDOUT_FILENO);
		if (ms->exe->fd[0])
		{
			dup2(ms->exe->fd[0] ,STDIN_FILENO);
			close(ms->exe->fd[0]);
		}
		if (ms->exe->fd[1])
		{
			dup2(ms->exe->fd[1] ,STDOUT_FILENO);
			close(ms->exe->fd[1]);
		}

		close(pipes[0]);
		close(pipes[1]);
		ft_execve_prepare(ms, env, 0);
		return (0);
	}

	pids[1] = fork(); //with second child i need to call the other file descriptor

	// >> is not working
	if (pids[1] == -1)
		ft_exit(errno, strerror(errno), NULL);
	if (pids[1] == 0) //child 2
	{
		printf("I am in child 2\n");
		dup2(pipes[0], STDIN_FILENO);
		if (ms->exe->next->fd[0])
		{
			dup2(ms->exe->next->fd[0] ,STDIN_FILENO);
			close(ms->exe->next->fd[0]);
		}

		if (ms->exe->next->fd[1])
		{
			dup2(ms->exe->next->fd[1] ,STDOUT_FILENO);
			close(ms->exe->next->fd[1]);
		}

		close(pipes[0]);
		close(pipes[1]);
		ft_execve_prepare(ms, env, 1);
		return (0);
	}
	//parent
	close(pipes[0]);
	close(pipes[1]);

	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
	return (0);
}

int	ft_tripplecommand(t_ms *ms,char **env)
{
	//nb of commands = 3
	int pipes[2][2]; // 0, 1
	int pids[3];  //0,1 2

	printf("Hi from tripplecommand\n");
	if (pipe(pipes[0]) == -1)
		ft_exit(errno, strerror(errno), NULL);
	if (pipe(pipes[1]) == -1)
		ft_exit(errno, strerror(errno), NULL);

	pids[0] = fork();
	if (pids[0] == -1)
		ft_exit(errno, strerror(errno), NULL);
	if (pids[0] == 0) //child 1
	{
		printf("I am in child 1\n");
		dup2(pipes[0][1], STDOUT_FILENO);
		if (ms->exe->fd[0])
		{
			dup2(ms->exe->fd[0] ,STDIN_FILENO);
			close(ms->exe->fd[0]);
		}
		if (ms->exe->fd[1])
		{
			dup2(ms->exe->fd[1] ,STDOUT_FILENO);
			close(ms->exe->fd[1]);
		}

		close(pipes[0][0]);
		close(pipes[0][1]);
		close(pipes[1][0]);
		close(pipes[1][1]);
		ft_execve_prepare(ms, env, 0);
		return (0);
	}

	pids[1] = fork(); //with second child i need to call the other file descriptor
	if (pids[1] == -1)
		ft_exit(errno, strerror(errno), NULL);
	if (pids[1] == 0) //child 2
	{
		printf("I am in child 2\n");
		dup2(pipes[0][0], STDIN_FILENO);
		dup2(pipes[1][1], STDOUT_FILENO);
		if (ms->exe->next->fd[0])
		{
			dup2(ms->exe->next->fd[0] ,STDIN_FILENO);
			close(ms->exe->next->fd[0]);
		}

		if (ms->exe->next->fd[1])
		{
			dup2(ms->exe->next->fd[1] ,STDOUT_FILENO);
			close(ms->exe->next->fd[1]);
		}

		close(pipes[0][0]);
		close(pipes[0][1]);
		close(pipes[1][0]);
		close(pipes[1][1]);
		ft_execve_prepare(ms, env, 1);
		return (0);
	}

	pids[2] = fork(); //with second child i need to call the other file descriptor
	if (pids[2] == -1)
		ft_exit(errno, strerror(errno), NULL);
	if (pids[2] == 0) //child 3
	{
		printf("I am in child 3\n");
		dup2(pipes[1][0], STDIN_FILENO);
		if (ms->exe->next->next->fd[0])
		{
			dup2(ms->exe->next->next->fd[0] ,STDIN_FILENO);
			close(ms->exe->next->next->fd[0]);
		}

		if (ms->exe->next->next->fd[1])
		{
			dup2(ms->exe->next->next->fd[1] ,STDOUT_FILENO);
			close(ms->exe->next->next->fd[1]);
		}

		close(pipes[0][0]);
		close(pipes[0][1]);
		close(pipes[1][0]);
		close(pipes[1][1]);
		ft_execve_prepare(ms, env, 2);
		return (0);
	}
	//parent
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);

	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
	waitpid(pids[2], NULL, 0);
	return (0);
}

int	ft_generalcommand(t_ms *ms,char **env)
{
	int	i;
	int	l;
	int k;
	int m;

	t_ex	*com;

	com = ms->exe;
	i = ft_cmds_count(ms->exe); //count the commands

	int pipes[i-1][2];
	int pids[i];

	printf("Hi from generalcommand\n");

	l = 0;
	while (l < i-1)
	{
		printf("Opening pipe %d\n", l);
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

			m = 0;
			while (m < i-1)
			{
				close(pipes[m][0]);
				close(pipes[m][1]);
				m++;
			}

			ft_execve_prepare(ms, env, l);
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
	/*if(ms->exe->next == NULL && ft_isbuiltin(ms->exe->command[0]))  --i commented isbuiltin so i can test real echo
	{
		ft_exe_buitin(ms->env, ms->exe->command);
		//if (ms->exe->fd[0])
		//	close(ms->exe->fd[0]);
		//if (ms->exe->fd[1] )
		//	close(ms->exe->fd[1]);
	}
	else*/
	/*if (ft_cmds_count(ms->exe) == 1)
		ft_singlecommand(ms, env);
	else if (ft_cmds_count(ms->exe) == 2)
		ft_doublecommand(ms, env);
	else
		ft_tripplecommand(ms, env);
	*/
	ft_generalcommand(ms, env);
}


	// TODO: if i have 3 commands and outfile in for example in the 2nd command - it will write to the outfile

	/* txt
	hhi
	hello
	ole
	bye
	bbye
	*/
		// < txt grep "h" | grep "o" >txt3 | echo hi
		// < txt grep "h" | grep "o" >txt3 | echo hi >>txt3
		// < txt grep "h" | grep "o" >>txt5 | < txt grep "l"
		// < txt grep "h" | grep "o" >>txt5 | < txt grep "le" >>txt5 (the first ist written ole then hello)

