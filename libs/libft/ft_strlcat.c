/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:03:16 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/21 23:23:44 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	len_dst = (size_t) ft_strlen(dst);
	len_src = (size_t) ft_strlen(src);
	if (len_dst > dstsize || dstsize == 0)
		return (len_src + dstsize);
	while (src[i] && i < (dstsize - len_dst - 1) && dstsize != len_dst)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}

/*int main(void)
{
    char string[] = "Hello there";
    char buffer[19] = "jstystysty";
    int r;

    r = ft_strlcat(buffer, string, 5);

    printf("'%s' into '%s', length %d\n",
            string,
            buffer,
            r
          );
}*/
