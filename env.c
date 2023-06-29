/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 08:17:04 by josorteg          #+#    #+#             */
/*   Updated: 2023/06/29 16:39:12 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"inc/minishell.h"

t_env   *get_env(char **env)
{
	int     i;
	t_env   *aux;
	t_env   *new;
	t_env   *res;
	t_env   *last;
	int     j;
	
   i = 0;
   while (env[i])
	{
		if (aux)
			last=aux;
		j = ft_strchrn(env[i], '=');
		new = malloc(sizeof(t_env));
		new->evar = ft_substr(env[i], 0, j);
		new->eval = ft_substr(env[i], j + 1, 0xffffff);
		new->next = NULL;
		if (i == 0)
			res = new;
		if(last)
			last->next = new;
		aux = new;
		i++;
	}
	return(res);
}

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
void    print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->evar, env->eval);
		env=env->next;
	}
	return;
}