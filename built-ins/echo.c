/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 08:50:15 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/27 13:28:18 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
*/

int	check_n(char *str)
{
	int i;


	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
		{
			i++;
			if (str[i] == '\0')
			{
				return (1);
			}
		}
	}
	return (0);
}

int	b_echo(char **com)
{
	int		n;
	int		m;
	int		i;
	int 	j;

	n = 0;
	i = 0;
	m = 0;
	while (com[++i])
	{
		while(check_n(com[i]) == 1 && n == 0)
		{
			m = 1;
			i++;
		}
		j = 0;
		while(com[i][j])
		{
			n = 1;
			write (1,&com[i][j++],1);
		}
		if (com [i + 1])
			write(1," ",1);
	}
	if (m == 0)
		write(1,"\n",1); //1 espace between arguments
	exit (0);
}

/*

int	main	(int args,char **argv)
{
	args = 0;
	b_echo(argv);
	return (0);
}
//gcc -Wall -Wextra -Werror echo.c


*/
