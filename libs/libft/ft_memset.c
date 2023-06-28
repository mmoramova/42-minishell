/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:29:11 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/21 23:41:05 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;

	s = b;
	while (len--)
		*s++ = (unsigned char)c;
	return (b);
}

/*int main(void)
{
	char s1[50] = "abcdefghijklmnop";
	char s2[50] = "abcdefghijklmnop";
	
	memset(s1 + 5, 'k', 4);
	ft_memset(s2 + 5, 'k', 204);
	printf ("%s\n%s", s1, s2);
}*/
