/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:48:38 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/05 18:16:44 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	int		j;
	int		i;
	char	*p;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return (s1);
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	j = -1;
	while (s2[++j])
		p[i + j] = s2[j];
	p[i + j] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (p);
}

int	ft_fd_isopen(int fd)
{
	if (fd && fd != -1 && fd != -2)
		return (1);
	return (0);
}

int	ft_count_types(t_tok *token, int type)
{
	int	len;

	len = 0;
	while (token)
	{
		if (token->type == type)
			len++;
		token = token -> next;
	}
	return (len);
}

int	openfd(t_ms *ms, int type, int fd[2], char *file)
{
	if (type == 2 || type == 3)
	{
		if (ft_fd_isopen(fd[0]) && fd[0] != ms->heredocfd)
			close(fd[0]);
		if (type == 2)
			fd[0] = open(file, O_RDONLY, 0666);
		else if (type == 3)
			fd[0] = ms->heredocfd;
		if (fd[0] == -1)
			return (ft_error(ms, 1, file, strerror(errno)));
	}
	else
	{
		if (ft_fd_isopen(fd[1]))
			close(fd[1]);
		if (type == 4)
			fd[1] = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (type == 5)
			fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd[1] == -1)
			return (ft_error(ms, 1, file, strerror(errno)));
	}
	return (0);
}
