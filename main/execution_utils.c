/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:31:36 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/31 12:40:26 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_paths(char *env)
{
	int		i;
	char	**paths;

	i = 0;
	if (env)
		paths = ft_split(env, ':');
	else
		paths = NULL;
		//paths = ft_split(DEF_PATH, ':');
	return (paths);
}

void	ft_execve(t_ms	*ms, char *path, char **cmd, char **env)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) != 0)
			exit(ft_error(ms, 126, cmd[0], strerror(errno)));
		if (execve(path, cmd, env) == -1)
			exit(ft_error(ms, errno, strerror(errno), NULL));
	}
}

void	execve_prepare(t_ms	*ms, char **cmd)
{
	int		i;
	char	**paths;
	//char	**env;
	DIR		*dir;
	char	*a;//new
	char	*b;

	i = 0;
	//env = env_toarray(ms);
	ms->array_env = env_toarray(ms);
	if (cmd[0][0] != '\0')
	{
		if (ft_strchr(cmd[0], '/') && (dir = opendir(cmd[0])))
			exit(ft_error(ms, 126, cmd[0], "is a directory"));
		paths = ft_get_paths(get_env_value(ms->env, "PATH"));
		if (ft_strchr(cmd[0], '/') || paths == NULL)
		{
			ft_execve(ms, cmd[0], cmd, ms->array_env);//env
			exit(ft_error(ms, 127, cmd[0], "No such file or directory"));
		}
		i = 0;
		while (paths[i])
		{
			b = ft_strjoin(paths[i++], "/");
			a = ft_strjoin(b,cmd[0]);
			ft_execve(ms, a, cmd, ms->array_env);//env
			free (a);
			free (b);
		}
		if (ms->array_env)
		 	free_double(ms->array_env);
		free_double(paths);
	}
	exit(ft_error(ms, 127, cmd[0], "command not found"));
}
