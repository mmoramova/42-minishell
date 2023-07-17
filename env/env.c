/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 08:17:04 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/17 11:54:15 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env(t_ms *ms, char **env)
{
	int     i;
	t_env   *aux;
	t_env   *new;


	aux = new_env(env[0]);
	ms->env = aux;
	i = 1;
	while (env[i])
	{
		new = new_env(env[i]);
		aux->next = new;
		aux = new;
		i++;
	}
	return(1);
}

void	add_env (t_ms *ms, char *newvar)
{
	t_env	*aux;

	aux = ms->env;
	while (aux && aux->next)
		aux = aux->next;
	aux->next = new_env(newvar);
}

t_env	*new_env(char *env)
{
	t_env		*new;
	int			k;
	size_t		j;

	j = ft_strchrn(env, '=');
	if (!(ft_strchr(env,'=')))
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return(NULL);
		new->evar = ft_strdup(env);
		new->eval = NULL;
		new->next = NULL;
		//no free si viene de cadena!!!!
		// if (env)
		// 	free(env);
		return(new);
	}
	k = ft_strlen(env);
	new = malloc(sizeof(t_env));
	if (!new)
		return(NULL);
	new->evar = ft_substr(env, 0, j);
	new->eval = ft_substr(env, j + 1, k);
	new->next = NULL;
	// if (env)
	// 	free(env);
	return (new);
}

// we can use getenv("var"), its allowed on the subject
// char *getenv(const char *name)
char    *get_env_value(t_env *env ,char *var)
{
	int     size;
	char    *str;
	t_env	*aux;

	if(!env || !var)
		return(NULL);
	aux = env;
	str = NULL;
	size = ft_strlen(var);
	while (aux && aux->next)
	{
		if(ft_strncmp (var, aux->evar, size) == 0)
			str = aux->eval;
		aux = aux->next;
	}
	return(str);
}

int	check_env (t_env *env, char *var)
{
	t_env	*aux;

	if(!env || !var)
		return(1);
	aux = env;

	while (aux && aux->next)
	{
		if(ft_strncmp (var, aux->evar, ft_strlen(aux->evar)) == 0)
			return(0);
		aux = aux->next;
	}
	return(1);
}

void	change_env(t_env *env, char *var, char *val)
{
	t_env		*aux;
	int			new_size;

	aux = env;
	while (aux->evar != var)
		aux = aux->next;
	if (aux->eval)
		free (aux->eval);
	new_size = (int)ft_strlen(val);
	aux->eval = malloc (new_size * sizeof(char));
	if (!aux->eval)
		return;
	aux->eval = val;
}

