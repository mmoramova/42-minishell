/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:20:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/17 20:43:00 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int ft_heredoc(char *file)
{
	int	pid;
	int	fd[2];
	char *ch;

	ch = file;
	printf("Hi from heredoc\n");

	if (pipe(fd) == -1)
		ft_exit(errno, strerror(errno), NULL);

	pid = fork();
	if (pid == -1)
		ft_exit(errno, strerror(errno), NULL);
	if (pid == 0) //child
	{
		printf("I am in heredoc child\n");
		//here i read from readline, for now i read from file

		//dup2(fd[1], STDOUT_FILENO);
		//i send what i read to fd[1]
		if(write(1, "test\n", 5) == -1)
			ft_exit(errno, strerror(errno), NULL);

		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	else //parent
	{
		printf("I am in heredoc parent\n");
		//dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		//close(fd[1]);
		waitpid(pid, NULL, 0);
		return(fd[0]);
	}
	return(0);
}*/


void ft_open(int type, int fd[2], char *file)
{
	if (type == 2)
	{
		if (fd[0])
			close(fd[0]);
		fd[0] = open(file, O_RDONLY, 0666);
		if (fd[0] == -1)
			ft_exit(errno, file, strerror(errno));
	}
	else if (type == 3)
	{
		if (fd[0])
			close(fd[0]);
		fd[0] = open(file, O_RDONLY, 0666);
		if (fd[0] == -1)
			ft_exit(errno, file, strerror(errno));

		//fd[0] = ft_heredoc(file);
		//if (fd[0] == -1)
		//	ft_exit(errno, file, strerror(errno));
		//printf("HEREDOC RETURNED THIS FD: %d\n", fd[0]);
	}
	else
	{
		if (fd[1])
			close(fd[1]);
		if (type == 4)
			fd[1] = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else
			fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND , 0666);
		if (fd[1] == -1)
			ft_exit(errno, file, strerror(errno));
	}
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
	lst -> command = malloc(sizeof(char *) * (ft_lstcmd_count(token) + 1));
	while (token && token->type != 1)
	{
		if (token->type == 0)
			lst -> command[i++] = ft_strdup(token ->content);
		if (token->type > 1)
		{
			printf("the type is %d\n", token->type);
			ft_open(token->type, lst->fd, token->next->content);
			token = token -> next;
		}
		token = token -> next;
	}
	lst -> command[i] = NULL;
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
	int		cntcmds;

	aux = NULL;
	token = ms->start;
	cntcmds = 0;
	while (token)
	{
		ft_exlstadd_back(&aux, ft_exlstnew(token));
		while (token && token->type != 1)
			token = token->next;
		if (token)
			token = token->next;
		cntcmds++;
	}
	ms->exe = aux;
	ms->cntcmds = cntcmds;
	//TODO FREE TOKEN

	/*token only for printing:*/
	int i = 0;
	while (aux)
	{
		i = 0;
		printf("Command is: ");
		while (aux->command[i])
			printf("%s ", aux->command[i++]);
		printf("\n");
		printf("fd[0]=%d || fd[1]=%d\n",aux->fd[0],aux->fd[1]);
		aux=aux->next;
	}
	printf("We have %d commands.\n", cntcmds);
}
