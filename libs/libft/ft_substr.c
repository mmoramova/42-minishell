/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:44:58 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/23 11:51:30 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	len_s;
	unsigned int	i;
	char			*p;

	len_s = ft_strlen(s);
	i = 0;
	if (len_s <= start)
		len = 0;
	else if (len_s < start + len)
		len = len_s - start;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (s[i] && len--)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

/*int main(void) {
	char s1[50] = "Hello123456";
	
	char *s2;
	s2 = ft_substr(s1, 10, 3);
	printf ("%s, %s", s1, s2);
}*/
