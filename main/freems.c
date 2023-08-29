/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freems.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:50:34 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/29 19:12:40 by josorteg         ###   ########.fr       */
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
	int		i;

	if (!tok)
		return ;
	i = 0;
	a = tok;
	while (a->next)
	{
		if (a->content)
		{
			while (a->content[i])
			{
				free(&a->content[i]);
				i++;
			}
			free(a->content);
		}
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
