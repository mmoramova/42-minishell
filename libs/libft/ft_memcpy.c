/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:15:41 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/21 22:35:40 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;

	s = src;
	d = dst;
	if (!d && !s)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dst);
}

/*int main(void)
{
	char s1[50] = "abcdefghijklmnop";
	char s2[50] = "hello";

	//memcpy(s1+5, s2, 5);
	//ft_memcpy(s1, s2,6);
	ft_memcpy(((void *)5), ((void *)0), 3);
	printf ("%s\n%s", s1, s2);
}*/
