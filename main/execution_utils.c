/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:31:36 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/15 18:39:10 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_exit(int exitnumber, char *txt, char *txt2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(txt, 2);
	if (txt2 && ft_strlen(txt2) > 0)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(txt2, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(exitnumber);
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

void	ft_execve(char *path, char **command, char **env)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) != 0)
			ft_exit(126, command[0], strerror(errno));
		if (execve(path, command, env) == -1)
			ft_exit(errno, strerror(errno), NULL);
	}
}

void	ft_execve_prepare(t_ms	*ms, char **env, int level)
{
	char	**command;
	int		i;
	int		j;
	char	**paths;
	t_ex	*com;

	j = 0;
	i = 0;

	printf("Executing level %d\n", level);
	com = ms->exe;
	while (level--)
		com = com->next;
	command = com->command;
	printf("Executing command %s %s\n",command[0], command[1]);
	// if (argv[0] == '.' && argv[1] == '/' && ft_strchr(argv, 32))
	// 	ft_exit(127, command[0], "No such file or directory");
	while (command[j])
	{
		if (command[j][0] == '\'')
			command[j] = ft_strtrim(command[j], "\'");
		else if (command[j][0] == '\"')
			command[j] = ft_strtrim(command[j], "\"");
		j++;
	}
	printf("Before execution-----fd[0]=%d || fd[1]=%d\n",com->fd[0],com->fd[1]);
	if (ft_strchr(command[0], '/'))
		ft_execve(command[0], command, env);
	paths = ft_get_paths(get_env_value(ms->env ,"PATH"));
	while (paths[i])
		ft_execve(ft_strjoin(ft_strjoin(paths[i++], "/"),
				command[0]), command, env);
	ft_exit(127, command[0], "command not found");
}
