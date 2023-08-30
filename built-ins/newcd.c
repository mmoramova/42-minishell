/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newcd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:09:02 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/30 16:29:40 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error3(t_ms *ms, int exitnumber, char *txt, char *txt2, char *txt3)
{
	if (txt)
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
	ms->exitstatus = exitnumber;
	return (exitnumber);
}

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

	change_env(ms->env, "OLDPWD", ft_strdup(get_env_value(ms->env, "PWD")));
	if (getcwd(str, PATH_MAX) == NULL)
	{
		com = ft_strdup(ft_strjoin("/", com));
		change_env(ms->env, "PWD",
			ft_strdup(ft_strjoin(get_env_value(ms->env, "PWD"), com)));
		ft_error3(ms, 1, "cd: error retrieving current directory",
			"getcwd: cannot access parent directories", strerror(errno));
	}
	else
		change_env(ms->env, "PWD", ft_strdup(getcwd(str, PATH_MAX)));
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
		ft_error(ms, 1, "cd", com[i], strerror(errno));
		return (1);
	}
	else
	{
		check_pwds(ms);
		set_pwds(ms, com[i]);
	}
	return (0);
}
