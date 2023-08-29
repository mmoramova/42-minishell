/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:44:22 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/29 19:08:30 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_expand (t_ms *ms, char *s)
{
	int		i;
	char	*aux;
	int		count;
	char	*var;

	i = 0;
	aux = NULL;
	while (s[i] !='$' && s[i] != '\0')
		i++;
	aux = ft_substr(s,0,i);

	while (s[i])
	{
		if (s[i] == '$' && (open_quotes(s, i) != 2))
		{
			i++;
			count = 0;
			while (s[i] && (!ft_strchr("\'\" /$|<>", s[i])))
			{
				count++;
				if (s[i++] == '?')
					break;
			}
			var = ft_substr(s, i - count, count);
			if (var[0] == '?')
				aux = ft_strjoinfree(aux, ft_itoa(ms->exitstatus));
			else if (check_env(ms->env, var) == 0)
				aux = ft_strjoinfree(aux, ft_exp_quotes(get_env_value (ms->env, var),open_quotes(s, i - 1)));
			else if ((s[i] == '\"' || s[i] == '\'') && open_quotes(s, i - 1) == 0)
				aux = ft_strjoinfree(aux, "");
			else if (var[0] == '\0')
				aux = ft_strjoin(aux, "$");
			else
				aux = ft_strjoinfree(aux, "");
		}
		count = 0;
		while ((s[i] !='$' || (s[i] == '$' && (open_quotes(s, i) == 2))) && s[i] != '\0')
		{
			count++;
			i++;
		}
		aux = ft_strjoinfree(aux, ft_substr(s, i - count, count));
	}
	ms->exitstatus = 0;
	return (aux);
}

t_tok	*ft_expand_token(char *str)
{
	t_tok	*lst;
	t_tok	*tmp;
	char	c;

	c = ' ';
	lst = NULL;
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str != c)
		{
			tmp = (t_tok *) malloc(sizeof(t_tok));
			if (!tmp)
				return (NULL);
			tmp -> content = ft_q_r(ft_substr(str, 0, ft_wordlen_wq(str, c)));
			tmp -> previous = ft_toklstlast(lst);
			tmp -> type = 0;
			tmp -> next = NULL;
			ft_toklstadd_back(&lst, tmp);
			str += ft_wordlen_wq(str, c) - 1;
		}
		str++;
	}
	return (lst);
}
