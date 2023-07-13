/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcomand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:34:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/13 12:13:43 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    print_env(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (aux->eval == NULL)
			printf("%s=\n", aux->evar);
		else
			printf("%s=%s\n", aux->evar, aux->eval);
		aux=aux->next;
	}
	return;
}

int	env(t_env *env)
{
	print_env(env);
	return (0);
}


