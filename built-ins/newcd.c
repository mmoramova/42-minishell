/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newcd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:09:02 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/02 12:29:42 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pwds(t_ms *ms)
{
	if (check_env(ms->env, "PWD") == 1)
		add_env(ms->env, "PWD", "");
	if (check_env(ms->env, "OLDPWD") == 1)
		add_env(ms->env, "OLDPWD", "");
}

void	set_pwds(t_ms *ms, char *com)
{
	char	str[PATH_MAX];

	change_env(ms->env, "OLDPWD", get_env_value(ms->env, "PWD"));
	if (getcwd(str, PATH_MAX) == NULL)
	{
		com = ft_strdup(ft_strjoin("/", com));
		change_env(ms->env, "PWD",
			ft_strdup(ft_strjoin(get_env_value(ms->env, "PWD"), com)));
		ms->exitstatus = 1;
		ft_error3(1, "cd: error retrieving current directory",
			"getcwd: cannot access parent directories", strerror(errno));
	}
	else
		change_env(ms->env, "PWD", getcwd(str, PATH_MAX));
}

int	cd(t_ms *ms, char **com)
{
	int	i;

	i = 1;
	if (com[i] == NULL)
		chdir(get_env_value(ms->env, "HOME"));
	else if (chdir (com[i]) != 0)
	{
		if (com[i][0] == 0)
			return (0);
		ms->exitstatus = 1;
		ft_error4(1, "cd", com[i], strerror(errno));
		return (1);
	}
	else
	{
		check_pwds(ms);
		set_pwds(ms, com[i]);
	}
	return (0);
}
