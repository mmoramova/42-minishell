/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:14:15 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/20 11:56:31 by josorteg         ###   ########.fr       */
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
		if (ft_strncmp(aux->evar,"-",2))
		{
			printf("declare\t-x\t");
			if (aux->eval == NULL)
				printf("%s\n", aux->evar);
				//string compare para el vacio
			else if (ft_strncmp(aux->eval, "",1) == 0)
				printf("%s=\"\"\n", aux->evar);
			else
				printf("%s=\"%s\"\n", aux->evar, aux->eval);
			aux=aux->next;
		}
	}
	exit(0);
}

int	export(t_ms *ms, char **com, int parent)
{
	int		i;
	t_env	*nenv;

	// export () imprime las variables
	if (com[1] == NULL)
		print_env_export(ms->env);
	else
	{
		i = 1;
		while (com[i])
		{
			printf("Adding with export\n");
			printf("adding=%s\n", com[i]);
			if (check_export(com[i]) == 1)
				return(1);
			nenv = malloc (sizeof(t_env));
			if (!nenv)
				return(1);
			nenv = new_env(com[i]);
			if(check_env(ms->env, nenv->evar) == 1)
			{
				printf("adding enviroment %s var name=%s\n", com[i], nenv->evar);
				add_env(ms->env,com[i]);
			}
			else
			{
				printf("changing enviroment %s\n", com[i]);
				if (ft_strchr(com[i],'=') == 0)
				{
					printf("Abort change, no = in export\n");
					return(0);
				}
				printf("variable a cambiar%s y valor%s\n",nenv->evar,nenv->eval);
				change_env(ms->env, nenv->evar, nenv->eval);
			}
			i++;
		}
	}
	if (parent == 1)
		return(0);
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

int	check_export(char	*nenv)
{
	int i;

	i = 0;
	if (ft_isalpha(nenv[0]) == 0 && nenv[0] != '_')
	{
		printf("fallo checkeo primera letra de %s\n", nenv);
		return(1);
	}
	i++;
	while (nenv[i] != '=' && nenv[i] != '\0')
	{
		if (ft_isalnum(nenv[i]) == 0 && nenv[i] != '_' && nenv[i] != '\0')
		{
			printf("fallo en checkeo formato\n");
			return(1);
		}
		i++;
	}
	printf("formato correcto\n");
	return(0);
}





