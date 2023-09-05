/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:18:01 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/05 18:19:05 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_export_plus(char *nenv)
{
	int	i;

	i = 0;
	i = 0;
	if (ft_isalpha(nenv[0]) == 0 && nenv[0] != '_')
		return (1);
	i++;
	while (nenv[i] != '+' && nenv[i] != '\0')
	{
		if (ft_isalnum(nenv[i]) == 0 && nenv[i] != '_' && nenv[i] != '\0')
			return (1);
		i++;
	}
	if (!nenv[i])
		return (1);
	if (nenv[i + 1] && nenv[i + 1] == '=')
		return (0);
	return (1);
}
