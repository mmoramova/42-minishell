/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:20:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/17 23:14:07 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_read(char *file, int fd[2])
{
	char	*line;

	while(42)
	{
		line = readline("> ");
		if (line && strlen(line) > 0)
		{
			if (ft_strncmp(line,file,strlen(file)) == 0)
			{
				free(line);
				exit(0);
			}
			ft_putstr_fd(line, fd[1]);
			ft_putchar_fd('\n', fd[1]);
			free(line);
		}
	}
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

int heredoc_execute(char *file)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit(errno, strerror(errno), NULL);
	pid = fork();
	if (pid == -1)
		ft_exit(errno, strerror(errno), NULL);
	if (pid == 0)
		heredoc_read(file, fd);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return(fd[0]);
}

void ft_open(int type, int fd[2], char *file)
{
	if (type == 2 || type == 3)
	{
		if (fd[0])
			close(fd[0]);
		if (type == 2)
			fd[0] = open(file, O_RDONLY, 0666);
		else
			fd[0] = heredoc_execute(file);
		if (fd[0] == -1)
			ft_exit(errno, file, strerror(errno));
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
