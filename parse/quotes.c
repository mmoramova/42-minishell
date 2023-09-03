/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 08:59:51 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/03 18:11:28 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_quotes(char *line, int in)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (line && i <= in)
	{
		if (res == 0 & line[i] == '\"')
			res = 1;
		else if (res == 0 & line[i] == '\'')
			res = 2;
		else if (res == 1 & line[i] == '\"')
			res = 0;
		else if (res == 2 & line[i] == '\'')
			res = 0;
		i++;
	}
	return (res);
}

int	ft_quotes_nbr(char *line)
{
	int	qnbr;
	int	i;

	qnbr = 0;
	i = 0;
	while (line[i])
	{
		if (open_quotes(line, i) != open_quotes(line, i - 1))
			qnbr++;
		i++;
	}
	return (qnbr);
}

char	*ft_q_r(char *s)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s) - ft_quotes_nbr(s) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if ((open_quotes(s, i) != open_quotes(s, i - 1)))
			i++;
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

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
