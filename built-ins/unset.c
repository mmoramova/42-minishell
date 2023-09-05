/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:00:39 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/05 18:15:08 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_env(t_ms *ms, char *com)
{
	t_env	*aux;
	t_env	*tmp;

	aux = ms->env;
	while (aux)
	{
		while (ft_strncmp(com, aux->evar, ft_strlen(aux->evar)) != 0)
		{
			tmp = aux;
			if (aux->next)
				aux = aux->next;
			else
				return ;
		}
		tmp->next = aux->next;
		aux->next = NULL;
		free_env(aux);
		return ;
	}
	return ;
}

int	unset(t_ms *ms, char **com)
{
	int		i;

	if (com[1] == NULL)
		return (0);
	i = 1;
	while (com[i])
	{
		if (check_export(com[i]) == 1)
		{
			ms->exitstatus = 1;
			ft_error4(1, com[0], com[i], "not a valid identifier");
			return (1);
		}
		if (check_env (ms->env, com[i]) == 1)
			i++;
		else
		{
			ft_unset_env(ms, com[i]);
			i++;
		}
	}
	return (0);
}
