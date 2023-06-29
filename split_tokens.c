/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:48:00 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/29 20:14:31 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"inc/minishell.h"

int	ft_wordlen_wq(char const *s, char c)
{
	int		len;

	len = 0;
	while (s[len] && s[len] != c)
	{
		if (s[len] == '\'')
		{
			len++;
			while (s[len] && s[len] != '\'')
				len++;
		}
		if (s[len] == '\"')
		{
			len++;
			while (s[len] && s[len] != '\"')
				len++;
		}
		len++;
	}
	return (len);
}

t_tok	*ft_toklstnew(char *content)
{
	t_tok	*lst;

	lst = (t_tok *) malloc(sizeof(t_tok));
	if (!lst)
		return (NULL);
	lst -> content = content;
	lst -> next = NULL;
	lst -> previous = NULL;
	return (lst);
}

t_tok	*ft_toklstlast(t_tok *lst)
{
	while (lst && lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_toklstadd_back(t_tok **lst, t_tok *new)
{
	if (*lst)
		ft_toklstlast(*lst)-> next = new;
	else
		*lst = new;
}

t_tok	*ft_split_tok(char *s, char c)
{
	int		i;
	t_tok	*lst;

	i = 0;
	lst = NULL;

	while (*s)
	{
		if (*s != c)
		{
			//printf("WORDLEN IS: %d\n", ft_wordlen_wq(s, c));
			ft_toklstadd_back(&lst, ft_toklstnew(ft_substr(s, 0, ft_wordlen_wq(s, c))));
			i++;
			s += ft_wordlen_wq(s, c) - 1;
		}
		s++;
	}
	return (lst);
}


/*int main(void)
{
	char *s  = "'z\"e\"ro' one \"two twoandhalf\" 'three four'";

	 t_tok *lst;
	 lst = ft_split_tok(s, ' ');


	while (lst)
	{
		printf("%s\n", lst->content);
		lst=lst->next;
	}

	//gcc split_tokens.c libs/libft/libft.a && ./a.out
}*/



