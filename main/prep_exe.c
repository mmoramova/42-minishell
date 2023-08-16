/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:20:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/04 15:33:47 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_types (t_tok *token, int type)
{
	int	len;

	len = 0;
	while(token)
	{
		if (token->type == type)
			len++;
		token = token -> next;
	}
	return(len);
}

int	ft_parent_exe(t_ms	*ms, char **command)
{
	if ((ft_strncmp(command[0],"cd",2) == 0
	|| ft_strncmp(command[0],"exit",4) == 0
	|| ft_strncmp(command[0],"unset",5) == 0
	|| ((ft_strncmp(command[0],"export",6) == 0) && command[1]))
	&& (ft_count_types(ms->start, 1) == 0))
		return (1);
	else
		return (0);
}

int	ft_open(t_ms *ms, int type, int fd[2], char *file)
{
	if (type == 2 || type == 3)
	{
		if (fd[0])
			close(fd[0]);
		if (type == 2)
			fd[0] = open(file, O_RDONLY, 0666);
		else if (type == 3)
			fd[0] = ms->heredocfd;
		if (fd[0] == -1)
		{
			ft_exit(1, file, strerror(errno), NULL);
			return(1);
		}
	}
	else
	{
		if (fd[1])
			close(fd[1]);
		if (type == 4)
			fd[1] = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (type == 5)
			fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND , 0666);
		if (fd[1] == -1)
		{
			ft_exit(1, file, strerror(errno), NULL);
			return(1);
		}
	}
	return(0);
}

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

t_ex	*ft_exlstnew(t_ms	*ms, t_tok *token)
{
	t_ex	*lst;
	int		i;
	int		res;

	i = 0;
	res = 0;
	lst = (t_ex *) malloc(sizeof(t_ex));
	if (!lst)
		return (NULL);
	lst -> next = NULL;
	lst -> command = malloc(sizeof(char *) * (ft_lstcmd_count(token) + 1));
	while (token && token->type != 1)
	{
		if (token->type == 0)
			lst -> command[i++] = ft_strdup(token ->content);
		if (token->type > 1 && res != 1)
		{
			res = ft_open(ms, token->type, lst->fd, token->next->content);
			token = token -> next;
		}
		token = token -> next;
	}
	lst -> command[i] = NULL;
	lst -> parent = ft_parent_exe(ms, lst -> command);
	//printf("comand=%s y parent=%d\n", lst -> command[0], lst -> parent);
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
	ms->cntcmds = 0;
	ms->heredocfd =  heredoc_fillfd(ms, token);
	while (token && token->content[0])
	{
		ft_exlstadd_back(&aux, ft_exlstnew(ms, token));
		while (token && token->type != 1)
			token = token->next;
		if (token)
			token = token->next;
		ms->cntcmds++;
	}
	ms->exe = aux;

	//TODO FREE TOKEN

	/*start of printing - delete later*/
	// int i = 0;
	// while (aux)
	// {
	// 	i = 0;
	// 	printf("Command is: ");
	// 	while (aux->command[i])
	// 		printf("%s ", aux->command[i++]);
	// 	printf("\n");
	// 	printf("fd[0]=%d || fd[1]=%d\n",aux->fd[0],aux->fd[1]);
	// 	aux=aux->next;
	// }
	// printf("We have %d commands.\n", cntcmds);
	/*end of printing*/
}
