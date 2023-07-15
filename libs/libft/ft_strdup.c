/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:23:41 by mmoramov          #+#    #+#             */
/*   Updated: 2023/07/13 18:10:28 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	len_s1;

	len_s1 = ft_strlen(s1) + 1;
	p = (char *)malloc(len_s1 * sizeof(char)); // sostituido void * por char *
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, len_s1);
	return (p);
}
