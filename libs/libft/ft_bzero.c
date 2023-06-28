/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:05:14 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/21 22:21:45 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*b;

	b = s;
	while (n--)
		*b++ = '\0';
}

/*int main(void)
{
	char s1[50] = "abcdefghijklmnop";
	char s2[50] = "abcdefghijklmnop";

	bzero(s1 + 4, 2);
	ft_bzero(s2 + 4, 2);
	printf ("%s\n%s", s1, s2);
}*/
