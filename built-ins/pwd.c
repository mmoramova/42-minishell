/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:30:02 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/30 15:02:55 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_env *env)
{
	char	str[PATH_MAX];

	if (env)
	{
		if (getcwd(str, PATH_MAX) != NULL)
			printf("%s\n", getcwd(str, PATH_MAX));
		else
			printf("%s\n", get_env_value(env, "PWD"));
	}
	exit(0);
}
