/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freems.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:50:34 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/12 17:36:12 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*a;
	t_env	*b;

	if (!env)
		return ;
	a = env;
	while (a->next)
	{
		free(a->evar);
		free(a->eval);
		b = a->next;
		free (a);
		a = b;
	}
	free(a->evar);
	free(a->eval);
	free (a);

}

void	free_line(char *line)
{
	free(line);
}

void	free_ms(t_ms *ms)
{
	if (ms->env)
		free_env(ms->env);
	// if (ms->start)
	// 	free_exe(ms->start);
	if (ms->line)
		free_line(ms->line);
	free(ms);
}
