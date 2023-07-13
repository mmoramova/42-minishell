/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:14:15 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/12 09:39:08 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// export variable=valor variable= "variable"="valor".....

// int	check_export(char *str)
// {

// }

//for export, we print no value vars, need format!!!!
// declare - x val="val"
	// 	-si el valor es NULL, no aparece el igual
	// 	-si el valor es 0 pero con igual, imprime ""


void    print_env_export(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		printf("declare\t-x\t");
		if (aux->eval == NULL)
			printf("%s\n", aux->evar);
			//string compare para el vacio
		else if (ft_strncmp(aux->eval, "",1) == 0)
			printf("%s=\"\"", aux->evar);
		else
			printf("%s=%s\n", aux->evar, aux->eval);
		aux=aux->next;
	}
}

int	export(t_env *env, char **com)
{
	int		i;
	t_env	*nenv;

	// export () imprime las variables
	if (com[1] == NULL)
		print_env_export(env);
	else
	{
		i = 1;
		while (com[i])
		{
			nenv = malloc (sizeof(t_env));
			if (!nenv)
				return(1);
			nenv = new_env(com[i]);

		}
	}
	return(0);
}
// EXPANSIONES Y COMILLAS!!!!! (Las haremos antes)

// variable:
// 	-empieza por letra o "_"
// 	-puede ir entre comillas pero siguiendo la primera rebla
// 	-Dentro solo vale letra, numero o "_"
// valor:
// 	-puede estar vacio sin igual entonces NULL (no modifica el valor si ya existe)
// 	-puede estar vacio despues del igual "" (cadena vacia) (no modifica el valor si ya existe)
// 	-puede ir entre comillas.
// 	-ninguna regla especial.






