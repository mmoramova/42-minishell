/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:14:15 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/31 00:24:41 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_export(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (ft_strncmp(aux->evar, "-", 2))
		{
			printf("declare -x ");
			if (aux->eval == NULL)
				printf("%s\n", aux->evar);
			else if (ft_strncmp(aux->eval, "", 1) == 0)
				printf("%s=\"\"\n", aux->evar);
			else
				printf("%s=\"%s\"\n", aux->evar, aux->eval);
			aux = aux->next;
		}
	}
}

int	add_exp(t_ms *ms, char **com, int i)
{
	t_env	*nenv;

	nenv = malloc (sizeof(t_env));
	if (!nenv)
		return (1);
	nenv = new_env(com[i]);
	if (check_env(ms->env, nenv->evar) == 1)
		add_env(ms->env, nenv->evar, nenv->eval);
	else if (ft_strchr(com[i], '=') != 0)
		change_env(ms->env, nenv->evar, nenv->eval);
	return (0);
}

int	export(t_ms *ms, char **com, int parent)
{
	int		i;
	int		error;

	(void)parent;
	error = 0;
	if (com[1] == NULL)
		print_env_export(ms->env);
	else
	{
		i = 0;
		while (com[++i])
		{
			if (check_export(com[i]) == 1)
			{
				ms->exitstatus = 1;
				ft_error4(1, com[0], com[i], "not a valid identifier");
				error = 1;
			}
			else
			{
				if (add_exp(ms, com, i) == 1)
					return (1);
			}
		}
	}
	return (error);
}

int	check_export(char *nenv)
{
	int	i;

	i = 0;
	if (ft_isalpha(nenv[0]) == 0 && nenv[0] != '_')
		return (1);
	i++;
	while (nenv[i] != '=' && nenv[i] != '\0')
	{
		if (ft_isalnum(nenv[i]) == 0 && nenv[i] != '_' && nenv[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}
