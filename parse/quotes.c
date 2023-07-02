/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 08:59:51 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/02 16:04:27 by josorteg         ###   ########.fr       */
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
