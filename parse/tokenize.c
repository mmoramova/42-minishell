/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:48:00 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/03 18:17:53 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse(t_ms *ms)
{
	if (open_quotes(ms->line, strlen(ms->line)) != 0)
		return (ft_error(ms, 1, "syntax error", "odd number of quotes"));
	ms->start = ft_split_tok(ms, ' ');
	ms->array_env = NULL;
	if (ms->start == NULL)
		return (1);
	return (0);
}

t_tok	*ft_split_tok(t_ms *ms, char c)
{
	t_tok	*lst;
	char	*s;
	char	*r;

	s = ms->line;
	lst = NULL;
	while (*s)
	{
		if (*s != c)
		{
			r = ft_substr(s, 0, ft_wordlen_wq(s, c));
			ft_toklstadd_back(&lst, ft_toklstnew(ms, lst, r));
			if (r)
				free(r);
			s += ft_wordlen_wq(s, c) - 1;
		}
		s++;
	}
	if (ft_tok_checks(ms, lst) == 1)
		lst = NULL;
	return (lst);
}

int	ft_tok_addtype(char *s)
{
	int	i;

	i = 0;
	if (s[i + 1] && ft_strchr("<", s[i]) && s[i] == s[i + 1])
		return (3);
	if (s[i + 1] && ft_strchr(">", s[i]) && s[i] == s[i + 1])
		return (5);
	if (ft_strchr("<", s[i]))
		return (2);
	if (ft_strchr(">", s[i]))
		return (4);
	if (ft_strchr("|", s[i]))
		return (1);
	return (0);
}

int	ft_tok_checks(t_ms *ms, t_tok *lst)
{
	t_tok	*previous;

	if (!lst)
		return (1);
	previous = lst;
	if (lst->type == 1)
	{
		ms->exitstatus = 258;
		ft_error2(258, "syntax error near unexpected token `",
			lst->content, "\'");
		return (1);
	}
	if (lst->type > 1 && !lst->next)
	{
		ms->exitstatus = 258;
		ft_error2(258, "syntax error near unexpected token `", "newline", "\'");
		return (1);
	}
	return (ft_tok_checks2(ms, lst));
}

int	ft_tok_checks2(t_ms *ms, t_tok *lst)
{
	t_tok	*previous;

	previous = lst;
	lst = lst -> next;
	while (lst)
	{
		if ((previous->type > 1 && (lst->type != 0))
			|| (previous->type == 1 && lst->type == 1))
		{
			ms->exitstatus = 258;
			ft_error2(258, "syntax error near unexpected token `",
				lst->content, "\'");
			return (1);
		}
		if ((lst->type > 0 && !lst->next))
		{
			ms->exitstatus = 258;
			ft_error2(258, "syntax error near unexpected token `",
				"newline", "\'");
			return (1);
		}
		previous = lst;
		lst = lst -> next;
	}
	return (0);
}
