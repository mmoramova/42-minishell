/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:00:53 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/23 11:55:20 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(long n)
{
	int	len;

	len = 1;
	while (n > 9)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*p;
	long	nbr;
	int		len;
	int		is_negative;

	nbr = n;
	is_negative = 0;
	if (nbr < 0)
	{
		is_negative = 1;
		nbr *= -1;
	}
	len = is_negative + ft_intlen(nbr);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	p[len] = '\0';
	while (len-- > 0)
	{
		p[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (is_negative)
		p[0] = '-';
	return (p);
}

/*int main(void)
{
    printf ("|%s|\n", ft_itoa(0));
    printf ("|%s|\n", ft_itoa(235));
    printf ("|%s|\n", ft_itoa(-325467));
    printf ("|%s|\n", ft_itoa(5));
    printf ("|%s|\n", ft_itoa(-2147483648));
}*/
