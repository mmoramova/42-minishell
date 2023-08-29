/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newcd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:09:02 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/29 11:41:31 by josorteg         ###   ########.fr       */
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

void	set_pwds(t_ms *ms)
{
	change_env(ms->env, "OLDPWD", get_env_value(ms->env, "PWD"));
	change_env(ms->env, "PWD", getcwd(NULL, PATH_MAX));
}

int	cd(t_ms *ms, char **com)
{
	int	i;

	i = 1;

	if (com[i] == NULL)
		com[i] = get_env_value(ms->env, "HOME");
	if (chdir (com[i]) != 0)
	{
		if (com[i][0] == 0)
			return (0);
		ft_error(ms, 1, "cd", com[1], strerror(errno));
		return (1);
	}
	else
	{
		check_pwds(ms);
		set_pwds(ms);
	}
	return (0);
}
