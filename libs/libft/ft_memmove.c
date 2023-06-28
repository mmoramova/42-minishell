/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:47:30 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/21 22:53:24 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;

	s = src;
	d = dst;
	if (!d && !s)
		return (NULL);
	if (d > s)
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	else if (s > d)
	{
		while (n--)
			*d++ = *s++;
	}
	return (dst);
}

/*int main(void)
{
	char s1[50] = "abcdefghijklmnop";
	char s2[50] = "hello";

	//memmove(s1+3, s1, 5);
	//ft_memmove(s1+3, s1,5);
	ft_memmove(((void *)0), ((void *)0), 0);
	printf ("%s\n%s", s1, s2);
}*/
