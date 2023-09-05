/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:00:23 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/05 21:12:43 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_one_space(char *str)
{
	int	space_count;
	int	i;

	i = 0;
	space_count = 0;
	if (!str)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && (i == 0 || str[i - 1] != ' '))
			space_count++;
		i++;
	}
	return ((int)ft_strlen(str) + space_count + 1);
}

char	*ft_exp_quotes(char *str, int quot)
{
	int		i;
	char	*result;
	int		j;

	(0 || (i = 0) || (j = 0));
	result = NULL;
	if (quot == 1)
		result = ft_strdup(str);
	else
	{
		result = malloc (ft_one_space(str) * sizeof(char));
		if (!result || !str)
			return (NULL);
		while (str[i])
		{
			if (str[i] == ' ' && (i == 0 || str[i - 1] != ' '))
				result[j++] = ' ';
			if (str[i] != ' ')
				result[j++] = str[i];
			i++;
		}
		result[j] = '\0';
	}
	free(str);
	return (result);
}

char	*ft_start_expand(char *s, int i)
{
	while (s[i] != '$' && s[i] != '\0')
		i++;
	return (ft_substr(s, 0, i));
}

char	*ft_var_expand(char *s, int i)
{
	int	count;

	count = 0;
	if (s[i] == '?')
	{
		count = 1;
		i++;
	}
	else
	{
		while (s[i] && (!ft_strchr("\'\" /$|<>?", s[i])))
		{
			count++;
			i++;
		}
	}
	return (ft_substr(s, i - count, count));
}

char	*ft_sub_expand(t_ms *ms, char *var, int i, char *str)
{
	if (var[0] == '?')
		return (ft_itoa(ms->exitstatus));
	else if (check_env(ms->env, var) == 0
		&& get_env_value (ms->env, var) != NULL)
		return (ft_exp_quotes(ft_strdup(get_env_value (ms->env, var)),
				open_quotes(str, i - 1)));
	else if ((!str || str[i] == '\"' || str[i] == '\'')
		&& open_quotes(str, i - 1) == 0)
		return (ft_strdup(""));
	else if (var[0] == '\0')
		return (ft_strdup("$"));
	else
	{
		ms->exitstatus = 0;
		return (ft_strdup(""));
	}
}
