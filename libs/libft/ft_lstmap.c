/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:49:46 by mmoramov          #+#    #+#             */
/*   Updated: 2022/10/28 12:27:30 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*current;
	void	*temp;

	new = NULL;
	while (lst)
	{
		temp = f(lst -> content);
		current = ft_lstnew(temp);
		if (!current)
		{
			ft_lstclear(&new, del);
			del(temp);
			return (NULL);
		}
		ft_lstadd_back(&new, current);
		lst = lst -> next;
	}
	return (new);
}
