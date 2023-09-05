/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:53:44 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/05 18:20:26 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_lstsize(t_env *lst)
{
	int	len;

	len = 0;
	while (lst && lst->eval)
	{
		len++;
		lst = lst -> next;
	}
	return (len);
}

char	**env_toarray(t_ms *ms)
{
	int		i;
	char	**p;
	t_env	*env;
	char	*a;

	i = 0;
	env = ms->env;
	p = malloc(sizeof(char *) * (env_lstsize(env) + 1));
	if (!p)
		return (NULL);
	while (env)
	{
		if (env->eval)
		{
			a = ft_strjoin(env->evar, "=");
			p[i] = ft_strjoin(a, env->eval);
			free (a);
		}
		env = env -> next;
		i++;
	}
	p[i] = NULL;
	return (p);
}

int	check_env(t_env *env, char *var)
{
	t_env	*aux;

	if (!env || !var)
		return (1);
	aux = env;
	while (aux)
	{
		if (ft_strncmp (var, aux->evar, ft_strlen(var)) == 0
			&& ft_strlen(var) == ft_strlen(aux->evar))
			return (0);
		aux = aux->next;
	}
	return (1);
}

void	change_env(t_env *env, char *var, char *val)
{
	t_env		*aux;

	aux = env;
	while (aux && !(ft_strncmp(aux->evar, var, (int)ft_strlen(aux->evar)) == 0
			&& ft_strlen(aux->evar) == ft_strlen(var)))
		aux = aux->next;
	if (aux->eval)
		free (aux->eval);
	if (val)
		aux->eval = ft_strdup(val);
	else
		aux->eval = ft_strdup("");
	return ;
}

void	plus_env(t_env *env, char *var, char *val)
{
	t_env	*aux;
	char	*str;

	aux = env;
	while (aux && !(ft_strncmp(aux->evar, var, (int)ft_strlen(aux->evar)) == 0
			&& ft_strlen(aux->evar) == ft_strlen(var)))
		aux = aux->next;
	if (val)
	{
		str = ft_strjoin(aux->eval, val);
		change_env(aux, var, str);
		free (str);
	}
	else
		change_env(aux, var, ft_strjoin(aux->eval, ""));
	return ;
}
