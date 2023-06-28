/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:20:43 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/21 23:33:38 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*s2)
		return ((char *) s1);
	while (s1[i] && i < len)
	{
		if (s1[i] == s2[j])
		{
			while (s2[j] && s1[i + j] == s2[j] && i + j < len)
				j++;
			if (s2[j] == '\0')
				return ((char *) s1 + i);
			j = 0;
		}
		i++;
	}
	return (NULL);
}

/*
int main(void)
{
 	char *s1 = "see FF your FF return FF now FF";
 	char *s2 = "FF";   
   	char *ptr;

    ptr = ft_strnstr(s1, s2, 15);
	printf("%s",ptr);
}
*/
