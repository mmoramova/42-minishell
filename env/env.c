/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 08:17:04 by josorteg          #+#    #+#             */
/*   Updated: 2023/06/29 09:18:31 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"inc/minishell.h"

t_env   *get_env(char **env)
{
    int     i;

    i = 0;
    while (env[i])
        printf("%s\n",env[i]);
    
    return(NULL);
}