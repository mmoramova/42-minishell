/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 08:50:15 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/05 21:27:35 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
		{
			i++;
			if (str[i] == '\0')
				return (1);
		}
	}
	return (0);
}

int	b_echo(char **com)
{
	int		n;
	int		m;
	int		i;
	int		j;

	n = 0;
	i = 0;
	m = 0;
	while (com[i] && com[++i])
	{
		while (com[i] && check_n(com[i]) == 1 && n == 0)
			(m = 1 && i++);
		j = 0;
		while (com[i] && com[i][j] != '\0')
		{
			write (1, &com[i][j], 1);
			(n = 1 && j++);
		}
		if (com[i] && com [i + 1])
			write(1, " ", 1);
	}
	if (m == 0)
		write(1, "\n", 1);
	return (0);
}
