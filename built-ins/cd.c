/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:59:46 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/18 18:13:40 by josorteg         ###   ########.fr       */
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
	printf("comand=%s  tag=%s", com[0], com[1]);
	if (com[i] == NULL)
	{
		if(chdir (get_env_value(env,"HOME")) != 0)
		{
			perror("chdir() error()");
			return(1);
		}
		//setear el valor de oldpwd del enviroment:oldpwd = pwd del enviroment io
		if (check_env(env, "OLDPWD") == 0)
		{
			change_env(env, "OLDPWD",get_env_value(env, "PWD"));
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







