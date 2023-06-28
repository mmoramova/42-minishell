/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:45:01 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/21 22:51:20 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*a;

	a = s;
	while (n--)
	{
		if (*a == (char) c)
			return ((void *) a);
		a++;
	}
	return (NULL);
}

/*int main(void)
{
	const char *str;
	int c;

	str = "tripo\0uille";
	//c = 't' + 256;
	c = '\0';
	printf("%s, %s, %c", memchr(str, c, 7), ft_memchr(str, c, 7),(char)c);
}*/
