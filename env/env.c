/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 08:17:04 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/02 17:40:38 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_env(t_ms *ms, char **env)
{
	int		i;
	t_env	*aux;
	t_env	*new;

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
	return (1);
}

void	add_env(t_env *env, char *var, char *val)
{
	t_env	*aux;
	t_env	*new;

	new = malloc(sizeof(t_env));
	aux = env;
	while (aux && aux->next)
		aux = aux->next;
	aux->next = new;
	aux = new;
	aux->evar = ft_strdup(var);
	if (val)
		aux->eval = ft_strdup(val);
	else
		aux->eval = NULL;
	aux->next = NULL;
}

t_env	*new_env(char *env)
{
	t_env		*new;
	int			k;
	size_t		j;

	new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
	j = ft_strchrn(env, '=');
	if (!(ft_strchr(env, '=')))
	{

		new->evar = ft_strdup(env);
		new->eval = NULL;
		new->next = NULL;
		return (new);
	}
	k = ft_strlen(env);
	new->evar = ft_substr(env, 0, j);
	new->eval = ft_substr(env, j + 1, k);
	new->next = NULL;
	return (new);
}

t_env	*new_env_plus(char *env)
{
	t_env		*new;
	int			k;
	size_t		j;

	new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
	j = ft_strchrn(env, '+');
	k = ft_strlen(env);
	new->evar = ft_substr(env, 0, j);
	new->eval = ft_substr(env, j + 2, k);
	new->next = NULL;
	return (new);
}

char	*get_env_value(t_env *env, char *var)
{
	char	*str;
	t_env	*aux;

	if (!env || !var)
		return (NULL);
	aux = env;
	str = NULL;
	while (aux)
	{
		if (ft_strncmp(var, aux->evar, ft_strlen(var)) == 0
			&& ft_strlen(aux->evar) == ft_strlen(var))
		{
			if (aux->eval)
				str = aux->eval;
			return (str);
		}
		aux = aux->next;
	}
	return (str);
}
