/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:00:39 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/26 11:30:06 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_env(t_ms *ms, char *com)
{
	t_env	*aux;
	t_env	*tmp;

	aux = ms->env;
	while(aux)
	{
		if(ft_strncmp (com, aux->next->evar, ft_strlen(aux->next->evar)) == 0)
			{	tmp = aux->next;
				if (aux->next->next != NULL)
					aux->next = aux->next->next;
				else
					aux->next = NULL;
				free(tmp);
				return;
			}
		aux = aux->next;
	}
}

int	unset(t_ms *ms ,char **com)
{
	int		i;

	if (com[1] == NULL || check_env(ms->env, com[1]))
		return(0);
	i = 1;
	while (com[i])
	{
		if (check_env (ms->env, com[i]) == 1)
			i++;
		else
		{
			ft_unset_env(ms, com[i]);
			i++;
		}
	}
	return(0);
}

