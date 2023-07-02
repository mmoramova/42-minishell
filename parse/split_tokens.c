/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:48:00 by mmoramov          #+#    #+#             */
/*   Updated: 2023/07/02 19:04:47 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wordlen_wq(char const *s, char c)
{
	int		i;
	char	aq;

	aq = '\0';
	i = 0;
	if (s[i + 1] && ft_strchr("<>", s[i]) && s[i] == s[i + 1])
		return (2);
	if (ft_strchr("|<>", s[i]))
		return (1);
	while (s[i] && (s[i] != c || aq != '\0')
		&& (!ft_strchr("|<>", s[i]) || aq != '\0'))
	{
		if (ft_strchr("\'\"", s[i]) && aq == '\0')
			aq = s[i];
		else if (ft_strchr("\'\"", s[i]) && aq != '\0' && s[i] == aq)
			aq = '\0';
		i++;
	}
	return (i);
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

void	ft_toklstadd_previous(t_tok *lst)
{
	t_tok	*previous;

	previous = lst;
	lst = lst -> next;
	while (lst)
	{
		lst -> previous = previous;
		previous = lst;
		lst = lst -> next;
	}
}

t_tok	*ft_split_tok(char *s, char c)
{
	t_tok	*lst;

	lst = NULL;
	while (*s)
	{
		if (*s != c)
		{
			//printf("WORDLEN IS: %d\n", ft_wordlen_wq(s, c));
			ft_toklstadd_back(&lst, ft_toklstnew(ft_substr(s, 0, ft_wordlen_wq(s, c))));
			s += ft_wordlen_wq(s, c) - 1;
		}
		s++;
	}
	ft_toklstadd_previous(lst);
	return (lst);
}

/*
int main(void)
{
	char *s  = "'z\"e\"ro' one \"two twoandhalf\" 'three four'";

	 t_tok *lst;
	 lst = ft_split_tok(s, ' ');


	while (lst)
	{
		printf("%s\n", lst->content);
		lst=lst->next;
	}

	printf("\n-------------previous:\n");
	lst = ft_split_tok(s, ' ');
	lst=lst->next;
	while (lst)
	{
		printf("%s\n", lst->previous->content);
		lst=lst->next;
	}

	//gcc split_tokens.c libs/libft/libft.a && ./a.out
}
*/


