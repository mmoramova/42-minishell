/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 08:17:04 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/20 22:40:06 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void shlvl_add(t_ms *ms) //its not finished, i will finish it
{
	int shlvl;
	char *val;

	val = get_env_value(ms->env, "SHLVL");
	if (val == NULL)
		shlvl = 1;
	else
		shlvl = ft_atoi(val) + 1;
	//printf("shlvl is %d", shlvl);
	if (shlvl < 0)
		shlvl = 0;
	if (shlvl > 1000)
	{
		ft_putstr_fd("warning: shell level (", 2);
		ft_putstr_fd(ft_itoa(shlvl), 2);
		ft_putstr_fd(") too high, resetting to 1", 2);
		ft_putstr_fd("\n", 2);
		shlvl = 1;
	}
	change_env(ms->env, "SHLVL", ft_itoa(shlvl));
}

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
	shlvl_add(ms);
	return(1);
}

void	add_env (t_env *env, char *var, char *val)
{
	t_env	*aux;
	t_env	*new;

	new= malloc(sizeof(t_env));
	aux = env;
	while (aux && aux->next)
		aux = aux->next;
	aux->next = new;
	aux = new;
	aux->evar = strdup(var);

	if (val)
		aux->eval = strdup(val);
	else
		aux->eval = NULL;

	aux->next = NULL;
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
	char    *str;
	t_env	*aux;

	if(!env || !var)
		return(NULL);
	aux = env;
	str = NULL;
	while (aux)
	{
		if(ft_strncmp (var, aux->evar, ft_strlen(var)) == 0
		&& ft_strlen(aux->evar) == ft_strlen(var))
		{
			str = aux->eval;
			return (str);
		}
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

	while (aux)
	{

		if(ft_strncmp (var, aux->evar, ft_strlen(var)) == 0
		&& ft_strlen(var) == ft_strlen(aux->evar))
		{
			return(0);
		}
		aux = aux->next;
	}
	//printf("la variable %s NO EXISTE EN EL ENVIROMENT\n", var);
	return(1);
}

void	change_env(t_env *env, char *var, char *val)
{
	t_env		*aux;

	aux = env;

	while (aux &&  !(ft_strncmp(aux->evar, var, (int)ft_strlen(aux->evar)) == 0
		&& ft_strlen(aux->evar) == ft_strlen(var)))
		aux = aux->next;
	if (aux->eval)
		free (aux->eval);
	if (val)
		aux->eval = strdup(val);
	else
		aux->eval =strdup("");
	return;
}

