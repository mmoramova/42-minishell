/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcomand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:34:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/05 18:13:01 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (aux->eval)
			printf("%s=%s\n", aux->evar, aux->eval);
		aux = aux->next;
	}
}

int	enviroment(t_env *env)
{
	print_env(env);
	exit (0);
}

void	shlvl_add(t_ms *ms)
{
	int		shlvl;
	char	*val;

	if (check_env(ms->env, "SHLVL") == 1)
		add_env(ms->env, "SHLVL", "1");
	else
	{
		val = get_env_value(ms->env, "SHLVL");
		shlvl = ft_atoi(val) + 1;
		if (shlvl < 0)
			shlvl = 0;
		if (shlvl > 1000)
		{
			ft_putstr_fd("warning: shell level (", 2);
			val = ft_itoa(shlvl);
			ft_putstr_fd(val, 2);
			ft_putstr_fd(") too high, resetting to 1\n", 2);
			shlvl = 1;
		}
		val = ft_itoa(shlvl);
		change_env(ms->env, "SHLVL", val);
		free(val);
	}
}
