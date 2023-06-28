/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:29:45 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/21 23:37:48 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	int		start;
	int		end;

	start = 0;
	while (s1[start])
	{
		if (ft_strchr(set, s1[start]) == NULL)
			break ;
		start++;
	}
	if (ft_strlen(s1) > 0)
		end = ft_strlen(s1) - 1;
	else
		end = 0;
	while (s1[end] && end > 0)
	{
		if (ft_strchr (set, s1[end]) == NULL)
			break ;
		end--;
	}
	p = ft_substr(s1, start, end - start + 1);
	return (p);
}

/*int main(void)
{
	char s1[50] = "hjg5";
	char s2[15] = "12345";

	char *s3;
	s3 = ft_strtrim(s1, s2);

	printf ("|%s|, |%s|, |%s|", s1, s2 , s3);
}*/
