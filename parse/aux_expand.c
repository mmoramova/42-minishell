/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:00:23 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/03 17:51:19 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//jose i think we can do one file from aux_expand and expand because in each one are just 2 funcitons :)
int	ft_one_space(char *str)
{
	int	space_count;
	int	i;

	i = 0;
	space_count = 0;
	if (!str)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && (i == 0 || str[i - 1] != ' '))
			space_count++;
		i++;
	}
	return ((int)ft_strlen(str) + space_count + 1);
}

char	*ft_exp_quotes(char *str, int quot)
{
	int		i;
	char	*result;
	int		j;

	i = 0;
	j = 0;
	result = NULL;
	if (quot == 1)
		return (str);
	else if (quot == 0)
	{
		result = malloc (ft_one_space(str) * sizeof(char));
		if (!result || !str)
			return (NULL);
		while (str[i])
		{
			if (str[i] == ' ' && (i == 0 || str[i - 1] != ' '))
				result[j++] = ' ';
			if (str[i] != ' ')
				result[j++] = str[i];
			i++;
		}
	}
	result[j] = '\0';
	return (result);
}
