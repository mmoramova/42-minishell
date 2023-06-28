/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:12:06 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/21 23:15:34 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*a;
	unsigned const char	*b;

	a = s1;
	b = s2;
	while (n--)
	{
		if (*a++ != *b++)
			return (*--a - *--b);
	}
	return (0);
}

/*int main(void)
{
	//char s1[50] = "abcdefghijklmnop";
	//char s2[48] = "hello";	
 	char *s1 = "atoms\0\0\0\0";
 	char *s2 = "atoms\0abc";

	printf("%d, %d", memcmp(s1, s2, 8), ft_memcmp(s1, s2, 8));
}*/
