/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 08:59:51 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/04 13:20:50 by josorteg         ###   ########.fr       */
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
		else if	(res == 2 & line[i] == '\'')
			res = 0;
		i++;
	}
	return (res);
}

int ft_quotes_nbr(char *line)
{
	//function returns how many quotes I have
	int qnbr;
	int i;

	qnbr = 0;
	i = 0;
	while(line[i])
		{
		if (open_quotes(line, i) != open_quotes(line, i-1))
		qnbr++;
		i++;
		}
	return (qnbr);
}

char *ft_quotes_remove(char *s)  //need to repair if the expansion adds one ' / "
{
	char *res;
	int i;
	int j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s) - ft_quotes_nbr(s) + 1));

	if (!res)
		return (NULL);

	while (s[i])
	{
		if ((open_quotes(s, i) != open_quotes(s, i-1)))
		i++;
		else
		res[j++] = s[i++];
	}
	res[j] = '\0';

	return(res);
}
/*
int main(void)
{
	char *s  = "'''";

	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));
	printf("%d\n", open_quotes(s,(int)strlen(s)));

	//gcc quotes.c && ./a.out
}
*/
