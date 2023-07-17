/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:48:00 by mmoramov          #+#    #+#             */
/*   Updated: 2023/07/17 18:30:39 by josorteg         ###   ########.fr       */
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


int ft_tok_addtype(char *s)
{
	int	i;

	i = 0;
	if (s[i + 1] && ft_strchr("<", s[i]) && s[i] == s[i + 1])
		return (3);
	if (s[i + 1] && ft_strchr(">", s[i]) && s[i] == s[i + 1])
		return (5);
	if (ft_strchr("<", s[i]))
		return (2);
	if (ft_strchr(">", s[i]))
		return (4);
	if (ft_strchr("|", s[i]))
		return (1);
	return (0);
}


t_tok	*ft_toklstnew(t_ms *ms, char *content)
{
	t_tok	*lst;
	char	*str;

	lst = (t_tok *) malloc(sizeof(t_tok));
	if (!lst)
		return (NULL);

	if (ft_strchrn (content,'$') == - 1)
		lst->content = ft_quotes_remove(content);
	else
	{
		printf("---before expand:%s\n",content);
		str = ft_expand(ms, content);
		printf("---after expand :%s\n",str);
		lst -> content = ft_quotes_remove(str);
		printf("---after expand + quotes:%s\n",lst -> content);
	}
	lst -> next = NULL;
	lst -> previous = NULL;
	lst -> type = ft_tok_addtype(content);
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

void	ft_tok_checks(t_tok *lst)
{
	t_tok	*previous;

	previous = lst;
	if (lst->type == 1)
	{
		exit(1);
		//TODO ERROR PIPE
	}
	lst = lst -> next;

	while (lst)
	{
		//ERRORS IN TOKENS
		if ((previous->type > 1 && (lst->type != 0))
			|| (previous->type == 1 && lst->type == 1)
			|| (lst->type > 0 && !lst->next))
		{
			//TODO ERROR
			exit(1);
		}
		previous = lst;
		lst = lst -> next;
	}

}

t_tok	*ft_split_tok(t_ms *ms, char c)
{
	t_tok	*lst;
	char	*s;

	s = ms->line;
	lst = NULL;
	while (*s)
	{
		if (*s != c)
		{
			//printf("WORDLEN IS: %d\n", ft_wordlen_wq(s, c));
			ft_toklstadd_back(&lst, ft_toklstnew(ms, ft_substr(s, 0, ft_wordlen_wq(s, c))));
			s += ft_wordlen_wq(s, c) - 1;

		}
		s++;
	}
	ft_toklstadd_previous(lst);
	ft_tok_checks(lst);

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


