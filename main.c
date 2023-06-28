/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:17 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/28 19:17:03 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "inc/minishell.h"

int	main(int argc, char **argv) // char *env[])
{
	char *str;

	if (argc != 1 && argv[0])
		return(1);

	while (1)
	{
		str = readline("minishell>");
		printf("%s\n", str);
		if (str)
		{
			add_history(str);
		}
	}
	//return (0);
}
