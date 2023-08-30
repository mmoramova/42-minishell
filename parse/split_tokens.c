/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:48:00 by mmoramov          #+#    #+#             */
/*   Updated: 2023/08/30 18:46:33 by mmoramov         ###   ########.fr       */
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

t_tok	*ft_toklstlast(t_tok *lst)
{
	while (lst && lst -> next)
		lst = lst -> next;
	return (lst);
}

t_tok	*ft_toklstnew(t_ms	*ms, t_tok	*tokens, char *content)
{
	t_tok	*lst;
	char	*str;

	(void)ms;
	lst = (t_tok *) malloc(sizeof(t_tok));
	if (!lst)
		return (NULL);
	lst -> previous = ft_toklstlast(tokens);
	lst -> type = ft_tok_addtype(content);
	lst -> next = NULL;
	if ((lst -> previous && lst -> previous -> type == 3))
		lst->content = content;
	else if (ft_strchrn (content,'$') == - 1)
		lst->content = ft_q_r(content);
	else
	{
		free(lst);
		str = ft_expand(ms, content);
		lst = ft_expand_token(str);
		if (lst)
			lst -> previous = ft_toklstlast(tokens);
	}
	//free(content);
	return (lst);
}

void	ft_toklstadd_back(t_tok **lst, t_tok *new)
{
	if (*lst)
		ft_toklstlast(*lst)-> next = new;
	else
		*lst = new;
}

int	ft_tok_checks(t_ms *ms, t_tok *lst)
{
	t_tok	*previous;

	if (!lst)
		return (1);
	previous = lst;
	if (lst->type == 1)
	{
		ft_error2(ms, 258, "syntax error near unexpected token `", lst->content, "\'");
		return (1);
	}
	if (lst->type > 1 && !lst->next)
	{
		ft_error2(ms, 258, "syntax error near unexpected token `", "newline", "\'");
		return (1);
	}
	lst = lst -> next;
	while (lst)
	{
		if ((previous->type > 1 && (lst->type != 0))
			|| (previous->type == 1 && lst->type == 1))
		{
			ft_error2(ms, 258, "syntax error near unexpected token `", lst->content, "\'");
			return (1);
		}
		if ((lst->type > 0 && !lst->next))
		{
			ft_error2(ms, 258, "syntax error near unexpected token `", "newline", "\'");
			return (1);
		}
		previous = lst;
		lst = lst -> next;
	}
	return (0);
}

t_tok	*ft_split_tok(t_ms *ms, char c)
{
	t_tok	*lst;
	char	*s;
	char	*r;

	//s = ft_expand(ms,ms->line);
	s = ms->line;
	lst = NULL;

	while (*s)
	{
		if (*s != c)
		{
			r = ft_substr(s, 0, ft_wordlen_wq(s, c));
			ft_toklstadd_back(&lst, ft_toklstnew(ms, lst, r));
			//free(r);
			s += ft_wordlen_wq(s, c) - 1;
		}
		s++;
	}

	if (ft_tok_checks(ms, lst) == 1)
		lst = NULL;
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


