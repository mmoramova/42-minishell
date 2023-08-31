/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freems.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:50:34 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/31 18:24:19 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	free_ex(t_ex *ex)
{
	t_ex	*a;
	int		i;

	if (!ex)
		return ;
	i = 0;
	a = ex;

	if (a->command)
		free_double(a->command);

	if (a -> previous)
		free(a ->previous);
	free (a);
	//a = NULL;
}

void	free_ex2(t_ex *ex)
{
	t_ex	*a;
	//t_ex	*b;
	int		i;

	if (!ex)
		return ;
	i = 0;
	a = ex;
	while (a->next)
	{
		if (a->command)
			free_double(a->command);
		if (a ->fd[0] && a->fd[0] != -2)
			close(a ->fd[0]);
		if (a ->fd[1] && a->fd[1] != -2)
			close(a ->fd[1]);
		if (a -> previous)
			free(a ->previous);
		// b = a->next;
		// if (a -> next)
		// 	free(a -> next);
		// a = NULL;
		// a = b;
		a = a->next;
	}
	// i = 0;
	if (a->command)
		free_double(a->command);
	if (a ->fd[0] && a->fd[0] != -2)
		close(a ->fd[0]);
	if (a ->fd[1] && a->fd[1] != -2)
		close(a ->fd[1]);
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

void	free_double(char **ptr)
{

    while (*ptr != NULL)
	{
        free(*ptr);
        ptr++;
    }
	ptr = NULL;
	free(ptr);
}
