/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freems.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:50:34 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/13 12:08:08 by josorteg         ###   ########.fr       */
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
		if (a->evar)
			free(a->evar);
		if (a->eval)
			free(a->eval);
		b = a->next;
		free (a);
		a = b;
	}
	// if (a->evar)
	// 	free(a->evar);
	// if (a->eval)
	// 	free(a->eval);
	// free (a);
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
	if (ms)
		free(ms);
}
