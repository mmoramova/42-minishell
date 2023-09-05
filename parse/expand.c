/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:44:22 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/05 18:55:22 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(t_ms *ms, char *s)
{
	int		i;
	char	*aux;
	int		count;
	char	*var;

	i = 0;
	aux = ft_start_expand(s, i);
	i = ft_strlen(aux);
	while (s[i])
	{
		if (s[i] == '$' && (open_quotes(s, i) != 2))
		{
			i++;
			var = ft_var_expand(s, i);
			i = i + ft_strlen(var);
			aux = ft_strjoinfree(aux, ft_sub_expand(ms, var, i, s));
			free(var);
		}
		count = 0;
		while ((s[i] != '$' || (s[i] == '$'
					&& (open_quotes(s, i) == 2))) && s[i] != '\0')
			(1 && (count = count + 1) && (i = i + 1));
		aux = ft_strjoinfree(aux, ft_substr(s, i - count, count));
	}
	return (aux);
}

t_tok	*ft_expand_token(char *str)
{
	t_tok	*lst;
	t_tok	*tmp;
	char	*mec;

	lst = NULL;
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str != ' ')
		{
			tmp = (t_tok *) malloc(sizeof(t_tok));
			if (!tmp)
				return (NULL);
			mec = ft_substr(str, 0, ft_wordlen_wq(str, ' '));
			tmp -> content = ft_q_r(mec);
			free(mec);
			(0 || (tmp -> previous = ft_toklstlast(lst)) || (tmp -> type = 0));
			tmp -> next = NULL;
			ft_toklstadd_back(&lst, tmp);
			str += ft_wordlen_wq(str, ' ') - 1;
		}
		str++;
	}
	return (lst);
}
