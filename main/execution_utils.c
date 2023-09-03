/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:31:36 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/03 18:55:19 by mmoramov         ###   ########.fr       */
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

void	ft_execve_paths(t_ms *ms, char **cmd, char **paths)
{
	int		i;
	char	*a;
	char	*b;

	i = 0;
	while (paths[i])
	{
		b = ft_strjoin(paths[i], "/");
		a = ft_strjoin(b, cmd[0]);
		ft_execve(ms, a, cmd, ms->array_env);
		free (a);
		free (b);
		i++;
	}
	free_doublechar(paths);
}

void	execve_prepare(t_ms	*ms, char **cmd)
{
	char	**paths;
	DIR		*dir;

	ms->array_env = env_toarray(ms);
	if (cmd[0][0] != '\0')
	{
		dir = opendir(cmd[0]);
		if (ft_strchr(cmd[0], '/') && (dir))
			exit(ft_error(ms, 126, cmd[0], "is a directory"));
		paths = ft_get_paths(get_env_value(ms->env, "PATH"));
		if (ft_strchr(cmd[0], '/') || paths == NULL)
		{
			ft_execve(ms, cmd[0], cmd, ms->array_env);
			exit(ft_error(ms, 127, cmd[0], "No such file or directory"));
		}
		ft_execve_paths(ms, cmd, paths);
	}
	ft_error(ms, 127, cmd[0], "command not found");
	if (ms->exe)
		free_ex(ms->exe);
	exit(127);
}
