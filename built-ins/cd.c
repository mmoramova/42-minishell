/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:59:46 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/20 10:57:14 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int cd (t_env *env,char **com)
{
	int 	i;
	char	*str;

	i = 1;
	change_env(env, "OLDPWD",getcwd(NULL, PATH_MAX));
	if (com[i] == NULL)
	{
		if(chdir (get_env_value(env,"HOME")) != 0)
		{
			perror("chdir() error()");
			return(1);
		}
		if (check_env(env,"PWD"))
		{
			str = ft_strjoinfree("PWD=",getcwd(NULL,PATH_MAX));
			add_env(env,str);
		}
		str = getcwd(NULL, PATH_MAX);
		if (!str)
			return(2);
		else
			change_env(env, "PWD", str);
		//setear el valor de oldpwd del enviroment:oldpwd = pwd del enviroment io
		if (check_env(env, "OLDPWD") == 0)
		{
			change_env(env, "OLDPWD",getcwd(NULL, PATH_MAX));
			str = getcwd(NULL, PATH_MAX);
			if (!str)
				return(2);
			else
				change_env(env, "PWD", str);
		}


		return(0);
	}
	else
	{
		if (chdir (com[i]) != 0)
		{
			perror("chdir() error()");
			return(1);
		}
		//setear el valor de oldpwd del enviroment:oldpwd = pwd del enviroment propio
		if (check_env(env, "OLDPWD") == 0)
		{

			change_env(env, "OLDPWD",get_env_value(env, "PWD"));
			str = getcwd(NULL, PATH_MAX);

			if (!str)
				return(2);
			change_env(env, "PWD", str);
		}
		return(0);
	}
}
//gcc -Wall -Wextra -Werror cd.c







