/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:05:32 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/21 23:51:54 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return ((size_t) ft_strlen(src));
}

/*int main(void)
{
    char string[] = "Hello there, Venus";
    char buffer[19] = "jstystysty";
    int r;

    r = ft_strlcpy(buffer, string, 5);

    printf("Copied '%s' into '%s', length %d\n",
            string,
            buffer,
            r
          );
}*/
