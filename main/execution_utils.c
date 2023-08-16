/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:31:36 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/16 19:20:17 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(int exitnumber, char *txt, char *txt2, char *txt3)
{
	ft_putstr_fd("minishell: ", 2);
	if(txt)
		ft_putstr_fd(txt, 2);
	if (txt2 && ft_strlen(txt2) > 0)
	{
			ft_putstr_fd(": ", 2);
		if (txt3 && !ft_strncmp(txt3, "not a valid identifier", 23))
			ft_putchar_fd('`', 2);
		ft_putstr_fd(txt2, 2);
		if (txt3 && !ft_strncmp(txt3, "not a valid identifier", 23))
			ft_putchar_fd('\'', 2);
	}
	if (txt3 && ft_strlen(txt3) > 0)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(txt3, 2);
	}
	ft_putstr_fd("\n", 2);
	g_exit.status = exitnumber;
	//printf("ft_exit: Exit status is %d\n", g_exitstatus);
}

void	ft_exit2(int exitnumber, char *txt, char *txt2, char *txt3)  //i will change the function name
{
	ft_putstr_fd("minishell: ", 2);
	if (txt)
		ft_putstr_fd(txt, 2);
	if (txt2)
		ft_putstr_fd(txt2, 2);
	if (txt3)
		ft_putstr_fd(txt3, 2);
	ft_putstr_fd("\n", 2);
	g_exit.status = exitnumber;
	//printf("ft_exit: Exit status is %d\n", g_exitstatus);
}

char	**ft_get_paths(char *env)
{
	int		i;
	char	**paths;

	i = 0;
	if (env)
		paths = ft_split(env, ':');
	else
		paths = ft_split(DEF_PATH, ':');
	return (paths);
}

void	ft_execve(char *path, char **cmd, char **env)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) != 0)
		{
			ft_exit(126, cmd[0], strerror(errno), NULL);
			exit(126);
		}
		if (execve(path, cmd, env) == -1)
		{
			ft_exit(errno, strerror(errno), NULL, NULL);
			exit(errno);
		}
	}
}

void	execve_prepare(t_ms	*ms, char **env, char **cmd)
{
	int		i;
	char	**paths;

	i = 0;
	// if (argv[0] == '.' && argv[1] == '/' && ft_strchr(argv, 32))
	// 	ft_exit(127, cmd[0], "No such file or directory", NULL);
	if (ft_strchr(cmd[0], '/'))
	{
		ft_execve(cmd[0], cmd, env);
		ft_exit(127, cmd[0], "No such file or directory", NULL);
		exit(127);
	}
	paths = ft_get_paths(get_env_value(ms->env, "PATH"));
	i = 0;
	while (paths[i])
		ft_execve(ft_strjoin(ft_strjoin(paths[i++], "/"),
				cmd[0]), cmd, env);
	ft_exit(127, cmd[0], "command not found", NULL);
	exit(127);
}
