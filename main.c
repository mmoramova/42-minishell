/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:17 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/29 17:24:36 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "inc/minishell.h"

int	main(int argc, char **argv, char *env[])
{
	t_ms	ms;

	if (argc != 1 && argv[0])
		return(1);
	ms.env = get_env(env);
	//print enviroment (like env, only for test)
	//print_env(ms.env);
	printf("%s\n",get_env_value(ms.env ,"PATH"));

	while (1)
	{
		ms.line = readline("minishell>");
		
		if (ms.line)
		{
			add_history(ms.line);
		}
	}
	//return (0);
}
