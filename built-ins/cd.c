/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:59:46 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/21 20:31:24 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int cd (t_ms *ms, char **com)
{
	int 	i;
	char	*str;

	i = 1;
	if (com[i] == NULL)
	{
		if(chdir (get_env_value(ms->env,"HOME")) != 0)
		{
			//error
			return(1);
		}
		if (check_env(ms->env,"PWD") == 1)
		{
			str = getcwd(NULL,PATH_MAX);
			add_env(ms->env, "PWD", str);
		}
		str = getcwd(NULL, PATH_MAX);
		if (!str)
			return(2);
		else
			change_env(ms->env, "PWD", str);
		//setear el valor de oldpwd del enviroment:oldpwd = pwd del enviroment io
		if (check_env(ms->env, "OLDPWD") == 0)
		{
			change_env(ms->env, "OLDPWD",getcwd(NULL, PATH_MAX));
			str = getcwd(NULL, PATH_MAX);
			if (!str)
				return(2);
			else
				change_env(ms->env, "PWD", str);
		}


		return(0);
	}
	else
	{
		if (chdir (com[i]) != 0)
		{
			//error
			return(1);
		}
		//setear el valor de oldpwd del enviroment:oldpwd = pwd del enviroment propio
		if (check_env(ms->env, "OLDPWD") == 0)
		{

			change_env(ms->env, "OLDPWD",get_env_value(ms->env, "PWD"));
			str = getcwd(NULL, PATH_MAX);

			if (!str)
				return(2);
			change_env(ms->env, "PWD", str);
		}
		else

		return(0);
	}
	return(0);
}
//gcc -Wall -Wextra -Werror cd.c







