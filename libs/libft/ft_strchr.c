/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:58:25 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/05 18:22:12 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && (*s != (char) c))
		s++;
	if (*s == (char) c)
		return ((char *) s);
	return (NULL);
}

int	ft_strchrn(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != (char) c))
		i++;
	if (s[i] == (char) c)
		return (i);
	return (-1);
}

/*int main(void)
{
	const char *str;
	int c;

	str = "tripouille";
	//c = 't' + 256;
	c = '\n';
	printf("%s, %s, %c", strchr(str, c), ft_strchr(str, c),(char)c);
}*/
