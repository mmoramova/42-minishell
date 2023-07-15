#include "minishell.h"
/*only for information, delete later*/

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
	int	pipes[2];
	int pids[2];

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
	int pipes[2][2];
	int pids[3];

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
