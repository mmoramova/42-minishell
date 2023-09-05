/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:54:25 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/05 18:30:39 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	str = NULL;
	lst = (t_tok *) malloc(sizeof(t_tok));
	if (!lst)
		return (NULL);
	lst -> previous = ft_toklstlast(tokens);
	lst -> type = ft_tok_addtype(content);
	lst -> next = NULL;
	if ((lst -> previous && lst -> previous -> type == 3))
		lst->content = ft_strdup(content);
	else if (ft_strchrn(content, '$') == -1)
		lst->content = ft_q_r(content);
	else
	{
		free(lst);
		str = ft_expand(ms, content);
		lst = ft_expand_token(str);
		if (lst)
			lst -> previous = ft_toklstlast(tokens);
	}
	if (str)
		free(str);
	return (lst);
}

void	ft_toklstadd_back(t_tok **lst, t_tok *new)
{
	if (*lst)
		ft_toklstlast(*lst)-> next = new;
	else
		*lst = new;
}

int	ft_lstcmd_count(t_tok *token)
{
	int	len;

	len = 0;
	while (token && token->type != 1)
	{
		if (token->type == 0)
			len++;
		else
			len--;
		token = token -> next;
	}
	return (len);
}
