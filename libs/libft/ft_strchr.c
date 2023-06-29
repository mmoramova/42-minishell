/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:58:25 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/29 15:40:09 by josorteg         ###   ########.fr       */
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

int		ft_strchrn(const char *s, int c)
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
