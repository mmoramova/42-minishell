/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_from_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:36:49 by mmoramov          #+#    #+#             */
/*   Updated: 2023/07/26 11:31:04 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"inc/minishell.h"

char	ft_set_quote(char act_quote, int nestednbr)
{
	char	singlequote;
	char	doublequote;
	char	new_quote;

	if (nestednbr == 0)
		return ('\0');
	singlequote = '\'';
	doublequote = '\"';
	if (act_quote == singlequote)
		new_quote = doublequote;
	else
		new_quote = singlequote;
	return (new_quote);
}

int	ft_wordlen_w_quotes(char const *s, char c)
{
	int		i;
	char	act_quote;
	int		nestednbr;

	act_quote = '\0';
	nestednbr = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && act_quote == '\0')
			return (i);
		if (ft_strchr("\'\"", s[i]))
		{
			if (act_quote != '\0' && s[i] == act_quote)
				act_quote = ft_set_quote(act_quote, nestednbr);
			else
			{
				act_quote = s[i];
				nestednbr += 1;
			}
		}
		i++;
	}
	return (i);
}

int	ft_wordlen_wq_woechar(char const *s, char c)
{
	int		i;
	char	act_quote;
	int		nestednbr;

	act_quote = '\0';
	nestednbr = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && act_quote == '\0')
			return (i);
		if (ft_strchr("\'\"", s[i]) && (s[i - 1] != '\\'))
		{
			if (act_quote != '\0' && s[i] == act_quote)
				act_quote = ft_set_quote(act_quote, nestednbr);
			else
			{
				act_quote = s[i];
				nestednbr += 1;
			}
		}
		i++;
	}
	return (i);
}

int	ft_wordcount_w_quotes(char const *s, char c)
{
	int	nbr;
	int	is_c;

	nbr = 0;
	is_c = 1;
	while (*s)
	{
		if (*s != c && is_c)
		{
			is_c = 0;
			nbr++;
		}
		else if (*s == c)
			is_c = 1;
		s++;
	}
	return (nbr);
}

char	*ft_substr_woechar(char const *s, unsigned int start, size_t len)
{
	unsigned int	len_s;
	unsigned int	i;
	unsigned int	j;
	char			*p;

	len_s = ft_strlen(s);
	i = 0;
	j = 0;
	if (len_s <= start)
		len = 0;
	else if (len_s < start + len)
		len = len_s - start;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (s[i] && len--)
	{
		if (s[start + i + j] == '\\')
			j += 1;
		p[i] = s[start + i + j];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_free_w_quotes(char **s, int len)
{
	while (len--)
		free(s[len]);
	free(s);
	return (NULL);
}

char	**ft_split_w_quotes(char *s, char c, int start)
{
	int		i;
	int		j;
	char	**p;

	(0 || (i = 0) || (j = 0));
	p = malloc(sizeof(char *) * (100 + 1));
	if (!p)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			p[j] = ft_substr_woechar(s, start, ft_wordlen_wq_woechar(&s[i], c));
			if (!p[j])
				return (ft_free_w_quotes(p, j));
			j++;
			i += (ft_wordlen_w_quotes(&s[i], c) - 1);
			start = i + 1;
		}
		else if (s[i] == c)
			start++;
		i++;
	}
	p[j] = NULL;
	return (p);
}


/*int main(void)
{
	char *s  = "wc hhcgh ghfghf \"jkl\" -l | grape \'kjhi\'";

	 char **t;
	 t = ft_split_w_quotes(s, ' ', 0);

	int i;
	i = 0;
	while (t[i])
    {
		printf("%s\n", t[i]);
		i++;
	}
	printf("%s\n", t[2]);
	//gcc ft_split_w_quotes.c libft/libft.a && ./a.out
}*/

