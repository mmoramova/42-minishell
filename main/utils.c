/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:48:38 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/03 18:15:39 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	int		j;
	int		i;
	char	*p;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return (s1);
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	j = -1;
	while (s2[++j])
		p[i + j] = s2[j];
	p[i + j] = '\0';
	free(s1);
	return (p);
}

char	*ft_strjoinfree2(char *s1, char *s2)
{
	int		j;
	int		i;
	char	*p;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return (s1);
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	j = -1;
	while (s2[++j])
		p[i + j] = s2[j];
	p[i + j] = '\0';
	free(s1);
	free(s2);
	return (p);
}
