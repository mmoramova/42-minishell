/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:20:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/03 18:41:10 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parent_exe(t_ms	*ms, char **command)
{
	if (command[0] && ((ft_strncmp(command[0], "cd", 2) == 0
				|| ft_strncmp(command[0], "exit", 4) == 0
				|| ft_strncmp(command[0], "unset", 5) == 0
				|| ((ft_strncmp(command[0], "export", 6) == 0) && command[1])))
		&& (ft_count_types(ms->start, 1) == 0))
		return (1);
	else
		return (0);
}

t_ex	*ft_exlstinit(void)
{
	t_ex	*lst;

	lst = (t_ex *) malloc(sizeof(t_ex));
	if (!lst)
		return (NULL);
	lst -> previous = NULL;
	lst -> next = NULL;
	lst->fd[0] = -2;
	lst->fd[1] = -2;
	lst -> command = NULL;
	return (lst);
}

t_ex	*ft_exlstnew(t_ms	*ms, t_tok *token)
{
	t_ex	*lst;
	int		i;
	int		res;

	i = 0;
	res = 0;
	lst = ft_exlstinit();
	if (!lst)
		return (NULL);
	lst -> command = malloc(sizeof(char *) * (ft_lstcmd_count(token) + 1));
	while (token && token->type != 1)
	{
		if (token->type == 0)
			lst -> command[i++] = ft_strdup(token ->content);
		if (token->type > 1)
		{
			if (res != 1)
				res = openfd(ms, token->type, lst->fd, token->next->content);
			token = token -> next;
		}
		token = token -> next;
	}
	lst -> command[i] = NULL;
	lst -> parent = ft_parent_exe(ms, lst -> command);
	return (lst);
}

void	ft_exlstadd_back(t_ex **lst, t_ex *new)
{
	t_ex	*aux;

	aux = *lst;
	if (*lst)
	{
		while (aux && aux -> next)
			aux = aux -> next;
		aux->next = new;
	}
	else
		*lst = new;
}

void	ft_prep_exe(t_ms *ms)
{
	t_ex	*aux;
	t_tok	*token;

	aux = NULL;
	token = ms->start;
	ms->cntcmds = 0;
	ms->heredocfd = -2;
	ms->heredocfd = heredoc_fillfd(ms, token);
	while (token && (token->content[0] || token->type == 0) && g_process != 1)
	{
		ft_exlstadd_back(&aux, ft_exlstnew(ms, token));
		while (token && token->type != 1)
			token = token->next;
		if (token)
			token = token->next;
		ms->cntcmds++;
	}
	ms->exe = aux;
	free_tok(ms->start);
}
