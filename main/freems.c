/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freems.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:50:34 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/03 18:28:06 by mmoramov         ###   ########.fr       */
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
		free_doublechar(a->command);

	if (a -> previous)
		free(a ->previous);
	free (a);
	//a = NULL;
}
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

void	free_ex2(t_ex *ex)
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

void	free_doublechar(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_doubleint(int **ptr)
{
	int i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
void	free_ex_exit(t_ms *ms, int exitstatus)
{
	if (ms->exe != NULL)
		free_ex2(ms->exe);
	if (ms->pids != NULL)
		free(ms->pids);
	exit(exitstatus);
}
