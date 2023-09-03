/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:54:25 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/03 18:07:41 by mmoramov         ###   ########.fr       */
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

	(void)ms;
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
	return (lst);
}

void	ft_toklstadd_back(t_tok **lst, t_tok *new)
{
	if (*lst)
		ft_toklstlast(*lst)-> next = new;
	else
		*lst = new;
}
