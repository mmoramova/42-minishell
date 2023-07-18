/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcomand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:34:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/18 18:18:35 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    print_env(t_env *env)
{
	t_env	*aux;

	aux = env;

	while (aux)
	{
		if (aux->eval)
			printf("%s=%s\n", aux->evar, aux->eval);
		aux=aux->next;
	}
	return;
}

int	enviroment(t_env *env)
{
	//char	*new;


	// if(check_env(env, "_") == 0)
	// {

	// 	new = malloc((ft_strlen(get_env_value(env,"_")) + 4) * sizeof(char));

	// 	new = ft_strjoinfree(get_env_value(env,"_"), "env");

	// 	change_env(env, "_", new);

	// }
	print_env(env);
	exit (0);
}
//No imprime comillas
//No imprime sin valor
//Imprime vacio con valor vacio
//Falta la _= para imprimir que en export no se imprime y que cambia con CATcada comando.
