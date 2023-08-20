/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:00:39 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/20 14:12:54 by mmoramov         ###   ########.fr       */
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


	if (com[1] == NULL)
		return(0);
	i = 1;

	while (com[i])
	{
		if (check_export(ms, com[i]) == 1)
				return(1);
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

