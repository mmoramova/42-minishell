/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:09:02 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/06 11:55:28 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pwds(t_ms *ms)
{
	if (check_env(ms->env, "PWD") == 1 && ms->pwd != 1)
		add_env(ms->env, "PWD", "");
	if (check_env(ms->env, "OLDPWD") == 1 && ms->oldpwd != 1)
		add_env(ms->env, "OLDPWD", "");
}

void	set_pwds(t_ms *ms, char *com)
{
	char	str[PATH_MAX];

	if (check_env(ms->env, "OLDPWD") == 0)
		change_env(ms->env, "OLDPWD", getcwd(str, PATH_MAX));
	if (getcwd(str, PATH_MAX) == NULL)
	{
		com = ft_strdup(ft_strjoin("/", com));
		change_env(ms->env, "PWD",
			ft_strdup(ft_strjoin(get_env_value(ms->env, "PWD"), com)));
		ms->exitstatus = 1;
		ft_error3(1, "cd: error retrieving current directory",
			"getcwd: cannot access parent directories", strerror(errno));
	}
	else if (check_env(ms->env, "PWD") == 0)
		change_env(ms->env, "PWD", getcwd(str, PATH_MAX));
	else
		getcwd(str, PATH_MAX);
}

int	cd(t_ms *ms, char **com)
{
	char	*s;

	if (com[1] == NULL)
		s = get_env_value(ms->env, "HOME");
	else
		s = (com[1]);
	if (s == NULL)
	{
		ft_error4(1, "cd", "HOME not set", NULL);
		ms->exitstatus = 1;
		return (1);
	}
	if (s[0] == 0)
		return (0);
	if (chdir (s) != 0)
	{
		ms->exitstatus = 1;
		ft_error4(1, "cd", s, strerror(errno));
		return (1);
	}
	check_pwds(ms);
	set_pwds(ms, s);
	return (0);
}
