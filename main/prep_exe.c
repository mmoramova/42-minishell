/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:20:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/12 19:47:05 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_lstcmd_count(t_tok *token)
{
	int	len;

	len = 0;
	while(token && token->type != 1)
	{
		if (token->type == 0)
			len++;
		else
			len--;
		token = token -> next;
	}
	return(len);
}

t_ex	*ft_exlstnew(t_tok *token)
{
	t_ex	*lst;
	int		i;

	i = 0;
	lst = (t_ex *) malloc(sizeof(t_ex));
	if (!lst)
		return (NULL);
	lst -> next = NULL;
	//lst -> fd[0] = NULL;
	//lst -> fd[1] = NULL;
	lst -> command = (char **) malloc(sizeof(char) * ft_lstcmd_count(token));

	while (token && token->type != 1)
	{
		//comands
		if (token->type == 0)
		{
			lst -> command[i] = ft_strdup(token ->content);
			i++;
		}

		//read <
		if (token->type == 2)
		{
			if (lst->fd[0])
				close(lst->fd[0]);
			lst->fd[0] = open(token->next->content, O_RDONLY, 0666);
			if (lst->fd[0] == -1)
				exit(1); //TODO EXIT
			token = token -> next;
		}

		//read >
		if (token->type == 4)
		{
			if (lst->fd[1])
				close(lst->fd[1]);
			lst->fd[1] = open(token->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (lst->fd[1] == -1)
				exit(1); //TODO EXIT
			token = token -> next;
		}
		//read >>
		if (token->type == 5)
		{
			if (lst->fd[1])
				close(lst->fd[1]);
			lst->fd[1] = open(token->next->content, O_WRONLY | O_CREAT, 0666);
			if (lst->fd[1] == -1)
				exit(1); //TODO EXIT
			token = token -> next;
		}

		token = token -> next;
	}

	return (lst);
}

t_ex	*ft_exlstlast(t_ex *lst)
{
	while (lst && lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_exlstadd_back(t_ex **lst, t_ex *new)
{
	if (*lst)
		ft_exlstlast(*lst)-> next = new;
	else
		*lst = new;
}

void	ft_prep_exe(t_ms	*ms)
{
	t_ex	*aux;
	t_tok	*token;

	aux = NULL;
	token = ms->start;
	while (token)
	{
		ft_exlstadd_back(&aux, ft_exlstnew(token));
		while (token && token->type != 1)
			token = token->next;
		if (token)
			token = token->next;
	}
	ms->exe = aux;
	//TODO FREE TOKEN

		/*token only for printing:*/
	int i = 0;
	while (aux)
	{
		i = 0;
		while (aux->command[i])
		{
			printf("command: %s \n", aux->command[i]);
			i++;
		}
		printf("fd[0]=%d || fd[1]=%d",aux->fd[0],aux->fd[1]);

		aux=aux->next;
	}
}
