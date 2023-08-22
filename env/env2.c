/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:53:44 by mmoramov          #+#    #+#             */
/*   Updated: 2023/08/21 17:27:50 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_lstsize(t_env *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst -> next;
	}
	return (len);
}

char	**env_toarray(t_ms *ms)
{
	int		i;
	char	**p;
	t_env	*env;

	i = 0;
	env = ms->env;
	p = malloc(sizeof(char *) * (env_lstsize(env) + 1));
	if (!p)
		return (NULL);
	while (env)
	{
		p[i] = ft_strjoin(ft_strjoin(env->evar, "="), env->eval);
		/*if (!p[i])
			{
				ft_free(p, i);
				return (NULL);
			}
		}*/
		//printf("env p[%d]: %s\n", i, p[i]);
		env = env -> next;
		i++;
	}
	p[i] = NULL;
	return (p);
}