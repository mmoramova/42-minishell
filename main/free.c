/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:50:34 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/05 18:29:43 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ex_closepipes(t_ex *ex)
{
	t_ex	*a;

	if (!ex)
		return ;
	a = ex;
	if (ft_fd_isopen(a->fd[0]))
		close(a ->fd[0]);
	if (ft_fd_isopen(a->fd[1]))
		close(a ->fd[1]);
}

void	free_ex(t_ex *ex)
{
	t_ex	*a;
	t_ex	*b;
	int		i;

	if (!ex)
		return ;
	i = 0;
	a = ex;
	while (a->next)
	{
		if (a->command != NULL)
			free_doublechar(a->command);
		free_ex_closepipes(a);
		if (a -> previous != NULL)
			free(a ->previous);
		b = a->next;
		free (a);
		a = b;
	}
	if (a->command != NULL)
		free_doublechar(a->command);
	free_ex_closepipes(a);
	free (a);
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
	if (a->content)
		free(a->content);
	free (a);
}

void	free_env(t_env *env)
{
	t_env	*a;
	t_env	*b;

	if (!env)
		return ;
	a = env;
	while (a)
	{
		if (a->evar)
			free(a->evar);
		if (a->eval)
			free(a->eval);
		b = a->next;
		free (a);
		a = NULL;
		a = b;
	}
}

void	free_ms(t_ms *ms)
{
	if (ms->env)
		free_env(ms->env);
	if (ms->line)
		free(ms->line);
	if (ms->start)
		free_tok(ms->start);
	if (ms->exe)
		free_ex(ms->exe);
	if (ms)
		free(ms);
}
