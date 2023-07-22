/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freems.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:50:34 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/22 20:05:15 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	free_ex(t_ex *ex)
{
	t_ex	*a;
	t_ex	*b;

	if (!ex)
		return ;
	a = ex;
	while (a->next)
	{
		if (a->command)
			free(a->command);
		b = a->next;
		free (a);
		a = b;
	}
}

void	free_tok(t_tok *tok)
{
	t_tok	*a;
	t_tok	*b;

	if (!tok)
		return ;
	a = tok;
	while (a->next)
	{
		if (a->content)
			free(a->content);
		b = a->next;
		free (a);
		a = b;
	}
}

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
	if (ms->start)
		free_tok(ms->start);
	if (ms->exe)
		free_ex(ms->exe);
	if (ms)
		free(ms);
}
