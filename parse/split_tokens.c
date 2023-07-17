/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:48:00 by mmoramov          #+#    #+#             */
/*   Updated: 2023/07/17 16:26:39 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// needs strjoin with free, tomorrow as the first thing!!!!


// char	*ft_strjoinfree(char *s1, char const *s2)
// {
// 	int		j;
// 	int		i;
// 	char	*p;

// 	if (!s1)
// 		return((char *)s2);
// 	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!p)
// 		return (NULL);
// 	i = -1;
// 	while (s1[++i])
// 		p[i] = s1[i];
// 	j = -1;
// 	while (s2[++j])
// 		p[i + j] = s2[j];
// 	p[i + j] = '\0';
// 	free(s1);
// 	s1 = NULL;
// 	return (p);
// }

// char	*ft_sub_expand(char *res,char *s,char *var, char *val);
// {

// }

// char	*ft_expand (t_ms *ms, char *s)
// {
// 	int	i;
// 	int count;
// 	char	*var;
// 	char	*val;
// 	char	*res;
// 	int		start;

// 	i = 0;
// 	count = 0;
// 	res = NULL;
// 	start = 0;

// 	while (s[i])
// 	{
// 		if (s[i] == '$' && (open_quotes(s,i) != 2))
// 		{
// 			i++;
// 			while (!ft_strchr("\'\" $",s[i++]) && s[i])
// 				count++;
// 			var = ft_substr(s ,i - count - 1 ,count + 1);
// 			if (check_env(ms->env, var) == 0)
// 			{
// 				val = get_env_value (ms->env,var);
// 				printf("\nvariable:%s valor:%s\n\n",var, val);
// 				res = malloc(ft_strlen(s) - ft_strlen(var) + ft_strlen(val));
// 				ft_sub_expand(res,s,var,val);
// 			}
// 			start = i;
// 		}
// 		i++;
// 	}

// 	if (i - start > 0)
// 	{
// 		printf("Calling substring 2 with %d, %d\n", start , i -start);
// 		res =ft_strjoinfree(res,ft_substr(s, start, i - start));
// 		//res =ft_substr(s, start, i - start);
// 	}
// 	return(res);
// }
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


int ft_tok_addtype(char *s)
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


t_tok	*ft_toklstnew(t_ms *ms, char *content)
{
	t_tok	*lst;

	lst = (t_tok *) malloc(sizeof(t_tok));
	if (!lst)
		return (NULL);

	if (ft_strchrn (content,'$') == - 1)
		lst->content = content;
	else
	{
		printf("---before expand:%s\n",content);
		lst -> content = ft_quotes_remove(ft_expand(ms, content));
		printf("---after expand + quotes:%s\n",lst -> content);
	}
	lst -> next = NULL;
	lst -> previous = NULL;
	lst -> type = ft_tok_addtype(content);
	return (lst);
}

t_tok	*ft_toklstlast(t_tok *lst)
{
	while (lst && lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_toklstadd_back(t_tok **lst, t_tok *new)
{
	if (*lst)
		ft_toklstlast(*lst)-> next = new;
	else
		*lst = new;
}

void	ft_toklstadd_previous(t_tok *lst)
{
	t_tok	*previous;

	previous = lst;
	lst = lst -> next;
	while (lst)
	{
		lst -> previous = previous;
		previous = lst;
		lst = lst -> next;
	}
}

void	ft_tok_checks(t_tok *lst)
{
	t_tok	*previous;

	previous = lst;
	if (lst->type == 1)
	{
		exit(1);
		//TODO ERROR PIPE
	}
	lst = lst -> next;

	while (lst)
	{
		//ERRORS IN TOKENS
		if ((previous->type > 1 && (lst->type != 0))
			|| (previous->type == 1 && lst->type == 1)
			|| (lst->type > 0 && !lst->next))
		{
			//TODO ERROR
			exit(1);
		}
		previous = lst;
		lst = lst -> next;
	}

}

t_tok	*ft_split_tok(t_ms *ms, char c)
{
	t_tok	*lst;
	char	*s;

	s = ms->line;
	lst = NULL;
	while (*s)
	{
		if (*s != c)
		{
			//printf("WORDLEN IS: %d\n", ft_wordlen_wq(s, c));
			ft_toklstadd_back(&lst, ft_toklstnew(ms, ft_substr(s, 0, ft_wordlen_wq(s, c))));
			s += ft_wordlen_wq(s, c) - 1;

		}
		s++;
	}
	ft_toklstadd_previous(lst);
	ft_tok_checks(lst);

	return (lst);
}


/*
int main(void)
{
	char *s  = "'z\"e\"ro' one \"two twoandhalf\" 'three four'";

	 t_tok *lst;
	 lst = ft_split_tok(s, ' ');


	while (lst)
	{
		printf("%s\n", lst->content);
		lst=lst->next;
	}

	printf("\n-------------previous:\n");
	lst = ft_split_tok(s, ' ');
	lst=lst->next;
	while (lst)
	{
		printf("%s\n", lst->previous->content);
		lst=lst->next;
	}

	//gcc split_tokens.c libs/libft/libft.a && ./a.out
}
*/


